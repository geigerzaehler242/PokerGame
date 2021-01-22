//
//  main.cpp
//  PokerGame
//
//  Created by fernando marto on 2021-01-22.
//

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <string>


class Card {
    
public:
    
    Card(char rank, char suit) : rank(rank), suit(suit) {}
    
    char getRank() {
        return rank;
    }
    
    char getSuit() {
        return suit;
    }
    
private:
    char rank;
    char suit;
};


enum GameIndicies {
    beginGameA = 6,
    lengthGameA = 11,
    beginGameB = 24,
    lengthGameB = 11,
    beginBoard = 42,
    lengthBoard = 14
};

void getGamesQueue(std::string inputFile, std::queue<std::string> &gamesQueue) {
    
    std::string line;
    std::ifstream myfile (inputFile);
    
    if (myfile.is_open()) {
        
        std::cout << "input file: " << std::endl;
        
        while ( getline (myfile, line) ) {
            std::cout << line << std::endl;
            gamesQueue.push(line);
        }
        myfile.close();
    }

    else std::cout << "Unable to open input file!" << std::endl;
    
}

void createHandCardVector(std::string handString, std::vector<Card> &handCardVector) {
    
    for(int i = 0; i < handString.size(); ) {
        
        handCardVector.push_back(Card(handString[i], handString[i+1]) );
        i += 2;
    }
}

void getHandsAndBoard(std::string gameString, std::vector<Card> &handAVector, std::vector<Card> &handBVector, std::vector<Card> &boardVector) {
    
    std::string handAString = "";
    std::string handBString = "";
    std::string boardString = "";
    
    handAString = gameString.substr(beginGameA, lengthGameA);
    handBString = gameString.substr(beginGameB, lengthGameB);
    boardString = gameString.substr(beginBoard, lengthBoard);
    
    handAString.erase(remove(handAString.begin(), handAString.end(), '-'), handAString.end());
    handBString.erase(remove(handBString.begin(), handBString.end(), '-'), handBString.end());
    boardString.erase(remove(boardString.begin(), boardString.end(), '-'), boardString.end());
    
    createHandCardVector(handAString, handAVector);
    createHandCardVector(handBString, handBVector);
    createHandCardVector(boardString, boardVector);
    
}


    


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "OMAHA Hi/Lo Game" << std::endl;
    
    std::string inputFile;
    std::string outputFile;
    
    if(argc == 3) {
        inputFile = argv[1];
        outputFile = argv[2];
    }
    else {
        std::cout << "input and output file names are required!" << std::endl;
    }
    
    std::queue<std::string> gamesQueue;
    std::vector<Card> handAVector;
    std::vector<Card> handBVector;
    std::vector<Card> boardVector;
    
    getGamesQueue( inputFile, gamesQueue);
    
    while(gamesQueue.size() > 0) {
        
        std::string gameString = gamesQueue.front();
        
        getHandsAndBoard(gameString, handAVector, handBVector, boardVector);
        
        gamesQueue.pop();
    }
    
    
    
    
    
    return 0;
}
