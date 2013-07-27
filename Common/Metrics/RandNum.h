/////////////////////////////////////////////////////////////////////////////////
// This class consists of a collection of random number generators. The majority
// of the methods are directly from Numerical Recipes in C, Second Edition, 
// by Press et. al. pp. 295-296. 
//
// This class is implemented as a singleton as described by Gamma et. al. in 
// Design Patterns, pp. 127-132.
///////////////////////////////////////////////////////////////////////////////


#ifndef RANDNUM_H
#define RANDNUM_H

class RandNum
{
public: 
    static RandNum*  instance();
    
    static void initializeSeed(long sd);
    // A call to this function sets the random number seed. It must be called
    // before any of the random number generator methods are called.

    static long getSeed(long sd) { return idum;}
    // A call to this function returns the random number seed.
    
    static double uniform();
    // This function is adapted from Numerical Recipes in C, Second Edition, 
    // by Press et. al. p. 280.
    
    // "Minimal" random number generator of Park and Miller with Bays-Durham shuffle 
    // and added safeguards. Returns a uniform random deviate between 0.0 and 1.0 
    // (exclusive of the endpoint values). RNMX should approximate the largest floating 
    // point value that is less than 1.

    static double uniformInRange(double lower, double upper);

/*********************************************************
    NOT RESTART CAPABLE
    // This function returns a uniform number in the range between lower and upper
    
    static double binomial(double p, int n);
**********************************************************/
    // This function is adapted from Numerical Recipes in C, Second Edition, 
    // by Press et. al. pp. 295-296.
    
    // Returns as a floating point number an integer value that is a random 
    // deviate drawn from a binomial distribution of n trials each of probability pp. 
    // using uniform as a source of uniform deviates.
    
    static double exponential();
    // This function is adapted from Numerical Recipes in C, Second Edition, 
    // by Press et. al. pp. 287.
   
    // Returns an exponentially distributed, positive, random deviate of unit mean,
    // using uniform() and the source of uniform deviates.
    
    static double gamma(int ia);
    
    // This function is adapted from Numerical Recipes in C, Second Edition, 
    // by Press et. al. pp. 292-293.
    
    // Returns a deviate distributed as a gamma distribution of integer order ia, 
    // i.e., a waiting time to the iath event in a Poisson process of unit mean, 
    // using uniform() as the source of uniform deviates.
    
    static int bit();
    // This function is adapted from Numerical Recipes in C, Second Edition, 
    // by Press et. al. pp. 297.
    
    // Returns as an integer a random bit, based on the 18 low significance bits in bitSeed.
    
    static double gaussian();
    // This function is adapted from Numerical Recipes in C, Second Edition, 
    // by Press et. al. pp. 289-290.
    
    // Returns a normally distributed deviate with zero mean and unit variance, 
    // using uniform() as the source of uniform deviates.
    
    static double gaussian(double mean, double standardDevation);

/************************************************************
    NOT RESTART CAPABLE

    // Returns a normally distributed deviate with a mean of mean and 
    // variance of standardDeviation squared, using uniform() as the 
    // source of uniform deviates.
    
    static double poisson(double xm);
**************************************************************/

    // This function is adapted from Numerical Recipes in C, Second Edition, 
    // by Press et. al. pp. 294-295.
    
    // Returns as a floating point number an integer value that is a random 
    // deviate drawn from a Poisson distribution of mean xm, using uniform()
    // as the source.
    
    static double round(double number);
    // This function is adapted from the PSF/JDSS algorithm document, 1997.
    // This function returns an integer which is equal to number with random rounding.
    
    static int sign();
    // RandNumly returns either a +1 or a -1.
    
  protected:
    RandNum();
  private:

/********************************
    NOT RESTART CAPABLE 
    static double gammln(double xx);
*********************************/

    // This function is adapted from Numerical Recipes in C, Second Edition, 
    // by Press et. al. pp. 214.
    
    // Returns the value of ln(gamma(xx)) for xx > 0
    
    static double logOf(double x);
    // Wrapper function around log() function to perform exception handling.
    // Returns the natural logarithm of x.
    
    static double sqrtOf(double x);
    // Wrapper function around sqrt() function to perform exception handling.
    // Returns the square root of x.
    
    static double tanOf(double x);
    // Wrapper function around tan() function to perform exception handling.
    // Returns the tangent of x measured in radians.
    
    static double floorOf(double x);
    // Wrapper function around floor() function to perform exception handling.
    // Returns the largest integral value not greater than x.
    
    static double expOf(double x);
    // Wrapper function around exp() function to perform exception handling.
    // Returns the exponential of x, defined as e**x.
    
    static double ceilOf(double x);
    // Wrapper function around ceil() function to perform exception handling.
    // Returns the smallest integral value not smaller than x.
    
    static double fmodOf(double x, double y);
    // Wrapper function around fmod() function to perform exception handling.
    // Returns the remainder of the division of x by y.
    
    static RandNum* instance_;
    static long bitSeed;
    static long idum;
    static long iset_;
    static double gset_;
    static const double PI;
    static const long IA;
    static const long IM;
    static const double AM;
    static const long IQ;
    static const long IR;
    static const int NTAB;
    static const long NDIV;
    static const double EPS;
    static const double RNMX;
//  static long iy;
//  static const long iv[NTAB]; 
//  static long iv[32]; 
    static const int IB1;
    static const int IB2;
    static const int IB5;
    static const long IB18;  


};

#endif // !defined(RANDNUM_H)
