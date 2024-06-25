// Tuvia Smadar
// Gunslokij@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "board.hpp"
#include "player.hpp"
#include "catan.hpp"
#include <sstream>
TEST_CASE("Catan Constructor & methods")
{
    Player player1(1, "Tuvia");
    Player player2(2, "Libi");
    Player player3(3, "Barel");
    Board board = Board(); 
    Catan catan(player1,player2,player3,board);

    SUBCASE("Players added")
    {
        std::vector<Player *> expected = {&player1, &player2, &player3};
        REQUIRE(catan.players == expected);

    }   

    SUBCASE("Taking development card")
    {
        std::ostringstream capture_stderr;
        std::streambuf* og_stderr = std::cerr.rdbuf(capture_stderr.rdbuf());
        CHECK_NOTHROW(catan.takeDevelopmentCard(1));
        std::cerr.rdbuf(og_stderr);  // Restore the original buffer
        CHECK_EQ(capture_stderr.str(), "It is not your turn!\n");
        // Clear any existing content in the stream
        capture_stderr.str("");
        capture_stderr.clear();

        catan.playTurn(player1);
        for(int i = 0 ; i < 25; i++) {
            catan.takeDevelopmentCard(1);
        }
        CHECK(player1.developmentCards.size()==25);
    }

    SUBCASE("Play turn")
    {
        std::ostringstream capture_stderr;
        std::streambuf* og_stderr = std::cerr.rdbuf(capture_stderr.rdbuf());
        
        catan.playTurn(player1);
        CHECK_NOTHROW(catan.playTurn(player2));
        
        CHECK_EQ(capture_stderr.str(), "Another player is playing his turn\n");
        
        // Clear any existing content in the stream
        capture_stderr.str("");
        capture_stderr.clear();
        // Restore the original buffer
        std::cerr.rdbuf(og_stderr);
    }

    SUBCASE("End turn")
    {
        std::ostringstream capture_stderr;
        std::streambuf* og_stderr = std::cerr.rdbuf(capture_stderr.rdbuf());
        // Clear any existing content in the stream
        capture_stderr.str("");
        capture_stderr.clear();
        
        CHECK_NOTHROW(catan.endTurn(player1));
        
        // Check the new captured output
        CHECK_EQ(capture_stderr.str(), "This is not your turn\n");
        
        // Restore the original buffer
        std::cerr.rdbuf(og_stderr);
    }
}

TEST_CASE("Player Constructor & methods")
{
    Player player1(1, "Tuvia");
    Player player2(2, "Libi");
    Player player3(3, "Barel");
    Board board = Board(); 
    Catan catan(player1,player2,player3,board);
    SUBCASE("PlayerID")
    {
        REQUIRE(player1.getId() == 1);
    }

    SUBCASE("Player name")
    {
        REQUIRE(player1.getName() == "Tuvia");
    }

    SUBCASE("Player resources")
    {
        for (const auto &resource : player1.resources)
        {
            REQUIRE(resource.second == 0);
        }
    }

    SUBCASE("Using development cards")
    {
        catan.playTurn(player1);
        for(int i = 0 ; i < 25; i++) {
            catan.takeDevelopmentCard(1);
        }
        CHECK(player1.developmentCards.size()==25);
        catan.playTurn(player1);

        player1.useYearOfPlenty("Wood","Brick");
        CHECK(player1.resources[0].second == 1);
        CHECK(player1.resources[1].second == 1);
        catan.endTurn(player1);
        catan.playTurn(player2);
        player2.addResource("Brick",1);
        catan.endTurn(player2);
        catan.playTurn(player1);
        player1.useMonopoly(catan,"Brick");
        CHECK(player2.resources[1].second == 0);
        CHECK(player1.resources[1].second == 2);

        player1.placeInitialSettlementAndRoad(0,1,board);
        player1.useRoadBuilding(board,1,2,2,3);
        player1.useKnight(catan);
        player1.useKnight(catan);
        player1.useKnight(catan);
        CHECK(player1.getPoints()==5);
    }
    
}




TEST_CASE("Board Constructor & methods")
{
    Board board = Board();

    Player player1(1,"Tuvia");
    Player player2(2,"Libi");
    Player player3(3,"Barel");


    Catan catan(player1,player2,player3,board);
   
    SUBCASE("Road and settelment assigment validation")
    {
        catan.playTurn(player1);
        std::ostringstream capture_stderr;
        std::streambuf* og_stderr = std::cerr.rdbuf(capture_stderr.rdbuf());
        // Clear any existing content in the stream
        capture_stderr.str("");
        capture_stderr.clear();
        
        CHECK_NOTHROW(player1.placeInitialSettlementAndRoad(1,30,board));
        CHECK_EQ(capture_stderr.str(), "Road is not valid!\n");
        std::cerr.rdbuf(og_stderr);

    }

    SUBCASE("Place city")
    {
        player1.addResource("Wheat", 5);
        player1.addResource("Ore", 5);
        catan.playTurn(player1);
        player1.placeInitialSettlementAndRoad(0,1,board);
        
        CHECK_NOTHROW(player1.upgradeToCity(0,board,catan));

    }
}
/*****************************Unfinished***********************************/

