package com.redpine.TradeDataAccess.AccountData.DAO;

import java.util.List;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.redpine.TradeDataAccess.AccountData.model.PurchaseData;
import com.redpine.TradeDataAccess.DAO.CommonDao;

public class PurchaseDataDao extends CommonDao {
	private static final Logger log = LoggerFactory
			.getLogger(PurchaseDataDao.class);

	public PurchaseDataDao() {
	}

	public void persist(PurchaseData entity) {
		getCurrentSession().save(entity);
	}

	public void update(PurchaseData entity) {
		getCurrentSession().update(entity);
	}

	public PurchaseData findById(String id) {
		PurchaseData data = null;
		try {
			data = (PurchaseData) getCurrentSession().get(
					PurchaseData.class, id);
		} catch (RuntimeException re) {
			log.error("get failed", re);
			throw re;
		}
		return data;
	}

	public void delete(PurchaseData entity) {
		getCurrentSession().delete(entity);
	}

	@SuppressWarnings("unchecked")
	public List<PurchaseData> findAll() {
		List<PurchaseData> data = (List<PurchaseData>) getCurrentSession()
				.createQuery("from PositionData").list();
		return data;
	}
}
