package com.redpine.TradeDataAccess.AccountData.DAO;

import java.util.List;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.redpine.TradeDataAccess.AccountData.model.AccountData;
import com.redpine.TradeDataAccess.DAO.CommonDao;

public class AccountDataDao extends CommonDao {
	private static final Logger log = LoggerFactory
			.getLogger(AccountDataDao.class);

	public AccountDataDao() {
	}

	public void persist(AccountData entity) {
		getCurrentSession().save(entity);
	}

	 public void update(AccountData entity) {
		 getCurrentSession().update(entity);
	 }

	public AccountData findById(String id) {
		AccountData data = null;
		try {
			data = (AccountData) getCurrentSession().get(
					AccountData.class, id);
		} catch (RuntimeException re) {
			log.error("get failed", re);
			throw re;
		}
		return data;
	}

	public void delete(AccountData entity) {
		getCurrentSession().delete(entity);
	}

	 @SuppressWarnings("unchecked")
	 public List<AccountData> findAll() {
	 List<AccountData> data = (List<AccountData>)
	 getCurrentSession().createQuery("from AccountData").list();
	 return data;
	 }
}
