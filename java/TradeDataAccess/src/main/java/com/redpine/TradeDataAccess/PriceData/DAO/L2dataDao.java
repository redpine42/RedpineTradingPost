package com.redpine.TradeDataAccess.PriceData.DAO;

import com.redpine.TradeDataAccess.DAO.CommonDao;
import com.redpine.TradeDataAccess.PriceData.model.L2data;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * DAO for class L2data.
 * 
 * @see com.redpine.TradeDataAccess.PriceData.model.L2data
 * @author dbrown
 */
public class L2dataDao extends CommonDao {

	private static final Logger log = LoggerFactory.getLogger(L2dataDao.class);

	public L2dataDao() {
	}

	public void persist(L2data entity) {
		getCurrentSession().save(entity);
	}

//	public void update(L2data entity) {
//		getCurrentSession().update(entity);
//	}

	public L2data findById(Integer id) {
		L2data tsData = null;
		try {
			tsData = (L2data) getCurrentSession().get(L2data.class, id);
		} catch (RuntimeException re) {
			log.error("get failed", re);
			throw re;
		}
		return tsData;
	}

	public void delete(L2data entity) {
		getCurrentSession().delete(entity);
	}

	//
	// @SuppressWarnings("unchecked")
	// public List<L2data> findAll() {
	// List<L2data> tsData = (List<L2data>)
	// getCurrentSession().createQuery("from L2data").list();
	// return tsData;
	// }

}
