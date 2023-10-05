#pragma once
#include <vector>
#include <iostream>

#include "OrderBook.h"
#include "AdvisorMain.h"

class PrintMenus{
    public:
    
        void printHelp(std::vector<std::string> tokens);
        void printProd(std::string currentTime);
        void printMin(std::vector<std::string> tokens, std::string currentTime);
        void printMax(std::vector<std::string> tokens, std::string currentTime);
        void printAvg(std::vector<std::string> tokens, std::string currentTime);
        void printPredict(std::vector<std::string> tokens, std::string currentTime);
        void printNotify(std::vector<std::string> tokens, std::string currentTime);
        std::string printStep(std::string currentTime);
        void printEnd();
};