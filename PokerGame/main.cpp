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
#include <set>
#include <map>

const static int RankCount = 13;
enum class CardSuit {Spades, Diamonds, Hearts, Clubs};
enum class RankHigh {Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace};
enum class RankLow {Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King};
enum class HighPokerHand {
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
const static std::vector<std::string> HighPokerHandStringVector = {
    "(High Card)",
    "(One Pair)",
    "(Two Pair)",
    "(3-of-a-Kind)",
    "(Straight)",
    "(Flush)",
    "(Full House)",
    "(4-of-a-Kind)",
    "(Straight Flush)"
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
    
//    bool operator< ( const Card &c2)
//    {
//        return this->rankHigh < c2.rankHigh;;
//    }
    
    RankHigh getRankHigh() const {
        return rankHigh;
    }
    
    RankLow getRankLow() const {
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
    
// TODO TESTING #################3
//    handAString = "8h9hThJhQh"; //STRAIGHT FLUSH
//    handAString = "8hQh4hJh9h"; //FLUSH
//    handAString = "As2h3s4d5s"; //STRAIGHT
    
    createHandCardVector(handAString, handAVector);
    createHandCardVector(handBString, handBVector);
    createHandCardVector(boardString, boardVector);
    
}

bool allCardsSameSuit(std::vector<Card> &playersHand) {
    
    CardSuit previousSuit = playersHand[0].getSuit();
    
    for(int i = 1; i < playersHand.size(); i++) {
        
        CardSuit currentSuit = playersHand[i].getSuit();
        
        if(currentSuit != previousSuit) {
            return false;
        }
        previousSuit = currentSuit;
    }
    
    return true;
}

bool straightCardsAceHigh(std::vector<Card> playersHand) {
    
    std::sort(playersHand.begin(), playersHand.end(), [](const Card & a, const Card & b) -> bool
    {
        return a.getRankHigh() < b.getRankHigh();
    });
    
    bool consecutive = true;
    for (int i = 1; i < playersHand.size(); ++i) {
        
        RankHigh rankHigh = playersHand[i].getRankHigh();
        int cardRank = static_cast<int>(rankHigh);
        
        RankHigh rankHighPrevious = playersHand[i - 1].getRankHigh();
        int cardRankPrevious = static_cast<int>(rankHighPrevious);
        
        if (cardRank != cardRankPrevious + 1) {
            consecutive = false;
            break;
        }
    }
    
    return consecutive;
}

bool straightCardsAceLow(std::vector<Card> playersHand) {
    
    std::sort(playersHand.begin(), playersHand.end(), [](const Card & a, const Card & b) -> bool
    {
        return a.getRankLow() < b.getRankLow();
    });
    
    bool consecutive = true;
    for (int i = 1; i < playersHand.size(); ++i) {
        
        RankLow rankLow = playersHand[i].getRankLow();
        int cardRank = static_cast<int>(rankLow);
        
        RankLow rankLowPrevious = playersHand[i - 1].getRankLow();
        int cardRankPrevious = static_cast<int>(rankLowPrevious);
        
        if (cardRank != cardRankPrevious + 1) {
            consecutive = false;
            break;
        }
    }
    
    return consecutive;
}

HighPokerHand findHighestHand( std::vector<Card> &playersHand) {
    std::vector<int> rankCountVector(RankCount);

    for (auto &card : playersHand) {
        
        RankHigh rankHigh = card.getRankHigh();
        int cardRank = static_cast<int>(rankHigh);
        ++rankCountVector[cardRank];
    }

    auto count_rank_counts = [&] (int count) {
        long rankCount = std::count(rankCountVector.begin(), rankCountVector.end(), count);
        return rankCount;
    };

    if(allCardsSameSuit(playersHand) && straightCardsAceHigh(playersHand) ) {
        return HighPokerHand::StraightFlush;
    }
    
    if (count_rank_counts(4) == 1) return HighPokerHand::FourOfAKind;

    if (count_rank_counts(3) == 1) {
        if (count_rank_counts(2) == 1) return HighPokerHand::FullHouse;
        else return HighPokerHand::ThreeOfAKind;
    }
    
    if(allCardsSameSuit(playersHand)) {
        return HighPokerHand::Flush;
    }
        
    //Straight
    if(!allCardsSameSuit(playersHand) && (straightCardsAceHigh(playersHand) || straightCardsAceLow(playersHand)) ) {
        return HighPokerHand::Straight;
    }

    if (count_rank_counts(2) == 1) return HighPokerHand::OnePair;
    if (count_rank_counts(2) == 2) return HighPokerHand::TwoPair;

    return HighPokerHand::HighCard;
}


void cardsPermutation(std::vector<Card> cards, size_t startIndex, size_t endIndex, std::vector<std::vector<Card>> &permutationVector)
{
    if (startIndex == endIndex) {
        permutationVector.push_back(cards);
    }
    else
    {
        for (size_t j = startIndex; j < cards.size(); j++)
        {
            std::swap(cards[startIndex], cards[j]);
            cardsPermutation(cards, startIndex + 1, endIndex, permutationVector);
            std::swap(cards[startIndex], cards[j]);
        }
    }
}

HighPokerHand findHighestHandCombination(std::vector<std::vector<Card>> &handXCardsPermutationVector,
                                         std::vector<std::vector<Card>> &boardCardsPermutationVector) {
    
    HighPokerHand highestHand = HighPokerHand::HighCard;
    
    HighPokerHand handX;
    
    std::vector<Card> handXCardsVector;
    std::vector<Card> boardCardsVector;
    
    for(auto & cardPermutation : handXCardsPermutationVector) {
        
        handXCardsVector.push_back(cardPermutation[0]);
        handXCardsVector.push_back(cardPermutation[1]);
        
        for(auto & boardPermutation : boardCardsPermutationVector) {
            
            handXCardsVector.push_back(boardPermutation[0]);
            handXCardsVector.push_back(boardPermutation[1]);
            handXCardsVector.push_back(boardPermutation[2]);
            
            handX = findHighestHand(handXCardsVector);
            if(handX > highestHand) {
                highestHand = handX;
            }
        }
        handXCardsVector.clear();
    }
    
    return highestHand;
}


//A player must combine any two of his cards with any three cards from the board to obtain 5 cards with the highest possible ranking for high hand,
std::string playHiHandGame(std::vector<std::vector<Card>> &handACardsPermutationVector,
                           std::vector<std::vector<Card>> &handBCardsPermutationVector,
                           std::vector<std::vector<Card>> &boardCardsPermutationVector) {
    
    std::string winningHandString = "";
    
    HighPokerHand highestHandA = findHighestHandCombination(handACardsPermutationVector, boardCardsPermutationVector);
    HighPokerHand highestHandB = findHighestHandCombination(handBCardsPermutationVector, boardCardsPermutationVector);
     
    if(highestHandA > highestHandB) {
        winningHandString = "=> HandA wins Hi " + HighPokerHandStringVector[static_cast<int>(highestHandA)] + "; ";
    }
    else if(highestHandA == highestHandB) {
        winningHandString = "=> Split Pot Hi " + HighPokerHandStringVector[static_cast<int>(highestHandA)] + "; ";
    }
    else {
        winningHandString = "=> HandB wins Hi " + HighPokerHandStringVector[static_cast<int>(highestHandB)] + "; ";
    }
    
    return winningHandString;
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
    
    
    getGamesQueue(inputFile, gamesQueue);
    
    while(gamesQueue.size() > 0) {
        
        std::vector<Card> handAVector;
        std::vector<Card> handBVector;
        std::vector<Card> boardVector;
        
        std::string gameString = gamesQueue.front();
        
        getHandsAndBoard(gameString, handAVector, handBVector, boardVector);
        
        std::vector<std::vector<Card>> handACardsPermutationVector;
        std::vector<std::vector<Card>> handBCardsPermutationVector;
        std::vector<std::vector<Card>> boardCardsPermutationVector;
        
        cardsPermutation( handAVector, 0, handAVector.size() - 1, handACardsPermutationVector);
        cardsPermutation( handBVector, 0, handBVector.size() - 1, handBCardsPermutationVector);
        cardsPermutation( boardVector, 0, boardVector.size() - 1, boardCardsPermutationVector);
        
 
        
        std::string outputLine = playHiHandGame(handACardsPermutationVector, handBCardsPermutationVector, boardCardsPermutationVector);
        
//and combine any other (or same) two of his cards with any other (or same) three cards from the board to obtain 5 cards with lowest possible low hand.
        
        
        
        gamesQueue.pop();
    }
    
    
    
    std::tuple<Card, HighPokerHand> junk = std::make_tuple(Card('K','s'), HighPokerHand::FullHouse);
    
    return 0;
}
