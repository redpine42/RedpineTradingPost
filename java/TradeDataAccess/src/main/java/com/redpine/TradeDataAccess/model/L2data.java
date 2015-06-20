package com.redpine.TradeDataAccess.model;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;

import static javax.persistence.GenerationType.IDENTITY;

import javax.persistence.Id;
import javax.persistence.Table;



/**
 * Persistence class for L2 Market Data.
 * 
 * @author dbrown
 *
 */
@Entity
@Table(name = "l2data")
public class L2data implements java.io.Serializable {

	/**
	 * 
	 */
	private static final long serialVersionUID = -7611100195402650868L;
	
	private Integer seq;
	private double timeStamp;
	private String symbol;
	private String mmid;
	private String source;
	private byte marketside;
	private double price;
	private int size;
	private int jdate;
	private int time;
	private byte closed;

	public L2data() {
	}

	/**
	 * @param symbol
	 * @param mmid
	 * @param source
	 * @param marketside
	 * @param price
	 * @param size
	 * @param jdate
	 * @param time
	 * @param closed
	 */
	public L2data(String symbol, String mmid, String source, byte marketside,
			double price, int size, int jdate, int time, byte closed) {
		this.symbol = symbol;
		this.mmid = mmid;
		this.source = source;
		this.marketside = marketside;
		this.price = price;
		this.size = size;
		this.jdate = jdate;
		this.time = time;
		this.closed = closed;
	}

	/**
	 * Returns the sequence number for this row (Primary Key).
	 * 
	 * @return Integer
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
	 * Returns the timestamp for when this row was created.
	 * 
	 * @return double
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
	 * Returns the Symbol for this row.
	 * 
	 * @return String
	 */
	@Column(name = "symbol", nullable = false, length = 8)
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
	 * Returns the Market Maker Id
	 * 
	 * @return String
	 */
	@Column(name = "mmid", nullable = false, length = 20)
	public String getMmid() {
		return this.mmid;
	}

	/**
	 * @param mmid
	 */
	@SuppressWarnings("unused")
	private void setMmid(String mmid) {
		this.mmid = mmid;
	}

	/**
	 * Source for data.
	 * 
	 * @return String
	 */
	@Column(name = "source", nullable = false, length = 5)
	public String getSource() {
		return this.source;
	}

	/**
	 * @param source
	 */
	@SuppressWarnings("unused")
	private void setSource(String source) {
		this.source = source;
	}

	/**
	 * Bid or ask.
	 * 
	 * @return byte
	 */
	@Column(name = "marketside", nullable = false)
	public byte getMarketside() {
		return this.marketside;
	}

	/**
	 * @param marketside
	 */
	@SuppressWarnings("unused")
	private void setMarketside(byte marketside) {
		this.marketside = marketside;
	}

	/**
	 * Price for this quote.
	 * 
	 * @return double
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
	 * Return size of quote.
	 * 
	 * @return int
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
	 * Integer day and year of quote.
	 * 
	 * @return int
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
	 * @return int
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
	 * Returns whether quote is closed.
	 * 
	 * @return byte
	 */
	@Column(name = "closed", nullable = false)
	public byte getClosed() {
		return this.closed;
	}

	/**
	 * @param closed
	 */
	public void setClosed(byte closed) {
		this.closed = closed;
	}

}
