RedpineTradingPost
==================

Automated Trading Platform.

1.  Initial realease will be work done in visual studio C++ against MBS Trading SDK.  Currently configured for Forex.  Working system.
The project was done in Microsoft Visual Studio C++.  The interface to MB Trading was done through COM.  
The trading interface should be FIX since this is a common interface in the community.

Here is the FIX gateway I want to build against.
http://www.mbtrading.com/developersMain.aspx?page=fix

The code has been refactored several times.  
Want to build out a webservices system.  
Use RSS and html bots to mine news data, the store would be mongodb, with a hadoop backend for doing indexing of data into and external indexing engine (cool tech used for realtime data analytics http://www.elasticsearch.org/).  
In the past I’ve used home grown Artificial Neural Networks.  
This go around I’m planning on using something like R http://www.r-project.org/. 
The goal is to data mine relationships between news events and price change.  

Now for the hard part.  
News information will be grabbed from RSS feeds and bots which can crawl raw html and scrub news stories.  
RSS is probably the most useful, Not sure I want to crawl html web pages.    
Now that you have the info, you have to use a semantic reasoned to figure out what it means http://en.wikipedia.org/wiki/Semantic_reasoner.  
Probably a better route is to look at NLP tools.  
IBM Watson used a combination of hadoop and UIMA http://en.wikipedia.org/wiki/UIMA.
