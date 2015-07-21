package com.redpine.TradeDataMessages.PriceData.MsgConsumer;

import java.sql.Timestamp;

public class L1Data {
	public Integer seq;
	public Timestamp timeStamp;
	public String symbol;
	public int size;
	public double price;
	public Timestamp recordTime;
	public double bid;
	public double ask;
	public int bidsize;
	public int asksize;
	public int volume;
}
