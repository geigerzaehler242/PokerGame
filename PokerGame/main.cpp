//
//  main.cpp
//  PokerGame
//
//  Created by fernando marto on 2021-01-22.
//

#include <iostream>
#include <fstream>
#include <queue>


void getHandsQueue(std::string inputFile, std::queue<std::string> &handsQueue) {
    
    std::string line;
    std::ifstream myfile (inputFile);
    
    if (myfile.is_open()) {
        
        std::cout << "input file: " << std::endl;
        
        while ( getline (myfile, line) )
        {
            std::cout << line << std::endl;
            handsQueue.push(line);
        }
        myfile.close();
    }

    else std::cout << "Unable to open input file!" << std::endl;
    
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "OMAHA Game" << std::endl;
    
    std::string inputFile;
    std::string outputFile;
    
    if(argc == 3) {
        inputFile = argv[1];
        outputFile = argv[2];
    }
    else {
        std::cout << "input and output file names are required!" << std::endl;
    }
    
    
    std::queue<std::string> handsQueue;
    
    getHandsQueue( inputFile, handsQueue);
    
    
    
    return 0;
}
