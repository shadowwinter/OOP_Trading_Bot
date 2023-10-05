#pragma once
#include <vector>
#include <iostream>

#include "printMenus.h"
#include "OrderBook.h"


class AdvisorMain{
    public:

      // OrderBook orderBook{"20200601.csv"};
     OrderBook orderBook{"20200317.csv"};

      std::string currentTime; 

      AdvisorMain();
      /**call this to start the simulation*/
      void init();

    private:
      void printMenu();
      std::string getUserInput();
      void processUserInput(std::string userInput);
       
       
};