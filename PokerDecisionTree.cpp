/*
Jhayden Pappas/Dean Bullock
Poker Decision-Making Program Using a Decision Tree
 *
 * This program simulates decision-making in poker using a simple decision tree structure.
 * Based on the player's hand, pot odds, and number of players, it suggests an action:
 * "raise," "call," or "fold." The decision tree is traversed by evaluating hand strength,
 * pot odds, and hand attributes (such as suited or connected cards), then selecting
 * the most favorable action.
 *
 * Key Features:
 * - Hand strength evaluation for pairs, high-value cards, and suited connectors.
 * - Dynamic pot odds calculation to determine bet potential.
 * - Flexible decision tree structure with nodes representing actions based on game conditions.
 * - Dynamic raise amount based on pot size, hand strength, and pot odds.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

struct DecisionNode {
    std::string action;
    double raiseAmount;
    DecisionNode* favorableOdds;
    DecisionNode* moderateOdds;
    DecisionNode* unfavorableOdds;
    
    DecisionNode(std::string act, double raise = 0) 
        : action(act), raiseAmount(raise), favorableOdds(nullptr), moderateOdds(nullptr), unfavorableOdds(nullptr) {}
};

// Function to calculate pot odds
double calculatePotOdds(double potSize, double toCall) {
    return (potSize / toCall) * 100;
}

// Function to evaluate hand strength based on the card ranks
int evaluateHandStrength(int rank1, int rank2, const std::string& suit1, const std::string& suit2) {
    if (rank1 == rank2 && rank1 >= 13) return 12; // Very strong pair (Aces or Kings)
    if (rank1 == rank2) return 10; // Other pairs are strong pre-flop
    if ((rank1 == 14 && rank2 >= 11) || (rank2 == 14 && rank1 >= 11)) return 9; // Premium high-card hands (Ace-King, Ace-Queen)
    if (suit1 == suit2 && (rank1 + rank2 > 15)) return 8; // Suited high cards
    if (suit1 == suit2 && std::abs(rank1 - rank2) == 1) return 7; // Connected suited cards
    if (rank1 + rank2 > 12) return 6; // High cards not suited
    if (std::abs(rank1 - rank2) == 1) return 5; // Connected but not suited
    return 3; // Weak hand
}

// Function to determine a dynamic raise amount with rounding
double calculateRaiseAmount(double potSize, int handStrength, int playersCalled, double potOdds) {
    double raiseAmount = potSize; // Start with pot size as a base raise

    if (handStrength >= 12) { // Very strong hand
        raiseAmount *= 3; // Triple the raise for top hands like pocket Aces or Kings
    } else if (handStrength > 7) { // Strong hand
        raiseAmount *= 1.5; // Increase moderately for other strong hands
    }

    // Further increase if pot odds are exceptionally high
    if (potOdds > 100) {
        raiseAmount *= 1.5; // Increase further for high pot odds
    }

    // Adjust based on number of players
    raiseAmount += playersCalled * 0.1 * potSize;

    // Round to the nearest 0.5 increment
    raiseAmount = std::round(raiseAmount * 2) / 2.0;

    return raiseAmount;
}

// Estimate initial pot size based on blinds and number of players who called
double estimatePotSize(double smallBlind, double bigBlind, int playersCalled) {
    return smallBlind + bigBlind + (playersCalled * bigBlind);
}

// Function to make pre-flop decisions based on pot odds and hand strength
void makeDecision(DecisionNode* root, int handStrength, double potSize, double toCall, int playersCalled, bool isSuited) {
    double potOdds = calculatePotOdds(potSize, toCall);
    std::cout << "Pot odds: " << potOdds << "%\n";

    DecisionNode* current = root;

    // Decision logic based on hand strength, pot odds, and suited condition
    if (handStrength >= 12) { // Very strong hand (e.g., pocket Aces or Kings)
        current = current->favorableOdds;
    } else if (handStrength >= 9 && potOdds > 50) { // Premium high-card hand with favorable pot odds
        current = current->favorableOdds;
    } else if (handStrength >= 7 && potOdds > 50 && isSuited) { // Connected suited cards with high pot odds
        current = current->favorableOdds;
    } else if (handStrength > 5 && potOdds > 50) { // Moderate hand and good pot odds
        current = current->moderateOdds;
    } else { // Low pot odds or weak hand
        current = current->unfavorableOdds;
    }

    if (current->action == "raise") {
        // Calculate a dynamic raise amount
        current->raiseAmount = calculateRaiseAmount(potSize, handStrength, playersCalled, potOdds);
    }

    std::cout << "Action: " << current->action;
    if (current->action == "raise") std::cout << " with amount: $" << current->raiseAmount << "\n";
    else std::cout << "\n";
}

// Function to parse card input
void parseCardInput(const std::string& input, int &rank1, std::string &suit1, int &rank2, std::string &suit2) {
    std::istringstream iss(input);
    std::string card1, card2;
    iss >> card1 >> suit1 >> card2 >> suit2;
    rank1 = std::stoi(card1);
    rank2 = std::stoi(card2);
}

int main() {
    // Define pre-flop decision tree for pot odds
    DecisionNode root("start");
    root.favorableOdds = new DecisionNode("raise"); // Favorable pot odds, raise dynamically
    root.moderateOdds = new DecisionNode("call"); // Moderate odds, call
    root.unfavorableOdds = new DecisionNode("fold"); // Low odds, fold

    int rank1, rank2, playersCalled;
    double smallBlind, bigBlind, toCall;
    std::string suit1, suit2, cardsInput;

    std::cout << "Enter your cards and suits (1-10, Jack = 11, Queen = 12, King = 13, Ace = 14, H = hearts, S = spades, D = diamonds, C = clubs): ";
    std::getline(std::cin, cardsInput);
    parseCardInput(cardsInput, rank1, suit1, rank2, suit2);

    std::cout << "Enter the small blind amount: ";
    std::cin >> smallBlind;

    std::cout << "Enter the big blind amount: ";
    std::cin >> bigBlind;

    std::cout << "Enter the number of players who called the big blind: ";
    std::cin >> playersCalled;

    std::cout << "Enter the amount needed to call: ";
    std::cin >> toCall;

    // Estimate pot size based on blinds and players who called
    double potSize = estimatePotSize(smallBlind, bigBlind, playersCalled);

    // Evaluate hand strength based on cards and suits
    int handStrength = evaluateHandStrength(rank1, rank2, suit1, suit2);

    // Determine if the hand is suited
    bool isSuited = (suit1 == suit2);

    // Make a decision based on inputs
    makeDecision(&root, handStrength, potSize, toCall, playersCalled, isSuited);

    return 0;
}
