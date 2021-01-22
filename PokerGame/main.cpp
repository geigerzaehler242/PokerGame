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
#include <tuple>

const static int RankCount = 13;
enum class CardSuit {Spades, Diamonds, Hearts, Clubs};
enum class RankHigh {Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace};
enum class RankLow {Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King};
enum class PokerHandHigh {
    HighCard,       //AhKsQhJc9h
    OnePair,        //AsAhKhQhJd
    TwoPair,        //AhAsKhKdQh
    ThreeOfAKind,   //AhAcAdKsQh
    Straight,       //As2h3s4d5s    <- Ace can count as high or low card
    Flush,          //3c6cTcJcKc
    FullHouse,      //AhAcAdKcKh
    FourOfAKind,    //KhKdKsKcAh
    StraightFlush   //8h9hThJhQh
};



class Card {
    
public:
    
    Card(const char rankChar, const char suitChar) {
        
        if(suitChar == 'h') {
            suit = CardSuit::Hearts;
        }
        else if(suitChar == 's') {
            suit = CardSuit::Spades;
        }
        else if(suitChar == 'c') {
            suit = CardSuit::Clubs;
        }
        else if(suitChar == 'd') {
            suit = CardSuit::Diamonds;
        }
        
        
        if(rankChar == '2') {
            rankHigh = RankHigh::Two;
            rankLow = RankLow::Two;
        }
        else if(rankChar == '3') {
            rankHigh = RankHigh::Three;
            rankLow = RankLow::Three;
        }
        else if(rankChar == '4') {
            rankHigh = RankHigh::Four;
            rankLow = RankLow::Four;
        }
        else if(rankChar == '5') {
            rankHigh = RankHigh::Five;
            rankLow = RankLow::Five;
        }
        else if(rankChar == '6') {
            rankHigh = RankHigh::Six;
            rankLow = RankLow::Six;
        }
        else if(rankChar == '7') {
            rankHigh = RankHigh::Seven;
            rankLow = RankLow::Seven;
        }
        else if(rankChar == '8') {
            rankHigh = RankHigh::Eight;
            rankLow = RankLow::Eight;
        }
        else if(rankChar == '9') {
            rankHigh = RankHigh::Nine;
            rankLow = RankLow::Nine;
        }
        else if(rankChar == 'T') {
            rankHigh = RankHigh::Ten;
            rankLow = RankLow::Ten;
        }
        else if(rankChar == 'J') {
            rankHigh = RankHigh::Jack;
            rankLow = RankLow::Jack;
        }
        else if(rankChar == 'Q') {
            rankHigh = RankHigh::Queen;
            rankLow = RankLow::Queen;
        }
        else if(rankChar == 'K') {
            rankHigh = RankHigh::King;
            rankLow = RankLow::King;
        }
        else {
            rankHigh = RankHigh::Ace;
            rankLow = RankLow::Ace;
        }
        
    }
    
    RankHigh getRankHigh() {
        return rankHigh;
    }
    
    RankLow getRankLow() {
        return rankLow;
    }
    
    CardSuit getSuit() {
        return suit;
    }
    
private:
    RankHigh rankHigh;
    RankLow rankLow;
    CardSuit suit;
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
    
    
    
    std::tuple<Card, PokerHandHigh> junk = std::make_tuple(Card('K','s'), PokerHandHigh::FullHouse);
    
    return 0;
}
