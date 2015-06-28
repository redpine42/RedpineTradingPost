/**
 * 
 */
package com.redpine.TradeDataAccess.PriceData.model.test;

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
public class L1dataTest {
	
	static final Logger logger = LoggerFactory.getLogger(L1dataTest.class);

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
		recordTime.setNanos(0);
		
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
			fail("setUpBeforeClass Runtime exception");
		}

		seq = data.getSeq();
		session.clear();
		session.close();
		
		logger.info("Finish setUpBeforeClass. seq = " + seq.toString());
	}

	@AfterClass
	public static void tearDownAfterClass() throws Exception {
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
			fail("setUpAfterClass Runtime exception");
		}

		session.close();
		logger.info("Finish setUpAfterClass. seq = " + seq.toString());
	}

	public L1data getL1Data() {
		L1dataDao l1Dao = new L1dataDao();
		Session session = l1Dao.openCurrentSession();
		Transaction transaction = null;
		L1data data = null;
		try {
			transaction = session.beginTransaction();
			data = l1Dao.findById(seq);
			transaction.commit();
		}
		catch(RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("getL1Data Runtime exception");
		}
		session.close();
		
		return data;
	}
	
	@Test
	public void testGetSeq() {
		logger.info("Enter L1dataTest.testGetSeq");
		
		L1data l1Data = getL1Data();
		
		assertNotNull("Data not retrieved.", l1Data);
		assertEquals("L1dataTest.seq data doesn't match.", seq, l1Data.getSeq());
	}

	@Test
	public void testGetTimeStamp() {
		logger.info("Enter L1dataTest.testGetTimeStamp");

		L1data l1Data = getL1Data();

		assertNotNull("Data not retrieved.", l1Data);
		assertNotNull("L1dataTest.timeStamp data doesn't match.", l1Data.getTimeStamp());
		logger.info("Creation Date: " + l1Data.getTimeStamp().toString());
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.PriceData.model.L1data#getSymbol()}.
	 */
	@Test
	public void testGetSymbol() {
		logger.info("Enter L1dataTest.testGetSymbol");

		L1data l1Data = getL1Data();

		assertNotNull("Data not retrieved.", l1Data);
		assertEquals("L1dataTest.symbol data doesn't match.", symbol, l1Data.getSymbol());
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.PriceData.model.L1data#getSize()}.
	 */
	@Test
	public void testGetSize() {
		logger.info("Enter L1dataTest.testGetSize");

		L1data l1Data = getL1Data();

		assertNotNull("Data not retrieved.", l1Data);
		assertEquals("L1dataTest.size data doesn't match.", size, l1Data.getSize());
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.PriceData.model.L1data#getPrice()}.
	 */
	@Test
	public void testGetPrice() {
		logger.info("Enter L1dataTest.testGetPrice");

		L1data l1Data = getL1Data();

		assertNotNull("Data not retrieved.", l1Data);
		assertEquals("L1dataTest.price data doesn't match.", price, l1Data.getPrice(), .01);
	}
	
	/**
	 * Test method for {@link com.redpine.TradeDataAccess.PriceData.model.L1data#getRecordTime()}.
	 */
	@Test
	public void testGetRecordTime() {
		logger.info("Enter L1dataTest.testGetRecordTime");

		L1data l1Data = getL1Data();

		assertNotNull("Data not retrieved.", l1Data);
		assertEquals("L1dataTest.recordtime data doesn't match.", recordTime, l1Data.getRecordTime());
	}


	/**
	 * Test method for {@link com.redpine.TradeDataAccess.PriceData.model.L1data#getBid()}.
	 */
	@Test
	public void testGetBid() {
		logger.info("Enter L1dataTest.testGetBid");

		L1data l1Data = getL1Data();

		assertNotNull("Data not retrieved.", l1Data);
		assertEquals("L1dataTest.bid data doesn't match.", bid, l1Data.getBid(), .01);
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.PriceData.model.L1data#getAsk()}.
	 */
	@Test
	public void testGetAsk() {
		logger.info("Enter L1dataTest.testGetAsk");

		L1data l1Data = getL1Data();

		assertNotNull("Data not retrieved.", l1Data);
		assertEquals("L1dataTest.ask data doesn't match.", ask, l1Data.getAsk(), .01);
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.PriceData.model.L1data#getBidsize()}.
	 */
	@Test
	public void testGetBidsize() {
		logger.info("Enter L1dataTest.testGetBidsize");

		L1data l1Data = getL1Data();

		assertNotNull("Data not retrieved.", l1Data);
		assertEquals("L1dataTest.bidSize data doesn't match.", bidsize, l1Data.getBidsize());
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.PriceData.model.L1data#getAsksize()}.
	 */
	@Test
	public void testGetAsksize() {
		logger.info("Enter L1dataTest.testGetAsksize");

		L1data l1Data = getL1Data();

		assertNotNull("Data not retrieved.", l1Data);
		assertEquals("L1dataTest.askSize data doesn't match.", asksize, l1Data.getAsksize());
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.PriceData.model.L1data#getVolume()}.
	 */
	@Test
	public void testGetVolume() {
		logger.info("Enter L1dataTest.testGetVolume");

		L1data l1Data = getL1Data();

		assertNotNull("Data not retrieved.", l1Data);
		assertEquals("L1dataTest.volume data doesn't match.", volume, l1Data.getVolume());
	}
}
