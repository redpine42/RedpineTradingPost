package com.Redpine;

import java.sql.Date;

/**
 * @author dbrown
 *
 */
public class L1Data {

	private String symbol;
	private Long lastSize;
	private Double lastPrice;
	private Long lastTime;
	private Long jdate;
	private Long seq;

	private Double bid;
	private Double ask;
	private Long bidSize;
	private Long askSiz;
	private Boolean upTick;
	private Long volume;
	private Boolean shortable;
	private Date timeStamp;

	/**
	 * @return the ask
	 */
	public Double getAsk() {
		return ask;
	}

	/**
	 * @return the askSiz
	 */
	public Long getAskSiz() {
		return askSiz;
	}

	/**
	 * @return the bid
	 */
	public Double getBid() {
		return bid;
	}

	/**
	 * @return the bidSize
	 */
	public Long getBidSize() {
		return bidSize;
	}

	/**
	 * @return the jdate
	 */
	public Long getJdate() {
		return jdate;
	}

	/**
	 * @return the lastPrice
	 */
	public Double getLastPrice() {
		return lastPrice;
	}

	/**
	 * @return the lastSize
	 */
	public Long getLastSize() {
		return lastSize;
	}

	/**
	 * @return the lastTime
	 */
	public Long getLastTime() {
		return lastTime;
	}

	/**
	 * @return the seq
	 */
	public Long getSeq() {
		return seq;
	}

	/**
	 * @return the shortable
	 */
	public Boolean getShortable() {
		return shortable;
	}

	/**
	 * @return the symbol_
	 */
	public String getSymbol() {
		return symbol;
	}

	/**
	 * @return the timeStamp
	 */
	public Date getTimeStamp() {
		return timeStamp;
	}

	/**
	 * @return the upTick
	 */
	public Boolean getUpTick() {
		return upTick;
	}

	/**
	 * @return the volume
	 */
	public Long getVolume() {
		return volume;
	}

	/**
	 * @param ask
	 *            the ask to set
	 */
	public void setAsk(Double ask) {
		this.ask = ask;
	}

	/**
	 * @param askSiz
	 *            the askSiz to set
	 */
	public void setAskSiz(Long askSiz) {
		this.askSiz = askSiz;
	}

	/**
	 * @param bid
	 *            the bid to set
	 */
	public void setBid(Double bid) {
		this.bid = bid;
	}

	/**
	 * @param bidSize
	 *            the bidSize to set
	 */
	public void setBidSize(Long bidSize) {
		this.bidSize = bidSize;
	}

	/**
	 * @param jdate
	 *            the jdate to set
	 */
	public void setJdate(Long jdate) {
		this.jdate = jdate;
	}

	/**
	 * @param lastSize
	 *            the lastSize to set
	 */
	public void setLastSize(Long lastSize) {
		this.lastSize = lastSize;
	}

	/**
	 * @param lastPrice
	 *            the lastPrice to setDate
	 */
	public void setPrice(Double lastPrice) {
		this.lastPrice = lastPrice;
	}

	/**
	 * @param seq
	 *            the seq to set
	 */
	public void setSeq(Long seq) {
		this.seq = seq;
	}

	/**
	 * @param shortable
	 *            the shortable to set
	 */
	public void setShortable(Boolean shortable) {
		this.shortable = shortable;
	}

	/**
	 * @param symbol_
	 *            the symbol_ to set
	 */
	public void setSymbol(String symbol) {
		this.symbol = symbol;
	}

	/**
	 * @param lastTime
	 *            the lastTime to set
	 */
	public void setTime(Long lastTime) {
		this.lastTime = lastTime;
	}

	/**
	 * @param timeStamp
	 *            the timeStamp to set
	 */
	public void setTimeStamp(Date timeStamp) {
		this.timeStamp = timeStamp;
	}

	/**
	 * @param upTick
	 *            the upTick to set
	 */
	public void setUpTick(Boolean upTick) {
		this.upTick = upTick;
	}

	/**
	 * @param volume
	 *            the volume to set
	 */
	public void setVolume(Long volume) {
		this.volume = volume;
	}

}
