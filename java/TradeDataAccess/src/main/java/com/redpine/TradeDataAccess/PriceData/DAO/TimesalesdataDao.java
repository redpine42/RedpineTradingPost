package com.redpine.TradeDataAccess.PriceData.DAO;

import com.redpine.TradeDataAccess.DAO.CommonDao;
import com.redpine.TradeDataAccess.PriceData.model.Timesalesdata;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * Home object for domain model class Timesalesdata.
 * 
 * @see com.redpine.TradeDataAccess.PriceData.model.Timesalesdata
 * @author Hibernate Tools
 */
// @Stateless
public class TimesalesdataDao extends CommonDao {

	private static final Logger log = LoggerFactory
			.getLogger(TimesalesdataDao.class);

	public TimesalesdataDao() {
	}

	public void persist(Timesalesdata entity) {
		getCurrentSession().save(entity);
	}

	// public void update(Timesalesdata entity) {
	// getCurrentSession().update(entity);
	// }

	public Timesalesdata findById(Integer id) {
		Timesalesdata tsData = null;
		try {
			tsData = (Timesalesdata) getCurrentSession().get(
					Timesalesdata.class, id);
		} catch (RuntimeException re) {
			log.error("get failed", re);
			throw re;
		}
		return tsData;
	}

	public void delete(Timesalesdata entity) {
		getCurrentSession().delete(entity);
	}

	//
	// @SuppressWarnings("unchecked")
	// public List<Timesalesdata> findAll() {
	// List<Timesalesdata> tsData = (List<Timesalesdata>)
	// getCurrentSession().createQuery("from Timesalesdata").list();
	// return tsData;
	// }

}
