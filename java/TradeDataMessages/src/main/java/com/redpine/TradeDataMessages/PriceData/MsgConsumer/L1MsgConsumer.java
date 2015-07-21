package com.redpine.TradeDataMessages.PriceData.MsgConsumer;

import javax.jms.Connection;
import javax.jms.Destination;
import javax.jms.ExceptionListener;
import javax.jms.JMSException;
import javax.jms.MapMessage;
import javax.jms.MessageConsumer;
import javax.jms.MessageListener;
import javax.jms.Session;
import javax.jms.TextMessage;
import javax.jms.Topic;

import org.apache.activemq.ActiveMQConnection;
import org.apache.activemq.ActiveMQConnectionFactory;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.redpine.TradeDataMessages.PriceData.MsgConsumer.L1MsgObserver;
import com.redpine.TradeDataMessages.PriceData.MsgConsumer.L1Data;

public class L1MsgConsumer  implements MessageListener, ExceptionListener {
	private static final Logger log = LoggerFactory
			.getLogger(L1MsgConsumer.class);

    private Session session;
    private Destination destination;
    private String subject = "L1Data" ;
    private String consumerName = "TradeClientListener";
    private String user = ActiveMQConnection.DEFAULT_USER;
    private String password = ActiveMQConnection.DEFAULT_PASSWORD;
    private String url = ActiveMQConnection.DEFAULT_BROKER_URL;
    private String clientId = "TradeClient";
    private L1MsgObserver observer = null;

    private static final L1MsgConsumer instance_ = new L1MsgConsumer();

    public static L1MsgConsumer getInstance()
    {
	return instance_;
    }

    private L1MsgConsumer()
    {
	
    }
    
    public void run() 
    {
        try 
        {
            ActiveMQConnectionFactory connectionFactory = new ActiveMQConnectionFactory(user, password, url);
            Connection connection = connectionFactory.createConnection();
            if (clientId != null && clientId.length() > 0 && !"null".equals(clientId)) 
            {
                connection.setClientID(clientId);
            }
            connection.setExceptionListener(this);
            connection.start();

            session = connection.createSession(false, Session.AUTO_ACKNOWLEDGE);
            destination = session.createTopic(subject);


            MessageConsumer consumer = session.createDurableSubscriber((Topic)destination, consumerName);
 
            consumer.setMessageListener(this);
 
        } 
        catch (Exception e)
        {
            System.out.println("Caught: " + e);
            e.printStackTrace();
        }
    }

    public void observe(L1MsgObserver ob)
    {
    	observer = ob;
    }
    
  	public void onMessage(javax.jms.Message message) {
		if (message instanceof TextMessage) {
			try {
				log.info("Recieved L1 message: "
						+ ((TextMessage) message).getText());
				if(observer != null)
				{
				    MapMessage msg1 = (MapMessage)message;
				    L1Data data = new L1Data();
				    try
				    {
				    	data.symbol = msg1.getString("Symbol");
						data.price = msg1.getDouble("LastPrice");
				    } 
				    catch (JMSException e)
				    {
					// TODO Auto-generated catch block
				    	log.error(e.toString());
				    }
				    observer.update(data);
				}			} catch (JMSException ex) {
				throw new RuntimeException(ex);
			}
		} else {
			throw new IllegalArgumentException(
					"Message must be of type TextMessage");
		}
	}
    public void onException(JMSException arg0)
    {
	// TODO Auto-generated method stub
	
    }

}