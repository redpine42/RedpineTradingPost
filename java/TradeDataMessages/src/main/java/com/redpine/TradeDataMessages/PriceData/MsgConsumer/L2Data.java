package com.redpine.TradeDataMessages.PriceData.MsgConsumer;

import java.sql.Timestamp;

public class L2Data {
	public Integer seq;
	public Timestamp timeStamp;
	public String symbol;
	public String mmid;
	public String source;
	public int marketside;
	public double price;
	public int size;
	public Timestamp recordTime;
	public byte closed;
}
