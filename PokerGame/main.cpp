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
#include <cmath>



enum class RankHigh {
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace
};
enum class RankLow {
    Ace,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King
};
enum class CardSuit {
    Spades,
    Diamonds,
    Hearts,
    Clubs
};
const static int RankCount = 13;

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

enum class LowPokerHand {
    DoesNotQualify,       //ATQ23
    DoesQualify        //5432A
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
    
    Card() {}
    
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
    
    bool operator==(const Card & r) const
    {
        if (rankHigh == r.rankHigh && suit == r.suit && rankLow == r.rankLow) return true;
        else return false;
    }
    
    RankHigh getRankHigh() const {
        return rankHigh;
    }
    
    RankLow getRankLow() const {
        return rankLow;
    }
    
    CardSuit getSuit() const {
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

void getGamesQueue(const std::string &inputFile, std::queue<std::string> &gamesQueue) {
    
    std::string line;
    std::ifstream myfile (inputFile);
    
    if (myfile.is_open()) {
        
        //std::cout << "input file: " << std::endl;
        
        while ( getline (myfile, line) ) {
            //std::cout << line << std::endl;
            gamesQueue.push(line);
        }
        myfile.close();
    }

    else std::cout << "Unable to open input file!" << std::endl;
    
}

void createHandCardVector(const std::string &handString, std::vector<Card> &handCardVector) {
    
    for(int i = 0; i < handString.size(); ) {
        
        handCardVector.push_back(Card(handString[i], handString[i+1]) );
        i += 2;
    }
}

void getHandsAndBoard(const std::string &gameString, std::vector<Card> &handAVector, std::vector<Card> &handBVector, std::vector<Card> &boardVector) {
    
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
//    handAString = "AsAdQhJd9c"; handBString = "AcAhQsJc8d"; //one pair with kicker
//    handAString = "As4dQh6d9c"; handBString = "AcKhQsJc8d"; //high card with kicker
//    handAString = "As4dQh6d9c"; handBString = "7cKhQsJc8d"; //high card
    
    createHandCardVector(handAString, handAVector);
    createHandCardVector(handBString, handBVector);
    createHandCardVector(boardString, boardVector);
    
}

bool allCardsSameSuit(const std::vector<Card> &playersHand) {
    
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

RankHigh findSecondHighRank(const std::vector<Card> &playersHand) {
    
    std::map<RankHigh, int> cardCountMap;
    std::map<RankHigh, int>::reverse_iterator pMap;
    RankHigh highestCardCountRank;
    
    for(auto & card : playersHand) {
        cardCountMap[card.getRankHigh()]++;
    }
    pMap = cardCountMap.rbegin();
    
    if(pMap->second == 2) {
        pMap++;
    }
    if(pMap->second == 2) {
        highestCardCountRank = pMap->first;
    }
    else {
        pMap++;
        highestCardCountRank = pMap->first;
    }

    return highestCardCountRank;
}

RankHigh findHighRank(const std::vector<Card> &playersHand) {
    
    std::map<RankHigh, int> cardCountMap;
    std::map<RankHigh, int>::reverse_iterator pMap;
    
    for(auto & card : playersHand) {
        cardCountMap[card.getRankHigh()]++;
    }
    pMap = cardCountMap.rbegin();
    
    RankHigh highestCardCountRank = pMap->first;
    
    return highestCardCountRank;
}

Card findHighCardAceLow(std::vector<Card> playersHand) {
    
    Card highCard;
    
    std::sort(playersHand.begin(), playersHand.end(), [](const Card & a, const Card & b) -> bool
    {
        return a.getRankLow() > b.getRankLow();
    });
    
    highCard = playersHand[0];
    
    return highCard;
}

Card findHighCardAceHigh(std::vector<Card> playersHand) {
    
    Card highCard;
    
    std::sort(playersHand.begin(), playersHand.end(), [](const Card & a, const Card & b) -> bool
    {
        return a.getRankHigh() > b.getRankHigh();
    });
    
    highCard = playersHand[0];
    
    return highCard;
}

HighPokerHand findHighestHand(const std::vector<Card> &playersHand, Card &highCard, RankHigh &highRank) {
    std::vector<int> rankCountVector(RankCount);

    for (auto &card : playersHand) {
        
        RankHigh rankHigh = card.getRankHigh();
        int cardRank = static_cast<int>(rankHigh);
        ++rankCountVector[cardRank];
    }

    auto rankCountCounter = [&] (int countTarget) {
        long rankCount = std::count(rankCountVector.begin(), rankCountVector.end(), countTarget);
        return rankCount;
    };

    //Straight Flush
    if(allCardsSameSuit(playersHand) && straightCardsAceHigh(playersHand) ) {
        highCard = findHighCardAceHigh(playersHand);
        return HighPokerHand::StraightFlush;
    }
    else if(allCardsSameSuit(playersHand) && straightCardsAceLow(playersHand) ) {
        highCard = findHighCardAceLow(playersHand);
        return HighPokerHand::StraightFlush;
    }
    
    //4 of a kind
    if (rankCountCounter(4) == 1) {
        highRank = findHighRank(playersHand);
        return HighPokerHand::FourOfAKind;
    }
    
    if (rankCountCounter(3) == 1) {
        //Full House
        highRank = findHighRank(playersHand);
        if (rankCountCounter(2) == 1) {
            return HighPokerHand::FullHouse;
        }
        else {
            return HighPokerHand::ThreeOfAKind;
        }
    }
    
    //Flush
    if(allCardsSameSuit(playersHand)) {
        highCard = findHighCardAceHigh(playersHand);
        return HighPokerHand::Flush;
    }
        
    //Straight
    if(!allCardsSameSuit(playersHand) && straightCardsAceHigh(playersHand) ) {
        highCard = findHighCardAceHigh(playersHand);
        return HighPokerHand::Straight;
    }
    else if(!allCardsSameSuit(playersHand) && straightCardsAceLow(playersHand) ) {
        highCard = findHighCardAceLow(playersHand);
        return HighPokerHand::Straight;
    }

    //1 pair
    if (rankCountCounter(2) == 1) {
        highRank = findHighRank(playersHand);
        return HighPokerHand::OnePair;
    }
    
    //2 pair
    if (rankCountCounter(2) == 2) {
        highRank = findHighRank(playersHand);
        return HighPokerHand::TwoPair;
    }
    //High Card
    highCard = findHighCardAceHigh(playersHand);
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

//highest card not being held in common
std::string processKicker(std::vector<Card> highHandCardsA, std::vector<Card> highHandCardsB, HighPokerHand highestHandA, HighPokerHand highestHandB) {

    std::string winningHandString = "";
    
    std::sort(highHandCardsA.begin(), highHandCardsA.end(), [](const Card & a, const Card & b) -> bool
    {
        return a.getRankHigh() > b.getRankHigh();
    });
    
    std::sort(highHandCardsB.begin(), highHandCardsB.end(), [](const Card & a, const Card & b) -> bool
    {
        return a.getRankHigh() > b.getRankHigh();
    });

    std::vector<Card>::iterator pHighHandCardsA;
    std::vector<Card>::iterator pHighHandCardsB;
    
    pHighHandCardsA = highHandCardsA.begin();
    pHighHandCardsB = highHandCardsB.begin();
    
    for( ; pHighHandCardsA != highHandCardsA.end() && pHighHandCardsB != highHandCardsB.end() ; pHighHandCardsA++, pHighHandCardsB++ ) {
        
        if(pHighHandCardsA->getRankHigh() == pHighHandCardsB->getRankHigh()) {
            continue;
        }
        else {
            break;
        }
    }
    
    if(pHighHandCardsA == highHandCardsA.end() || pHighHandCardsB == highHandCardsB.end()) {
        winningHandString = "=> Split Pot Hi " + HighPokerHandStringVector[static_cast<int>(highestHandA)] + "; ";
    }
    else if(pHighHandCardsA->getRankHigh() > pHighHandCardsB->getRankHigh()) {
        winningHandString = "=> HandA wins Hi " + HighPokerHandStringVector[static_cast<int>(highestHandA)] + "; ";
    }
    else if(pHighHandCardsA->getRankHigh() < pHighHandCardsB->getRankHigh()) {
        winningHandString = "=> HandB wins Hi " + HighPokerHandStringVector[static_cast<int>(highestHandB)] + "; ";
    }
    else {
        winningHandString = "=> Split Pot Hi " + HighPokerHandStringVector[static_cast<int>(highestHandA)] + "; ";
    }

    return winningHandString;
}


HighPokerHand findHighestHandCombination(const std::vector<std::vector<Card>> &handXCardsPermutationVector,
                                         const std::vector<std::vector<Card>> &boardCardsPermutationVector,
                                         Card &highCard,
                                         RankHigh &highRank,
                                         std::vector<Card> &highHandCards) {
    
    HighPokerHand highestHand = HighPokerHand::HighCard;
    
    HighPokerHand handX;
    
    std::vector<Card> handXCardsVector;
    std::vector<Card> boardCardsVector;
    
    Card currentHighCard = Card('2', 's');
    
    for(auto &cardPermutation : handXCardsPermutationVector) {
        
        handXCardsVector.push_back(cardPermutation[0]);
        handXCardsVector.push_back(cardPermutation[1]);
        
        for(auto &boardPermutation : boardCardsPermutationVector) {
            
            handXCardsVector.push_back(boardPermutation[0]);
            handXCardsVector.push_back(boardPermutation[1]);
            handXCardsVector.push_back(boardPermutation[2]);
            
            handX = findHighestHand(handXCardsVector, highCard, highRank);
            
            if(handX == highestHand && highHandCards != handXCardsVector) {
                
                if(handX == HighPokerHand::StraightFlush ||
                   handX == HighPokerHand::Straight) {
                    
                    if(highCard.getRankHigh() > currentHighCard.getRankHigh()) {
                        highHandCards = handXCardsVector;
                        currentHighCard = highCard;
                    }
                }
                else {
                
                    //need to compare similar hands for higher kicker etc...
                    std::string testForNewHighHand = processKicker(handXCardsVector, highHandCards, highestHand, highestHand);
                    size_t found = testForNewHighHand.find("HandA");
                    if (found != std::string::npos) {
                        highHandCards = handXCardsVector;
                    }
                }
            }
            
            if(handX > highestHand) {
                highestHand = handX;
                highHandCards = handXCardsVector;
            }
            handXCardsVector.pop_back();
            handXCardsVector.pop_back();
            handXCardsVector.pop_back();
        }
        handXCardsVector.clear();
    }
    
    if(highestHand == HighPokerHand::StraightFlush ||
       highestHand == HighPokerHand::Straight) {
        
        highCard = currentHighCard;
    }
    
    
    return highestHand;
}


//A player must combine any two of his cards with any three cards from the board to obtain 5 cards with the highest possible ranking for high hand,
std::string playHiHandGame(const std::vector<std::vector<Card>> &handACardsPermutationVector,
                           const std::vector<std::vector<Card>> &handBCardsPermutationVector,
                           const std::vector<std::vector<Card>> &boardCardsPermutationVector) {
    
    std::string winningHandString = "";
    
    Card highCardA, kickerA;
    Card highCardB, kickerB;
    RankHigh highRankA, highRankB;
    std::vector<Card> highHandCardsA;
    std::vector<Card> highHandCardsB;
    
    HighPokerHand highestHandA = findHighestHandCombination(handACardsPermutationVector, boardCardsPermutationVector, highCardA, highRankA, highHandCardsA);
    HighPokerHand highestHandB = findHighestHandCombination(handBCardsPermutationVector, boardCardsPermutationVector, highCardB, highRankB, highHandCardsB);
     
    if(highestHandA > highestHandB) {
        winningHandString = "=> HandA wins Hi " + HighPokerHandStringVector[static_cast<int>(highestHandA)] + "; ";
    }
    else if(highestHandA < highestHandB) {
        winningHandString = "=> HandB wins Hi " + HighPokerHandStringVector[static_cast<int>(highestHandB)] + "; ";
    }
    else { //(highestHandA == highestHandB)
        
        //high card check
        if(highestHandA == HighPokerHand::StraightFlush ||
           highestHandA == HighPokerHand::Flush ||
           highestHandA == HighPokerHand::Straight) {
         
            if(highCardA.getRankHigh() > highCardB.getRankHigh()) {
                winningHandString = "=> HandA wins Hi " + HighPokerHandStringVector[static_cast<int>(highestHandA)] + "; ";
            }
            else if(highCardA.getRankHigh() < highCardB.getRankHigh()) {
                winningHandString = "=> HandB wins Hi " + HighPokerHandStringVector[static_cast<int>(highestHandB)] + "; ";
            }
            else {
                winningHandString = processKicker(highHandCardsA, highHandCardsB, highestHandA, highestHandB);
            }
        }
        //high card check
        else if(highestHandA == HighPokerHand::HighCard ) {

            if(highCardA.getRankHigh() > highCardB.getRankHigh()) {
                winningHandString = "=> HandA wins Hi " + HighPokerHandStringVector[static_cast<int>(highestHandA)] + "; ";
            }
            else if(highCardA.getRankHigh() < highCardB.getRankHigh()) {
                winningHandString = "=> HandB wins Hi " + HighPokerHandStringVector[static_cast<int>(highestHandB)] + "; ";
            }
            else {
                winningHandString = processKicker(highHandCardsA, highHandCardsB, highestHandA, highestHandB);
            }
        }
        else { //high rank check
            
            if(highestHandA == HighPokerHand::FullHouse ||
               highestHandA == HighPokerHand::OnePair ||
               highestHandA == HighPokerHand::ThreeOfAKind ||
               highestHandA == HighPokerHand::FourOfAKind) {
                
                if(highRankA > highRankB) {
                    winningHandString = "=> HandA wins Hi " + HighPokerHandStringVector[static_cast<int>(highestHandA)] + "; ";
                }
                else if(highRankA < highRankB) {
                    winningHandString = "=> HandB wins Hi " + HighPokerHandStringVector[static_cast<int>(highestHandB)] + "; ";
                }
                else {
                    //only 1 pair could land here
                    winningHandString = processKicker(highHandCardsA, highHandCardsB, highestHandA, highestHandB);
                }
            }
            else {
                //highestHandA == HighPokerHand::TwoPair
                
                if(highRankA > highRankB) {
                    winningHandString = "=> HandA wins Hi " + HighPokerHandStringVector[static_cast<int>(highestHandA)] + "; ";
                }
                else if(highRankA < highRankB) {
                    winningHandString = "=> HandB wins Hi " + HighPokerHandStringVector[static_cast<int>(highestHandB)] + "; ";
                }
                else {
                    highRankA = findSecondHighRank(highHandCardsA);
                    highRankB = findSecondHighRank(highHandCardsB);
                    
                    if(highRankA > highRankB) {
                        winningHandString = "=> HandA wins Hi " + HighPokerHandStringVector[static_cast<int>(highestHandA)] + "; ";
                    }
                    else if(highRankA < highRankB) {
                        winningHandString = "=> HandB wins Hi " + HighPokerHandStringVector[static_cast<int>(highestHandB)] + "; ";
                    }
                    else {
                        winningHandString = "=> Split Pot Hi " + HighPokerHandStringVector[static_cast<int>(highestHandA)] + "; ";
                    }
                }
            }
        }
    }
    
    return winningHandString;
}







LowPokerHand confirmLowHandCards(const std::vector<Card> &handXCardsVector) {
    
    LowPokerHand lowestHand = LowPokerHand::DoesNotQualify;
    
    std::map<RankLow, int> rankCountMap;
    
    for(auto &card : handXCardsVector) {
    //b) None of the cards should be higher than 8. Aces are always considered to have the value of 1 for low hand evaluation.
        if(card.getRankLow() > RankLow::Eight) {
            return lowestHand;
        }
        rankCountMap[card.getRankLow()]++;
    }
    
    for(auto &cardRank : rankCountMap) { //a) All 5 cards should have different rank
        if(cardRank.second > 1) {
            return lowestHand;
        }
    }
    
    lowestHand = LowPokerHand::DoesQualify;
    
    return lowestHand;
}

int convertCardVectorToInt(const std::vector<Card> &playerHand) {
    
    int result = 0;
    
    for(int i = 0; i < playerHand.size(); i++) {
        
        int cardValue = static_cast<int>(playerHand[i].getRankLow()) + 1;
        
        result *= 10;
        result += cardValue;
    }
    
    return result;
}

LowPokerHand findLowestHandCombination(const std::vector<std::vector<Card>> &handXCardsPermutationVector,
                                         const std::vector<std::vector<Card>> &boardCardsPermutationVector,
                                       std::vector<Card> &lowHandCards,
                                       std::vector<int> &lowHandIntVectorX) {
    
    int lowestHandValue = INT_MAX;
    
    LowPokerHand handX = LowPokerHand::DoesNotQualify;
    LowPokerHand lowestHandX = LowPokerHand::DoesNotQualify;
    
    std::vector<Card> handXCardsVector;
    std::vector<Card> boardCardsVector;
    std::vector<Card> tempCardsVector;
    
    for(auto &cardPermutation : handXCardsPermutationVector) {
        
        handXCardsVector.push_back(cardPermutation[0]);
        handXCardsVector.push_back(cardPermutation[1]);
        
        for(auto &boardPermutation : boardCardsPermutationVector) {
            
            handXCardsVector.push_back(boardPermutation[0]);
            handXCardsVector.push_back(boardPermutation[1]);
            handXCardsVector.push_back(boardPermutation[2]);
            
            handX = confirmLowHandCards(handXCardsVector);
            
            if(handX == LowPokerHand::DoesQualify) {
                tempCardsVector = handXCardsVector;

                std::sort(tempCardsVector.begin(), tempCardsVector.end(), [](const Card & a, const Card & b) -> bool
                {
                    return a.getRankLow() > b.getRankLow();
                });
                            
                int playerCardsHandIntValue = convertCardVectorToInt(tempCardsVector);
                
                if(playerCardsHandIntValue < lowestHandValue) {
                    lowestHandValue = playerCardsHandIntValue;
                    lowHandCards = tempCardsVector;
                    lowestHandX = handX;
                }
            }
            handXCardsVector.pop_back();
            handXCardsVector.pop_back();
            handXCardsVector.pop_back();
        }
        handXCardsVector.clear();
    }
    
    lowHandIntVectorX.push_back(lowestHandValue);
    
    return lowestHandX;
}

std::string convertLoHandToString(std::vector<Card> lowHandIntVectorX) {
    
    std::string result = "";
    
    for(int i = 0; i < lowHandIntVectorX.size(); i++) {
        
        int cardValue = static_cast<int>(lowHandIntVectorX[i].getRankLow()) + 1;
        
        std::string stringValue = std::to_string(cardValue);
        
        if(stringValue == "1") {
            stringValue = "A";
        }
        result += stringValue;
    }

    return result;
}


//player must combine any other (or same) two of his cards with any other (or same) three cards from the board to obtain 5 cards with lowest possible low hand.
std::string playLoHandGame(const std::vector<std::vector<Card>> &handACardsPermutationVector,
                           const std::vector<std::vector<Card>> &handBCardsPermutationVector,
                           const std::vector<std::vector<Card>> &boardCardsPermutationVector) {
    
    std::string winningLoHandString = "";
    
    std::vector<Card> lowHandCardsA;
    std::vector<Card> lowHandCardsB;
    std::vector<int> lowHandIntVectorA;
    std::vector<int> lowHandIntVectorB;
    int lowHandIntValueA;
    int lowHandIntValueB;
    
    LowPokerHand lowestHandA = findLowestHandCombination(handACardsPermutationVector, boardCardsPermutationVector, lowHandCardsA, lowHandIntVectorA);
    LowPokerHand lowestHandB = findLowestHandCombination(handBCardsPermutationVector, boardCardsPermutationVector, lowHandCardsB, lowHandIntVectorB);
    
    lowHandIntValueA = lowHandIntVectorA[0];
    lowHandIntValueB = lowHandIntVectorB[0];
    
//    Any qualified low hand beats a hand that did not qualify for low. If no hand qualifies for low, then all chips are awarded to the winner(s) of the high hand.
    
//If both hands qualify for low, the hand containing higher card loses, i.e. 5432A beats 86743. If senior card or cards are equal, then the first card that is different decides the hand. For example, 7632A beats 76432, because the third card for the second hand is higher than the third card for the first hand.
    
    
    if(lowestHandA == LowPokerHand::DoesQualify && lowestHandB == LowPokerHand::DoesNotQualify) {
        winningLoHandString = "HandA wins Lo (" + convertLoHandToString(lowHandCardsA) + ")";
    }
    else if(lowestHandA == LowPokerHand::DoesNotQualify && lowestHandB == LowPokerHand::DoesQualify) {
        winningLoHandString = "HandB wins Lo (" + convertLoHandToString(lowHandCardsB) + ")";
    }
    else if(lowestHandA == LowPokerHand::DoesNotQualify && lowestHandB == LowPokerHand::DoesNotQualify) {
        winningLoHandString = "No hand qualified for Low";
    }
    else if(lowHandIntValueA < lowHandIntValueB ) {
        winningLoHandString = "HandA wins Lo (" + convertLoHandToString(lowHandCardsA) + ")";
    }
    else if(lowHandIntValueA > lowHandIntValueB) {
        winningLoHandString = "HandB wins Lo (" + convertLoHandToString(lowHandCardsB) + ")";
    }
    else {
        winningLoHandString = "Split Pot Lo (" + convertLoHandToString(lowHandCardsA) + ")";
    }
    
    return winningLoHandString;
}



int main(int argc, const char * argv[]) {
    
    std::cout << "OMAHA Hi/Lo Game" << std::endl << std::endl;
    
    std::string inputFile;
    std::string outputFile;
    std::string outputString;
    
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
        
        auto sortLambda = [](const Card & a, const Card & b) -> bool
        {
            return a.getRankHigh() > b.getRankHigh();
        };
        std::sort(handAVector.begin(), handAVector.end(), sortLambda);
        std::sort(handBVector.begin(), handBVector.end(), sortLambda);
        std::sort(boardVector.begin(), boardVector.end(), sortLambda);
        
        std::vector<std::vector<Card>> handACardsPermutationVector; //sort for hi cards to low cards rank
        std::vector<std::vector<Card>> handBCardsPermutationVector;
        std::vector<std::vector<Card>> boardCardsPermutationVector;
        
        cardsPermutation(handAVector, 0, handAVector.size() - 1, handACardsPermutationVector);
        cardsPermutation(handBVector, 0, handBVector.size() - 1, handBCardsPermutationVector);
        cardsPermutation(boardVector, 0, boardVector.size() - 1, boardCardsPermutationVector);
        
        outputString += gameString;
        outputString += '\n';
        
        std::string outputLine = playHiHandGame(handACardsPermutationVector, handBCardsPermutationVector, boardCardsPermutationVector);
        
        outputString += outputLine;
        
        outputLine = playLoHandGame(handACardsPermutationVector, handBCardsPermutationVector, boardCardsPermutationVector);
        outputString += outputLine;
        
        outputString += '\n';
        
        gamesQueue.pop();
    }
    
    std::cout << outputString << std::endl;
    
    std::ofstream ofs (outputFile, std::ofstream::out);
    ofs << outputString;
    ofs.close();
    
    return 0;
}
