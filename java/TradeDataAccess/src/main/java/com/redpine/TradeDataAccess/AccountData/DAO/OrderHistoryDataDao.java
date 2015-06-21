package com.redpine.TradeDataAccess.AccountData.DAO;

import java.util.List;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.redpine.TradeDataAccess.AccountData.model.OrderHistoryData;
import com.redpine.TradeDataAccess.DAO.CommonDao;

public class OrderHistoryDataDao extends CommonDao {
	private static final Logger log = LoggerFactory
			.getLogger(OrderHistoryDataDao.class);

	public OrderHistoryDataDao() {
	}

	public void persist(OrderHistoryData entity) {
		getCurrentSession().save(entity);
	}

	public void update(OrderHistoryData entity) {
		getCurrentSession().update(entity);
	}

	public OrderHistoryData findById(String id) {
		OrderHistoryData data = null;
		try {
			data = (OrderHistoryData) getCurrentSession().get(
					OrderHistoryData.class, id);
		} catch (RuntimeException re) {
			log.error("get failed", re);
			throw re;
		}
		return data;
	}

	public void delete(OrderHistoryData entity) {
		getCurrentSession().delete(entity);
	}

	@SuppressWarnings("unchecked")
	public List<OrderHistoryData> findAll() {
		List<OrderHistoryData> data = (List<OrderHistoryData>) getCurrentSession()
				.createQuery("from OrderHistoryData").list();
		return data;
	}
}
