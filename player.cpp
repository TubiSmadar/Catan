#include "player.hpp"
#include <random>
#include <algorithm>
using namespace std;
namespace ariel {
    Player::Player(string name) {
        this->name = name;
        this->points = 0;
        this->developmentCards = {{}};
    }

    Player::Player() {}

    int Player::rollDice() {
        std::random_device rd;
        std::mt19937 g(rd());
        int roll1 =random() % 6 + 1;

        return roll1;
    }
}