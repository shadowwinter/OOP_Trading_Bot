#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

class OrderBook{
    public:
    /**construct, reading a csv data file*/
        OrderBook(std::string filename);

    /**return vector of all known products in the dataset*/ 
        std::vector<std::string> getKnownProducts();

    /**return vector of Orders according to the sent filters*/
        std::vector<OrderBookEntry> getOrders(OrderBookType type, std::string product, std::string timestamp);
    
    /**return vector of all known timestamps in the dataset*/ 
        std::vector<std::string> getKnownTimestamps();
    
    /**return vector of Orders over the last multiple timesteps according to the sent filters*/
        std::vector<OrderBookEntry> getOrdersMultipleTimestep(OrderBookType type, std::string product, std::string timestamp, std::string noOfTimesteps);
    
    /**return vector of Orders over the last 10 timesteps (or less) according to the sent filters*/
        std::vector<std::vector<OrderBookEntry>> getOrdersMaxTenTimestep(OrderBookType type, std::string product, std::string timestamp);

    /**return earliest time in the orderbook*/
        std::string getEarliestTime();
    
    /**return the next time after the sent time in the orderbook
     * if there is no next timestamp, wraps around to the start*/
        std::string getNextTime(std::string timestamp);

    /**returns lowest price in the current type,product and timestamp*/
        static double getLowPrice(std::vector<OrderBookEntry>& orders);

    /**returns highest price in the current type,product and timestamp*/
        static double getHighPrice(std::vector<OrderBookEntry>& orders);

    /**returns average price in the current type,product and timestamp*/
        static double getMeanPrice(std::vector<OrderBookEntry>& orders);
        
    /**returns true/false depending on if the string is an integer or not*/
        bool is_int(std::string str);
    
    /**returns true/false depending on if the string is a double or not*/
        bool is_double(std::string str);

    private:
       std::vector<OrderBookEntry> orders; 
};