#include "OrderBook.h"
#include "CSVReader.h"
#include <map>
#include <cmath>
#include <algorithm>
#include <iostream>

/**construct, reading a csv data file*/
OrderBook::OrderBook(std::string filename){
    CSVReader csvreader;
    orders = csvreader.readCSV(filename);
}

/**return vector of all known products in the dataset*/ 
std::vector<std::string> OrderBook::getKnownProducts(){
    std::vector<std::string> products;

    std::map<std::string, bool> prodMap;

    for(OrderBookEntry& e : orders){
        prodMap[e.product] = true;
    }
    //now flatten the map to a vector of strings
    for(auto const& e : prodMap){
        products.push_back(e.first);
    }

    return products;
}

/**return vector of Orders according to the sent filters*/
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, std::string product, std::string timestamp){
    std::vector<OrderBookEntry> orders_sub;
    for(OrderBookEntry& e : orders){
        if(e.orderType == type && e.product == product && e.timestamp == timestamp){
            orders_sub.push_back(e);
        }
    }
    return orders_sub;
}

/**return vector of all known timestamps in the dataset*/ 
std::vector<std::string> OrderBook::getKnownTimestamps(){
    std::vector<std::string> timestamps;

    std::map<std::string, bool> timeMap;

    for(OrderBookEntry& e : orders){
        timeMap[e.timestamp] = true;
    }
    //now flatten the map to a vector of strings
    for(auto const& e : timeMap){
        timestamps.push_back(e.first);
    }

    return timestamps;
}

/**return vector of Orders over the last multiple timesteps according to the sent filters*/
std::vector<OrderBookEntry> OrderBook::getOrdersMultipleTimestep(OrderBookType type, std::string product, std::string timestamp, std::string noOfTimesteps){
    std::vector<OrderBookEntry> orders_sub;
    for(OrderBookEntry& e : orders){

        //get all the known timestamps so that we are able to compare and get the range between the current timestep and the no. of last timesteps.
        std::vector<std::string> knownTimestamps = OrderBook::getKnownTimestamps();

        std::string key = timestamp; 

        //finds the position of the current timestamp, so that we are able to collect up to the last 10 no. of timesteps to do necessary calculations
        std::vector<std::string>::iterator itr = std::find(knownTimestamps.begin(), knownTimestamps.end(), key);
        

        //if the current timestep is indeed in the vector of all known timestamps, carry out
        if(itr!=knownTimestamps.end()){
            
            //the end will be the current timestep location
            int end = std::distance(knownTimestamps.begin(),itr); 

            //the range will be the range where we will be carrying out the calculations
            int range;
            
            try{
                range = std::stoi(noOfTimesteps);
                
                //the start will be where the start of the range of the no. of timesteps is at
                int start = end - range;
                int temp = start;
                
                //if the range is acceptable, push all relevant products into vector to do calculations
                if(start>=-1){
                    if(e.orderType == type && e.product == product &&  e.timestamp<= knownTimestamps[end] && e.timestamp > knownTimestamps[temp]){
                        temp = temp + 1;
                        orders_sub.push_back(e);
                    }
                }
                else{
                    std::cout << "Please choose a smaller timestep! You are currently on timestep #" << end+1 << "." << std::endl;
                    break;
                }  
            } 
            catch(const std::exception& e){
                std::cout << "OrderBook::getOrdersMultipleTimestep: Bad no. of timesteps: " << noOfTimesteps << std::endl;
                break;
            }  
        }else{
            std::cout<<"Timestamp invalid!" <<std::endl;
            break;
        }
        
    }
    return orders_sub;
}


/**return vector of Orders over the last 10 timesteps (or less) according to the sent filters*/
std::vector<std::vector<OrderBookEntry>> OrderBook::getOrdersMaxTenTimestep(OrderBookType type, std::string product, std::string timestamp){
    
    std::vector<std::vector<OrderBookEntry>> orders_sub;

        //get all the known timestamps so that we are able to compare and get the range between the current timestep and the no. of last timesteps.
        std::vector<std::string> knownTimestamps = OrderBook::getKnownTimestamps();

        std::string key = timestamp; 

        //finds the position of the current timestamp, so that we are able to collect the last few no. of timesteps to do necessary calculations
        std::vector<std::string>::iterator itr = std::find(knownTimestamps.begin(), knownTimestamps.end(), key);
        
        //if the current timestep is indeed in the vector of all known timestamps, carry out
        //.end() is used to return an iterator pointing to next to last element of the vector container
        //therefore = .end() means it is not in the vector, so itr!= .end() means that it is in the vector
        if(itr!=knownTimestamps.end()){
            
            //the current timestep location
            int current = std::distance(knownTimestamps.begin(),itr); 
            
            try{
                //to find the start of the range that we will be carrying out the calculations on (max 10 steps for moving avg,)
                int start = current - 9; 
                int temp = start;
                    
                //if there are enough for 10 timestamps, push all relevant products into vector to do calculations
                if(start>=-1){
                    for(int i=0; i<9; i++){ 
                        temp = temp + 1;
                        orders_sub.push_back(OrderBook::getOrders(type, product, knownTimestamps[temp]));
                    }
                }
                else{ //else just push all products from current time stamp all the way to start of dataset
                    for(int i=0; i<=current; i++){ 
                        orders_sub.push_back(OrderBook::getOrders(type, product, knownTimestamps[i]));
                    }
                }

            } 
            catch(const std::exception& e){
                std::cout << "OrderBook::getOrdersMaxTenTimestep: Error!" << std::endl;
                //break;
            }  
        }else{
            std::cout<<"Timestamp invalid!" <<std::endl;
            //break;
        }
        
    
    return orders_sub;
}


/**return earliest time in the orderbook*/
std::string OrderBook::getEarliestTime(){
    return orders[0].timestamp;
}

/**return the next time after the sent time in the orderbook
 * if there is no next timestamp, wraps around to the start*/
std::string OrderBook::getNextTime(std::string timestamp){
    std::string next_timestamp  = "";
    for(OrderBookEntry& e: orders){
        if(e.timestamp > timestamp) {
            next_timestamp = e.timestamp;
            break;
        }
    }
    if (next_timestamp == "") next_timestamp = orders[0].timestamp;
    return next_timestamp;
}

/**returns lowest price in the current type,product and timestamp*/
double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders){
    double min = orders[0].price;
    for(OrderBookEntry& e: orders){
        if(e.price < min) min = e.price;
    }
    return min;
}

/**returns highest price in the current type,product and timestamp*/
double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders){
    double max = orders[0].price;
    for(OrderBookEntry& e: orders){
        if(e.price > max) max = e.price;
    }
    return max;
}

/**returns average price in the current type,product and timestamp*/
double OrderBook::getMeanPrice(std::vector<OrderBookEntry>& orders){
    double sum = 0.0, mean;
    for(OrderBookEntry& e: orders){
        sum += e.price;
    }
    mean = sum / orders.size();
    return mean;
}

/**returns true/false depending on if the string is an integer or not*/
bool OrderBook::is_int(std::string str){
    bool ans;
    for (int i = 0; i < str.length(); i++){
        if (isdigit(str[i]) == false){
            ans= false;
            break;
        }
        ans= true;
    }
    return ans;
}

/**returns true/false depending on if the string is a double or not*/
bool OrderBook::is_double(std::string str){
    bool ans;
    double check;

    int str_int = 0;     
    double str_double = 0.0;
      
    str_int = std::stoi(str);
    str_double = std::stod(str);     

    check = str_int / str_double;

    if (check == 1.00){
        ans = false; // str is integer
        return ans;
    }else{
        ans = true;  // str is double
        return ans;
    }
}

