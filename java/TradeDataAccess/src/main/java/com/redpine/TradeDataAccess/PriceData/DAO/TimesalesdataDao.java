package com.redpine.TradeDataAccess.PriceData.DAO;

import com.redpine.TradeDataAccess.PriceData.model.Timesalesdata;
import com.redpine.TradeDataAccess.Util.HibernateUtil;

import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;


/**
 * Home object for domain model class Timesalesdata.
 * @see com.redpine.TradeDataAccess.PriceData.model.Timesalesdata
 * @author Hibernate Tools
 */
//@Stateless
public class TimesalesdataDao {

	private static final Logger log = LoggerFactory.getLogger(TimesalesdataDao.class);

	  private Session currentSession;
      private Transaction currentTransaction;

	      public TimesalesdataDao() {
	      }

	      public Session openCurrentSession() {
	          currentSession = getSessionFactory().openSession();
	          return currentSession;
	      }

	      public Session openCurrentSessionwithTransaction() {
	          currentSession = getSessionFactory().openSession();
	          currentTransaction = currentSession.beginTransaction();
	          return currentSession;
	      }
	       

	      public void closeCurrentSession() {
	          currentSession.close();
	      }
	
	       
	      public void closeCurrentSessionwithTransaction() {
	          currentTransaction.commit();
	          currentSession.close();
	      }
	       

	      private static SessionFactory getSessionFactory() {
	          return HibernateUtil.getSessionFactory();
	      }


	      public Session getCurrentSession() {

	          return currentSession;

	      }

	   
	      public void setCurrentSession(Session currentSession) {
	          this.currentSession = currentSession;
	      }

	   
	      public Transaction getCurrentTransaction() {
	          return currentTransaction;
	      }

   
	      public void setCurrentTransaction(Transaction currentTransaction) {
	          this.currentTransaction = currentTransaction;
	      }
	   
	      public void persist(Timesalesdata entity) {
	    	  getCurrentSession().save(entity);
	      }
	   
//	      public void update(Timesalesdata entity) {
//	          getCurrentSession().update(entity);
//	      }

	      public Timesalesdata findById(Integer id) {
	    	  Timesalesdata tsData = null;
	    	  try {
	    		  tsData = (Timesalesdata) getCurrentSession().get(Timesalesdata.class, id);
	    	  } catch (RuntimeException re) {
				log.error("get failed", re);
				throw re;
	    	  }
	          return tsData;
	      }
	   
	      public void delete(Timesalesdata entity) {
	          getCurrentSession().delete(entity);
	      }
	   
//
//	      @SuppressWarnings("unchecked")
//	      public List<Timesalesdata> findAll() {
//	          List<Timesalesdata> tsData = (List<Timesalesdata>) getCurrentSession().createQuery("from Timesalesdata").list();
//	          return tsData;
//	      }

}
