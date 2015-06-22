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

import com.redpine.TradeDataAccess.PriceData.DAO.L2dataDao;
import com.redpine.TradeDataAccess.PriceData.model.L2data;
import com.redpine.TradeDataAccess.Util.DataEnums.OrderSide;

public class L2dataTest {

	static final Logger logger = LoggerFactory.getLogger(L2dataTest.class);

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
		L2dataDao l2Dao = new L2dataDao();
		Session session = l2Dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			L2data entity = l2Dao.findById(seq);
			l2Dao.delete(entity);
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

	public L2data getL2Data() {
		L2dataDao l2Dao = new L2dataDao();
		Session session = l2Dao.openCurrentSession();
		Transaction transaction = null;
		L2data data = null;
		try {
			transaction = session.beginTransaction();
			data = l2Dao.findById(seq);
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
		logger.info("Enter L2dataTest.testGetSeq");

		L2data l2Data = getL2Data();

		assertNotNull("Data not retrieved.", l2Data);
		assertEquals("L2dataTest.seq data doesn't match.", seq, l2Data.getSeq());
	}

	@Test
	public void testGetTimeStamp() {
		logger.info("Enter L1dataTest.testGetTimeStamp");

		L2data l2Data = getL2Data();

		assertNotNull("Data not retrieved.", l2Data);
		assertNotNull("L2dataTest.timeStamp data doesn't match.", l2Data.getTimeStamp());
		logger.info("Creation Date: " + l2Data.getTimeStamp().toString());
	}


	@Test
	public void testGetSymbol() {
		logger.info("Enter L2dataTest.testGetSymbol");

		L2data l2Data = getL2Data();

		assertNotNull("Data not retrieved.", l2Data);
		assertEquals("L2dataTest.symbol data doesn't match.", symbol, l2Data.getSymbol());
	}

	@Test
	public void testGetMmid() {
		logger.info("Enter L2dataTest.testGetMmid");

		L2data l2Data = getL2Data();

		assertNotNull("Data not retrieved.", l2Data);
		assertEquals("L2dataTest.mmid data doesn't match.", mmid, l2Data.getMmid());
	}

	@Test
	public void testGetSource() {
		logger.info("Enter L2dataTest.testGetSource");

		L2data l2Data = getL2Data();

		assertNotNull("Data not retrieved.", l2Data);
			assertEquals("L2dataTest.source data doesn't match.", source, l2Data.getSource());
	}

	@Test
	public void testGetMarketside() {
		logger.info("Enter L2dataTest.testGetMarketside");

		L2data l2Data = getL2Data();

		assertNotNull("Data not retrieved.", l2Data);
		assertEquals("L2dataTest.marketside data doesn't match.", marketside, l2Data.getMarketside());
	}

	@Test
	public void testGetPrice() {
		logger.info("Enter L2dataTest.testGetPrice");

		L2data l2Data = getL2Data();

		assertNotNull("Data not retrieved.", l2Data);
		assertEquals("L2dataTest.price data doesn't match.", price, l2Data.getPrice(), .01);
	}

	@Test
	public void testGetSize() {
		logger.info("Enter L2dataTest.testGetSize");

		L2data l2Data = getL2Data();

		assertNotNull("Data not retrieved.", l2Data);
		assertEquals("L2dataTest.size data doesn't match.", size, l2Data.getSize());
	}

	@Test
	public void testGetRecordTime() {
		logger.info("Enter L2dataTest.testGetRecordTime");

		L2data l2Data = getL2Data();

		assertNotNull("Data not retrieved.", l2Data);
		assertEquals("L2dataTest.time data doesn't match.", recordTime, l2Data.getRecordTime());
	}

	@Test
	public void testGetClosed() {
		logger.info("Enter L2dataTest.testGetClosed");

		L2data l2Data = getL2Data();

		assertNotNull("Data not retrieved.", l2Data);
		assertEquals("L2dataTest.closed data doesn't match.", closed, l2Data.getClosed());
	}
}
