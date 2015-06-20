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
	private float timeStamp;
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

	@Id
	@GeneratedValue(strategy = IDENTITY)
	@Column(name = "seq", unique = true, nullable = false)
	public Integer getSeq() {
		return this.seq;
	}

	public void setSeq(Integer seq) {
		this.seq = seq;
	}

	@Column(name = "timeStamp", nullable = false, precision = 12, scale = 0)
	public float getTimeStamp() {
		return this.timeStamp;
	}

	public void setTimeStamp(float timeStamp) {
		this.timeStamp = timeStamp;
	}

	@Column(name = "Symbol", nullable = false, length = 7)
	public String getSymbol() {
		return this.symbol;
	}

	public void setSymbol(String symbol) {
		this.symbol = symbol;
	}

	@Column(name = "size", nullable = false)
	public int getSize() {
		return this.size;
	}

	public void setSize(int size) {
		this.size = size;
	}

	@Column(name = "price", nullable = false, precision = 22, scale = 0)
	public double getPrice() {
		return this.price;
	}

	public void setPrice(double price) {
		this.price = price;
	}

	@Column(name = "time", nullable = false)
	public int getTime() {
		return this.time;
	}

	public void setTime(int time) {
		this.time = time;
	}

	@Column(name = "jdate", nullable = false)
	public int getJdate() {
		return this.jdate;
	}

	public void setJdate(int jdate) {
		this.jdate = jdate;
	}

	@Column(name = "bid", nullable = false, precision = 22, scale = 0)
	public double getBid() {
		return this.bid;
	}

	public void setBid(double bid) {
		this.bid = bid;
	}

	@Column(name = "ask", nullable = false, precision = 22, scale = 0)
	public double getAsk() {
		return this.ask;
	}

	public void setAsk(double ask) {
		this.ask = ask;
	}

	@Column(name = "bidsize", nullable = false)
	public int getBidsize() {
		return this.bidsize;
	}

	public void setBidsize(int bidsize) {
		this.bidsize = bidsize;
	}

	@Column(name = "asksize", nullable = false)
	public int getAsksize() {
		return this.asksize;
	}

	public void setAsksize(int asksize) {
		this.asksize = asksize;
	}

	@Column(name = "volume", nullable = false)
	public int getVolume() {
		return this.volume;
	}

	public void setVolume(int volume) {
		this.volume = volume;
	}

}
