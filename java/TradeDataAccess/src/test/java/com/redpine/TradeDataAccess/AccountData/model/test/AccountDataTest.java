/**
 * 
 */
package com.redpine.TradeDataAccess.AccountData.model.test;

import static org.junit.Assert.*;

import java.sql.Timestamp;

import org.hibernate.Session;
import org.hibernate.Transaction;
import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.redpine.TradeDataAccess.AccountData.DAO.AccountDataDao;
import com.redpine.TradeDataAccess.AccountData.model.AccountData;

/**
 * @author dbrown
 *
 */
public class AccountDataTest {

	static final Logger logger = LoggerFactory.getLogger(AccountDataTest.class);
	private static String accountId = "accountId-1";

	private static String eventType = "eventType-1";
	private static String accountName = "accountName-1";
	private static long accountType = 0;
	private static String bank = "bank-1";
	private static String baseCurrency = "baseCurrency-1";
	private static String branch = "branch-1";
	private static long cancelsToday = 0;
	private static double credit = 1000.11;
	private static double currentEquity = 1000.12;
	private static double currentExcess = 1000.13;
	private static String customer = "customer-1";
	private static double dailyRealizedPL = 10.1;
	private static double MMRMultiplier = 10.2;
	private static double MMRUsed = 10.3;
	private static double morningCash = 1000.14;
	private static double morningEquity = 1000.15;
	private static double morningExcess = 1000.16;
	private static double overnightExcess = 1000.17;
	private static Boolean permedForCADEquities = false;
	private static Boolean permedForEquities = true;
	private static Boolean permedForForex = false;
	private static Boolean permedForFutures = true;
	private static Boolean permedForOptions = false;
	private static String routingId = "routingId-1";
	private static String semiDelimited = "semiDelimited-1";
	private static long sharesToday = 100;
	private static long tradesToday = 2;

	/**
	 * @throws java.lang.Exception
	 */
	@BeforeClass
	public static void setUpBeforeClass() throws Exception {

		AccountData data = new AccountData(accountId, eventType, accountName,
				accountType, bank, baseCurrency, branch, cancelsToday, credit,
				currentEquity, currentExcess, customer, dailyRealizedPL,
				MMRMultiplier, MMRUsed, morningCash, morningEquity,
				morningExcess, overnightExcess, permedForCADEquities,
				permedForEquities, permedForForex, permedForFutures,
				permedForOptions, routingId, semiDelimited, sharesToday,
				tradesToday);
		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			dao.persist(data);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("setUpBeforeClass Runtime exception");
		}

		session.close();

		logger.info("Finish setUpBeforeClass.");
	}

	/**
	 * @throws java.lang.Exception
	 */
	@AfterClass
	public static void tearDownAfterClass() throws Exception {
		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			AccountData entity = dao.findById(accountId);
			dao.delete(entity);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("setUpAfterClass Runtime exception");
		}

		session.close();
		logger.info("Finish setUpAfterClass");
	}

	private AccountData getAccountData() {
		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		AccountData data = null;
		try {
			transaction = session.beginTransaction();
			data = dao.findById(accountId);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("getAccountData Runtime exception");
		}
		session.close();

		return data;
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getAccountId()}
	 * .
	 */
	@Test
	public final void testGetAccountId() {
		logger.info("Enter AccountDataTest.");

		AccountData data = getAccountData();

		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetAccountId data doesn't match.",
				accountId, data.getAccountId());
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getEventType()}
	 * .
	 */
	@Test
	public final void testGetEventType() {
		logger.info("Enter AccountDataTest.");

		AccountData data = getAccountData();

		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetEventType data doesn't match.",
				eventType, data.getEventType());
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setEventType(java.lang.String)}
	 * .
	 */
	@Test
	public final void testSetEventType() {
		AccountData data = null;

		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			eventType = "eventType-2";
			data = dao.findById(accountId);
			data.setEventType(eventType);
			dao.update(data);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("testSetEventType Runtime exception");
		}

		session.close();

		data = getAccountData();
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetEventType data doesn't match.",
				eventType, data.getEventType());
		logger.info("Finish testSetEventType.");
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getAccountName()}
	 * .
	 */
	@Test
	public final void testGetAccountName() {
		logger.info("Enter AccountDataTest.");

		AccountData data = getAccountData();

		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetAccountName data doesn't match.",
				accountName, data.getAccountName());
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setAccountName(java.lang.String)}
	 * .
	 */
	@Test
	public final void testSetAccountName() {
		AccountData data = null;

		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			accountName = "accountName-2";
			data = dao.findById(accountId);
			data.setAccountName(accountName);
			dao.update(data);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("testSetAccountName Runtime exception");
		}

		session.close();

		data = getAccountData();
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testSetAccountName data doesn't match.",
				accountName, data.getAccountName());
		logger.info("Finish testSetAccountName.");
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getAccountType()}
	 * .
	 */
	@Test
	public final void testGetAccountType() {
		logger.info("Enter AccountDataTest.");

		AccountData data = getAccountData();

		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetAccountType data doesn't match.",
				accountType, data.getAccountType());
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setAccountType(long)}
	 * .
	 */
	@Test
	public final void testSetAccountType() {
		AccountData data = null;

		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			accountType = 2;
			data = dao.findById(accountId);
			data.setAccountType(accountType);
			dao.update(data);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("testSetAccountType Runtime exception");
		}

		session.close();

		data = getAccountData();
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testSetAccountType data doesn't match.",
				accountType, data.getAccountType());
		logger.info("Finish testSetAccountType.");
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getBank()}
	 * .
	 */
	@Test
	public final void testGetBank() {
		logger.info("Enter AccountDataTest.");

		AccountData data = getAccountData();

		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetBank data doesn't match.", bank,
				data.getBank());
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setBank(java.lang.String)}
	 * .
	 */
	@Test
	public final void testSetBank() {
		AccountData data = null;

		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			bank = "bank-2";
			data = dao.findById(accountId);
			data.setBank(bank);
			dao.update(data);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("testSetBank Runtime exception");
		}

		session.close();

		data = getAccountData();
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testSetBank data doesn't match.",
				bank, data.getBank());
		logger.info("Finish testSetBank.");
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getBaseCurrency()}
	 * .
	 */
	@Test
	public final void testGetBaseCurrency() {
		logger.info("Enter AccountDataTest.");

		AccountData data = getAccountData();

		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetBaseCurrency data doesn't match.",
				baseCurrency, data.getBaseCurrency());
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setBaseCurrency(java.lang.String)}
	 * .
	 */
	@Test
	public final void testSetBaseCurrency() {
		AccountData data = null;

		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			baseCurrency = "currency-2";
			data = dao.findById(accountId);
			data.setBaseCurrency(baseCurrency);
			dao.update(data);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("testSetBaseCurrency Runtime exception");
		}

		session.close();

		data = getAccountData();
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testSetBaseCurrency data doesn't match.",
				baseCurrency, data.getBaseCurrency());
		logger.info("Finish testSetBaseCurrency.");
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getBranch()}
	 * .
	 */
	@Test
	public final void testGetBranch() {
		logger.info("Enter AccountDataTest.");

		AccountData data = getAccountData();

		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetBranch data doesn't match.",
				branch, data.getBranch());
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setBranch(java.lang.String)}
	 * .
	 */
	@Test
	public final void testSetBranch() {
		AccountData data = null;

		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			branch = "branch-2";
			data = dao.findById(accountId);
			data.setBranch(branch);
			dao.update(data);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("testSetBranch Runtime exception");
		}

		session.close();

		data = getAccountData();
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testSetBranch data doesn't match.",
				branch, data.getBranch());
		logger.info("Finish testSetBranch.");
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getCancelsToday()}
	 * .
	 */
	@Test
	public final void testGetCancelsToday() {
		logger.info("Enter AccountDataTest.");

		AccountData data = getAccountData();

		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetCancelsToday data doesn't match.",
				cancelsToday, data.getCancelsToday());
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setCancelsToday(long)}
	 * .
	 */
	@Test
	public final void testSetCancelsToday() {
		AccountData data = null;

		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			cancelsToday = 10;
			data = dao.findById(accountId);
			data.setCancelsToday(cancelsToday);
			dao.update(data);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("testSetCancelsToday Runtime exception");
		}

		session.close();

		data = getAccountData();
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testSetCancelsToday data doesn't match.",
				cancelsToday, data.getCancelsToday());
		logger.info("Finish testSetCancelsToday.");
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getCredit()}
	 * .
	 */
	@Test
	public final void testGetCredit() {
		logger.info("Enter AccountDataTest.");

		AccountData data = getAccountData();

		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetCredit data doesn't match.",
				credit, data.getCredit(), .01);
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setCredit(double)}
	 * .
	 */
	@Test
	public final void testSetCredit() {
		AccountData data = null;

		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			credit = 2000.15;
			data = dao.findById(accountId);
			data.setCredit(credit);
			dao.update(data);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("testSetCredit Runtime exception");
		}

		session.close();

		data = getAccountData();
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testSetCredit data doesn't match.",
				credit, data.getCredit(), .01);
		logger.info("Finish testSetCredit.");
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getCurrentEquity()}
	 * .
	 */
	@Test
	public final void testGetCurrentEquity() {
		logger.info("Enter AccountDataTest.");

		AccountData data = getAccountData();

		assertNotNull("Data not retrieved.", data);
		assertEquals(
				"AccountDataTest.testGetCurrentEquity data doesn't match.",
				currentEquity, data.getCurrentEquity(), .01);
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setCurrentEquity(double)}
	 * .
	 */
	@Test
	public final void testSetCurrentEquity() {
		AccountData data = null;

		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			currentEquity = 2000.14;
			data = dao.findById(accountId);
			data.setCurrentEquity(currentEquity);
			dao.update(data);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("testSetCurrentEquity Runtime exception");
		}

		session.close();

		data = getAccountData();
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testSetCurrentEquity data doesn't match.",
				currentEquity, data.getCurrentEquity(), .01);
		logger.info("Finish testSetCurrentEquity.");
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getCurrentExcess()}
	 * .
	 */
	@Test
	public final void testGetCurrentExcess() {
		logger.info("Enter AccountDataTest.");

		AccountData data = getAccountData();

		assertNotNull("Data not retrieved.", data);
		assertEquals(
				"AccountDataTest.testGetCurrentExcess data doesn't match.",
				currentExcess, data.getCurrentExcess(), .01);
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setCurrentExcess(double)}
	 * .
	 */
	@Test
	public final void testSetCurrentExcess() {
		AccountData data = null;

		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			currentExcess = 2000.12;
			data = dao.findById(accountId);
			data.setCurrentExcess(currentExcess);
			dao.update(data);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("testSetCurrentExcess Runtime exception");
		}

		session.close();

		data = getAccountData();
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testSetCurrentExcess data doesn't match.",
				currentExcess, data.getCurrentExcess(), .01);
		logger.info("Finish testSetCurrentExcess.");
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getCustomer()}
	 * .
	 */
	@Test
	public final void testGetCustomer() {
		logger.info("Enter AccountDataTest.");

		AccountData data = getAccountData();

		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetCustomer data doesn't match.",
				customer, data.getCustomer());
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setCustomer(java.lang.String)}
	 * .
	 */
	@Test
	public final void testSetCustomer() {
		AccountData data = null;

		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			customer = "customer-2";
			data = dao.findById(accountId);
			data.setCustomer(customer);
			dao.update(data);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("testSetCustomer Runtime exception");
		}

		session.close();

		data = getAccountData();
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testSetCustomer data doesn't match.",
				customer, data.getCustomer());
		logger.info("Finish testSetCustomer.");
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getDailyRealizedPL()}
	 * .
	 */
	@Test
	public final void testGetDailyRealizedPL() {
		logger.info("Enter AccountDataTest.");

		AccountData data = getAccountData();

		assertNotNull("Data not retrieved.", data);
		assertEquals(
				"AccountDataTest.testGetDailyRealizedPL data doesn't match.",
				dailyRealizedPL, data.getDailyRealizedPL(), .01);
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setDailyRealizedPL(double)}
	 * .
	 */
	@Test
	public final void testSetDailyRealizedPL() {
		AccountData data = null;

		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			dailyRealizedPL = 3000.11;
			data = dao.findById(accountId);
			data.setDailyRealizedPL(dailyRealizedPL);
			dao.update(data);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("testSetDailyRealizedPL Runtime exception");
		}

		session.close();

		data = getAccountData();
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testSetDailyRealizedPL data doesn't match.",
				dailyRealizedPL, data.getDailyRealizedPL(), .01);
		logger.info("Finish testSetDailyRealizedPL.");
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getMMRMultiplier()}
	 * .
	 */
	@Test
	public final void testGetMMRMultiplier() {
		logger.info("Enter AccountDataTest.");

		AccountData data = getAccountData();

		assertNotNull("Data not retrieved.", data);
		assertEquals(
				"AccountDataTest.testGetMMRMultiplier data doesn't match.",
				MMRMultiplier, data.getMMRMultiplier(), .01);
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setMMRMultiplier(double)}
	 * .
	 */
	@Test
	public final void testSetMMRMultiplier() {
		AccountData data = null;

		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			MMRMultiplier = 20.12;
			data = dao.findById(accountId);
			data.setMMRMultiplier(MMRMultiplier);
			dao.update(data);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("testSetMMRMultiplier Runtime exception");
		}

		session.close();

		data = getAccountData();
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testSetMMRMultiplier data doesn't match.",
				MMRMultiplier, data.getMMRMultiplier(), .01);
		logger.info("Finish testSetMMRMultiplier.");
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getMMRUsed()}
	 * .
	 */
	@Test
	public final void testGetMMRUsed() {
		logger.info("Enter AccountDataTest.");

		AccountData data = getAccountData();

		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetMMRUsed data doesn't match.",
				MMRUsed, data.getMMRUsed(), .01);
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setMMRUsed(double)}
	 * .
	 */
	@Test
	public final void testSetMMRUsed() {
		AccountData data = null;

		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			MMRUsed = 20.11;
			data = dao.findById(accountId);
			data.setMMRUsed(MMRUsed);
			dao.update(data);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("testSetMMRUsed Runtime exception");
		}

		session.close();

		data = getAccountData();
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testSetMMRUsed data doesn't match.",
				MMRUsed, data.getMMRUsed(), .01);
		logger.info("Finish testSetMMRUsed.");
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getMorningCash()}
	 * .
	 */
	@Test
	public final void testGetMorningCash() {
		logger.info("Enter AccountDataTest.");

		AccountData data = getAccountData();

		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetMorningCash data doesn't match.",
				morningCash, data.getMorningCash(), .01);
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setMorningCash(double)}
	 * .
	 */
	@Test
	public final void testSetMorningCash() {
		AccountData data = null;

		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			morningCash = 2000.14;
			data = dao.findById(accountId);
			data.setMorningCash(morningCash);
			dao.update(data);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("testSetMorningCash Runtime exception");
		}

		session.close();

		data = getAccountData();
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testSetMorningCash data doesn't match.",
				morningCash, data.getMorningCash(), .01);
		logger.info("Finish testSetMorningCash.");
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getMorningEquity()}
	 * .
	 */
	@Test
	public final void testGetMorningEquity() {
		logger.info("Enter AccountDataTest.");

		AccountData data = getAccountData();

		assertNotNull("Data not retrieved.", data);
		assertEquals(
				"AccountDataTest.testGetMorningEquity data doesn't match.",
				morningEquity, data.getMorningEquity(), .01);
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setMorningEquity(double)}
	 * .
	 */
	@Test
	public final void testSetMorningEquity() {
		AccountData data = null;

		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			morningEquity = 2000.13;
			data = dao.findById(accountId);
			data.setMorningEquity(morningEquity);
			dao.update(data);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("testSetMorningEquity Runtime exception");
		}

		session.close();

		data = getAccountData();
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testSetMorningEquity data doesn't match.",
				morningEquity, data.getMorningEquity(), .01);
		logger.info("Finish testSetMorningEquity.");
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getMorningExcess()}
	 * .
	 */
	@Test
	public final void testGetMorningExcess() {
		logger.info("Enter AccountDataTest.");

		AccountData data = getAccountData();

		assertNotNull("Data not retrieved.", data);
		assertEquals(
				"AccountDataTest.testGetMorningExcess data doesn't match.",
				morningExcess, data.getMorningExcess(), .01);
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setMorningExcess(double)}
	 * .
	 */
	@Test
	public final void testSetMorningExcess() {
		AccountData data = null;

		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			morningExcess = 2000.12;
			data = dao.findById(accountId);
			data.setMorningExcess(morningExcess);
			dao.update(data);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("testSetMorningExcess Runtime exception");
		}

		session.close();

		data = getAccountData();
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testSetMorningExcess data doesn't match.",
				morningExcess, data.getMorningExcess(), .01);
		logger.info("Finish testSetMorningExcess.");
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getOvernightExcess()}
	 * .
	 */
	@Test
	public final void testGetOvernightExcess() {
		logger.info("Enter AccountDataTest.");

		AccountData data = getAccountData();

		assertNotNull("Data not retrieved.", data);
		assertEquals(
				"AccountDataTest.testGetOvernightExcess data doesn't match.",
				overnightExcess, data.getOvernightExcess(), .01);
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setOvernightExcess(double)}
	 * .
	 */
	@Test
	public final void testSetOvernightExcess() {
		AccountData data = null;

		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			overnightExcess = 2000.11;
			data = dao.findById(accountId);
			data.setOvernightExcess(overnightExcess);
			dao.update(data);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("testSetOvernightExcess Runtime exception");
		}

		session.close();

		data = getAccountData();
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testSetOvernightExcess data doesn't match.",
				overnightExcess, data.getOvernightExcess(), .01);
		logger.info("Finish testSetOvernightExcess.");
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getPermedForCADEquities()}
	 * .
	 */
	@Test
	public final void testGetPermedForCADEquities() {
		logger.info("Enter AccountDataTest.");

		AccountData data = getAccountData();

		assertNotNull("Data not retrieved.", data);
		assertEquals(
				"AccountDataTest.testGetPermedForCADEquities data doesn't match.",
				permedForCADEquities, data.getPermedForCADEquities());
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setPermedForCADEquities(java.lang.Boolean)}
	 * .
	 */
	@Test
	public final void testSetPermedForCADEquities() {
		AccountData data = null;

		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			permedForCADEquities = true;
			data = dao.findById(accountId);
			data.setPermedForCADEquities(permedForCADEquities);
			dao.update(data);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("testSetPermedForCADEquities Runtime exception");
		}

		session.close();

		data = getAccountData();
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testSetPermedForCADEquities data doesn't match.",
				permedForCADEquities, data.getPermedForCADEquities());
		logger.info("Finish testSetPermedForCADEquities.");
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getPermedForEquities()}
	 * .
	 */
	@Test
	public final void testGetPermedForEquities() {
		logger.info("Enter AccountDataTest.");

		AccountData data = getAccountData();

		assertNotNull("Data not retrieved.", data);
		assertEquals(
				"AccountDataTest.testGetPermedForEquities data doesn't match.",
				permedForEquities, data.getPermedForEquities());
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setPermedForEquities(java.lang.Boolean)}
	 * .
	 */
	@Test
	public final void testSetPermedForEquities() {
		AccountData data = null;

		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			permedForEquities = false;
			data = dao.findById(accountId);
			data.setPermedForEquities(permedForEquities);
			dao.update(data);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("testSetPermedForEquities Runtime exception");
		}

		session.close();

		data = getAccountData();
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testSetPermedForEquities data doesn't match.",
				permedForEquities, data.getPermedForEquities());
		logger.info("Finish testSetPermedForEquities.");
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getPermedForForex()}
	 * .
	 */
	@Test
	public final void testGetPermedForForex() {
		logger.info("Enter AccountDataTest.");

		AccountData data = getAccountData();

		assertNotNull("Data not retrieved.", data);
		assertEquals(
				"AccountDataTest.testGetPermedForForex data doesn't match.",
				permedForForex, data.getPermedForForex());
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setPermedForForex(java.lang.Boolean)}
	 * .
	 */
	@Test
	public final void testSetPermedForForex() {
		AccountData data = null;

		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			permedForForex = true;
			data = dao.findById(accountId);
			data.setPermedForForex(permedForForex);
			dao.update(data);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("testSetPermedForForex Runtime exception");
		}

		session.close();

		data = getAccountData();
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testSetPermedForForex data doesn't match.",
				permedForForex, data.getPermedForForex());
		logger.info("Finish testSetPermedForForex.");
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getPermedForFutures()}
	 * .
	 */
	@Test
	public final void testGetPermedForFutures() {
		logger.info("Enter AccountDataTest.");

		AccountData data = getAccountData();

		assertNotNull("Data not retrieved.", data);
		assertEquals(
				"AccountDataTest.testGetPermedForFutures data doesn't match.",
				permedForFutures, data.getPermedForFutures());
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setPermedForFutures(java.lang.Boolean)}
	 * .
	 */
	@Test
	public final void testSetPermedForFutures() {
		AccountData data = null;

		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			permedForFutures = false;
			data = dao.findById(accountId);
			data.setPermedForFutures(permedForFutures);
			dao.update(data);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("testSetPermedForFutures Runtime exception");
		}

		session.close();

		data = getAccountData();
		assertNotNull("Data not retrieved.", data);
		assertEquals(
				"AccountDataTest.testSetPermedForFutures data doesn't match.",
				permedForFutures, data.getPermedForFutures());
		logger.info("Finish testSetPermedForFutures.");
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getPermedForOptions()}
	 * .
	 */
	@Test
	public final void testGetPermedForOptions() {
		logger.info("Enter AccountDataTest.");

		AccountData data = getAccountData();

		assertNotNull("Data not retrieved.", data);
		assertEquals(
				"AccountDataTest.testGetPermedForOptions data doesn't match.",
				permedForOptions, data.getPermedForOptions());
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setPermedForOptions(java.lang.Boolean)}
	 * .
	 */
	@Test
	public final void testSetPermedForOptions() {
		AccountData data = null;

		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			permedForOptions = true;
			data = dao.findById(accountId);
			data.setPermedForOptions(permedForOptions);
			dao.update(data);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("testSetPermedForOptions Runtime exception");
		}

		session.close();

		data = getAccountData();
		assertNotNull("Data not retrieved.", data);
		assertEquals(
				"AccountDataTest.testSetPermedForOptions data doesn't match.",
				permedForOptions, data.getPermedForOptions());
		logger.info("Finish testSetPermedForOptions.");
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getRoutingId()}
	 * .
	 */
	@Test
	public final void testGetRoutingId() {
		logger.info("Enter AccountDataTest.");

		AccountData data = getAccountData();

		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetRoutingId data doesn't match.",
				routingId, data.getRoutingId());
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setRoutingId(java.lang.String)}
	 * .
	 */
	@Test
	public final void testSetRoutingId() {
		AccountData data = null;

		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			routingId = "routingId-2";
			data = dao.findById(accountId);
			data.setRoutingId(routingId);
			dao.update(data);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("testSetRoutingId Runtime exception");
		}

		session.close();

		data = getAccountData();
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testSetRoutingId data doesn't match.",
				routingId, data.getRoutingId());
		logger.info("Finish testSetRoutingId.");
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getSemiDelimited()}
	 * .
	 */
	@Test
	public final void testGetSemiDelimited() {
		logger.info("Enter AccountDataTest.");

		AccountData data = getAccountData();

		assertNotNull("Data not retrieved.", data);
		assertEquals(
				"AccountDataTest.testGetSemiDelimited data doesn't match.",
				semiDelimited, data.getSemiDelimited());
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setSemiDelimited(java.lang.String)}
	 * .
	 */
	@Test
	public final void testSetSemiDelimited() {
		AccountData data = null;

		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			semiDelimited = "semiDelimited-2";
			data = dao.findById(accountId);
			data.setSemiDelimited(semiDelimited);
			dao.update(data);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("testSetSemiDelimited Runtime exception");
		}

		session.close();

		data = getAccountData();
		assertNotNull("Data not retrieved.", data);
		assertEquals(
				"AccountDataTest.testGetSemiDelimited data doesn't match.",
				semiDelimited, data.getSemiDelimited());
		logger.info("Finish testSetSemiDelimited.");
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getSharesToday()}
	 * .
	 */
	@Test
	public final void testGetSharesToday() {
		logger.info("Enter AccountDataTest.");

		AccountData data = getAccountData();

		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetSharesToday data doesn't match.",
				sharesToday, data.getSharesToday());
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setSharesToday(long)}
	 * .
	 */
	@Test
	public final void testSetSharesToday() {
		AccountData data = null;

		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			sharesToday = 5000;
			data = dao.findById(accountId);
			data.setSharesToday(sharesToday);
			dao.update(data);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("testSetSharesToday Runtime exception");
		}

		session.close();

		data = getAccountData();
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testSetSharesToday data doesn't match.",
				sharesToday, data.getSharesToday());
		logger.info("Finish testSetSharesToday.");
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getTradesToday()}
	 * .
	 */
	@Test
	public final void testGetTradesToday() {
		logger.info("Enter AccountDataTest.");

		AccountData data = getAccountData();

		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetTradesToday data doesn't match.",
				tradesToday, data.getTradesToday());
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setTradesToday(long)}
	 * .
	 */
	@Test
	public final void testSetTradesToday() {
		AccountData data = null;

		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			tradesToday = 200;
			data = dao.findById(accountId);
			data.setTradesToday(tradesToday);
			dao.update(data);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("testSetTradesToday Runtime exception");
		}

		session.close();

		data = getAccountData();
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testSetTradesToday data doesn't match.",
				tradesToday, data.getTradesToday());
		logger.info("Finish testSetTradesToday.");
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getTimestamp()}
	 * .
	 */
	@Test
	public final void testGetTimestamp() {
		logger.info("Enter AccountDataTest.");

		AccountData data = getAccountData();

		assertNotNull("Data not retrieved.", data);
		logger.info("AccountDataTest.testGetTimestamp data: ",
				data.getTimestamp());
	}

	/**
	 * Test method for
	 * {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setTimestamp(java.sql.Timestamp)}
	 * .
	 */
	@Test
	public final void testUpdateTimestamp() {
		AccountData data = getAccountData();
		Timestamp timestamp = data.getTimestamp();

		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			eventType = "eventType-2";
 			data.setEventType(eventType);
			dao.update(data);
			session.flush(); 
			transaction.commit();
		} catch (RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("testUpdateTimestamp Runtime exception");
		}

		session.close();

		data = getAccountData();
		assertNotNull("Data not retrieved.", data);
		assertNotEquals("AccountDataTest.testUpdateTimestamp matches.",
				timestamp, data.getTimestamp());
		logger.info("Finish testUpdateTimestamp.");
	}

}
