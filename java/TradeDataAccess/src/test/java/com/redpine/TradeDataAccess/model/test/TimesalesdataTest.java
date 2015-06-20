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

	private static Integer tSeq = 0;
	private static Double tTimeStamp = 67435.5;
	private static String tSymbol = "TEST";
	private static int tSizeVal = 1234567;
	private static double tPrice = 123.45;
	private static int tTimeVal = 82828;
	private static int tJdate = 2014199;
	private static int tTsstatus = 0;
	private static int tTstype = 2;

	private static TimesalesdataDao tsDao;

	@BeforeClass
	public static void setUpBeforeClass() throws Exception {
		Timesalesdata data = new Timesalesdata(tSymbol, tSizeVal, tPrice,
				tTimeVal, tJdate, tTsstatus, tTstype);
		data.setTimeStamp(tTimeStamp);
		tsDao = new TimesalesdataDao();
		Session session = tsDao.openCurrentSession();
		Transaction transaction = session.beginTransaction();
		tsDao.persist(data);
		transaction.commit();

		tSeq = data.getSeq();

		logger.info("Finish setUpBeforeClass. seq = " + tSeq.toString());
	}

	@AfterClass
	public static void tearDownAfterClass() throws Exception {
		Session session = tsDao.getCurrentSession();
		Transaction transaction = session.beginTransaction();
		Timesalesdata entity = tsDao.findById(tSeq);
		tsDao.delete(entity);
		transaction.commit();
		session.close();
		logger.info("Finish setUpAfterClass. seq = " + tSeq.toString());
	}

	@Test
	public void testGetSeq() {
		logger.info("Enter TimesalesdataTest.testGetSeq");

		Timesalesdata tsData = tsDao.findById(tSeq);

		if (null == tsData) {
			fail("Data not retrieved.");
		} else if (tSeq != tsData.getSeq()) {
			fail("Timesalesdata.seq data doesn't match.");
		}
	}

	@Test
	public void testGetTimeStamp() {
		logger.info("Enter TimesalesdataTest.testGetTimeStamp");

		Timesalesdata tsData = tsDao.findById(tSeq);

		if (null == tsData) {
			fail("Data not retrieved.");
		} else if (tTimeStamp != tsData.getTimeStamp()) {
			fail("Timesalesdata.TimeStamp data doesn't match.");
		}
	}

	@Test
	public void testSetTimeStamp() {
		logger.info("Enter TimesalesdataTest.testSetTimeStamp");

		Timesalesdata tsData = tsDao.findById(tSeq);

		if (null == tsData) {
			fail("Data not retrieved.");
		} else {
			++tTimeStamp;
			tsData.setTimeStamp(tTimeStamp);
			Session session = tsDao.getCurrentSession();
			Transaction transaction = session.beginTransaction();
			tsDao.update(tsData);
			transaction.commit();
			Timesalesdata updatedData = tsDao.findById(tSeq);
			if (null == updatedData) {
				fail("Data not retrieved.");
			} else if (tTimeStamp != updatedData.getTimeStamp()) {
				fail("Timesalesdata.TimeStamp data doesn't match.");
			}
		}
	}

	@Test
	public void testGetSymbol() {
		logger.info("Enter TimesalesdataTest.testGetSymbol");

		Timesalesdata tsData = tsDao.findById(tSeq);

		if (null == tsData) {
			fail("Data not retrieved.");
		} else if (tSymbol != tsData.getSymbol()) {
			fail("Timesalesdata.Symbol data doesn't match.");
		}
	}

	@Test
	public void testSetSymbol() {
		logger.info("Enter TimesalesdataTest.testGetSizeVal");

		Timesalesdata tsData = tsDao.findById(tSeq);

		if (null == tsData) {
			fail("Data not retrieved.");
		} else {
			tSymbol = "TEST1";
			tsData.setSymbol(tSymbol);
			Session session = tsDao.getCurrentSession();
			Transaction transaction = session.beginTransaction();
			tsDao.update(tsData);
			transaction.commit();
			Timesalesdata updatedData = tsDao.findById(tSeq);

			if (null == updatedData) {
				fail("Data not retrieved.");
			} else if (tSymbol != tsData.getSymbol()) {
				fail("Timesalesdata.Symbol data doesn't match.");
			}
		}
	}

	@Test
	public void testGetSizeVal() {
		logger.info("Enter TimesalesdataTest.testGetSizeVal");

		Timesalesdata tsData = tsDao.findById(tSeq);

		if (null == tsData) {
			fail("Data not retrieved.");
		} else if (tSizeVal != tsData.getSizeVal()) {
			fail("Timesalesdata.sizeVal data doesn't match.");
		}
	}

	@Test
	public void testSetSizeVal() {
		logger.info("Enter TimesalesdataTest.testSetSizeVal");

		Timesalesdata tsData = tsDao.findById(tSeq);

		if (null == tsData) {
			fail("Data not retrieved.");
		} else {
			++tSizeVal;
			tsData.setSizeVal(tSizeVal);
			Session session = tsDao.getCurrentSession();
			Transaction transaction = session.beginTransaction();
			tsDao.update(tsData);
			transaction.commit();
			Timesalesdata updatedData = tsDao.findById(tSeq);

			if (null == updatedData) {
				fail("Data not retrieved.");
			} else if (tSizeVal != tsData.getSizeVal()) {
				fail("Timesalesdata.sizeVal data doesn't match.");
			}
		}
	}

	@Test
	public void testGetPrice() {
		logger.info("Enter TimesalesdataTest.testGetPrice");

		Timesalesdata tsData = tsDao.findById(tSeq);

		if (null == tsData) {
			fail("Data not retrieved.");
		} else if (tPrice != tsData.getPrice()) {
			fail("Timesalesdata.price data doesn't match.");
		}
	}

	@Test
	public void testSetPrice() {
		logger.info("Enter TimesalesdataTest.testSetPrice");

		Timesalesdata tsData = tsDao.findById(tSeq);

		if (null == tsData) {
			fail("Data not retrieved.");
		} else {
			++tPrice;
			tsData.setPrice(tPrice);
			Session session = tsDao.getCurrentSession();
			Transaction transaction = session.beginTransaction();
			tsDao.update(tsData);
			transaction.commit();
			Timesalesdata updatedData = tsDao.findById(tSeq);

			if (null == updatedData) {
				fail("Data not retrieved.");
			} else if (tPrice != tsData.getPrice()) {
				fail("Timesalesdata.price data doesn't match.");
			}
		}
	}

	@Test
	public void testGetTimeVal() {
		logger.info("Enter TimesalesdataTest.testGetTimeVal");

		Timesalesdata tsData = tsDao.findById(tSeq);

		if (null == tsData) {
			fail("Data not retrieved.");
		} else if (tTimeVal != tsData.getTimeVal()) {
			fail("Timesalesdata.timeVal data doesn't match.");
		}
	}

	@Test
	public void testSetTimeVal() {
		logger.info("Enter TimesalesdataTest.testSetTimeVal");

		Timesalesdata tsData = tsDao.findById(tSeq);

		if (null == tsData) {
			fail("Data not retrieved.");
		} else {
			++tTimeVal;
			tsData.setTimeVal(tTimeVal);
			Session session = tsDao.getCurrentSession();
			Transaction transaction = session.beginTransaction();
			tsDao.update(tsData);
			transaction.commit();
			Timesalesdata updatedData = tsDao.findById(tSeq);

			if (null == updatedData) {
				fail("Data not retrieved.");
			} else if (tTimeVal != tsData.getTimeVal()) {
				fail("Timesalesdata.timeVal data doesn't match.");
			}
		}
	}

	@Test
	public void testGetJdate() {
		logger.info("Enter TimesalesdataTest.testGetJdate");

		Timesalesdata tsData = tsDao.findById(tSeq);

		if (null == tsData) {
			fail("Data not retrieved.");
		} else if (tJdate != tsData.getJdate()) {
			fail("Timesalesdata.jdate data doesn't match.");
		}
	}

	@Test
	public void testSetJdate() {
		logger.info("Enter TimesalesdataTest.testSetJdate");

		Timesalesdata tsData = tsDao.findById(tSeq);

		if (null == tsData) {
			fail("Data not retrieved.");
		} else {
			++tJdate;
			tsData.setJdate(tJdate);
			Session session = tsDao.getCurrentSession();
			Transaction transaction = session.beginTransaction();
			tsDao.update(tsData);
			transaction.commit();
			Timesalesdata updatedData = tsDao.findById(tSeq);

			if (null == updatedData) {
				fail("Data not retrieved.");
			} else if (tJdate != tsData.getJdate()) {
				fail("Timesalesdata.jdate data doesn't match.");
			}
		}
	}

	@Test
	public void testGetTsstatus() {
		logger.info("Enter TimesalesdataTest.testGetTsstatus");

		Timesalesdata tsData = tsDao.findById(tSeq);

		if (null == tsData) {
			fail("Data not retrieved.");
		} else if (tTsstatus != tsData.getTsstatus()) {
			fail("Timesalesdata.tsstatus data doesn't match.");
		}
	}

	@Test
	public void testSetTsstatus() {
		logger.info("Enter TimesalesdataTest.testSetTsstatus");

		Timesalesdata tsData = tsDao.findById(tSeq);

		if (null == tsData) {
			fail("Data not retrieved.");
		} else {
			++tTsstatus;
			tsData.setTsstatus(tTsstatus);
			Session session = tsDao.getCurrentSession();
			Transaction transaction = session.beginTransaction();
			tsDao.update(tsData);
			transaction.commit();
			Timesalesdata updatedData = tsDao.findById(tSeq);

			if (null == updatedData) {
				fail("Data not retrieved.");
			} else if (tTsstatus != tsData.getTsstatus()) {
				fail("Timesalesdata.tsstatus data doesn't match.");
			}
		}
	}

	@Test
	public void testGetTstype() {
		logger.info("Enter TimesalesdataTest.testGetTstype");

		Timesalesdata tsData = tsDao.findById(tSeq);

		if (null == tsData) {
			fail("Data not retrieved.");
		} else if (tTstype != tsData.getTstype()) {
			fail("Timesalesdata.tstype data doesn't match.");
		}
	}

	@Test
	public void testSetTstype() {
		logger.info("Enter TimesalesdataTest.testSetTstype");

		Timesalesdata tsData = tsDao.findById(tSeq);

		if (null == tsData) {
			fail("Data not retrieved.");
		} else {
			++tTstype;
			tsData.setTstype(tTstype);
			Session session = tsDao.getCurrentSession();
			Transaction transaction = session.beginTransaction();
			tsDao.update(tsData);
			transaction.commit();
			Timesalesdata updatedData = tsDao.findById(tSeq);

			if (null == updatedData) {
				fail("Data not retrieved.");
			} else if (tTstype != tsData.getTstype()) {
				fail("Timesalesdata.tstype data doesn't match.");
			}
		}
	}
}
