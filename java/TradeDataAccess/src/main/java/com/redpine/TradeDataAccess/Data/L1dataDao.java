package com.redpine.TradeDataAccess.Data;

import com.redpine.TradeDataAccess.Data.L1data;

import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;


/**
 * DAO for class L1data.
 * @see com.redpine.TradeDataAccess.Data.L1data
 * @author dbrown
 */
public class L1dataDao {

	private static final Logger log = LoggerFactory.getLogger(L1dataDao.class);

	@PersistenceContext
	private EntityManager entityManager;

	public void persist(L1data transientInstance) {
		log.debug("persisting L1data instance");
		try {
			entityManager.persist(transientInstance);
			log.debug("persist successful");
		} catch (RuntimeException re) {
			log.error("persist failed", re);
			throw re;
		}
	}

	public void remove(L1data persistentInstance) {
		log.debug("removing L1data instance");
		try {
			entityManager.remove(persistentInstance);
			log.debug("remove successful");
		} catch (RuntimeException re) {
			log.error("remove failed", re);
			throw re;
		}
	}

	public L1data merge(L1data detachedInstance) {
		log.debug("merging L1data instance");
		try {
			L1data result = entityManager.merge(detachedInstance);
			log.debug("merge successful");
			return result;
		} catch (RuntimeException re) {
			log.error("merge failed", re);
			throw re;
		}
	}

	public L1data findById(long id) {
		log.debug("getting L1data instance with id: " + id);
		try {
			L1data instance = entityManager.find(L1data.class, id);
			log.debug("get successful");
			return instance;
		} catch (RuntimeException re) {
			log.error("get failed", re);
			throw re;
		}
	}
}
