package com.redpine.TradeDataAccess.Data;

import com.redpine.TradeDataAccess.Data.Timesalesdata;

import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;


/**
 * Home object for domain model class Timesalesdata.
 * @see com.redpine.TradeDataAccess.Data.Timesalesdata
 * @author Hibernate Tools
 */
//@Stateless
public class TimesalesdataDao {

	private static final Logger log = LoggerFactory.getLogger(TimesalesdataDao.class);

	@PersistenceContext
	private EntityManager entityManager;

	public void persist(Timesalesdata transientInstance) {
		log.debug("persisting Timesalesdata instance");
		try {
			entityManager.persist(transientInstance);
			log.debug("persist successful");
		} catch (RuntimeException re) {
			log.error("persist failed", re);
			throw re;
		}
	}

	public void remove(Timesalesdata persistentInstance) {
		log.debug("removing Timesalesdata instance");
		try {
			entityManager.remove(persistentInstance);
			log.debug("remove successful");
		} catch (RuntimeException re) {
			log.error("remove failed", re);
			throw re;
		}
	}

	public Timesalesdata merge(Timesalesdata detachedInstance) {
		log.debug("merging Timesalesdata instance");
		try {
			Timesalesdata result = entityManager.merge(detachedInstance);
			log.debug("merge successful");
			return result;
		} catch (RuntimeException re) {
			log.error("merge failed", re);
			throw re;
		}
	}

	public Timesalesdata findById(Integer id) {
		log.debug("getting Timesalesdata instance with id: " + id);
		try {
			Timesalesdata instance = entityManager
					.find(Timesalesdata.class, id);
			log.debug("get successful");
			return instance;
		} catch (RuntimeException re) {
			log.error("get failed", re);
			throw re;
		}
	}
}
