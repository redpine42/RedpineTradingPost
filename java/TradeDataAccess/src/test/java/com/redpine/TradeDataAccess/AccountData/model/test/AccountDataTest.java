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
	private static double morningEquity= 1000.15;
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
				accountType, bank, baseCurrency, branch,
				cancelsToday, credit, currentEquity,
				currentExcess, customer, dailyRealizedPL,
				MMRMultiplier, MMRUsed, morningCash,
				morningEquity, morningExcess, overnightExcess,
				permedForCADEquities, permedForEquities,
				permedForForex, permedForFutures,
				permedForOptions, routingId, semiDelimited,
				sharesToday, tradesToday);
		AccountDataDao dao = new AccountDataDao();
		Session session = dao.openCurrentSession();
		Transaction transaction = null;
		try {
			transaction = session.beginTransaction();
			dao.persist(data);
			transaction.commit();
		}
		catch(RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("setUpBeforeClass Runtime exception");
		}

		session.clear();
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
			transaction.commit();
		}
		catch(RuntimeException e) {
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
			transaction.commit();
		}
		catch(RuntimeException e) {
			transaction.rollback();
			e.printStackTrace();
			fail("getAccountData Runtime exception");
		}
		session.close();
		
		return data;
	}
	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getAccountId()}.
	 */
	@Test
	public final void testGetAccountId() {
		logger.info("Enter AccountDataTest.");
		
		AccountData data = getAccountData();
		
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetAccountId data doesn't match.", accountId, data.getAccountId());
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getEventType()}.
	 */
	@Test
	public final void testGetEventType() {
		logger.info("Enter AccountDataTest.");
		
		AccountData data = getAccountData();
		
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetEventType data doesn't match.", eventType, data.getEventType());	
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setEventType(java.lang.String)}.
	 */
	@Test
	public final void testSetEventType() {
		fail("Not yet implemented"); // TODO
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getAccountName()}.
	 */
	@Test
	public final void testGetAccountName() {
		logger.info("Enter AccountDataTest.");
		
		AccountData data = getAccountData();
		
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetAccountName data doesn't match.", accountName, data.getAccountName());
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setAccountName(java.lang.String)}.
	 */
	@Test
	public final void testSetAccountName() {
		fail("Not yet implemented"); // TODO
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getAccountType()}.
	 */
	@Test
	public final void testGetAccountType() {
			logger.info("Enter AccountDataTest.");
		
		AccountData data = getAccountData();
		
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetAccountType data doesn't match.", accountType, data.getAccountType());
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setAccountType(long)}.
	 */
	@Test
	public final void testSetAccountType() {
		fail("Not yet implemented"); // TODO
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getBank()}.
	 */
	@Test
	public final void testGetBank() {
		logger.info("Enter AccountDataTest.");
		
		AccountData data = getAccountData();
		
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetBank data doesn't match.", bank, data.getBank());
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setBank(java.lang.String)}.
	 */
	@Test
	public final void testSetBank() {
		fail("Not yet implemented"); // TODO
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getBaseCurrency()}.
	 */
	@Test
	public final void testGetBaseCurrency() {
		logger.info("Enter AccountDataTest.");
		
		AccountData data = getAccountData();
		
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetBaseCurrency data doesn't match.", baseCurrency, data.getBaseCurrency());
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setBaseCurrency(java.lang.String)}.
	 */
	@Test
	public final void testSetBaseCurrency() {
		fail("Not yet implemented"); // TODO
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getBranch()}.
	 */
	@Test
	public final void testGetBranch() {
		logger.info("Enter AccountDataTest.");
		
		AccountData data = getAccountData();
		
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetBranch data doesn't match.", branch, data.getBranch());
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setBranch(java.lang.String)}.
	 */
	@Test
	public final void testSetBranch() {
		fail("Not yet implemented"); // TODO
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getCancelsToday()}.
	 */
	@Test
	public final void testGetCancelsToday() {
		logger.info("Enter AccountDataTest.");
		
		AccountData data = getAccountData();
		
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetCancelsToday data doesn't match.", cancelsToday, data.getCancelsToday());	
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setCancelsToday(long)}.
	 */
	@Test
	public final void testSetCancelsToday() {
		fail("Not yet implemented"); // TODO
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getCredit()}.
	 */
	@Test
	public final void testGetCredit() {
		logger.info("Enter AccountDataTest.");
		
		AccountData data = getAccountData();
		
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetCredit data doesn't match.", credit, data.getCredit(), .01);
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setCredit(double)}.
	 */
	@Test
	public final void testSetCredit() {
		fail("Not yet implemented"); // TODO
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getCurrentEquity()}.
	 */
	@Test
	public final void testGetCurrentEquity() {
		logger.info("Enter AccountDataTest.");
		
		AccountData data = getAccountData();
		
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetCurrentEquity data doesn't match.", currentEquity, data.getCurrentEquity(), .01);
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setCurrentEquity(double)}.
	 */
	@Test
	public final void testSetCurrentEquity() {
		fail("Not yet implemented"); // TODO
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getCurrentExcess()}.
	 */
	@Test
	public final void testGetCurrentExcess() {
		logger.info("Enter AccountDataTest.");
		
		AccountData data = getAccountData();
		
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetCurrentExcess data doesn't match.", currentExcess, data.getCurrentExcess(), .01);
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setCurrentExcess(double)}.
	 */
	@Test
	public final void testSetCurrentExcess() {
		fail("Not yet implemented"); // TODO
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getCustomer()}.
	 */
	@Test
	public final void testGetCustomer() {
		logger.info("Enter AccountDataTest.");
		
		AccountData data = getAccountData();
		
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetCustomer data doesn't match.", customer, data.getCustomer());
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setCustomer(java.lang.String)}.
	 */
	@Test
	public final void testSetCustomer() {
		fail("Not yet implemented"); // TODO
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getDailyRealizedPL()}.
	 */
	@Test
	public final void testGetDailyRealizedPL() {
		logger.info("Enter AccountDataTest.");
		
		AccountData data = getAccountData();
		
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetDailyRealizedPL data doesn't match.", dailyRealizedPL, data.getDailyRealizedPL(), .01);
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setDailyRealizedPL(double)}.
	 */
	@Test
	public final void testSetDailyRealizedPL() {
		fail("Not yet implemented"); // TODO
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getMMRMultiplier()}.
	 */
	@Test
	public final void testGetMMRMultiplier() {
		logger.info("Enter AccountDataTest.");
		
		AccountData data = getAccountData();
		
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetMMRMultiplier data doesn't match.", MMRMultiplier, data.getMMRMultiplier(), .01);
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setMMRMultiplier(double)}.
	 */
	@Test
	public final void testSetMMRMultiplier() {
		fail("Not yet implemented"); // TODO
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getMMRUsed()}.
	 */
	@Test
	public final void testGetMMRUsed() {
		logger.info("Enter AccountDataTest.");
		
		AccountData data = getAccountData();
		
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetMMRUsed data doesn't match.", MMRUsed, data.getMMRUsed(), .01);
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setMMRUsed(double)}.
	 */
	@Test
	public final void testSetMMRUsed() {
		fail("Not yet implemented"); // TODO
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getMorningCash()}.
	 */
	@Test
	public final void testGetMorningCash() {
		logger.info("Enter AccountDataTest.");
		
		AccountData data = getAccountData();
		
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetMorningCash data doesn't match.", morningCash, data.getMorningCash(), .01);
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setMorningCash(double)}.
	 */
	@Test
	public final void testSetMorningCash() {
		fail("Not yet implemented"); // TODO
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getMorningEquity()}.
	 */
	@Test
	public final void testGetMorningEquity() {
		logger.info("Enter AccountDataTest.");
		
		AccountData data = getAccountData();
		
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetMorningEquity data doesn't match.", morningEquity, data.getMorningEquity(), .01);
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setMorningEquity(double)}.
	 */
	@Test
	public final void testSetMorningEquity() {
		fail("Not yet implemented"); // TODO
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getMorningExcess()}.
	 */
	@Test
	public final void testGetMorningExcess() {
		logger.info("Enter AccountDataTest.");
		
		AccountData data = getAccountData();
		
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetMorningExcess data doesn't match.", morningExcess, data.getMorningExcess(), .01);
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setMorningExcess(double)}.
	 */
	@Test
	public final void testSetMorningExcess() {
		fail("Not yet implemented"); // TODO
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getOvernightExcess()}.
	 */
	@Test
	public final void testGetOvernightExcess() {
		logger.info("Enter AccountDataTest.");
		
		AccountData data = getAccountData();
		
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetOvernightExcess data doesn't match.", overnightExcess, data.getOvernightExcess(), .01);
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setOvernightExcess(double)}.
	 */
	@Test
	public final void testSetOvernightExcess() {
		fail("Not yet implemented"); // TODO
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getPermedForCADEquities()}.
	 */
	@Test
	public final void testGetPermedForCADEquities() {
		logger.info("Enter AccountDataTest.");
		
		AccountData data = getAccountData();
		
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetPermedForCADEquities data doesn't match.", permedForCADEquities, data.getPermedForCADEquities());
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setPermedForCADEquities(java.lang.Boolean)}.
	 */
	@Test
	public final void testSetPermedForCADEquities() {
		fail("Not yet implemented"); // TODO
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getPermedForEquities()}.
	 */
	@Test
	public final void testGetPermedForEquities() {
		logger.info("Enter AccountDataTest.");
		
		AccountData data = getAccountData();
		
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetPermedForEquities data doesn't match.", permedForEquities, data.getPermedForEquities());
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setPermedForEquities(java.lang.Boolean)}.
	 */
	@Test
	public final void testSetPermedForEquities() {
		fail("Not yet implemented"); // TODO
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getPermedForForex()}.
	 */
	@Test
	public final void testGetPermedForForex() {
		logger.info("Enter AccountDataTest.");
		
		AccountData data = getAccountData();
		
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetPermedForForex data doesn't match.", permedForForex, data.getPermedForForex());
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setPermedForForex(java.lang.Boolean)}.
	 */
	@Test
	public final void testSetPermedForForex() {
		fail("Not yet implemented"); // TODO
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getPermedForFutures()}.
	 */
	@Test
	public final void testGetPermedForFutures() {
		logger.info("Enter AccountDataTest.");
		
		AccountData data = getAccountData();
		
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetPermedForFutures data doesn't match.", permedForFutures, data.getPermedForFutures());
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setPermedForFutures(java.lang.Boolean)}.
	 */
	@Test
	public final void testSetPermedForFutures() {
		fail("Not yet implemented"); // TODO
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getPermedForOptions()}.
	 */
	@Test
	public final void testGetPermedForOptions() {
		logger.info("Enter AccountDataTest.");
		
		AccountData data = getAccountData();
		
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetPermedForOptions data doesn't match.", permedForOptions, data.getPermedForOptions());
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setPermedForOptions(java.lang.Boolean)}.
	 */
	@Test
	public final void testSetPermedForOptions() {
		fail("Not yet implemented"); // TODO
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getRoutingId()}.
	 */
	@Test
	public final void testGetRoutingId() {
		logger.info("Enter AccountDataTest.");
		
		AccountData data = getAccountData();
		
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetRoutingId data doesn't match.", routingId, data.getRoutingId());
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setRoutingId(java.lang.String)}.
	 */
	@Test
	public final void testSetRoutingId() {
		fail("Not yet implemented"); // TODO
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getSemiDelimited()}.
	 */
	@Test
	public final void testGetSemiDelimited() {
		logger.info("Enter AccountDataTest.");
		
		AccountData data = getAccountData();
		
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetSemiDelimited data doesn't match.", semiDelimited, data.getSemiDelimited());
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setSemiDelimited(java.lang.String)}.
	 */
	@Test
	public final void testSetSemiDelimited() {
		fail("Not yet implemented"); // TODO
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getSharesToday()}.
	 */
	@Test
	public final void testGetSharesToday() {
		logger.info("Enter AccountDataTest.");
		
		AccountData data = getAccountData();
		
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetSharesToday data doesn't match.", sharesToday, data.getSharesToday());
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setSharesToday(long)}.
	 */
	@Test
	public final void testSetSharesToday() {
		fail("Not yet implemented"); // TODO
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getTradesToday()}.
	 */
	@Test
	public final void testGetTradesToday() {
		logger.info("Enter AccountDataTest.");
		
		AccountData data = getAccountData();
		
		assertNotNull("Data not retrieved.", data);
		assertEquals("AccountDataTest.testGetTradesToday data doesn't match.", tradesToday, data.getTradesToday());
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setTradesToday(long)}.
	 */
	@Test
	public final void testSetTradesToday() {
		fail("Not yet implemented"); // TODO
	}

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#getTimestamp()}.
	 */
	@Test
	public final void testGetTimestamp() {
		logger.info("Enter AccountDataTest.");
		
		AccountData data = getAccountData();
		
		assertNotNull("Data not retrieved.", data);
		logger.info("AccountDataTest.testGetTimestamp data: ", data.getTimestamp());
	}
	

	/**
	 * Test method for {@link com.redpine.TradeDataAccess.AccountData.model.AccountData#setTimestamp(java.sql.Timestamp)}.
	 */
	@Test
	public final void testUpdateTimestamp() {
		fail("Not yet implemented"); // TODO
	}

}
