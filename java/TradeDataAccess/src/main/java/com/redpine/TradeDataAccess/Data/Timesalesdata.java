package com.redpine.TradeDataAccess.Data;



import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import static javax.persistence.GenerationType.IDENTITY;
import javax.persistence.Id;
import javax.persistence.Table;
import javax.persistence.Version;

/**
 * 
 */
@Entity
@Table(name = "timesalesdata", catalog = "backtest")
public class Timesalesdata implements java.io.Serializable {

	/**
	 * 
	 */
	private static final long serialVersionUID = 701846244721510440L;
	
	private Integer seq;
	private Double timeStamp;
	private String symbol;
	private int sizeVal;
	private double price;
	private int timeVal;
	private int jdate;
	private int tsstatus;
	private int tstype;

	public Timesalesdata() {
	}

	public Timesalesdata(String symbol, int sizeVal, double price, int timeVal,
			int jdate, int tsstatus, int tstype) {
		this.symbol = symbol;
		this.sizeVal = sizeVal;
		this.price = price;
		this.timeVal = timeVal;
		this.jdate = jdate;
		this.tsstatus = tsstatus;
		this.tstype = tstype;
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

	@Version
	@Column(name = "timeStamp", precision = 22, scale = 0)
	public Double getTimeStamp() {
		return this.timeStamp;
	}

	public void setTimeStamp(Double timeStamp) {
		this.timeStamp = timeStamp;
	}

	@Column(name = "symbol", nullable = false, length = 7)
	public String getSymbol() {
		return this.symbol;
	}

	public void setSymbol(String symbol) {
		this.symbol = symbol;
	}

	@Column(name = "sizeVal", nullable = false)
	public int getSizeVal() {
		return this.sizeVal;
	}

	public void setSizeVal(int sizeVal) {
		this.sizeVal = sizeVal;
	}

	@Column(name = "price", nullable = false, precision = 22, scale = 0)
	public double getPrice() {
		return this.price;
	}

	public void setPrice(double price) {
		this.price = price;
	}

	@Column(name = "timeVal", nullable = false)
	public int getTimeVal() {
		return this.timeVal;
	}

	public void setTimeVal(int timeVal) {
		this.timeVal = timeVal;
	}

	@Column(name = "jdate", nullable = false)
	public int getJdate() {
		return this.jdate;
	}

	public void setJdate(int jdate) {
		this.jdate = jdate;
	}

	@Column(name = "tsstatus", nullable = false)
	public int getTsstatus() {
		return this.tsstatus;
	}

	public void setTsstatus(int tsstatus) {
		this.tsstatus = tsstatus;
	}

	@Column(name = "tstype", nullable = false)
	public int getTstype() {
		return this.tstype;
	}

	public void setTstype(int tstype) {
		this.tstype = tstype;
	}

}
