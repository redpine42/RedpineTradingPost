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

import com.redpine.TradeDataAccess.PriceData.DAO.L2dataDao;
import com.redpine.TradeDataAccess.PriceData.model.L2data;
import com.redpine.TradeDataAccess.Util.DataEnums.OrderSide;

/**
 * @author dbrown
 *
 */
public class L2dataDaoTest {

	static final Logger logger = LoggerFactory.getLogger(L2dataDaoTest.class);

	private static Integer seq = 0;
	private static String symbol = "TEST";
	private static String mmid = "MMID";
	private static String source = "ABCDE";
	private static OrderSide marketside = OrderSide.ASK;
	private static double price = 123456.78;
	private static int size = 100000;
	private static Timestamp recordTime = new Timestamp(new Date().getTime());
	private static byte closed = 0;

	@BeforeClass
	public static void setUpBeforeClass() throws Exception {
		recordTime.setNanos(0); // MySQL does not save milliseconds
		
		L2data data = new L2data(symbol, mmid, source, marketside, price, size,
			 recordTime, closed);

		L2dataDao l2Dao = new L2dataDao();
		Session session = l2Dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			l2Dao.persist(data);
			transaction.commit();
		} catch(RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("setUpBeforeClass Runtime exception");
		}

		seq = data.getSeq();
		session.clear();
		session.close();
		
		logger.info("Finish setUpBeforeClass. seq = " + seq.toString());
	}

	@AfterClass
	public static void tearDownAfterClass() throws Exception {

		L2dataDao l2Dao = new L2dataDao();
		Session session = l2Dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			L2data entity = l2Dao.findById(seq);
			l2Dao.delete(entity);
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
	 * Test method for {@link com.redpine.TradeDataAccess.PriceData.DAO.L2dataDao#persist(com.redpine.TradeDataAccess.PriceData.model.L2data)}.
	 */
	@Test
	public void testPersist() {
		logger.info("L2dataDaoTest:testPersist");
		L2data data = new L2data(symbol, mmid, source, marketside, price, size,
				 recordTime, closed);

		L2dataDao l2Dao = new L2dataDao();
		Session session = l2Dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			l2Dao.persist(data);
		
			transaction.commit();
		}
		catch(RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("L2Data.testPersist Runtime exception");
		}
		
		Integer seq = data.getSeq();
		session.clear();
		
		try {
			transaction = session.beginTransaction();
			data = l2Dao.findById(seq);
		
			assertNotNull("Failed L2DataDao.testPersist - retrieve", data);
			assertEquals("Failed L2DataDao.testPersist - value symbol", symbol, data.getSymbol());
			assertEquals("Failed L2DataDao.testPersist - value mmid",mmid, data.getMmid());
			assertEquals("Failed L2DataDao.testPersist - value price", price, data.getPrice(), .01);
			assertEquals("Failed L2DataDao.testPersist - value recordTime", recordTime, data.getRecordTime());
			assertEquals("Failed L2DataDao.testPersist - value source", source, data.getSource());
			assertEquals("Failed L2DataDao.testPersist - value marketside", marketside, data.getMarketside());
			assertEquals("Failed L2DataDao.testPersist - value size", size, data.getSize());
			assertEquals("Failed L2DataDao.testPersist - value closed", closed, data.getClosed());
		
			l2Dao.delete(data);

			transaction.commit();
		}
		catch(RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("L2Data.testPersist Runtime exception");
		
		}
		session.clear();
		session.close();
	
		logger.info("Finish testPersist");
	}
	
	/**
	 * Test method for {@link com.redpine.TradeDataAccess.PriceData.DAO.L2dataDao#findById(java.lang.Integer)}.
	 */
	@Test
	public void testFindById() {
		logger.info("L2dataDaoTest:testFindById");

		L2dataDao l2Dao = new L2dataDao();
		Session session = l2Dao.openCurrentSession();

		L2data data = l2Dao.findById(seq);
		
		assertNotNull("Failed L2DataDao.testFindById - retrieve", data);
		assertEquals("Failed L2DataDao.testFindById - value symbol", symbol, data.getSymbol());
		assertEquals("Failed L2DataDao.testFindById - value mmid",mmid, data.getMmid());
		assertEquals("Failed L2DataDao.testFindById - value price", price, data.getPrice(), .01);
		assertEquals("Failed L2DataDao.testFindById - value recordTime", recordTime, data.getRecordTime());
		assertEquals("Failed L2DataDao.testFindById - value source", source, data.getSource());
		assertEquals("Failed L2DataDao.testFindById - value marketside", marketside, data.getMarketside());
		assertEquals("Failed L2DataDao.testFindById - value size", size, data.getSize());
		assertEquals("Failed L2DataDao.testFindById - value closed", closed, data.getClosed());
			
		session.clear();
		session.close();
	
		logger.info("Finish testFindById.");
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.PriceData.DAO.L2dataDao#delete(com.redpine.TradeDataAccess.PriceData.model.L2data)}.
	 */
	@Test
	public void testDelete() {
		logger.info("L2dataDaoTest:testDelete");
		L2data data = new L2data(symbol, mmid, source, marketside, price, size,
				 recordTime, closed);

		L2dataDao l2Dao = new L2dataDao();
		Session session = l2Dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			l2Dao.persist(data);
		
			transaction.commit();
		}
		catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("L2Data.testDelete Runtime exception");
		}
		
		Integer seq = data.getSeq();
		session.clear();
		
		try {
			transaction = session.beginTransaction();
			data = l2Dao.findById(seq);
		
			assertNotNull("Failed L2DataDao.testDelete - retrieve", data);
		
			l2Dao.delete(data);

			transaction.commit();
		}
		catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("L2Data.testDelete Runtime exception");
		}

		session.clear();

		data = l2Dao.findById(seq);
		
		assertNull("Failed L2DataDao.testDelete - delete", data);

		session.clear();
		session.close();
	}
}
