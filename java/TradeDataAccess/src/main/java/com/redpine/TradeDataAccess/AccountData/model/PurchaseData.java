package com.redpine.TradeDataAccess.AccountData.model;

import java.sql.Time;
import java.util.Date;

import com.redpine.TradeDataAccess.Util.DataEnums.ExecutionType;
import com.redpine.TradeDataAccess.Util.DataEnums.TradeStatus;
import com.redpine.TradeDataAccess.Util.DataEnums.TradeType;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;
import javax.persistence.Version;

@Entity
@Table(name = "PurchaseData")
public class PurchaseData {
	private String accountId;
	private String symbol;
	private int size;
	private int sharesFilled;
	private double price;
	private double stopPrice;
	private double stopLowerPrice;
	private double stopUpperPrice;

	private double strikePrice;
	private Time timePlaced;
	private Time timeFilled;
	private Date date;

	private double gap;
    
	private TradeType typeTrade;
	private ExecutionType executionType;
	private TradeStatus status;

	private String orderNumber;
	private String errorMessage;
	private String reason;
	
	
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
	 * @return the size
	 */
	public int getSize() {
		return size;
	}
	/**
	 * @param size the size to set
	 */
	public void setSize(int size) {
		this.size = size;
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
	 * @return the stopPrice
	 */
	public double getStopPrice() {
		return stopPrice;
	}
	/**
	 * @param stopPrice the stopPrice to set
	 */
	public void setStopPrice(double stopPrice) {
		this.stopPrice = stopPrice;
	}
	/**
	 * @return the stopLowerPrice
	 */
	public double getStopLowerPrice() {
		return stopLowerPrice;
	}
	/**
	 * @param stopLowerPrice the stopLowerPrice to set
	 */
	public void setStopLowerPrice(double stopLowerPrice) {
		this.stopLowerPrice = stopLowerPrice;
	}
	/**
	 * @return the stopUpperPrice
	 */
	public double getStopUpperPrice() {
		return stopUpperPrice;
	}
	/**
	 * @param stopUpperPrice the stopUpperPrice to set
	 */
	public void setStopUpperPrice(double stopUpperPrice) {
		this.stopUpperPrice = stopUpperPrice;
	}
	/**
	 * @return the strikePrice
	 */
	public double getStrikePrice() {
		return strikePrice;
	}
	/**
	 * @param strikePrice the strikePrice to set
	 */
	public void setStrikePrice(double strikePrice) {
		this.strikePrice = strikePrice;
	}
	/**
	 * @return the timePlaced
	 */
	public Time getTimePlaced() {
		return timePlaced;
	}
	/**
	 * @param timePlaced the timePlaced to set
	 */
	public void setTimePlaced(Time timePlaced) {
		this.timePlaced = timePlaced;
	}
	/**
	 * @return the timeFilled
	 */
	public Time getTimeFilled() {
		return timeFilled;
	}
	/**
	 * @param timeFilled the timeFilled to set
	 */
	public void setTimeFilled(Time timeFilled) {
		this.timeFilled = timeFilled;
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
	 * @return the gap
	 */
	public double getGap() {
		return gap;
	}
	/**
	 * @param gap the gap to set
	 */
	public void setGap(double gap) {
		this.gap = gap;
	}
	/**
	 * @return the typeTrade
	 */
	public TradeType getTypeTrade() {
		return typeTrade;
	}
	/**
	 * @param typeTrade the typeTrade to set
	 */
	public void setTypeTrade(TradeType typeTrade) {
		this.typeTrade = typeTrade;
	}
	/**
	 * @return the executionType
	 */
	public ExecutionType getExecutionType() {
		return executionType;
	}
	/**
	 * @param executionType the executionType to set
	 */
	public void setExecutionType(ExecutionType executionType) {
		this.executionType = executionType;
	}
	/**
	 * @return the status
	 */
	public TradeStatus getStatus() {
		return status;
	}
	/**
	 * @param status the status to set
	 */
	public void setStatus(TradeStatus status) {
		this.status = status;
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
	 * @return the errorMessage
	 */
	public String getErrorMessage() {
		return errorMessage;
	}
	/**
	 * @param errorMessage the errorMessage to set
	 */
	public void setErrorMessage(String errorMessage) {
		this.errorMessage = errorMessage;
	}
	/**
	 * @return the reason
	 */
	public String getReason() {
		return reason;
	}
	/**
	 * @param reason the reason to set
	 */
	public void setReason(String reason) {
		this.reason = reason;
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
