package com.redpine.TradeDataAccess.AccounData.model;

import java.sql.Time;
import java.util.Date;

import javax.persistence.Entity;
import javax.persistence.Table;

@Entity
@Table(name = "OpenOrderData")
public class OpenOrderData {
	private String accountId;
	private String eventType;
	private String account;
	private String customer;
	private Boolean acknowledged;
	private String buySell;
	private String currentEvent;
	private Date date;
	private String orderNumber;
	private int orderType;
	private String prefMMID;
	private double price;
	private int quantity;
	private Boolean replaceable;
	private String route;
	private int sharesFilled;
	private double stopLimit;
	private String symbol;
	private Time time;
	private int timeInForce;
	private String token;
	private String traderId;
	private double trailingOffset;
	private int volumeType;
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
	 * @return the acknowledged
	 */
	public Boolean getAcknowledged() {
		return acknowledged;
	}
	/**
	 * @param acknowledged the acknowledged to set
	 */
	public void setAcknowledged(Boolean acknowledged) {
		this.acknowledged = acknowledged;
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
	 * @return the currentEvent
	 */
	public String getCurrentEvent() {
		return currentEvent;
	}
	/**
	 * @param currentEvent the currentEvent to set
	 */
	public void setCurrentEvent(String currentEvent) {
		this.currentEvent = currentEvent;
	}
	/**
	 * @return the date
	 */
	public Date getDate() {
		return date;
	}
	/**
	 * @param date the date to set
	 */
	public void setDate(Date date) {
		this.date = date;
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
	 * @return the replaceable
	 */
	public Boolean getReplaceable() {
		return replaceable;
	}
	/**
	 * @param replaceable the replaceable to set
	 */
	public void setReplaceable(Boolean replaceable) {
		this.replaceable = replaceable;
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
	public Time getTime() {
		return time;
	}
	/**
	 * @param time the time to set
	 */
	public void setTime(Time time) {
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
	 * @return the trailingOffset
	 */
	public double getTrailingOffset() {
		return trailingOffset;
	}
	/**
	 * @param trailingOffset the trailingOffset to set
	 */
	public void setTrailingOffset(double trailingOffset) {
		this.trailingOffset = trailingOffset;
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
	
	
}
