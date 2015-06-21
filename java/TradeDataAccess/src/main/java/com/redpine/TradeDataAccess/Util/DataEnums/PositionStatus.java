/**
 * 
 */
package com.redpine.TradeDataAccess.Util.DataEnums;

/**
 * @author dbrown
 *
 */
public enum PositionStatus
{
    NoPosition,
	OpenOrderWaiting,
	OpenOrderPartialFill,
    OpenFilled,
    CloseOrderWaiting,
	CloseOrderPartialFill,
    CloseFilled,
    Canceled,
	Rejected;
};