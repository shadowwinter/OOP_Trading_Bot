#include "OrderBookEntry.h"

//the implementation, where we do the work. here we specify how things actually work
OrderBookEntry::OrderBookEntry(double _price, double _amount, std::string _timestamp, std::string _product, OrderBookType _orderType, std::string _username)
: price(_price), amount(_amount), timestamp(_timestamp), product(_product), orderType(_orderType), username(_username)
{
    
}

/**converts the string bid/ask into enum type*/
OrderBookType OrderBookEntry::stringToOrderBookType(std::string s){
    if(s == "ask"){
        return OrderBookType::ask;
    }
    if(s == "bid"){
        return OrderBookType::bid;
    }
    return OrderBookType::unknown;
}