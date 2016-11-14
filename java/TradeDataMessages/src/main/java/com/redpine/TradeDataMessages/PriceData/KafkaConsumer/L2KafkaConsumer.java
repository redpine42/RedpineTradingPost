package com.redpine.TradeDataMessages.PriceData.KafkaConsumer;

import org.springframework.kafka.annotation.KafkaListener;
import org.springframework.kafka.support.Acknowledgment;
import org.springframework.kafka.support.KafkaHeaders;
import org.springframework.messaging.handler.annotation.Header;
import org.springframework.messaging.handler.annotation.Payload;

public class L2KafkaConsumer {

	@KafkaListener(id = "L2InChannel", topics = "L2Topic")
	public void consumeInMessage(@Payload String data,
			@Header(KafkaHeaders.RECEIVED_TOPIC) String topic,
			@Header(KafkaHeaders.RECEIVED_PARTITION_ID) String partitionId,
			Acknowledgment ack) {
		ack.acknowledge();
	}
}