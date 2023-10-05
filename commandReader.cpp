#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "commandReader.h"

/** function implementation*/ //enum class min, max
std::vector<std::string> CommandReader::tokenise(std::string userInput, char separator){
    //string vector tokens ##stores the tokens
    std::vector<std::string> tokens;

    // int start, end ## used to delineate the position of the tokens
    signed int start, end;
    std::string token;
    
    // start = userInput.find_first_not_of(separator)
    start = userInput.find_first_not_of(separator,0);
    
    // do
    do{

    // end = next 'separator' after start
    end = userInput.find_first_of(separator,start); 

    // if start == userInput.length or start == end ## nothing more to find
    // break
    if(start == userInput.length() || start == end) break;
    
    // if end >= 0 ## we found the separator
    // token = userInput.substr(start, end - start) ## start, substring length
    if(end >= 0) token = userInput.substr(start, end - start);

    // else
    // token = userInput.substr(start, userInput.length - start) ## end is invalid
    else token = userInput.substr(start, userInput.length() - start);

    // add token to the end of the tokens vector
    tokens.push_back(token);

    // start = end + 1 ## move past this token
    start = end + 1;
    
    // while (end > 0) ## continue loop condition
    }while(end>0);

    return tokens;
}
