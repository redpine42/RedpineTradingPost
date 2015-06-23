package com.redpine.TradeDataAccess.AccountData.DAO.test;


import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import org.junit.ClassRule;
import org.junit.rules.ExternalResource;
import org.junit.runner.RunWith;
import org.junit.runners.Suite;
import org.junit.runners.Suite.SuiteClasses;

import com.redpine.TradeDataAccess.Util.HibernateUtil;

@RunWith(Suite.class)
@SuiteClasses({ OpenOrderDataDaoTest.class, OrderHistoryDaoTest.class, PositionDataDaoTest.class,  PurchaseDataDaoTest.class, AccountDataDaoTest.class})
public class HibernateTestSuite {

    static HibernateUtil util;
    static final Logger logger = LoggerFactory.getLogger(HibernateTestSuite.class);


	    // This is a static field.  Per the ClassRule documentation,
	    // to use a ClassRule we need a field that is "public, static,
	    // and a subtype of of TestRule."
	    // See http://junit.czweb.org/apidocs/org/junit/ClassRule.html
	    @ClassRule
	    public static ExternalResource testRule = new ExternalResource(){
	        @Override
	        protected void before() throws Throwable{
	        	logger.info("Create Hibernate Util (Session Factory)");
	            util = new HibernateUtil();
	        };

	        @Override
	        protected void after(){
	            // Nothing to do here in this case.
	            logger.info("Inside RuleSuite::ExternalResource::after.");
	        };
	    };
	}
