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

import com.redpine.TradeDataAccess.PriceData.DAO.L1dataDao;
import com.redpine.TradeDataAccess.PriceData.model.L1data;

/**
 * @author dbrown
 *
 */
public class L1dataDaoTest {

	static final Logger logger = LoggerFactory.getLogger(L1dataDaoTest.class);

	private static Integer seq = 0;
	private static String symbol = "TEST";
	private static int size = 100000;
	private static double price = 123.45;
	private static Timestamp recordTime = new Timestamp(new Date().getTime());
	private static double bid = 123.44;
	private static double ask = 123.45;
	private static int bidsize = 100;
	private static int asksize = 200;
	private static int volume = 500;
	
	
	@BeforeClass
	public static void setUpBeforeClass() throws Exception {
		logger.info("L1dataDaoTest:setUpBeforeClass");
		recordTime.setNanos(0);  // MySQL does not save milliseconds
		
		L1data data = new L1data(symbol, size, price, recordTime,
				bid, ask, bidsize, asksize, volume);
		L1dataDao l1Dao = new L1dataDao();
		Session session = l1Dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction =  session.beginTransaction();
			l1Dao.persist(data);

			transaction.commit();
		}
		catch(RuntimeException e) {
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
		logger.info("L1dataDaoTest:tearDownAfterClass:");

		L1dataDao l1Dao = new L1dataDao();
		Session session = l1Dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			L1data entity = l1Dao.findById(seq);
			l1Dao.delete(entity);
			transaction.commit();
		}
		catch(RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("tearDownAfterClass Runtime exception");
		}

		session.close();
		logger.info("Finish setUpAfterClass. seq = " + seq.toString());
	}
	/**
	 * Test method for {@link com.redpine.TradeDataAccess.PriceData.DAO.L1dataDao#persist(com.redpine.TradeDataAccess.PriceData.model.L1data)}.
	 */
	@Test
	public void testPersist() {
		logger.info("L1dataDaoTest:testPersist");
		L1data data = new L1data(symbol, size, price, recordTime,
				bid, ask, bidsize, asksize, volume);

		L1dataDao l1Dao = new L1dataDao();
		Session session = l1Dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			l1Dao.persist(data);
		
			transaction.commit();
		}
		catch(RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("L1Data.testPersist Runtime exception");
		}
		
		Integer seq = data.getSeq();
		session.clear();
		
		try {
			transaction = session.beginTransaction();
			data = l1Dao.findById(seq);
		
			assertNotNull("Failed L1DataDao.testPersist - retrieve", data);
			assertEquals("Failed L1DataDao.testPersist - value symbol", symbol, data.getSymbol());
			assertEquals("Failed L1DataDao.testPersist - value size",size, data.getSize());
			assertEquals("Failed L1DataDao.testPersist - value price", price, data.getPrice(), .01);
			assertEquals("Failed L1DataDao.testPersist - value recordTime", recordTime, data.getRecordTime());
			assertEquals("Failed L1DataDao.testPersist - value bid", bid, data.getBid(), .01);
			assertEquals("Failed L1DataDao.testPersist - value ask", ask, data.getAsk(), .01);
			assertEquals("Failed L1DataDao.testPersist - value bidsize", bidsize, data.getBidsize());
			assertEquals("Failed L1DataDao.testPersist - value asksize", asksize, data.getAsksize());
			assertEquals("Failed L1DataDao.testPersist - value volume", volume, data.getVolume());
		
			l1Dao.delete(data);

			transaction.commit();
		}
		catch(RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("L1Data.testPersist Runtime exception");
		
		}
		session.clear();
		session.close();
		
		logger.info("Finish testPersist");
	}


	/**
	 * Test method for {@link com.redpine.TradeDataAccess.PriceData.DAO.L1dataDao#findById(java.lang.Integer)}.
	 */
	@Test
	public void testFindById() {
		logger.info("L1dataDaoTest:testFindById");
		L1dataDao l1Dao = new L1dataDao();
		Session session = l1Dao.openCurrentSession();

		L1data data = l1Dao.findById(seq);
		
		assertNotNull("Failed L1DataDao.testFindById - retrieve", data);
		assertEquals("Failed L1DataDao.testFindById - value symbol", symbol, data.getSymbol());
		assertEquals("Failed L1DataDao.testFindById - value size",size, data.getSize());
		assertEquals("Failed L1DataDao.testFindById - value price", price, data.getPrice(), .01);
		assertEquals("Failed L1DataDao.testFindById - value recordTime", recordTime, data.getRecordTime());
		assertEquals("Failed L1DataDao.testFindById - value bid", bid, data.getBid(), .01);
		assertEquals("Failed L1DataDao.testFindById - value ask", ask, data.getAsk(), .01);
		assertEquals("Failed L1DataDao.testFindById - value bidsize", bidsize, data.getBidsize());
		assertEquals("Failed L1DataDao.testFindById - value asksize", asksize, data.getAsksize());
		assertEquals("Failed L1DataDao.testFindById - value volume", volume, data.getVolume());
			
		session.clear();
		session.close();
		
		logger.info("Finish testFindById.");
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.PriceData.DAO.L1dataDao#delete(com.redpine.TradeDataAccess.PriceData.model.L1data)}.
	 */
	@Test
	public void testDelete() {
		logger.info("L1dataDaoTest:testDelete");
		L1data data = new L1data(symbol, size, price, recordTime,
				bid, ask, bidsize, asksize, volume);

		L1dataDao l1Dao = new L1dataDao();
		Session session = l1Dao.openCurrentSession();
		Transaction transaction = null;

		try {
			transaction = session.beginTransaction();
			l1Dao.persist(data);
		
			transaction.commit();
		}
		catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("L1Data.testDelete Runtime exception");
		}
		
		Integer seq = data.getSeq();
		session.clear();
		
		try {
			transaction = session.beginTransaction();
			data = l1Dao.findById(seq);
		
			assertNotNull("Failed L1DataDao.testDelete - retrieve", data);
		
			l1Dao.delete(data);

			transaction.commit();
		}
		catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("L1Data.testDelete Runtime exception");
		}

		session.clear();

		data = l1Dao.findById(seq);
		
		assertNull("Failed L1DataDao.testDelete - delete", data);

		session.clear();
		session.close();
	}
}
