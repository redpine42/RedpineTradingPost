package com.redpine.TradeDataAccess.AccountData.DAO;

import java.util.List;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.redpine.TradeDataAccess.AccountData.model.OpenOrderData;
import com.redpine.TradeDataAccess.DAO.CommonDao;


public class OpenOrderDataDao extends CommonDao {
	private static final Logger log = LoggerFactory
			.getLogger(OpenOrderDataDao.class);

	public OpenOrderDataDao() {
	}

	public void persist(OpenOrderData entity) {
		getCurrentSession().save(entity);
	}

	 public void update(OpenOrderData entity) {
		 getCurrentSession().update(entity);
	 }

	public OpenOrderData findById(String id) {
		OpenOrderData data = null;
		try {
			data = (OpenOrderData) getCurrentSession().get(
					OpenOrderData.class, id);
		} catch (RuntimeException re) {
			log.error("get failed", re);
			throw re;
		}
		return data;
	}

	public void delete(OpenOrderData entity) {
		getCurrentSession().delete(entity);
	}

	 @SuppressWarnings("unchecked")
	 public List<OpenOrderData> findAll() {
	 List<OpenOrderData> data = (List<OpenOrderData>)
	 getCurrentSession().createQuery("from OpenOrderData").list();
	 return data;
	 }
}
