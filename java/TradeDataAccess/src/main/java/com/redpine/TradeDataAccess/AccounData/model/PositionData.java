package com.redpine.TradeDataAccess.AccounData.model;

import javax.persistence.Entity;
import javax.persistence.Table;

@Entity
@Table(name = "PositionData")
public class PositionData {
	private String accountId;
	private int aggregatePosition;
	private int closableShares;
	private double commission;
	private int intradayPosition;
	private double intradayPrice;
	private double MMRPct;
	private double MMRUsed;
	private int overnightPosition;
	private double overnightPrice;
	private int pendingBuyShares;
	private int pendingSellShares;
	private double realizedPNL;
	private String symbol;	
	private String eventType;
	private String account;
	private String customer;
	/**
	 * @return the accountId
	 */
	public String getAccountId() {
		return accountId;
	}
	/**
	 * @param accountId the accountId to set
	 */
	public void setAccountId(String accountId) {
		this.accountId = accountId;
	}
	/**
	 * @return the aggregatePosition
	 */
	public int getAggregatePosition() {
		return aggregatePosition;
	}
	/**
	 * @param aggregatePosition the aggregatePosition to set
	 */
	public void setAggregatePosition(int aggregatePosition) {
		this.aggregatePosition = aggregatePosition;
	}
	/**
	 * @return the closableShares
	 */
	public int getClosableShares() {
		return closableShares;
	}
	/**
	 * @param closableShares the closableShares to set
	 */
	public void setClosableShares(int closableShares) {
		this.closableShares = closableShares;
	}
	/**
	 * @return the commission
	 */
	public double getCommission() {
		return commission;
	}
	/**
	 * @param commission the commission to set
	 */
	public void setCommission(double commission) {
		this.commission = commission;
	}
	/**
	 * @return the intradayPosition
	 */
	public int getIntradayPosition() {
		return intradayPosition;
	}
	/**
	 * @param intradayPosition the intradayPosition to set
	 */
	public void setIntradayPosition(int intradayPosition) {
		this.intradayPosition = intradayPosition;
	}
	/**
	 * @return the intradayPrice
	 */
	public double getIntradayPrice() {
		return intradayPrice;
	}
	/**
	 * @param intradayPrice the intradayPrice to set
	 */
	public void setIntradayPrice(double intradayPrice) {
		this.intradayPrice = intradayPrice;
	}
	/**
	 * @return the mMRPct
	 */
	public double getMMRPct() {
		return MMRPct;
	}
	/**
	 * @param mMRPct the mMRPct to set
	 */
	public void setMMRPct(double mMRPct) {
		MMRPct = mMRPct;
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
	 * @return the overnightPosition
	 */
	public int getOvernightPosition() {
		return overnightPosition;
	}
	/**
	 * @param overnightPosition the overnightPosition to set
	 */
	public void setOvernightPosition(int overnightPosition) {
		this.overnightPosition = overnightPosition;
	}
	/**
	 * @return the overnightPrice
	 */
	public double getOvernightPrice() {
		return overnightPrice;
	}
	/**
	 * @param overnightPrice the overnightPrice to set
	 */
	public void setOvernightPrice(double overnightPrice) {
		this.overnightPrice = overnightPrice;
	}
	/**
	 * @return the pendingBuyShares
	 */
	public int getPendingBuyShares() {
		return pendingBuyShares;
	}
	/**
	 * @param pendingBuyShares the pendingBuyShares to set
	 */
	public void setPendingBuyShares(int pendingBuyShares) {
		this.pendingBuyShares = pendingBuyShares;
	}
	/**
	 * @return the pendingSellShares
	 */
	public int getPendingSellShares() {
		return pendingSellShares;
	}
	/**
	 * @param pendingSellShares the pendingSellShares to set
	 */
	public void setPendingSellShares(int pendingSellShares) {
		this.pendingSellShares = pendingSellShares;
	}
	/**
	 * @return the realizedPNL
	 */
	public double getRealizedPNL() {
		return realizedPNL;
	}
	/**
	 * @param realizedPNL the realizedPNL to set
	 */
	public void setRealizedPNL(double realizedPNL) {
		this.realizedPNL = realizedPNL;
	}
	/**
	 * @return the symbol
	 */
	public String getSymbol() {
		return symbol;
	}
	/**
	 * @param symbol the symbol to set
	 */
	public void setSymbol(String symbol) {
		this.symbol = symbol;
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
	 * @return the account
	 */
	public String getAccount() {
		return account;
	}
	/**
	 * @param account the account to set
	 */
	public void setAccount(String account) {
		this.account = account;
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
	
	
}
