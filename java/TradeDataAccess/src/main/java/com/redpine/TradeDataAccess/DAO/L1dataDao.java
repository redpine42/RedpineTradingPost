package com.redpine.TradeDataAccess.DAO;

import com.redpine.TradeDataAccess.model.L1data;

import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.boot.registry.StandardServiceRegistryBuilder;
import org.hibernate.cfg.Configuration;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;


/**
 * DAO for class L1data.
 * @see com.redpine.TradeDataAccess.model.L1data
 * @author dbrown
 */
public class L1dataDao {

	private static final Logger log = LoggerFactory.getLogger(L1dataDao.class);

	private Session currentSession;
	private Transaction currentTransaction;

	public L1dataDao() {
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

		Configuration configuration = new Configuration().configure();
		StandardServiceRegistryBuilder builder = new StandardServiceRegistryBuilder()
				.applySettings(configuration.getProperties());
		SessionFactory sessionFactory = configuration
				.buildSessionFactory(builder.build());
		return sessionFactory;
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

	public void persist(L1data entity) {
		getCurrentSession().save(entity);
	}

	public void update(L1data entity) {
		getCurrentSession().update(entity);
	}

	public L1data findById(Integer id) {
		L1data tsData = null;
		try {
			tsData = (L1data) getCurrentSession().get(L1data.class, id);
		} catch (RuntimeException re) {
			log.error("get failed", re);
			throw re;
		}
		return tsData;
	}

	public void delete(L1data entity) {
		getCurrentSession().delete(entity);
	}

	//
	// @SuppressWarnings("unchecked")
	// public List<L1data> findAll() {
	// List<L1data> tsData = (List<L1data>)
	// getCurrentSession().createQuery("from L1data").list();
	// return tsData;
	// }
}
