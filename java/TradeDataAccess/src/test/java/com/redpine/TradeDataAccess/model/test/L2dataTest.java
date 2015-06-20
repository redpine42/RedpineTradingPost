package com.redpine.TradeDataAccess.model.test;

import static org.junit.Assert.*;

import org.hibernate.Session;
import org.hibernate.Transaction;
import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.redpine.TradeDataAccess.DAO.L2dataDao;
import com.redpine.TradeDataAccess.model.L2data;

public class L2dataTest {

	static final Logger logger = LoggerFactory.getLogger(L2dataTest.class);

	private static Integer seq = 0;
	private static double timeStamp = 67435.5;
	private static String symbol = "TEST";
	private static String mmid = "MMID";
	private static String source = "ABCDE";
	private static byte marketside = 0;
	private static double price = 123456.78;
	private static int size = 100000;
	private static int jdate = 2014199;
	private static int time = 82828;
	private static byte closed = 0;

	private static L2dataDao l2Dao;

	@BeforeClass
	public static void setUpBeforeClass() throws Exception {
		L2data data = new L2data(symbol, mmid, source, marketside, price, size,
				jdate, time, closed);
		data.setTimeStamp(timeStamp);
		l2Dao = new L2dataDao();
		Session session = l2Dao.openCurrentSession();
		Transaction transaction = session.beginTransaction();
		l2Dao.persist(data);
		transaction.commit();

		seq = data.getSeq();

		logger.info("Finish setUpBeforeClass. seq = " + seq.toString());
	}

	@AfterClass
	public static void tearDownAfterClass() throws Exception {
		Session session = l2Dao.getCurrentSession();
		Transaction transaction = session.beginTransaction();
		L2data entity = l2Dao.findById(seq);
		l2Dao.delete(entity);
		transaction.commit();
		session.close();
		logger.info("Finish setUpAfterClass. seq = " + seq.toString());
	}

	@Test
	public void testGetSeq() {
		logger.info("Enter L2dataTest.testGetSeq");

		L2data l2Data = l2Dao.findById(seq);

		if (null == l2Data) {
			fail("Data not retrieved.");
		} else if (seq != l2Data.getSeq()) {
			fail("L2dataTest.seq data doesn't match.");
		}
	}

	@Test
	public void testSetTimeStamp() {
		logger.info("Enter L2dataTest.testSetTimeStamp");

		L2data l2Data = l2Dao.findById(seq);

		if (null == l2Data) {
			fail("Data not retrieved.");
		} else {
			++timeStamp;
			l2Data.setTimeStamp(timeStamp);
			Session session = l2Dao.getCurrentSession();
			Transaction transaction = session.beginTransaction();
			l2Dao.update(l2Data);
			transaction.commit();
			L2data updatedData = l2Dao.findById(seq);

			if (null == updatedData) {
				fail("Data not retrieved.");
			} else if (timeStamp != l2Data.getTimeStamp()) {
				fail("L2data.timestamp data doesn't match.");
			}
		}
	}

	@Test
	public void testGetTimeStamp() {
		logger.info("Enter L2dataTest.testGetTimeStamp");

		L2data l2Data = l2Dao.findById(seq);

		if (null == l2Data) {
			fail("Data not retrieved.");
		} else if (timeStamp != l2Data.getTimeStamp()) {
			fail("L2dataTest.timeStamp data doesn't match.");
		}
	}

	@Test
	public void testGetSymbol() {
		logger.info("Enter L2dataTest.testGetSymbol");

		L2data l2Data = l2Dao.findById(seq);

		if (null == l2Data) {
			fail("Data not retrieved.");
		} else if (symbol != l2Data.getSymbol()) {
			fail("L2dataTest.symbol data doesn't match.");
		}
	}

	@Test
	public void testGetMmid() {
		logger.info("Enter L2dataTest.testGetMmid");

		L2data l2Data = l2Dao.findById(seq);

		if (null == l2Data) {
			fail("Data not retrieved.");
		} else if (mmid != l2Data.getMmid()) {
			fail("L2dataTest.mmid data doesn't match.");
		}
	}

	@Test
	public void testGetSource() {
		logger.info("Enter L2dataTest.testGetSource");

		L2data l2Data = l2Dao.findById(seq);

		if (null == l2Data) {
			fail("Data not retrieved.");
		} else if (source != l2Data.getSource()) {
			fail("L2dataTest.source data doesn't match.");
		}
	}

	@Test
	public void testGetMarketside() {
		logger.info("Enter L2dataTest.testGetMarketside");

		L2data l2Data = l2Dao.findById(seq);

		if (null == l2Data) {
			fail("Data not retrieved.");
		} else if (marketside != l2Data.getMarketside()) {
			fail("L2dataTest.marketside data doesn't match.");
		}
	}

	@Test
	public void testGetPrice() {
		logger.info("Enter L2dataTest.testGetPrice");

		L2data l2Data = l2Dao.findById(seq);

		if (null == l2Data) {
			fail("Data not retrieved.");
		} else if (price != l2Data.getPrice()) {
			fail("L2dataTest.price data doesn't match.");
		}
	}

	@Test
	public void testGetSize() {
		logger.info("Enter L2dataTest.testGetSize");

		L2data l2Data = l2Dao.findById(seq);

		if (null == l2Data) {
			fail("Data not retrieved.");
		} else if (size != l2Data.getSize()) {
			fail("L2dataTest.size data doesn't match.");
		}
	}

	@Test
	public void testGetJdate() {
		logger.info("Enter L2dataTest.testGetJdate");

		L2data l2Data = l2Dao.findById(seq);

		if (null == l2Data) {
			fail("Data not retrieved.");
		} else if (jdate != l2Data.getJdate()) {
			fail("L2dataTest.jdate data doesn't match.");
		}
	}

	@Test
	public void testGetTime() {
		logger.info("Enter L2dataTest.testGetTime");

		L2data l2Data = l2Dao.findById(seq);

		if (null == l2Data) {
			fail("Data not retrieved.");
		} else if (time != l2Data.getTime()) {
			fail("L2dataTest.time data doesn't match.");
		}
	}

	@Test
	public void testGetClosed() {
		logger.info("Enter L2dataTest.testGetClosed");

		L2data l2Data = l2Dao.findById(seq);

		if (null == l2Data) {
			fail("Data not retrieved.");
		} else if (closed != l2Data.getClosed()) {
			fail("L2dataTest.closed data doesn't match.");
		}

	}
}
