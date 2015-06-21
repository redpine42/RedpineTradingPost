/**
 * 
 */
package com.redpine.TradeDataAccess.PriceData.DAO.test;

import static org.junit.Assert.*;

import java.sql.Timestamp;
import java.util.Date;

import org.hibernate.Session;
import org.hibernate.Transaction;
import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.redpine.TradeDataAccess.PriceData.DAO.TimesalesdataDao;
import com.redpine.TradeDataAccess.PriceData.model.Timesalesdata;
import com.redpine.TradeDataAccess.Util.DataEnums.TickStatus;
import com.redpine.TradeDataAccess.Util.DataEnums.TickType;

/**
 * @author dbrown
 *
 */
public class TimesalesdataDaoTest {

	static final Logger logger = LoggerFactory
			.getLogger(TimesalesdataDaoTest.class);

	private static Integer seq = 0;
	private static String symbol = "TEST";
	private static int sizeVal = 1234567;
	private static double price = 123.45;
	private static Timestamp recordTime = new Timestamp(new Date().getTime());
	private static TickStatus tsstatus = TickStatus.NORMAL;
	private static TickType tstype = TickType.ASK_TICK;

	private static TimesalesdataDao tsDao;

	@BeforeClass
	public static void setUpBeforeClass() throws Exception {
		recordTime.setNanos(0); // MySQL does not save milliseconds
		
		Timesalesdata data = new Timesalesdata(symbol, sizeVal, price,
				recordTime, tsstatus, tstype);
		tsDao = new TimesalesdataDao();
		Session session = tsDao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction =session.beginTransaction();
			tsDao.persist(data);
			transaction.commit();
		} catch(RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("setUpBeforeClass Runtime exception");
		}

		seq = data.getSeq();

		session.clear();
		logger.info("Finish setUpBeforeClass. seq = " + seq.toString());
	}

	@AfterClass
	public static void tearDownAfterClass() throws Exception {
		Session session = tsDao.getCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			Timesalesdata entity = tsDao.findById(seq);
			tsDao.delete(entity);
			transaction.commit();
		} catch(RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("tearDownAfterClass Runtime exception");
		}

		session.close();
		logger.info("Finish tearDownAfterClass. seq = ");
	}



	/**
	 * Test method for {@link com.redpine.TradeDataAccess.PriceData.DAO.TimesalesdataDao#persist(com.redpine.TradeDataAccess.PriceData.model.Timesalesdata)}.
	 */
	@Test
	public void testPersist() {
		logger.info("TimesalesdataDaoTest:testPersist");
		Timesalesdata data = new Timesalesdata(symbol, sizeVal, price,
				recordTime, tsstatus, tstype);
		Session session = tsDao.getCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			tsDao.persist(data);
		
			transaction.commit();
		}
		catch(RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("Timesalesdata.testPersist Runtime exception");
		}
		
		Integer seq = data.getSeq();
		session.clear();
		
		try {
			transaction = session.beginTransaction();
			data = tsDao.findById(seq);
		
			assertNotNull("Failed TimesalesDataDao.testPersist - retrieve", data);
			assertEquals("Failed TimesalesDataDao.testPersist - value symbol", symbol, data.getSymbol());
			assertEquals("Failed TimesalesDataDao.testPersist - value sizeVal", sizeVal, data.getSizeVal());
			assertEquals("Failed TimesalesDataDao.testPersist - value price", price, data.getPrice(), .01);
			assertEquals("Failed TimesalesDataDao.testPersist - value recordTime", recordTime, data.getRecordTime());
			assertEquals("Failed TimesalesDataDao.testPersist - value tsstatus", tsstatus, data.getTsstatus());
			assertEquals("Failed TimesalesDataDao.testPersist - value tstype", tstype, data.getTstype());

			tsDao.delete(data);

			transaction.commit();
		}
		catch(RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("Timesalesdata.testPersist Runtime exception");
		
		}
		session.clear();
	
		logger.info("Finish testPersist");
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.PriceData.DAO.TimesalesdataDao#findById(java.lang.Integer)}.
	 */
	@Test
	public void testFindById() {
		logger.info("TimesalesdataDaoTest:testFindById");
		Session session = tsDao.getCurrentSession();

		Timesalesdata data = tsDao.findById(seq);
		
		assertNotNull("Failed TimesalesDataDao.testFindById - retrieve", data);
		assertEquals("Failed TimesalesDataDao.testFindById - value symbol", symbol, data.getSymbol());
		assertEquals("Failed TimesalesDataDao.testFindById - value sizeVal", sizeVal, data.getSizeVal());
		assertEquals("Failed TimesalesDataDao.testFindById - value price", price, data.getPrice(), .01);
		assertEquals("Failed TimesalesDataDao.testFindById - value recordTime", recordTime, data.getRecordTime());
		assertEquals("Failed TimesalesDataDao.testFindById - value tsstatus", tsstatus, data.getTsstatus());
		assertEquals("Failed TimesalesDataDao.testFindById - value tstype", tstype, data.getTstype());

			
		session.clear();
	
		logger.info("Finish testFindById.");
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.PriceData.DAO.TimesalesdataDao#delete(com.redpine.TradeDataAccess.PriceData.model.Timesalesdata)}.
	 */
	@Test
	public void testDelete() {
		logger.info("TimesalesdataDaoTest:testDelete");
		Timesalesdata data = new Timesalesdata(symbol, sizeVal, price,
				recordTime, tsstatus, tstype);
		Session session = tsDao.getCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			tsDao.persist(data);
		
			transaction.commit();
		}
		catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("Timesalesdata.testDelete Runtime exception");
		}
		
		Integer seq = data.getSeq();
		session.clear();
		
		try {
			transaction = session.beginTransaction();
			data = tsDao.findById(seq);
		
			assertNotNull("Failed TimesalesdataDao.testDelete - retrieve", data);
		
			tsDao.delete(data);

			transaction.commit();
		}
		catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("Timesalesdata.testDelete Runtime exception");
		}

		session.clear();

		data = tsDao.findById(seq);
		
		assertNull("Failed TimesalesdataDao.testDelete - delete", data);

		session.clear();	
	}
}
