package com.redpine.TradeDataAccess.model;


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
	private double timeStamp;
	private String symbol;
	private int size;
	private double price;
	private int time;
	private int jdate;
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

	public L1data(String symbol, int size, double price, int time, int jdate,
			double bid, double ask, int bidsize, int asksize, int volume) {
		this.symbol = symbol;
		this.size = size;
		this.price = price;
		this.time = time;
		this.jdate = jdate;
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
	@Column(name = "timeStamp", nullable = false, precision = 22, scale = 0)
	public double getTimeStamp() {
		return this.timeStamp;
	}

	/**
	 * @param timeStamp
	 */
	public void setTimeStamp(double timeStamp) {
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
	@Column(name = "time", nullable = false)
	public int getTime() {
		return this.time;
	}

	/**
	 * @param time
	 */
	@SuppressWarnings("unused")
	private void setTime(int time) {
		this.time = time;
	}

	/**
	 * @return
	 */
	@Column(name = "jdate", nullable = false)
	public int getJdate() {
		return this.jdate;
	}

	/**
	 * @param jdate
	 */
	@SuppressWarnings("unused")
	private void setJdate(int jdate) {
		this.jdate = jdate;
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
