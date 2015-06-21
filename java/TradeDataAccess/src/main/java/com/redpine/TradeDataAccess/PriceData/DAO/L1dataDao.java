package com.redpine.TradeDataAccess.PriceData.DAO;

import com.redpine.TradeDataAccess.DAO.CommonDao;
import com.redpine.TradeDataAccess.PriceData.model.L1data;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;


/**
 * DAO for class L1data.
 * @see com.redpine.TradeDataAccess.PriceData.model.L1data
 * @author dbrown
 */
public class L1dataDao extends CommonDao {

	private static final Logger log = LoggerFactory.getLogger(L1dataDao.class);

	public L1dataDao() {
	}

	public void persist(L1data entity) {
		getCurrentSession().save(entity);
	}

//	public void update(L1data entity) {
//		getCurrentSession().update(entity);
//	}

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
