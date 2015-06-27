package com.redpine.TradeDataAccess.AccountData.model;

import java.sql.Timestamp;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.Table;
import javax.persistence.Version;

@Entity
@Table(name = "AccountData")
public class AccountData {

	@GeneratedValue
	private String accountId;

	private String eventType;
	private String accountName;
	private long accountType;
	private String bank;
	private String baseCurrency;
	private String branch;
	private long cancelsToday;
	private double credit;
	private double currentEquity;
	private double currentExcess;
	private String customer;
	private double dailyRealizedPL;
	private double MMRMultiplier;
	private double MMRUsed;
	private double morningCash;
	private double morningEquity;
	private double morningExcess;
	private double overnightExcess;
	private Boolean permedForCADEquities;
	private Boolean permedForEquities;
	private Boolean permedForForex;
	private Boolean permedForFutures;
	private Boolean permedForOptions;
	private String routingId;
	private String semiDelimited;
	private long sharesToday;
	private long tradesToday;
	private Timestamp timestamp;
	
	
	/**
	 * @param accountId
	 * @param eventType
	 * @param accountName
	 * @param accountType
	 * @param bank
	 * @param baseCurrency
	 * @param branch
	 * @param cancelsToday
	 * @param credit
	 * @param currentEquity
	 * @param currentExcess
	 * @param customer
	 * @param dailyRealizedPL
	 * @param mMRMultiplier
	 * @param mMRUsed
	 * @param morningCash
	 * @param morningEquity
	 * @param morningExcess
	 * @param overnightExcess
	 * @param permedForCADEquities
	 * @param permedForEquities
	 * @param permedForForex
	 * @param permedForFutures
	 * @param permedForOptions
	 * @param routingId
	 * @param semiDelimited
	 * @param sharesToday
	 * @param tradesToday
	 */
	public AccountData(String accountId, String eventType, String accountName,
			long accountType, String bank, String baseCurrency, String branch,
			long cancelsToday, double credit, double currentEquity,
			double currentExcess, String customer, double dailyRealizedPL,
			double mMRMultiplier, double mMRUsed, double morningCash,
			double morningEquity, double morningExcess, double overnightExcess,
			Boolean permedForCADEquities, Boolean permedForEquities,
			Boolean permedForForex, Boolean permedForFutures,
			Boolean permedForOptions, String routingId, String semiDelimited,
			long sharesToday, long tradesToday) {
		super();
		this.accountId = accountId;
		this.eventType = eventType;
		this.accountName = accountName;
		this.accountType = accountType;
		this.bank = bank;
		this.baseCurrency = baseCurrency;
		this.branch = branch;
		this.cancelsToday = cancelsToday;
		this.credit = credit;
		this.currentEquity = currentEquity;
		this.currentExcess = currentExcess;
		this.customer = customer;
		this.dailyRealizedPL = dailyRealizedPL;
		MMRMultiplier = mMRMultiplier;
		MMRUsed = mMRUsed;
		this.morningCash = morningCash;
		this.morningEquity = morningEquity;
		this.morningExcess = morningExcess;
		this.overnightExcess = overnightExcess;
		this.permedForCADEquities = permedForCADEquities;
		this.permedForEquities = permedForEquities;
		this.permedForForex = permedForForex;
		this.permedForFutures = permedForFutures;
		this.permedForOptions = permedForOptions;
		this.routingId = routingId;
		this.semiDelimited = semiDelimited;
		this.sharesToday = sharesToday;
		this.tradesToday = tradesToday;
	}
	
	public AccountData(){
	}
	
	/**
	 * @return the accountId
	 */
	@Id
	@Column(name = "accountId", unique = true, nullable = false)
	public String getAccountId() {
		return accountId;
	}
	/**
	 * @param accountId the accountId to set
	 */
	@SuppressWarnings("unused")
	private void setAccountId(String accountId) {
		this.accountId = accountId;
	}
	/**
	 * @return the eventType
	 */
	public String getEventType() {
		return eventType;
	}
	/**
	 * @param eventType the eventType to set
	 */
	public void setEventType(String eventType) {
		this.eventType = eventType;
	}
	/**
	 * @return the accountName
	 */
	public String getAccountName() {
		return accountName;
	}
	/**
	 * @param accountName the accountName to set
	 */
	public void setAccountName(String accountName) {
		this.accountName = accountName;
	}
	/**
	 * @return the accountType
	 */
	public long getAccountType() {
		return accountType;
	}
	/**
	 * @param accountType the accountType to set
	 */
	public void setAccountType(long accountType) {
		this.accountType = accountType;
	}
	/**
	 * @return the bank
	 */
	public String getBank() {
		return bank;
	}
	/**
	 * @param bank the bank to set
	 */
	public void setBank(String bank) {
		this.bank = bank;
	}
	/**
	 * @return the baseCurrency
	 */
	public String getBaseCurrency() {
		return baseCurrency;
	}
	/**
	 * @param baseCurrency the baseCurrency to set
	 */
	public void setBaseCurrency(String baseCurrency) {
		this.baseCurrency = baseCurrency;
	}
	/**
	 * @return the branch
	 */
	public String getBranch() {
		return branch;
	}
	/**
	 * @param branch the branch to set
	 */
	public void setBranch(String branch) {
		this.branch = branch;
	}
	/**
	 * @return the cancelsToday
	 */
	public long getCancelsToday() {
		return cancelsToday;
	}
	/**
	 * @param cancelsToday the cancelsToday to set
	 */
	public void setCancelsToday(long cancelsToday) {
		this.cancelsToday = cancelsToday;
	}
	/**
	 * @return the credit
	 */
	public double getCredit() {
		return credit;
	}
	/**
	 * @param credit the credit to set
	 */
	public void setCredit(double credit) {
		this.credit = credit;
	}
	/**
	 * @return the currentEquity
	 */
	public double getCurrentEquity() {
		return currentEquity;
	}
	/**
	 * @param currentEquity the currentEquity to set
	 */
	public void setCurrentEquity(double currentEquity) {
		this.currentEquity = currentEquity;
	}
	/**
	 * @return the currentExcess
	 */
	public double getCurrentExcess() {
		return currentExcess;
	}
	/**
	 * @param currentExcess the currentExcess to set
	 */
	public void setCurrentExcess(double currentExcess) {
		this.currentExcess = currentExcess;
	}
	/**
	 * @return the customer
	 */
	public String getCustomer() {
		return customer;
	}
	/**
	 * @param customer the customer to set
	 */
	public void setCustomer(String customer) {
		this.customer = customer;
	}
	/**
	 * @return the dailyRealizedPL
	 */
	public double getDailyRealizedPL() {
		return dailyRealizedPL;
	}
	/**
	 * @param dailyRealizedPL the dailyRealizedPL to set
	 */
	public void setDailyRealizedPL(double dailyRealizedPL) {
		this.dailyRealizedPL = dailyRealizedPL;
	}
	/**
	 * @return the mMRMultiplier
	 */
	public double getMMRMultiplier() {
		return MMRMultiplier;
	}
	/**
	 * @param mMRMultiplier the mMRMultiplier to set
	 */
	public void setMMRMultiplier(double mMRMultiplier) {
		MMRMultiplier = mMRMultiplier;
	}
	/**
	 * @return the mMRUsed
	 */
	public double getMMRUsed() {
		return MMRUsed;
	}
	/**
	 * @param mMRUsed the mMRUsed to set
	 */
	public void setMMRUsed(double mMRUsed) {
		MMRUsed = mMRUsed;
	}
	/**
	 * @return the morningCash
	 */
	public double getMorningCash() {
		return morningCash;
	}
	/**
	 * @param morningCash the morningCash to set
	 */
	public void setMorningCash(double morningCash) {
		this.morningCash = morningCash;
	}
	/**
	 * @return the morningEquity
	 */
	public double getMorningEquity() {
		return morningEquity;
	}
	/**
	 * @param morningEquity the morningEquity to set
	 */
	public void setMorningEquity(double morningEquity) {
		this.morningEquity = morningEquity;
	}
	/**
	 * @return the morningExcess
	 */
	public double getMorningExcess() {
		return morningExcess;
	}
	/**
	 * @param morningExcess the morningExcess to set
	 */
	public void setMorningExcess(double morningExcess) {
		this.morningExcess = morningExcess;
	}
	/**
	 * @return the overnightExcess
	 */
	public double getOvernightExcess() {
		return overnightExcess;
	}
	/**
	 * @param overnightExcess the overnightExcess to set
	 */
	public void setOvernightExcess(double overnightExcess) {
		this.overnightExcess = overnightExcess;
	}
	/**
	 * @return the permedForCADEquities
	 */
	public Boolean getPermedForCADEquities() {
		return permedForCADEquities;
	}
	/**
	 * @param permedForCADEquities the permedForCADEquities to set
	 */
	public void setPermedForCADEquities(Boolean permedForCADEquities) {
		this.permedForCADEquities = permedForCADEquities;
	}
	/**
	 * @return the permedForEquities
	 */
	public Boolean getPermedForEquities() {
		return permedForEquities;
	}
	/**
	 * @param permedForEquities the permedForEquities to set
	 */
	public void setPermedForEquities(Boolean permedForEquities) {
		this.permedForEquities = permedForEquities;
	}
	/**
	 * @return the permedForForex
	 */
	public Boolean getPermedForForex() {
		return permedForForex;
	}
	/**
	 * @param permedForForex the permedForForex to set
	 */
	public void setPermedForForex(Boolean permedForForex) {
		this.permedForForex = permedForForex;
	}
	/**
	 * @return the permedForFutures
	 */
	public Boolean getPermedForFutures() {
		return permedForFutures;
	}
	/**
	 * @param permedForFutures the permedForFutures to set
	 */
	public void setPermedForFutures(Boolean permedForFutures) {
		this.permedForFutures = permedForFutures;
	}
	/**
	 * @return the permedForOptions
	 */
	public Boolean getPermedForOptions() {
		return permedForOptions;
	}
	/**
	 * @param permedForOptions the permedForOptions to set
	 */
	public void setPermedForOptions(Boolean permedForOptions) {
		this.permedForOptions = permedForOptions;
	}
	/**
	 * @return the routingId
	 */
	public String getRoutingId() {
		return routingId;
	}
	/**
	 * @param routingId the routingId to set
	 */
	public void setRoutingId(String routingId) {
		this.routingId = routingId;
	}
	/**
	 * @return the semiDelimited
	 */
	public String getSemiDelimited() {
		return semiDelimited;
	}
	/**
	 * @param semiDelimited the semiDelimited to set
	 */
	public void setSemiDelimited(String semiDelimited) {
		this.semiDelimited = semiDelimited;
	}
	/**
	 * @return the sharesToday
	 */
	public long getSharesToday() {
		return sharesToday;
	}
	/**
	 * @param sharesToday the sharesToday to set
	 */
	public void setSharesToday(long sharesToday) {
		this.sharesToday = sharesToday;
	}
	/**
	 * @return the tradesToday
	 */
	public long getTradesToday() {
		return tradesToday;
	}
	/**
	 * @param tradesToday the tradesToday to set
	 */
	public void setTradesToday(long tradesToday) {
		this.tradesToday = tradesToday;
	}
	/**
	 * @return the timestamp
	 */
	@Column(name = "timeStamp", 
	        updatable = false,
	        columnDefinition="TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP")
	public Timestamp getTimestamp() {
		return timestamp;
	}
	/**
	 * @param timestamp the timestamp to set
	 */
	@SuppressWarnings("unused")
	private void setTimestamp(Timestamp timestamp) {
		this.timestamp = timestamp;
	}
	@Version
	protected Integer version;


	public Integer getVersion() {
		return version;
	}

	public void setVersion(Integer version) {
		this.version = version;
	}
}
