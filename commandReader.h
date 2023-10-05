#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

/** function prototype*/

class CommandReader{
    public:
        // CommandReader();
        //static std::vector<OrderBookEntry> readCSV(std::string csvFile);
        static std::vector<std::string> tokenise(std::string userInput, char separator);
        //static OrderBookEntry stringsToOBE(std::string price, std::string amount, std::string timestamp, std::string product, OrderBookType orderType);

    
    private:
        //static OrderBookEntry stringsToOBE(std::vector<std::string> strings);

};