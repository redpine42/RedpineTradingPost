package com.redpine.TradeDataAccess.PriceData.model;


import java.sql.Timestamp;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;

import static javax.persistence.GenerationType.IDENTITY;

import javax.persistence.Id;
import javax.persistence.Table;

/**
 * 
 */
@Entity
@Table(name = "l1data")
public class L1data implements java.io.Serializable {

	/**
	 * 
	 */
	private static final long serialVersionUID = 5629249431166308720L;
	
	private Integer seq;
	private Timestamp timeStamp;
	private String symbol;
	private int size;
	private double price;
	private Timestamp recordTime;
	private double bid;
	private double ask;
	private int bidsize;
	private int asksize;
	private int volume;

	/**
	 * 
	 */
	public L1data() {
	}

	public L1data(String symbol, int size, double price, Timestamp recordTime,
			double bid, double ask, int bidsize, int asksize, int volume) {
		this.symbol = symbol;
		this.size = size;
		this.price = price;
		this.recordTime = recordTime;
		this.bid = bid;
		this.ask = ask;
		this.bidsize = bidsize;
		this.asksize = asksize;
		this.volume = volume;
	}

	/**
	 * @return
	 */
	@Id
	@GeneratedValue(strategy = IDENTITY)
	@Column(name = "seq", unique = true, nullable = false)
	public Integer getSeq() {
		return this.seq;
	}

	/**
	 * @param seq
	 */
	@SuppressWarnings("unused")
	private void setSeq(Integer seq) {
		this.seq = seq;
	}

	/**
	 * @return
	 */
	@Column(name = "timeStamp", 
	        updatable = false,
	        columnDefinition="TIMESTAMP(6) DEFAULT CURRENT_TIMESTAMP(6)")
	public Timestamp getTimeStamp() {
		return this.timeStamp;
	}

	/**
	 * @param timeStamp
	 */
	@SuppressWarnings("unused")
	private void setTimeStamp(Timestamp timeStamp) {
		this.timeStamp = timeStamp;

	}

	/**
	 * @return
	 */
	@Column(name = "Symbol", nullable = false, length = 7)
	public String getSymbol() {
		return this.symbol;
	}

	/**
	 * @param symbol
	 */
	@SuppressWarnings("unused")
	private void setSymbol(String symbol) {
		this.symbol = symbol;
	}

	/**
	 * @return
	 */
	@Column(name = "size", nullable = false)
	public int getSize() {
		return this.size;
	}

	/**
	 * @param size
	 */
	@SuppressWarnings("unused")
	private void setSize(int size) {
		this.size = size;
	}

	/**
	 * @return
	 */
	@Column(name = "price", nullable = false, precision = 22, scale = 0)
	public double getPrice() {
		return this.price;
	}

	/**
	 * @param price
	 */
	@SuppressWarnings("unused")
	private void setPrice(double price) {
		this.price = price;
	}

	/**
	 * @return
	 */
	@Column(name = "recordTime", nullable = false)
	public Timestamp getRecordTime() {
		return this.recordTime;
	}

	/**
	 * @param time
	 */
	@SuppressWarnings("unused")
	private void setRecordTime(Timestamp recordTime) {
		this.recordTime = recordTime;
	}

	/**
	 * @return
	 */
	@Column(name = "bid", nullable = false, precision = 22, scale = 0)
	public double getBid() {
		return this.bid;
	}

	/**
	 * @param bid
	 */
	@SuppressWarnings("unused")
	private void setBid(double bid) {
		this.bid = bid;
	}

	/**
	 * @return
	 */
	@Column(name = "ask", nullable = false, precision = 22, scale = 0)
	public double getAsk() {
		return this.ask;
	}

	/**
	 * @param ask
	 */
	@SuppressWarnings("unused")
	private void setAsk(double ask) {
		this.ask = ask;
	}

	/**
	 * @return
	 */
	@Column(name = "bidsize", nullable = false)
	public int getBidsize() {
		return this.bidsize;
	}

	/**
	 * @param bidsize
	 */
	@SuppressWarnings("unused")
	private void setBidsize(int bidsize) {
		this.bidsize = bidsize;
	}

	/**
	 * @return
	 */
	@Column(name = "asksize", nullable = false)
	public int getAsksize() {
		return this.asksize;
	}

	/**
	 * @param asksize
	 */
	@SuppressWarnings("unused")
	private void setAsksize(int asksize) {
		this.asksize = asksize;
	}

	/**
	 * @return
	 */
	@Column(name = "volume", nullable = false)
	public int getVolume() {
		return this.volume;
	}

	/**
	 * @param volume
	 */
	@SuppressWarnings("unused")
	private void setVolume(int volume) {
		this.volume = volume;
	}

}
