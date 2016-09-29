
@KafkaListener(id = "L1InChannel",topics =   CommonContants.KAFKA_TOPIC.SERVER_IN_CHANNEL)
public void consumeInMessage(@Payload String data,
                                 @Header(KafkaHeaders.RECEIVED_TOPIC) String topic,
                              @Header(KafkaHeaders.RECEIVED_PARTITION_ID) String partitionId,
                              Acknowledgment ack) {
    logger.info("[serverInMessage]data=" + data);
    ack.acknowledge();
}
