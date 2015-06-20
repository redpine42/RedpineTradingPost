package com.redpine.TradeDataAccess.model.test;

import com.redpine.TradeDataAccess.DAO.TimesalesdataDao;
import com.redpine.TradeDataAccess.model.Timesalesdata;

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
	private static Double timeStamp = 67435.5;
	private static String symbol = "TEST";
	private static int sizeVal = 1234567;
	private static double price = 123.45;
	private static int timeVal = 82828;
	private static int jdate = 2014199;
	private static int tsstatus = 0;
	private static int tstype = 2;

	private static TimesalesdataDao tsDao;

	@BeforeClass
	public static void setUpBeforeClass() throws Exception {
		Timesalesdata data = new Timesalesdata(symbol, sizeVal, price,
				timeVal, jdate, tsstatus, tstype);
		data.setTimeStamp(timeStamp);
		tsDao = new TimesalesdataDao();
		Session session = tsDao.openCurrentSession();
		Transaction transaction = session.beginTransaction();
		tsDao.persist(data);
		transaction.commit();

		seq = data.getSeq();

		logger.info("Finish setUpBeforeClass. seq = " + seq.toString());
	}

	@AfterClass
	public static void tearDownAfterClass() throws Exception {
		Session session = tsDao.getCurrentSession();
		Transaction transaction = session.beginTransaction();
		Timesalesdata entity = tsDao.findById(seq);
		tsDao.delete(entity);
		transaction.commit();
		session.close();
		logger.info("Finish setUpAfterClass. seq = " + seq.toString());
	}

	@Test
	public void testGetSeq() {
		logger.info("Enter TimesalesdataTest.testGetSeq");

		Timesalesdata tsData = tsDao.findById(seq);

		if (null == tsData) {
			fail("Data not retrieved.");
		} else if (seq != tsData.getSeq()) {
			fail("Timesalesdata.seq data doesn't match.");
		}
	}

	@Test
	public void testGetTimeStamp() {
		logger.info("Enter TimesalesdataTest.testGetTimeStamp");

		Timesalesdata tsData = tsDao.findById(seq);

		if (null == tsData) {
			fail("Data not retrieved.");
		} else if (timeStamp != tsData.getTimeStamp()) {
			fail("Timesalesdata.TimeStamp data doesn't match.");
		}
	}
	
	@Test
	public void testSetTimeStamp() {
		logger.info("Enter TimesalesdataTest.testSetTimeStamp");

		Timesalesdata tsData = tsDao.findById(seq);

		if (null == tsData) {
			fail("Data not retrieved.");
		} else {
			++timeStamp;
			tsData.setTimeStamp(timeStamp);
			Session session = tsDao.getCurrentSession();
			Transaction transaction = session.beginTransaction();
			tsDao.update(tsData);
			transaction.commit();
			Timesalesdata updatedData = tsDao.findById(seq);

			if (null == updatedData) {
				fail("Data not retrieved.");
			} else if (timeStamp != tsData.getTimeStamp()) {
				fail("Timesalesdata.timestamp data doesn't match.");
			}
		}
	}
	@Test
	public void testGetSymbol() {
		logger.info("Enter TimesalesdataTest.testGetSymbol");

		Timesalesdata tsData = tsDao.findById(seq);

		if (null == tsData) {
			fail("Data not retrieved.");
		} else if (symbol != tsData.getSymbol()) {
			fail("Timesalesdata.Symbol data doesn't match.");
		}
	}

	@Test
	public void testGetSizeVal() {
		logger.info("Enter TimesalesdataTest.testGetSizeVal");

		Timesalesdata tsData = tsDao.findById(seq);

		if (null == tsData) {
			fail("Data not retrieved.");
		} else if (sizeVal != tsData.getSizeVal()) {
			fail("Timesalesdata.sizeVal data doesn't match.");
		}
	}

	@Test
	public void testGetPrice() {
		logger.info("Enter TimesalesdataTest.testGetPrice");

		Timesalesdata tsData = tsDao.findById(seq);

		if (null == tsData) {
			fail("Data not retrieved.");
		} else if (price != tsData.getPrice()) {
			fail("Timesalesdata.price data doesn't match.");
		}
	}

	@Test
	public void testGetTimeVal() {
		logger.info("Enter TimesalesdataTest.testGetTimeVal");

		Timesalesdata tsData = tsDao.findById(seq);

		if (null == tsData) {
			fail("Data not retrieved.");
		} else if (timeVal != tsData.getTimeVal()) {
			fail("Timesalesdata.timeVal data doesn't match.");
		}
	}

	@Test
	public void testGetJdate() {
		logger.info("Enter TimesalesdataTest.testGetJdate");

		Timesalesdata tsData = tsDao.findById(seq);

		if (null == tsData) {
			fail("Data not retrieved.");
		} else if (jdate != tsData.getJdate()) {
			fail("Timesalesdata.jdate data doesn't match.");
		}
	}

	@Test
	public void testGetTsstatus() {
		logger.info("Enter TimesalesdataTest.testGetTsstatus");

		Timesalesdata tsData = tsDao.findById(seq);

		if (null == tsData) {
			fail("Data not retrieved.");
		} else if (tsstatus != tsData.getTsstatus()) {
			fail("Timesalesdata.tsstatus data doesn't match.");
		}
	}


	@Test
	public void testGetTstype() {
		logger.info("Enter TimesalesdataTest.testGetTstype");

		Timesalesdata tsData = tsDao.findById(seq);

		if (null == tsData) {
			fail("Data not retrieved.");
		} else if (tstype != tsData.getTstype()) {
			fail("Timesalesdata.tstype data doesn't match.");
		}
	}
}
