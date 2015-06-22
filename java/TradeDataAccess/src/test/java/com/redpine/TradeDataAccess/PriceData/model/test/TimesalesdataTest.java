package com.redpine.TradeDataAccess.PriceData.model.test;

import java.sql.Timestamp;
import java.util.Date;

import com.redpine.TradeDataAccess.PriceData.DAO.TimesalesdataDao;
import com.redpine.TradeDataAccess.PriceData.model.Timesalesdata;
import com.redpine.TradeDataAccess.Util.DataEnums.TickStatus;
import com.redpine.TradeDataAccess.Util.DataEnums.TickType;

import static org.junit.Assert.*;

import org.hibernate.Session;
import org.hibernate.Transaction;
import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class TimesalesdataTest {

	static final Logger logger = LoggerFactory
			.getLogger(TimesalesdataTest.class);

	private static Integer seq = 0;
	private static String symbol = "TEST";
	private static int sizeVal = 1234567;
	private static double price = 123.45;
	private static Timestamp recordTime = new Timestamp(new Date().getTime());
	private static TickStatus tsstatus = TickStatus.NORMAL;
	private static TickType tstype = TickType.ASK_TICK;

	@BeforeClass
	public static void setUpBeforeClass() throws Exception {
		recordTime.setNanos(0); // MySQL does not save milliseconds
		
		Timesalesdata data = new Timesalesdata(symbol, sizeVal, price,
				recordTime, tsstatus, tstype);
		TimesalesdataDao tsDao = new TimesalesdataDao();
		Session session = tsDao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			tsDao.persist(data);
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
		TimesalesdataDao tsDao = new TimesalesdataDao();
		Session session = tsDao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			Timesalesdata entity = tsDao.findById(seq);
			tsDao.delete(entity);
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

	public Timesalesdata getTimesalesdata() {
		TimesalesdataDao tsDao = new TimesalesdataDao();
		Session session = tsDao.openCurrentSession();
		Transaction transaction = null;
		Timesalesdata data = null;
		try {
			transaction = session.beginTransaction();
			data = tsDao.findById(seq);
			transaction.commit();
		}
		catch(RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("getTimesalesdata Runtime exception");
		}
		session.close();
		
		return data;
	}

	@Test
	public void testGetSeq() {
		logger.info("Enter TimesalesdataTest.testGetSeq");

		Timesalesdata tsData = getTimesalesdata();

		assertNotNull("Data not retrieved.", tsData);
		assertEquals("Timesalesdata.seq data doesn't match.", seq, tsData.getSeq());
	}

	@Test
	public void testGetTimeStamp() {
		logger.info("Enter L1dataTest.testGetTimeStamp");

		Timesalesdata tsData = getTimesalesdata();

		assertNotNull("Data not retrieved.", tsData);
		assertNotNull("TimesalesdataTest.timeStamp data doesn't match.", tsData.getTimeStamp());
		logger.info("Creation Date:" + tsData.getTimeStamp().toString());
	}
	
	@Test
	public void testGetSymbol() {
		logger.info("Enter TimesalesdataTest.testGetSymbol");

		Timesalesdata tsData = getTimesalesdata();

		assertNotNull("Data not retrieved.", tsData);
		assertEquals("Timesalesdata.Symbol data doesn't match.", symbol, tsData.getSymbol());
	}

	@Test
	public void testGetSizeVal() {
		logger.info("Enter TimesalesdataTest.testGetSizeVal");

		Timesalesdata tsData = getTimesalesdata();

		assertNotNull("Data not retrieved.", tsData);
		assertEquals("Timesalesdata.sizeVal data doesn't match.", sizeVal, tsData.getSizeVal());
	}

	@Test
	public void testGetPrice() {
		logger.info("Enter TimesalesdataTest.testGetPrice");

		Timesalesdata tsData = getTimesalesdata();

		assertNotNull("Data not retrieved.", tsData);
		assertEquals("Timesalesdata.price data doesn't match.", price, tsData.getPrice(), .01);
	}

	@Test
	public void testGetRecordTime() {
		logger.info("Enter TimesalesdataTest.testGetRecordTimel");

		Timesalesdata tsData = getTimesalesdata();

		assertNotNull("Data not retrieved.", tsData);
		assertEquals("Timesalesdata.recordTime data doesn't match.", recordTime, tsData.getRecordTime());

		logger.info("Record Date:" + tsData.getRecordTime().toString());
	}

	@Test
	public void testGetTsstatus() {
		logger.info("Enter TimesalesdataTest.testGetTsstatus");

		Timesalesdata tsData = getTimesalesdata();

		assertNotNull("Data not retrieved.", tsData);
		assertEquals("Timesalesdata.tsstatus data doesn't match.", tsstatus, tsData.getTsstatus());
	}


	@Test
	public void testGetTstype() {
		logger.info("Enter TimesalesdataTest.testGetTstype");

		Timesalesdata tsData = getTimesalesdata();

		assertNotNull("Data not retrieved.", tsData);
		assertEquals("Timesalesdata.tstype data doesn't match.", tstype, tsData.getTstype());
	}
}
