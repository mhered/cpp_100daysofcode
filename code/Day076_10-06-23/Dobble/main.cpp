#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "dobble.hpp"

std::vector<std::string> icons = {
    "coffee",
    "knight",
    "rubik3",
    "color_pencil",
    "lego",
    "smartphone",
    "apple",
    "cookie",
    "sneakers",
    "balloons",
    "diamond",
    "lion",
    "stack_of_books",
    "banana",
    "nigiri",
    "basketball",
    "drink",
    "oboe",
    "strawberry",
    "bike_helmet",
    "f1_car",
    "palette",
    "straws",
    "burger",
    "fish",
    "pancakes",
    "sunglasses",
    "caravan",
    "flamenco",
    "pirate",
    "sun",
    "chef",
    "flower",
    "plane_ticket",
    "swimming",
    "chinese_dragon",
    "gamepad",
    "popcorn",
    "tyrannosaurus_rex",
    "cinema_ticket",
    "icecream",
    "puffin",
    "violin",
    "circus_tent",
    "jellyfish",
    "robot",
    "zebra",
    "clover",
    "judo",
    "rocket",
    "light_bulb",
    "star",
    "board_games",
    "surf",
    "tennis",
    "programming",
    "plane"};

int count_matches(std::vector<int> card1, std::vector<int> card2)
{
    int count = 0;
    for (int i = 0; i < card1.size(); i++)
    {
        for (int j = 0; j < card2.size(); j++)
        {
            if (card1[i] == card2[j])
                count++;
        }
    }
    return count;
}

bool check_deck(std::vector<std::vector<int>> cards)
{
    bool result = true;
    for (int i = 0; i < cards.size(); i++)
    {
        for (int j = 0; j < cards.size(); j++)
        {
            if (i != j)
            {
                int matches = count_matches(cards[i], cards[j]);
                if (matches != 1)
                {
                    std::cout << "Error: cards " << i << " and " << j << " have " << matches << " matches" << std::endl;
                    result = false;
                }
            }
        }
    }

    // List all cards
    int i = 0;
    for (auto card : cards)
    {
        std::cout << "" << i++ << ": " << std::flush;

        for (auto idx : card)
        {
            std::cout << icons[idx - 1] << ", " << std::flush;
        }
        std::cout << std::endl;
    }
    return result;
}

int main()
{
    // Dobble Algorithm
    // Based on http://www.101computing.net/the-dobble-algorithm/  (python)

    // The number of symbols on a card has to be a prime number n + 1
    int numberOfSymbolsOnCard = 8; // i.e. 7+1
    bool shuffleSymbolsOnCard = false;

    std::vector<std::vector<int>> cards;

    // Work out the prime number
    int n = numberOfSymbolsOnCard - 1;

    // Total number of cards that can be generated following the Dobble rules
    int numberOfCards = std::pow(n, 2) + n + 1; // e.g. 7^2 + 7 + 1 = 57

    // Add first set of n+1 cards (e.g. 8 cards)
    for (int i = 0; i < (n + 1); i++)
    {
        // Each will contain the first symbol
        std::vector<int> card = {1};
        // And n more symbols
        for (int j = 0; j < n; j++)

        {
            card.push_back((j + 1) + (i * n) + 1);
        }
        cards.push_back(card);
    }

    // Add n sets of n cards
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // Make a new card with 1 symbol
            std::vector<int> card = {i + 2};
            // Add n symbols on the card(e.g .7 symbols)
            for (int k = 0; k < n; k++)
            {
                int val = (n + 1 + n * k + (i * k + j) % n) + 1;
                card.push_back(val);
            }
            cards.push_back(card);
        }
    }
    if (!check_deck(cards))
        return -1;

    // create deck
    for (int i = 0; i < cards.size(); i++)
    {
        std::stringstream ss;
        ss << "Card" << std::setw(2) << std::setfill('0') << i + 1;

        std::vector<std::string> icons_in_card;
        for (int k = 0; k < cards[i].size(); k++)
            icons_in_card.push_back(icons[cards[i][k] - 1]);

        make_dobble_card(icons_in_card, ss.str());
    }
}