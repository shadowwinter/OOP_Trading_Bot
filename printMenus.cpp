#include "printMenus.h"
#include "OrderBookEntry.h"
#include "AdvisorMain.h"

#include <stdlib.h> 
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

AdvisorMain advisorMain;
std::vector<std::string> knownProds = advisorMain.orderBook.getKnownProducts();
std::vector<std::string> knownTimestamps = advisorMain.orderBook.getKnownTimestamps();
std::vector<std::vector<std::string>> notifyReq;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PrintMenus::printHelp(std::vector<std::string> tokens){

    if(tokens.size()==1){
        std::cout << "The available commands are: help, help <cmd>, prod, min, max, avg, predict, notify, time, step, end. \nUse 'help <cmd>' to find out how each command works." <<std::endl;
    }
    else{
        std::map<std::string,int> options {
            {"prod",1},
            {"min",2},
            {"max",3},
            {"avg",4},
            {"predict",5},
            {"notify",6},
            {"time",7},
            {"step",8},
            {"end",9}
        };

        int option;

        try{
            //maps user input to options
            option = options.at(tokens[1]);

        }catch(const std::exception& e){
            //no need to throw - returns to asking user for input
            std::cout << "No such command: " << tokens[1] << ". Enter 'help' for a list of commands. " << std::endl;
        }   

        switch(option){
            case 1: //prod
                std::cout << "Enter 'prod' to get the list of all available products." << std::endl;
                break;
            case 2: //min
                std::cout << "Enter 'min <product> <bid/ask>' to find minimum bid/ask for product in the current timestep." << std::endl;
                std::cout << "Eg. min ETH/BTC ask -> Returns the minimum ask for ETH/BTC in the current timestep." << std::endl;
                break;
            case 3: //max
                std::cout << "Enter 'max <product> <bid/ask>' to find maximum bid/ask for product in the current timestep." << std::endl;
                std::cout << "Eg. max DOGE/USDT bid -> Returns the maximum bid for ETH/BTC in the current timestep." << std::endl;
                break;
            case 4: //avg
                std::cout << "Enter 'avg <product> <bid/ask> <timesteps>' to compute the average bid/ask for product over the previous number of timesteps." << std::endl;
                std::cout << "Eg. avg ETH/USDT bid 10 -> Returns the average ETH/USDT bid price over the last 10 timesteps." << std::endl;
                break;
            case 5: //predict
                std::cout << "Enter 'predict <min/max> <product> <bid/ask>' to predict the min/max bid/ask for product for the next timestep." << std::endl;
                std::cout << "Eg. predict max BTC/USDT bid -> Returns the prediction of the max BTC/USDT bid for the next timestep."  << std::endl;
                break;
            case 6: //notify
                std::cout << "Enter 'notify <product> <bid/ask> <price>' to get notified if there is a suitable buy/sell price in the next timesteps." << std::endl;
                std::cout << "Eg. notify ETH/USDT bid 110 -> Returns a notification if there is an ask price of 110 or less in the next timesteps.\n"  << std::endl;
                std::cout << "Enter 'notify show' to show all set notifications. \n" << std::endl;
                std::cout << "Enter 'notify delete {product} {bid/ask} {price}' to delete notifications for specific requests. {} denotes optional portions." << std::endl;
                std::cout << "Eg. notify delete DOGE/BTC -> Deletes all DOGE/BTC notifications in the next timesteps."  << std::endl;
                break;
            case 7: //time
                std::cout << "Enter 'time' to get the current timestep." << std::endl;
                break;
            case 8: //step
                std::cout << "Enter 'step' to move onto the next timestep." << std::endl;
                break; 
            case 9: //end
                std::cout << "Enter 'end' to terminate the program." << std::endl;
                break; 
        }

    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PrintMenus::printProd(std::string currentTime){
    std::cout << "All available products: " <<std::endl;

    for(std::string const p : advisorMain.orderBook.getKnownProducts()){
        std::cout << "->" << p << std::endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PrintMenus::printMin(std::vector<std::string> tokens, std::string currentTime){
    
    if(tokens.size() == 3){

        //to ensure that the user input products match a product in our database
        if(std::find(std::begin(knownProds),std::end(knownProds), tokens[1])!=std::end(knownProds)){

            if(tokens[2]=="bid"){
                std::vector<OrderBookEntry> entries = advisorMain.orderBook.getOrders(OrderBookType::bid, tokens[1], currentTime);
                std::cout << "Bids seen: " << entries.size() << std::endl;
                std::cout << "Min bid for " << tokens[1] << " in the current timestep is: " << advisorMain.orderBook.getLowPrice(entries) << std::endl;

            }
            else if(tokens[2]=="ask"){
                std::vector<OrderBookEntry> entries = advisorMain.orderBook.getOrders(OrderBookType::ask, tokens[1], currentTime);
                std::cout << "Asks seen: " << entries.size() << std::endl;
                std::cout << "Min ask for " << tokens[1] << " in the current timestep is: " << advisorMain.orderBook.getLowPrice(entries) << std::endl;
            }
            else{
                std::cout << "Invalid third input. Enter 'min <product> <bid/ask>' to use this function." << std::endl;
            }
        }
        else{
            std::cout << "Invalid second input. Enter 'min <product> <bid/ask>' to use this function." << std::endl;
        }
    }
    else{
        std::cout << "Invalid input. Enter 'min <product> <bid/ask>' to use this function." << std::endl;
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PrintMenus::printMax(std::vector<std::string> tokens, std::string currentTime){

    if(tokens.size() == 3){

        if(std::find(std::begin(knownProds),std::end(knownProds), tokens[1])!=std::end(knownProds)){

            if(tokens[2]=="bid"){
                std::vector<OrderBookEntry> entries = advisorMain.orderBook.getOrders(OrderBookType::bid, tokens[1], currentTime);
                std::cout << "Bids seen: " << entries.size() << std::endl;
                std::cout << "Max bid for " << tokens[1] << " in the current timestep is: " << advisorMain.orderBook.getHighPrice(entries) << std::endl;

            }
            else if(tokens[2]=="ask"){
                std::vector<OrderBookEntry> entries = advisorMain.orderBook.getOrders(OrderBookType::ask, tokens[1], currentTime);
                std::cout << "Asks seen: " << entries.size() << std::endl;
                std::cout << "Max ask for " << tokens[1] << " in the current timestep is: " << advisorMain.orderBook.getHighPrice(entries) << std::endl;
            }
            else{
                std::cout << "Invalid third input. Enter 'max <product> <bid/ask>' to use this function." << std::endl;
            }
        }
        else{
            std::cout << "Invalid second input. Enter 'max <product> <bid/ask>' to use this function." << std::endl;
        }
    }
    else{
        std::cout << "Invalid input. Enter 'max <product> <bid/ask>' to use this function." << std::endl;
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PrintMenus::printAvg(std::vector<std::string> tokens, std::string currentTime){

    // std::vector<std::string> knownTimestamps = advisorMain.orderBook.getKnownTimestamps();
    // std::cout << "known timestamps; " << knownTimestamps.size() << std::endl;

    if(tokens.size() == 4){

        if(std::find(std::begin(knownProds),std::end(knownProds), tokens[1])!=std::end(knownProds)){

            if(tokens[2]=="bid"){
                //fetches all entries in the previous x timesteps that user asked for
                std::vector<OrderBookEntry> entries = advisorMain.orderBook.getOrdersMultipleTimestep(OrderBookType::bid, tokens[1], currentTime, tokens[3]);
                double mean = advisorMain.orderBook.getMeanPrice(entries);
                if(entries.size()!=0){
                    std::cout << "Bids seen: " << entries.size() << std::endl;
                    std::cout << "Avg bid for " << tokens[1] << " in the last " << tokens[3] << " timesteps is: " << mean << std::endl;
                }
            }
            else if(tokens[2]=="ask"){
                std::vector<OrderBookEntry> entries = advisorMain.orderBook.getOrdersMultipleTimestep(OrderBookType::ask, tokens[1], currentTime, tokens[3]);
                if(entries.size()!=0){
                    std::cout << "Asks seen: " << entries.size() << std::endl;
                    std::cout << "Avg ask for " << tokens[1] << " in the last " << tokens[3] << " timesteps is: " << advisorMain.orderBook.getMeanPrice(entries) << std::endl;
                }
            }
            else{
                std::cout << "Invalid third input (bid/ask). Enter 'avg <product> <bid/ask> <timesteps>' to use this function." << std::endl;
            }
        }
        else{
            std::cout << "Invalid second input (product). Enter 'avg <product> <bid/ask> <timesteps>' to use this function." << std::endl;
        }
    }
    else{
        std::cout << "Invalid input. Enter 'avg <product> <bid/ask> <timesteps>' to use this function." << std::endl;
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PrintMenus::printPredict(std::vector<std::string> tokens, std::string currentTime){

    std::vector<std::string> knownTimestamps = advisorMain.orderBook.getKnownTimestamps();
    
    if(tokens.size() == 4){

        if(std::find(std::begin(knownProds),std::end(knownProds), tokens[2])!=std::end(knownProds)){

            if(tokens[1]=="min"){

                if(tokens[3]=="bid"){

                    std::vector<std::vector<OrderBookEntry>> entries = advisorMain.orderBook.getOrdersMaxTenTimestep(OrderBookType::bid, tokens[2], currentTime);
                    
                    if(entries.size()!=0){
                        //checks that the # of timesteps are correct during testing
                        //std::cout << "Timesteps to compare: " << entries.size() << std::endl;

                        std::vector<double> allMinBids;

                        //gets vector of the last 10 min of the day, to compute moving avg
                        for(int i=0; i<entries.size(); i++){
                            
                            allMinBids.push_back(advisorMain.orderBook.getLowPrice(entries[i]));
                            
                            //to prove that the correct products are getting pushed into the vector during testing
                            // std::cout << "allMinBids " << i << ": " << allMinBids[i] << std::endl;
                        }

                        double sum = 0.0, mean;
                        for(int i=0; i< allMinBids.size(); i++){
                            sum += allMinBids[i];
                        }
                        mean = sum/allMinBids.size(); 

                        std::cout << "The min bid prediction for the next timestep is: " << mean << std::endl;
                    }
                }

                else if(tokens[3]=="ask"){
                    std::vector<std::vector<OrderBookEntry>> entries = advisorMain.orderBook.getOrdersMaxTenTimestep(OrderBookType::ask, tokens[2], currentTime);
                    
                    if(entries.size()!=0){
                        //std::cout << "Timesteps to compare: " << entries.size() << std::endl;

                        std::vector<double> allMinAsks;

                        //gets vector of the last 10 min of the day, to compute moving avg
                        for(int i=0; i<entries.size(); i++){
                            
                            allMinAsks.push_back(advisorMain.orderBook.getLowPrice(entries[i]));
                            //std::cout << "allMinAsks " << i << ": " << allMinAsks[i] << std::endl;
                        }

                        double sum = 0.0, mean;
                        for(int i=0; i< allMinAsks.size(); i++){
                            sum += allMinAsks[i];
                        }
                        mean = sum/allMinAsks.size(); 

                        std::cout << "The min ask prediction for the next timestep is: " << mean << std::endl;
                    }
                }
                else{
                    std::cout << "Invalid fourth input (bid/ask). Enter 'predict <min/max> <product> <bid/ask>' to use this function." << std::endl;
                }
            }

            else if(tokens[1]=="max"){

                if(tokens[3]=="bid"){

                    std::vector<std::vector<OrderBookEntry>> entries = advisorMain.orderBook.getOrdersMaxTenTimestep(OrderBookType::bid, tokens[2], currentTime);
                    
                    if(entries.size()!=0){
                        // std::cout << "Timesteps to compare: " << entries.size() << std::endl;

                        std::vector<double> allMaxBids;

                        //gets vector of the last 10 min of the day, to compute moving avg
                        for(int i=0; i<entries.size(); i++){
                            
                            allMaxBids.push_back(advisorMain.orderBook.getHighPrice(entries[i]));
                            // std::cout << "allMaxBids " << i << ": " << allMaxBids[i] << std::endl;
                        }

                        double sum = 0.0, mean;
                        for(int i=0; i< allMaxBids.size(); i++){
                            sum += allMaxBids[i];
                        }
                        mean = sum/allMaxBids.size();
                        
                            
                        

                        std::cout << "The max bid prediction for the next timestep is: " << mean << std::endl;
                    }
                }

                else if(tokens[3]=="ask"){
                    std::vector<std::vector<OrderBookEntry>> entries = advisorMain.orderBook.getOrdersMaxTenTimestep(OrderBookType::ask, tokens[2], currentTime);
                    
                    if(entries.size()!=0){
                        std::cout << "Timesteps to compare: " << entries.size() << std::endl;

                        std::vector<double> allMaxAsks;

                        //gets vector of the last 10 min of the day, to compute moving avg
                        for(int i=0; i<entries.size(); i++){
                            
                            allMaxAsks.push_back(advisorMain.orderBook.getHighPrice(entries[i]));
                            //std::cout << "allMaxAsks " << i << ": " << allMaxAsks[i] << std::endl;
                        }

                        double sum = 0.0, mean;
                        for(int i=0; i< allMaxAsks.size(); i++){
                            sum += allMaxAsks[i];
                        }
                        mean = sum/allMaxAsks.size(); 

                        std::cout << "The max ask prediction for the next timestep is: " << mean << std::endl;
                    }
                }
                else{
                    std::cout << "Invalid fourth input (bid/ask). Enter 'predict <min/max> <product> <bid/ask>' to use this function." << std::endl;
                }
            }
            else{
                std::cout << "Invalid second input (min/max). Enter 'predict <min/max> <product> <bid/ask>' to use this function." << std::endl;
            }
        }
        else{
            std::cout << "Invalid third input (product). Enter 'predict <min/max> <product> <bid/ask>' to use this function." << std::endl;
        }
    }
    else{
        std::cout << "Invalid input. Enter 'predict <min/max> <product> <bid/ask>' to use this function." << std::endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PrintMenus::printNotify(std::vector<std::string> tokens, std::string currentTime){

    std::string nextTime;
    double price;

    if(tokens[1] == "show" ){
        if(notifyReq.size()!=0){
            std::cout << "All your requests: " << std::endl;
            for (int i = 0; i < notifyReq.size(); i++)
            {
                std::cout << notifyReq[i][1] << " " << notifyReq[i][2] << " " << notifyReq[i][3] << std::endl; 
            }
        }
        else{
            std::cout << "You have no requests!" << std::endl;
        }
    }//end else if tokens[1] = show


    else if(tokens[1] != "delete" && tokens.size() >= 4){

        if(std::find(std::begin(knownProds),std::end(knownProds), tokens[1])!=std::end(knownProds)){

            if(tokens[2]=="bid"){
                try{
                    if( advisorMain.orderBook.is_double(tokens[3]) || advisorMain.orderBook.is_int(tokens[3]) ){ //check if input is either string/double
                        std::cout << "Got your bid request of " << tokens[1] << " at: " << tokens[3] << std::endl;
                        notifyReq.push_back(tokens);
                    }else{
                    std::cout << "Invalid fourth input (price). Enter 'notify <product> <bid/ask> <price>' to use this function." << std::endl;
                    }

                }catch(const std::exception& e){
                    std::cout << "Invalid fourth input (price). Enter 'notify <product> <bid/ask> <price>' to use this function." << std::endl;
                }

            }//end if bid

            else if(tokens[2]=="ask"){
                try{
                    if( advisorMain.orderBook.is_double(tokens[3]) || advisorMain.orderBook.is_int(tokens[3]) ){
                        std::cout << "Got your ask request of " << tokens[1] << " at: " << tokens[3] << std::endl;
                        notifyReq.push_back(tokens);
                    }else{
                    std::cout << "Invalid fourth input (price). Enter 'notify <product> <bid/ask> <price>' to use this function." << std::endl;
                    }

                }catch(const std::exception& e){
                    std::cout << "Invalid fourth input (price). Enter 'notify <product> <bid/ask> <price>' to use this function." << std::endl;
                }
            }//end if ask

            else{
                std::cout << "Invalid third input (bid/ask). Enter 'notify <product> <bid/ask> <price>' to use this function." << std::endl;
            }

        }//end if product name
        else{
            std::cout << "Invalid second input (product). Enter 'notify <product> <bid/ask> <price>' to use this function." << std::endl;
        }

    }//end if size == 4


    else if(tokens[1] == "delete"){ 

        bool deleted=false;

        for (int i = 0; i < notifyReq.size(); i++){
            if(tokens.size()==2){ //delete all requests
                notifyReq.clear();
                deleted=true;
            }//end if size ==2

            if(tokens.size()==3){ //delete all [product] requests
                if(tokens[2]==notifyReq[i][1]){
                    notifyReq.erase(notifyReq.begin()+i);
                    i--;
                    deleted=true;
                }
            }//end if size ==3

            if(tokens.size()==4){ //delete all [product] bid/ask requests
                if(tokens[3]==notifyReq[i][2] && tokens[2]==notifyReq[i][1]){
                    notifyReq.erase(notifyReq.begin()+i);
                    i--;
                    deleted=true;
                }
            }//end if size ==4

            if(tokens.size()==5){ //delete specific price requests
                if(tokens[4]==notifyReq[i][3] && tokens[3]==notifyReq[i][2] && tokens[2]==notifyReq[i][1]){
                    notifyReq.erase(notifyReq.begin()+i);
                    i--;
                    deleted=true;
                }
            }//end if size ==5

        }//end for notifyreq size
        
        if(deleted){
            std::cout << "Deleted!" << std::endl;
        }
        else if (!deleted){
            std::cout << "You have no matching entries to delete" << std::endl;
        }

    }//end else if tokens[1] = delete

    else{
        std::cout << "Invalid input. Enter 'notify <product> <bid/ask> <price>' to use this function." << std::endl;
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string PrintMenus::printStep(std::string currentTime){
    std::cout << "Going to next time frame. " << std::endl;

    std::string nextTime = advisorMain.orderBook.getNextTime(currentTime);
    double price;

    for(int i=0; i< notifyReq.size(); i++){

        price = std::stod(notifyReq[i][3]);

        //gets the data from the next time step before moving forward so that we can compare if the next timestep has matches
        if(notifyReq[i][2]=="bid"){
            std::vector<OrderBookEntry> entries = advisorMain.orderBook.getOrders(OrderBookType::bid, notifyReq[i][1], nextTime);
            double min = advisorMain.orderBook.getLowPrice(entries);

            if(min<=price){ //if there are matches, notify
                std::cout << "There is a match of your bid request of " << notifyReq[i][1] << " at: " << notifyReq[i][3] << std::endl;                   
            }
        }//end if bid

        if(notifyReq[i][2]=="ask"){
            std::vector<OrderBookEntry> entries = advisorMain.orderBook.getOrders(OrderBookType::ask, notifyReq[i][1], nextTime);
            double max = advisorMain.orderBook.getHighPrice(entries);

            if(max>=price){
                std::cout << "There is a match of your ask request of " << notifyReq[i][1] << " at: " << notifyReq[i][3] << std::endl;
            }
        }//end if ask
    }

    //move on to next time step
    currentTime  = advisorMain.orderBook.getNextTime(currentTime);
    return currentTime;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PrintMenus::printEnd(){
    std::cout << "Thank you for using AdvisorBot! Program will now terminate."  <<std::endl;
    exit (EXIT_FAILURE);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
