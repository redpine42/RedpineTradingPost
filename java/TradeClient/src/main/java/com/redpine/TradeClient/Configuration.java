package com.redpine.TradeClient;

public class Configuration
{
    private static final Configuration instance_ = new Configuration();

    public static Configuration getInstance()
    {
	return instance_;
    }
    
    String[] getSymbols()
    {
	String [] ret = {"EUR/USD","EUR/CHF","USD/CHF"};
	return ret;
    }
    private Configuration()
    {
    }
}
