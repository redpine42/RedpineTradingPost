package com.redpine.TradeDataAccess.AccountData.DAO;

import java.util.List;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.redpine.TradeDataAccess.AccountData.model.PositionData;
import com.redpine.TradeDataAccess.DAO.CommonDao;

public class PositionDataDao extends CommonDao {
	private static final Logger log = LoggerFactory
			.getLogger(PositionDataDao.class);

	public PositionDataDao() {
	}

	public void persist(PositionData entity) {
		getCurrentSession().save(entity);
	}

	public void update(PositionData entity) {
		getCurrentSession().update(entity);
	}

	public PositionData findById(String id) {
		PositionData data = null;
		try {
			data = (PositionData) getCurrentSession().get(
					PositionData.class, id);
		} catch (RuntimeException re) {
			log.error("get failed", re);
			throw re;
		}
		return data;
	}

	public void delete(PositionData entity) {
		getCurrentSession().delete(entity);
	}

	@SuppressWarnings("unchecked")
	public List<PositionData> findAll() {
		List<PositionData> data = (List<PositionData>) getCurrentSession()
				.createQuery("from PositionData").list();
		return data;
	}
}
