/**
 * 
 */
package com.redpine.TradeDataAccess.model.test;

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

import com.redpine.TradeDataAccess.DAO.L1dataDao;
import com.redpine.TradeDataAccess.model.L1data;

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
	
	
	private static L1dataDao l1Dao;

	@BeforeClass
	public static void setUpBeforeClass() throws Exception {
		L1data data = new L1data(symbol, size, price, recordTime,
				bid, ask, bidsize, asksize, volume);
		l1Dao = new L1dataDao();
		Session session = l1Dao.openCurrentSession();
		Transaction transaction = session.beginTransaction();
		l1Dao.persist(data);
		transaction.commit();

		seq = data.getSeq();
		session.clear();
		
		logger.info("Finish setUpBeforeClass. seq = " + seq.toString());
	}

	@AfterClass
	public static void tearDownAfterClass() throws Exception {
		Session session = l1Dao.getCurrentSession();
		Transaction transaction = session.beginTransaction();
		L1data entity = l1Dao.findById(seq);
		l1Dao.delete(entity);
		transaction.commit();
		session.close();
		logger.info("Finish setUpAfterClass. seq = " + seq.toString());
	}

	@Test
	public void testGetSeq() {
		logger.info("Enter L1dataTest.testGetSeq");

		L1data l1Data = l1Dao.findById(seq);

		if (null == l1Data) {
			fail("Data not retrieved.");
		} else if (seq != l1Data.getSeq()) {
			fail("L1dataTest.seq data doesn't match.");
		}
	}

	@Test
	public void testGetTimeStamp() {
		logger.info("Enter L1dataTest.testGetTimeStamp");

		L1data l1Data = l1Dao.findById(seq);

		if (null == l1Data) {
			fail("Data not retrieved.");
		} else if (l1Data.getTimeStamp() == null) {
			fail("L1dataTest.timeStamp data doesn't match.");
		} else	{
			logger.info("Creation Date: " + l1Data.getTimeStamp().toString());
		}
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.model.L1data#getSymbol()}.
	 */
	@Test
	public void testGetSymbol() {
		logger.info("Enter L1dataTest.testGetSymbol");

		L1data l1Data = l1Dao.findById(seq);

		if (null == l1Data) {
			fail("Data not retrieved.");
		} else if (!symbol.equals(l1Data.getSymbol())) {
			fail("L1dataTest.symbol data doesn't match.");
		}
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.model.L1data#getSize()}.
	 */
	@Test
	public void testGetSize() {
		logger.info("Enter L1dataTest.testGetSize");

		L1data l1Data = l1Dao.findById(seq);

		if (null == l1Data) {
			fail("Data not retrieved.");
		} else if (size != l1Data.getSize()) {
			fail("L1dataTest.size data doesn't match.");
		}
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.model.L1data#getPrice()}.
	 */
	@Test
	public void testGetPrice() {
		logger.info("Enter L1dataTest.testGetPrice");

		L1data l1Data = l1Dao.findById(seq);

		if (null == l1Data) {
			fail("Data not retrieved.");
		} else if (price != l1Data.getPrice()) {
			fail("L1dataTest.price data doesn't match.");
		}
	}
	
	/**
	 * Test method for {@link com.redpine.TradeDataAccess.model.L1data#getTime()}.
	 */
	@Test
	public void testGetRecordTime() {
		logger.info("Enter L1dataTest.testGetRecordTime");

		L1data l1Data = l1Dao.findById(seq);

		if (null == l1Data) {
			fail("Data not retrieved.");
		} else if (recordTime.equals(l1Data.getRecordTime())) {
			fail("L1dataTest.time data doesn't match.");
		}

	}


	/**
	 * Test method for {@link com.redpine.TradeDataAccess.model.L1data#getBid()}.
	 */
	@Test
	public void testGetBid() {
		logger.info("Enter L1dataTest.testGetBid");

		L1data l1Data = l1Dao.findById(seq);

		if (null == l1Data) {
			fail("Data not retrieved.");
		} else if (bid != l1Data.getBid()) {
			fail("L1dataTest.bid data doesn't match.");
		}

	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.model.L1data#getAsk()}.
	 */
	@Test
	public void testGetAsk() {
		logger.info("Enter L1dataTest.testGetAsk");

		L1data l1Data = l1Dao.findById(seq);

		if (null == l1Data) {
			fail("Data not retrieved.");
		} else if (ask != l1Data.getAsk()) {
			fail("L1dataTest.ask data doesn't match.");
		}

	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.model.L1data#getBidsize()}.
	 */
	@Test
	public void testGetBidsize() {
		logger.info("Enter L1dataTest.testGetBidsize");

		L1data l1Data = l1Dao.findById(seq);

		if (null == l1Data) {
			fail("Data not retrieved.");
		} else if (bidsize != l1Data.getBidsize()) {
			fail("L1dataTest.bidSize data doesn't match.");
		}

	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.model.L1data#getAsksize()}.
	 */
	@Test
	public void testGetAsksize() {
		logger.info("Enter L1dataTest.testGetAsksize");

		L1data l1Data = l1Dao.findById(seq);

		if (null == l1Data) {
			fail("Data not retrieved.");
		} else if (asksize != l1Data.getAsksize()) {
			fail("L1dataTest.askSize data doesn't match.");
		}

	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.model.L1data#getVolume()}.
	 */
	@Test
	public void testGetVolume() {
		logger.info("Enter L1dataTest.testGetVolume");

		L1data l1Data = l1Dao.findById(seq);

		if (null == l1Data) {
			fail("Data not retrieved.");
		} else if (volume != l1Data.getVolume()) {
			fail("L1dataTest.volume data doesn't match.");
		}

	}
}
