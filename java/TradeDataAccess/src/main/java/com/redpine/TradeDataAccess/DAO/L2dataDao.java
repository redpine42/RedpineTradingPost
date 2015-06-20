package com.redpine.TradeDataAccess.DAO;

import com.redpine.TradeDataAccess.model.L2data;

import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;


/**
 * DAO for class L2data.
 * @see com.redpine.TradeDataAccess.model.L2data
 * @author dbrown
 */
public class L2dataDao {

	private static final Logger log = LoggerFactory.getLogger(L2dataDao.class);

	@PersistenceContext
	private EntityManager entityManager;

	public void persist(L2data transientInstance) {
		log.debug("persisting L2data instance");
		try {
			entityManager.persist(transientInstance);
			log.debug("persist successful");
		} catch (RuntimeException re) {
			log.error("persist failed", re);
			throw re;
		}
	}

	public void remove(L2data persistentInstance) {
		log.debug("removing L2data instance");
		try {
			entityManager.remove(persistentInstance);
			log.debug("remove successful");
		} catch (RuntimeException re) {
			log.error("remove failed", re);
			throw re;
		}
	}

	public L2data merge(L2data detachedInstance) {
		log.debug("merging L2data instance");
		try {
			L2data result = entityManager.merge(detachedInstance);
			log.debug("merge successful");
			return result;
		} catch (RuntimeException re) {
			log.error("merge failed", re);
			throw re;
		}
	}

	public L2data findById(Integer id) {
		log.debug("getting L2data instance with id: " + id);
		try {
			L2data instance = entityManager.find(L2data.class, id);
			log.debug("get successful");
			return instance;
		} catch (RuntimeException re) {
			log.error("get failed", re);
			throw re;
		}
	}
}
