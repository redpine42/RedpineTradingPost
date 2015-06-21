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
@Table(name = "timesalesdata")
public class Timesalesdata implements java.io.Serializable {

	/**
	 * 
	 */
	private static final long serialVersionUID = 701846244721510440L;
	
	private Integer seq;
	private Timestamp timeStamp;
	private String symbol;
	private int sizeVal;
	private double price;
	private Timestamp recordTime;
	private int tsstatus;
	private int tstype;

	public Timesalesdata() {
	}

	/**
	 * @param symbol
	 * @param sizeVal
	 * @param price
	 * @param timeVal
	 * @param jdate
	 * @param tsstatus
	 * @param tstype
	 */
	public Timesalesdata(String symbol, int sizeVal, double price, Timestamp recordTime,
			int tsstatus, int tstype) {
		this.symbol = symbol;
		this.sizeVal = sizeVal;
		this.price = price;
		this.recordTime = recordTime;
		this.tsstatus = tsstatus;
		this.tstype = tstype;
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
	@Column(name = "timeStamp")
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
	@Column(name = "symbol", nullable = false, length = 7)
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
	@Column(name = "sizeVal", nullable = false)
	public int getSizeVal() {
		return this.sizeVal;
	}

	/**
	 * @param sizeVal
	 */
	@SuppressWarnings("unused")
	private void setSizeVal(int sizeVal) {
		this.sizeVal = sizeVal;
	}

	/**
	 * @return
	 */
	@Column(name = "price", nullable = false, precision = 22, scale = 0)
	public double getPrice() {
		return this.price;
	}

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
	 * @param timeVal
	 */
	@SuppressWarnings("unused")
	private void setRecordTime(Timestamp recordTime) {
		this.recordTime = recordTime;
	}

	/**
	 * @return
	 */
	@Column(name = "tsstatus", nullable = false)
	public int getTsstatus() {
		return this.tsstatus;
	}

	/**
	 * @param tsstatus
	 */
	@SuppressWarnings("unused")
	private void setTsstatus(int tsstatus) {
		this.tsstatus = tsstatus;
	}

	/**
	 * @return
	 */
	@Column(name = "tstype", nullable = false)
	public int getTstype() {
		return this.tstype;
	}

	/**
	 * @param tstype
	 */
	@SuppressWarnings("unused")
	private void setTstype(int tstype) {
		this.tstype = tstype;
	}

}
