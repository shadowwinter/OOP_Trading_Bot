# Object_Oriented_Prog
A simple trading bot made using C++

The advisor bot aims to help cryptocurrency investors analyse exchange data and make informed decisions with the help of statistics. 
This bot uses a dataset of cryptocurrency trading data which includes the timestamp, trade type, trade currency and trade amount, to perform statistical functions to help analyze the exchange data, 
including finding the lowest and highest prices for a specific product, finding averages, and predicting next prices. 

Users are equipped with a wallet with "cryptocurrency" and is able to make trades to buy or sell "cryptocurrency" after analyzing the "market" data using the built in functions.

The bot cycles through the timestamps in the dataset, and assumes the current timestamp to be the "live" timestamp. Users are able to make bids to buy or sell their wallet credit, which would be processed when they move on to the next time stamp. 
The bot looks for a match of their request in the current dataset and allows the user to "make the trade" if there is an entry that meets the request. Their wallet is then updated with the new credit balance.

I have added on a notification feature on top of the source code that was taught in school, which alerts the users on the next timestep, should any of their notification requests at the current timestamp meet a match. 
This works by checking the trading data of the next timestamp from when the user makes the notification request, and checks the dataset for a match on their requuest. Should there be a match, the user is notified when they move onto the next timestamp.


To start, open the terminal and navigate to the code folder, and run the "./a.exe" command (without the quotation marks).
Typing "help" in the bot returns the help menu.
