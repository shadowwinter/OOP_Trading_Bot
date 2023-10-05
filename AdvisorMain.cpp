#include "AdvisorMain.h"
#include "commandReader.h"
#include "printMenus.h"

#include <iostream>
#include <vector>
#include <map>
using namespace std;

AdvisorMain::AdvisorMain(){

}

void AdvisorMain::init(){
    std::string input;
    currentTime = orderBook.getEarliestTime();
    
    while(true){
        printMenu();
        input = getUserInput();
        processUserInput(input);
    }
}


void AdvisorMain::printMenu(){
    std::cout << "==================================================================================" <<std::endl;
    std::cout << "Please enter a command, or 'help' for a list of commands." << std::endl;
    std::cout << "==================================================================================" <<std::endl;
}

std::string AdvisorMain::getUserInput(){
    std::string userInput;
    std::cout << "Current time: " << currentTime <<std::endl;
    std::cout << "Your command: " <<std::endl;
    std::getline(std::cin, userInput);

    return userInput;
}

void AdvisorMain::processUserInput(std::string userInput){

    std::vector<std::string> tokens = CommandReader::tokenise(userInput, ' ');

    //makes sure program got the input
    // std::cout << "Ok! We got your input: " << userInput <<std::endl;
    

    //makes sure tokenizing works
    // for(int i=0; i<tokens.size(); ++i){
    //     std::cout << i << ": " << tokens[i] << std::endl;
    // }

    std::map<string,int> options {
        {"help",1}, 
        {"prod",2},
        {"min",3},
        {"max",4},
        {"avg",5},
        {"predict",6},
        {"notify",7},
        {"time",8},
        {"step",9},
        {"end",0}
    };

    int option;

    try{
        option = options.at(tokens[0]);
        std::cout << " " << std::endl;

    }catch(const std::exception& e){
        //no need to throw - returns to asking user for input
        std::cout << "\nNo such command: " << userInput << ". Enter 'help' for a list of commands. " << std::endl;
    }   

    //creates an object of printMenus so that we are able to access the functions
    PrintMenus printMenus;

    switch(option){
        case 1: //help
            printMenus.printHelp(tokens);
            break;
        case 2: //prod
            printMenus.printProd(currentTime);
            break;
        case 3: //min
            printMenus.printMin(tokens, currentTime);
            break;
        case 4: //max
            printMenus.printMax(tokens, currentTime);
            break;
        case 5: //avg
            printMenus.printAvg(tokens, currentTime);
            break;
        case 6: //predict
            printMenus.printPredict(tokens, currentTime);
            break;
        case 7: //notify
            printMenus.printNotify(tokens, currentTime);
            break;
        case 8: //time
            std::cout << "The current time is: " << currentTime <<std::endl;
            break;
        case 9: //step
            currentTime = printMenus.printStep(currentTime);            
            break; 
        case 0: //end
            printMenus.printEnd();
            break;
    }

}

