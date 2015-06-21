package com.redpine.TradeDataAccess.AccountData.model;

import java.util.Date;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;

@Entity
@Table(name = "OrderHistoryData")
public class OrderHistoryData {
	private String accountId;
	private String eventType;
	private String account;
	private String customer;
	private String buySell;
	private int capacity;
	private int contractsAhead;
	private String date;
	private double discPrice;
	private int displayQuantity;
	private String event;
	private int execId;
	private String message;
	private String orderNumber;
	private int orderType;
	private String origTraderId;
	private String prefMMID;
	private double price;
	private int quantity;
	private String remoteId;
	private String route;
	private int sharesFilled;
	private double stopLimit;
	private String symbol;
	private Date time;
	private int timeInForce;
	private String token;
	private String traderId;
	private int volumeType;
	private int execType;
	
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
	public void setAccountId(String accountId) {
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
	/**
	 * @return the buySell
	 */
	public String getBuySell() {
		return buySell;
	}
	/**
	 * @param buySell the buySell to set
	 */
	public void setBuySell(String buySell) {
		this.buySell = buySell;
	}
	/**
	 * @return the capacity
	 */
	public int getCapacity() {
		return capacity;
	}
	/**
	 * @param capacity the capacity to set
	 */
	public void setCapacity(int capacity) {
		this.capacity = capacity;
	}
	/**
	 * @return the contractsAhead
	 */
	public int getContractsAhead() {
		return contractsAhead;
	}
	/**
	 * @param contractsAhead the contractsAhead to set
	 */
	public void setContractsAhead(int contractsAhead) {
		this.contractsAhead = contractsAhead;
	}
	/**
	 * @return the date
	 */
	public String getDate() {
		return date;
	}
	/**
	 * @param date the date to set
	 */
	public void setDate(String date) {
		this.date = date;
	}
	/**
	 * @return the discPrice
	 */
	public double getDiscPrice() {
		return discPrice;
	}
	/**
	 * @param discPrice the discPrice to set
	 */
	public void setDiscPrice(double discPrice) {
		this.discPrice = discPrice;
	}
	/**
	 * @return the displayQuantity
	 */
	public int getDisplayQuantity() {
		return displayQuantity;
	}
	/**
	 * @param displayQuantity the displayQuantity to set
	 */
	public void setDisplayQuantity(int displayQuantity) {
		this.displayQuantity = displayQuantity;
	}
	/**
	 * @return the event
	 */
	public String getEvent() {
		return event;
	}
	/**
	 * @param event the event to set
	 */
	public void setEvent(String event) {
		this.event = event;
	}
	/**
	 * @return the execId
	 */
	public int getExecId() {
		return execId;
	}
	/**
	 * @param execId the execId to set
	 */
	public void setExecId(int execId) {
		this.execId = execId;
	}
	/**
	 * @return the message
	 */
	public String getMessage() {
		return message;
	}
	/**
	 * @param message the message to set
	 */
	public void setMessage(String message) {
		this.message = message;
	}
	/**
	 * @return the orderNumber
	 */
	public String getOrderNumber() {
		return orderNumber;
	}
	/**
	 * @param orderNumber the orderNumber to set
	 */
	public void setOrderNumber(String orderNumber) {
		this.orderNumber = orderNumber;
	}
	/**
	 * @return the orderType
	 */
	public int getOrderType() {
		return orderType;
	}
	/**
	 * @param orderType the orderType to set
	 */
	public void setOrderType(int orderType) {
		this.orderType = orderType;
	}
	/**
	 * @return the origTraderId
	 */
	public String getOrigTraderId() {
		return origTraderId;
	}
	/**
	 * @param origTraderId the origTraderId to set
	 */
	public void setOrigTraderId(String origTraderId) {
		this.origTraderId = origTraderId;
	}
	/**
	 * @return the prefMMID
	 */
	public String getPrefMMID() {
		return prefMMID;
	}
	/**
	 * @param prefMMID the prefMMID to set
	 */
	public void setPrefMMID(String prefMMID) {
		this.prefMMID = prefMMID;
	}
	/**
	 * @return the price
	 */
	public double getPrice() {
		return price;
	}
	/**
	 * @param price the price to set
	 */
	public void setPrice(double price) {
		this.price = price;
	}
	/**
	 * @return the quantity
	 */
	public int getQuantity() {
		return quantity;
	}
	/**
	 * @param quantity the quantity to set
	 */
	public void setQuantity(int quantity) {
		this.quantity = quantity;
	}
	/**
	 * @return the remoteId
	 */
	public String getRemoteId() {
		return remoteId;
	}
	/**
	 * @param remoteId the remoteId to set
	 */
	public void setRemoteId(String remoteId) {
		this.remoteId = remoteId;
	}
	/**
	 * @return the route
	 */
	public String getRoute() {
		return route;
	}
	/**
	 * @param route the route to set
	 */
	public void setRoute(String route) {
		this.route = route;
	}
	/**
	 * @return the sharesFilled
	 */
	public int getSharesFilled() {
		return sharesFilled;
	}
	/**
	 * @param sharesFilled the sharesFilled to set
	 */
	public void setSharesFilled(int sharesFilled) {
		this.sharesFilled = sharesFilled;
	}
	/**
	 * @return the stopLimit
	 */
	public double getStopLimit() {
		return stopLimit;
	}
	/**
	 * @param stopLimit the stopLimit to set
	 */
	public void setStopLimit(double stopLimit) {
		this.stopLimit = stopLimit;
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
	 * @return the time
	 */
	public Date getTime() {
		return time;
	}
	/**
	 * @param time the time to set
	 */
	public void setTime(Date time) {
		this.time = time;
	}
	/**
	 * @return the timeInForce
	 */
	public int getTimeInForce() {
		return timeInForce;
	}
	/**
	 * @param timeInForce the timeInForce to set
	 */
	public void setTimeInForce(int timeInForce) {
		this.timeInForce = timeInForce;
	}
	/**
	 * @return the token
	 */
	public String getToken() {
		return token;
	}
	/**
	 * @param token the token to set
	 */
	public void setToken(String token) {
		this.token = token;
	}
	/**
	 * @return the traderId
	 */
	public String getTraderId() {
		return traderId;
	}
	/**
	 * @param traderId the traderId to set
	 */
	public void setTraderId(String traderId) {
		this.traderId = traderId;
	}
	/**
	 * @return the volumeType
	 */
	public int getVolumeType() {
		return volumeType;
	}
	/**
	 * @param volumeType the volumeType to set
	 */
	public void setVolumeType(int volumeType) {
		this.volumeType = volumeType;
	}
	/**
	 * @return the execType
	 */
	public int getExecType() {
		return execType;
	}
	/**
	 * @param execType the execType to set
	 */
	public void setExecType(int execType) {
		this.execType = execType;
	}

}
