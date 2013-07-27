#include "RandNum.h"


#include <cmath>

RandNum* RandNum::instance_ = 0;
long RandNum::idum = 0;
long RandNum::iset_ = 0;
double RandNum::gset_ = 0.0;
long RandNum::bitSeed = 0;
const double RandNum::PI = 3.141592654;
const long RandNum::IA = 16807;
const long RandNum::IM = 2147483647;
const double RandNum::AM = (1.0/IM);
const long RandNum::IQ = 127773;
const long RandNum::IR = 2836;
const int RandNum::NTAB = 32;
const long RandNum::NDIV = (1+(IM-1)/NTAB);
const double RandNum::EPS = 1.2e-7;
const double RandNum::RNMX = (1.0-EPS);
//long RandNum::iy = 0L;
//long RandNum::iv[32];  // the 32 is due to NTAB

const int RandNum::IB1 = 1;
const int RandNum::IB2 = 2;
const int RandNum::IB5 = 16;
const long RandNum::IB18 = 131072;

RandNum::RandNum()
{
}

void RandNum::initializeSeed(long sd)
{	
    // A call to this function sets the random number seed. It must be called
    // before any of the random number generator methods are called.
    
    // set the seed for uniform()
    idum = sd;
    
    // set the seed for bit()
    bitSeed = sd;	
    bit();
}

RandNum* RandNum::instance()
{
    if (instance_ == 0) {
        instance_ = new RandNum;
    }
    return instance_;
}

double RandNum::uniform()
{
    // Park and Miller's Minimal Standard Random Number Generator
    // Adapted for C++ from Numerical Recipes in C, 2nd edition
    long    ia_ = 16807;
    long    im_ = 2147483647;
    double  am_ = 1.0 / im_;
    long    iq_ = 127773;
    long    ir_ = 2836;
    long    mask_ = 123459876;
    
    idum ^= mask_;
    long k = idum / iq_;
    idum = ia_ * (idum - k * iq_) - ir_ * k;
    if (idum < 0) {
    idum += im_;
    }
    double ans = am_ * idum;
    idum ^= mask_;

#ifdef INTEGRATE_DEBUG
    std::cout << "RandNum::uniform(): " << ans << std::endl;
#endif
    
    return ans;

}

double RandNum::uniformInRange(double lower, double upper)
{
    double randomNumber = uniform();

    double diff = upper-lower;
    diff = diff * randomNumber;
    
    return lower + diff;
}

/**********************************************
    
    THIS CODE IS CURRENTLY UNUSED AND NOT SUPPORTED BY RESTART
    DUE TO THE LOCAL STATIC VARIABLES.  FIX IT BY MAKING LOCAL
    STATICS INTO MEMBER DATA.

double RandNum::binomial(double pp, int n)
{    
    // This function is adapted from Numerical Recipes in C, Second Edition, 
    // by Press et. al. pp. 295-296.
    
    // Returns as a floating point number an integer value that is a random 
    // deviate drawn from a binomial distribution of n trials each of probability pp. 
    // using uniform as a source of uniform deviates.
    
    int j;
    static int nold=(-1);
    double am,em,g,angle,p,bnl,sq,t,y;
    static double pold=(-1.0),pc,plog,pclog,en,oldg;

    p=(pp <= 0.5 ? pp : 1.0-pp);
    am=n*p;
    if (n < 25) {
        bnl=0.0;
        for (j=1;j<=n;j++)
            if (uniform() < p) ++bnl;
    } else if (am < 1.0) {
        g=exp(-am);
        t=1.0;
        for (j=0;j<=n;j++) {
            t *= uniform();
            if (t < g) break;
        }
        bnl=(j <= n ? j : n);
    } else {
        if (n != nold) {
            en=n;
            oldg=gammln(en+1.0);
            nold=n;
        } if (p != pold) {
            pc=1.0-p;
            plog=log(p);
            pclog=log(pc);
            pold=p;
        }
        sq=sqrt(2.0*am*pc);
        do {
            do {
                angle=PI*uniform();
                y=tan(angle);
                em=sq*y+am;
            } while (em < 0.0 || em >= (en+1.0));
            em=floor(em);
            t=1.2*sq*(1.0+y*y)*exp(oldg-gammln(em+1.0)
                -gammln(en-em+1.0)+em*plog+(en-em)*pclog);
        } while (uniform() > t);
        bnl=em;
    }
    if (p != pp) bnl=n-bnl;
    return bnl;
}
************************************************************/

double RandNum::exponential()
{
    // This function is adapted from Numerical Recipes in C, Second Edition, 
    // by Press et. al. pp. 287.
    
    // Returns an exponentially distributed, positive, random deviate of unit mean,
    // using uniform() and the source of uniform deviates.
    
    
    double dum;
    
    do
        dum = uniform();
    while (dum == 0.0);
    
    return -log(dum);
}

double RandNum::gamma(int ia)
{
    // This function is adapted from Numerical Recipes in C, Second Edition, 
    // by Press et. al. pp. 292-293.
    
    // Returns a deviate distributed as a gamma distribution of integer order ia, 
    // i.e., a waiting time to the iath event in a Poisson process of unit mean, 
    // using uniform() as the source of uniform deviates.
    
    int j;
    double am,e,s,v1,v2,x,y;
    
    if (ia < 1) return 0; // error flag
    if (ia < 6) {
        x=1.0;
        for (j=1;j<=ia;j++) x *= uniform();
        x = -log(x);
    } else {
        do {
            do {
                do {
                    v1=2.0*uniform()-1.0;
                    v2=2.0*uniform()-1.0;
                } while (v1*v1+v2*v2 > 1.0);
                y=v2/v1;
                am=ia-1;
                s=sqrt(2.0*am+1.0);
                x=s*y+am;
            } while (x <= 0.0);
            e=(1.0+y*y)*exp(am*log(x/am)-s*y);
        } while (uniform() > e);
    }
    return x;
}

double RandNum::gaussian()
{
    // This function is adapted from Numerical Recipes in C, Second Edition, 
    // by Press et. al. pp. 289-290.
    
    // Returns a normally distributed deviate with zero mean and unit variance, 
    // using uniform() as the source of uniform deviates.
    
    double fac,rsq,v1,v2;
    double retVal;
    
    if  (iset_ == 0) {
        do {
            v1=2.0*uniform()-1.0;
            v2=2.0*uniform()-1.0;
            rsq=v1*v1+v2*v2;
        } while (rsq >= 1.0 || rsq == 0.0);
        fac=sqrt(-2.0*log(rsq)/rsq);
        gset_=v1*fac;
        iset_=1;
        retVal = v2*fac;
    } else {
        iset_=0;
        retVal = gset_;
    }

#ifdef INTEGRATE_DEBUG
    std::cout << "RandNum::gaussian() :"  << retVal << std::endl;
#endif

    return retVal;
}

double RandNum::gaussian(double mean, double standardDeviation)
{
    // Returns a normally distributed deviate with a mean of mean and 
    // variance of standardDeviation squared, using uniform() as the 
    // source of uniform deviates.

    double retVal = mean + standardDeviation * gaussian();

#ifdef INTEGRATE_DEBUG
    std::cout << "RandNum::gaussian(double mean, double standardDeviation) :"  << retVal << std::endl;
#endif
    
    return retVal;
}

/*********************************************

    GET RID OF LOCAL STATIC VARIABLES TO MAKE RESTART CAPABLE.

double RandNum::poisson(double xm)
{
    // This function is adapted from Numerical Recipes in C, Second Edition, 
    // by Press et. al. pp. 294-295.
    
    // Returns as a floating point number an integer value that is a random 
    // deviate drawn from a Poisson distribution of mean xm, using uniform()
    // as the source of uniform deviates.
    
    static double sq,alxm,g,oldm=(-1.0);
    double em,t,y;
    
    if (xm < 12.0) {
        if (xm != oldm) {
            oldm=xm;
            g=exp(-xm);
        }
        em = -1;
        t=1.0;
        do {
            ++em;
            t *= uniform();
        } while (t > g);
    } else {
        if (xm != oldm) {
            oldm=xm;
            sq=sqrt(2.0*xm);
            alxm=log(xm);
            g=xm*alxm-gammln(xm+1.0);
        }
        do {
            do {
                y=tan(PI*uniform());
                em=sq*y+xm;
            } while (em < 0.0);
            em=floor(em);
            t=0.9*(1.0+y*y)*exp(em*alxm-gammln(em+1.0)-g);
        } while (uniform() > t);
    }
    return em;
}
*********************************************************/

int RandNum::bit()
{
    // This function is adapted from Numerical Recipes in C, Second Edition, 
    // by Press et. al. pp. 297.
    
    // Returns as an integer a random bit, based on the 18 low significance bits in bitSeed.
    
    unsigned long newbit;
    
    newbit = (bitSeed & IB18) >> 17
        ^ (bitSeed & IB5) >> 4
        ^ (bitSeed & IB2) >> 1
        ^ (bitSeed & IB1);
    bitSeed=(bitSeed << 1) | newbit;
    return (int) newbit;
}

int RandNum::sign()
{
    // RandNumly returns either a +1 or a -1.
    
    return 2 * bit() - 1;
}

double RandNum::round(double x)
{
    // This function returns an integer which is equal to number with random rounding
    return (( uniform() > fmod((x), 1.0) ) ? floor((x)) : ceil((x)));
}

/*************************************************

    GET RID OF LOCAL STATICS TO MAKE RESTART CAPABLE.

double RandNum::gammln(double xx)
{
    // This function is adapted from Numerical Recipes in C, Second Edition, 
    // by Press et. al. pp. 214.
    
    // Returns the value of ln(gamma(xx)) for xx > 0.
    
    double x,y,tmp,ser;
    static double cof[6]={76.18009172947146,-86.50532032941677,
                          24.01409824083091,-1.231739572450155,
                          0.1208650973866179e-2,-0.5395239384953e-5};
    int j;
    
    y=x=xx;
    tmp=x+5.5;
    tmp -= (x+0.5)*log(tmp);
    ser=1.000000000190015;
    for (j=0;j<=5;j++) ser += cof[j]/++y;
    return -tmp+log(2.5066282746310005*ser/x);
}
*******************************************************/

