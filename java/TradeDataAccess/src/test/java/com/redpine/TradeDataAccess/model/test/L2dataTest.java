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

import com.redpine.TradeDataAccess.DAO.L2dataDao;
import com.redpine.TradeDataAccess.model.L2data;

public class L2dataTest {

	static final Logger logger = LoggerFactory.getLogger(L2dataTest.class);

	private static Integer seq = 0;
	private static String symbol = "TEST";
	private static String mmid = "MMID";
	private static String source = "ABCDE";
	private static byte marketside = 0;
	private static double price = 123456.78;
	private static int size = 100000;
	private static Timestamp recordTime = new Timestamp(new Date().getTime());
	private static byte closed = 0;

	private static L2dataDao l2Dao;

	@BeforeClass
	public static void setUpBeforeClass() throws Exception {
		L2data data = new L2data(symbol, mmid, source, marketside, price, size,
			 recordTime, closed);
		l2Dao = new L2dataDao();
		Session session = l2Dao.openCurrentSession();
		Transaction transaction = session.beginTransaction();
		l2Dao.persist(data);
		transaction.commit();

		seq = data.getSeq();
		session.clear();
		
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
	public void testGetTimeStamp() {
		logger.info("Enter L1dataTest.testGetTimeStamp");

		L2data l2Data = l2Dao.findById(seq);

		if (null == l2Data) {
			fail("Data not retrieved.");
		} else if (l2Data.getTimeStamp() == null) {
			fail("L2dataTest.timeStamp data doesn't match.");
		} else	{
			logger.info("Creation Date: " + l2Data.getTimeStamp().toString());
		}
	}


	@Test
	public void testGetSymbol() {
		logger.info("Enter L2dataTest.testGetSymbol");

		L2data l2Data = l2Dao.findById(seq);

		if (null == l2Data) {
			fail("Data not retrieved.");
		} else if (!symbol.equals(l2Data.getSymbol())) {
			fail("L2dataTest.symbol data doesn't match.");
		}
	}

	@Test
	public void testGetMmid() {
		logger.info("Enter L2dataTest.testGetMmid");

		L2data l2Data = l2Dao.findById(seq);

		if (null == l2Data) {
			fail("Data not retrieved.");
		} else if (!mmid.equals(l2Data.getMmid())) {
			fail("L2dataTest.mmid data doesn't match.");
		}
	}

	@Test
	public void testGetSource() {
		logger.info("Enter L2dataTest.testGetSource");

		L2data l2Data = l2Dao.findById(seq);

		if (null == l2Data) {
			fail("Data not retrieved.");
		} else if (!source.equals(l2Data.getSource())) {
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
	public void testGetRecordTime() {
		logger.info("Enter L2dataTest.testGetRecordTime");

		L2data l2Data = l2Dao.findById(seq);

		if (null == l2Data) {
			fail("Data not retrieved.");
		} else if (recordTime.equals(l2Data.getRecordTime())) {
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
