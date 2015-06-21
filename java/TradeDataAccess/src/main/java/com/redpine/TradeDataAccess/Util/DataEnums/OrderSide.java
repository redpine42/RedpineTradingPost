package com.redpine.TradeDataAccess.Util.DataEnums;

/**
 * @author dbrown
 *
 */
public enum OrderSide
{  
	BID(1),
	ASK(2);
	
	 private final int number;

	 private OrderSide(int number) {
		this.number = number;
	}

	public int getNumber() {
		return number;
	}
};