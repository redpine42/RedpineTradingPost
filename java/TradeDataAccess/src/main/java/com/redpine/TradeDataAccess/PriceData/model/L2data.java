package com.redpine.TradeDataAccess.PriceData.model;

import java.sql.Timestamp;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.EnumType;
import javax.persistence.Enumerated;
import javax.persistence.GeneratedValue;

import static javax.persistence.GenerationType.IDENTITY;

import javax.persistence.Id;
import javax.persistence.Table;

import com.redpine.TradeDataAccess.Util.DataEnums.OrderSide;



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
	private Timestamp timeStamp;
	private String symbol;
	private String mmid;
	private String source;
	private OrderSide marketside;
	private double price;
	private int size;
	private Timestamp recordTime;
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
	public L2data(String symbol, String mmid, String source, OrderSide marketside,
			double price, int size, Timestamp recordTime, byte closed) {
		this.symbol = symbol;
		this.mmid = mmid;
		this.source = source;
		this.marketside = marketside;
		this.price = price;
		this.size = size;
		this.recordTime = recordTime;
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
	@Column(name = "timeStamp", 
	        updatable = false,
	        columnDefinition="TIMESTAMP DEFAULT CURRENT_TIMESTAMP")
	public Timestamp getTimeStamp() {
		return this.timeStamp;
	}

	@SuppressWarnings("unused")
	private void setTimeStamp(Timestamp timeStamp) {
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
	@Enumerated(EnumType.ORDINAL)
	@Column(name = "marketside", nullable = false)
	public OrderSide getMarketside() {
		return this.marketside;
	}

	/**
	 * @param marketside
	 */
	@SuppressWarnings("unused")
	private void setMarketside(OrderSide marketside) {
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
	 * @return int
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
