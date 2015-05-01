package com.redpine.TradeMessageConsumer;

import javax.jms.Connection;
import javax.jms.Destination;
import javax.jms.ExceptionListener;
import javax.jms.JMSException;
import javax.jms.MapMessage;
import javax.jms.Message;
import javax.jms.MessageConsumer;
import javax.jms.MessageListener;
import javax.jms.Session;
import javax.jms.Topic;

import org.apache.activemq.ActiveMQConnection;
import org.apache.activemq.ActiveMQConnectionFactory;

public class TradeMessageConsumer implements MessageListener, ExceptionListener
{
    private Session session;
    private Destination destination;
    private String subject = "L1Data" ;
    private String consumerName = "TradeClientListener";
    private String user = ActiveMQConnection.DEFAULT_USER;
    private String password = ActiveMQConnection.DEFAULT_PASSWORD;
    private String url = ActiveMQConnection.DEFAULT_BROKER_URL;
    private String clientId = "TradeClient";
    private L1DataObserver observer = null;

    private static final TradeMessageConsumer instance_ = new TradeMessageConsumer();

    public static TradeMessageConsumer getInstance()
    {
	return instance_;
    }

    private TradeMessageConsumer()
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

    public void observe(L1DataObserver ob)
    {
	observer = ob;
    }
    
    //@Override
    public void onMessage(Message msg)
    {
	
	// TODO Auto-generated method stub
	if(observer != null)
	{
	    MapMessage msg1 = (MapMessage)msg;
	    L1Data data = new L1Data();
	    try
	    {
		data.symbol_ = msg1.getString("Symbol");
		data.price_ = msg1.getDouble("LastPrice");
	    } 
	    catch (JMSException e)
	    {
		// TODO Auto-generated catch block
		e.printStackTrace();
	    }
	    observer.update(data);
	}
    }

    //@Override
    public void onException(JMSException arg0)
    {
	// TODO Auto-generated method stub
	
    }
}
