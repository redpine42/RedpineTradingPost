package com.redpine.TradeDataMessages.PriceData.MsgConsumer;

import javax.jms.JMSException;
import javax.jms.MessageListener;
import javax.jms.TextMessage;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class TimeSalesMsgConsumer implements MessageListener {
	private static final Logger log = LoggerFactory
			.getLogger(TimeSalesMsgConsumer.class);

	public void onMessage(javax.jms.Message message) {
		if (message instanceof TextMessage) {
			try {
				log.info("Recieved TimeSales message: "
						+ ((TextMessage) message).getText());
			} catch (JMSException ex) {
				throw new RuntimeException(ex);
			}
		} else {
			throw new IllegalArgumentException(
					"Message must be of type TextMessage");
		}
	}
}