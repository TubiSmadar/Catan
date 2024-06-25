#include <iostream>
#include "player.hpp"
#include "board.hpp"
#include "catan.hpp"

using namespace std;


int main() {
    Board board = Board();

    Player player1(1,"Tuvia");
    Player player2(2,"Libi");
    Player player3(3,"Barel");


    Catan catan(player1,player2,player3,board);
    board.printBoard();   
    cout << "Game is ready start first turn" << endl;
    catan.playTurn(player1);
    player1.placeInitialSettlementAndRoad(5,6,board);
    catan.endTurn(player1);
    catan.playTurn(player2);
    player2.placeInitialSettlementAndRoad(10,11,board);
    catan.endTurn(player2);
    catan.playTurn(player3);
    player3.placeInitialSettlementAndRoad(20,19,board);
    player3.placeInitialSettlementAndRoad(18,19,board);
    catan.endTurn(player3);
    catan.playTurn(player2);
    player2.placeInitialSettlementAndRoad(12,11,board);
    catan.endTurn(player2);
    catan.playTurn(player1);
    player1.placeInitialSettlementAndRoad(7,6,board);

    player1.rollDice(catan);
    player1.chooseDevelopmentCard(catan);
    catan.endTurn(player1);

    catan.playTurn(player2);
    player2.rollDice(catan);
    player2.placeRoad(12,13,board,0);
    catan.endTurn(player2);

    catan.playTurn(player3);
    player3.rollDice(catan);
    player3.chooseDevelopmentCard(catan);
    player3.tradeResources(catan,2,"Ore",1,"Wood",1);
    player3.useMonopoly(catan,"Ore");
    catan.endTurn(player3);


    exit(0);

}
