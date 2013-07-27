#pragma once

class L2DataInterface;
#include <activemq/library/ActiveMQCPP.h>
#include <decaf/lang/Thread.h>
#include <decaf/lang/Runnable.h>
#include <decaf/util/concurrent/CountDownLatch.h>
#include <decaf/lang/Integer.h>
#include <decaf/util/Date.h>
#include <activemq/core/ActiveMQConnectionFactory.h>
#include <activemq/util/Config.h>
#include <cms/Connection.h>
#include <cms/Session.h>
#include <cms/TextMessage.h>
#include <cms/BytesMessage.h>
#include <cms/MapMessage.h>
#include <cms/ExceptionListener.h>
#include <cms/MessageListener.h>
#include <stdlib.h>
#include <iostream>
#include <memory>

using namespace activemq::core;
using namespace decaf::util::concurrent;
using namespace decaf::util;
using namespace decaf::lang;
using namespace cms;

class L2DataConsumer : public ExceptionListener,
                           public MessageListener,
                           public Runnable
{
public:
	L2DataConsumer(L2DataInterface * cb);
	~L2DataConsumer(void);
    void run();
	void waitUntilReady();

private:
	void onMessage( const Message* message );
	void onException( const CMSException& ex AMQCPP_UNUSED);

	L2DataInterface * cb_;

    CountDownLatch latch;
    CountDownLatch doneLatch;
    Connection* connection;
    Session* session;
    Destination* destination;
    MessageConsumer* consumer;
    long waitMillis;
    std::string brokerURI;
};
