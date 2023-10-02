#include <catch2/catch.hpp>

#include "Loader.h"
#include "Board.h"


TEST_CASE("Test des functions utilitaires", "[Board][Position]")
{
    Loader loader {};
    Board board {loader.getBoard(0)};

    SECTION("Le bon déplacement de la position selon la direction Nord", "[Position][MOVE]"){
        Position posTest {0,0};
        REQUIRE(posTest.move(Direction::NORD) == Position{0,-1});
    }
    SECTION("Le bon déplacement de la position selon la direction Sud", "[Position][MOVE]"){
        Position posTest {0,0};
        REQUIRE(posTest.move(Direction::SUD) == Position{0,1});
    }
    SECTION("Le bon déplacement de la position selon la direction Est", "[Position][MOVE]"){
        Position posTest {0,0};
        REQUIRE(posTest.move(Direction::EST) == Position{1,0});
    }
    SECTION("Le bon déplacement de la position selon la direction Ouest", "[Position][MOVE]"){
        Position posTest {0,0};
        REQUIRE(posTest.move(Direction::OUEST) == Position{-1,0});
    }

    SECTION("Les positions sont bien dans le board", "[isInsideBoard]"){
        Position posHautGauche {0,0};
        Position posBasDroite {17,17};
        REQUIRE(board.isInBoard(Position{0,0}));
        REQUIRE(board.isInBoard(Position{17,17}));
        REQUIRE_FALSE(board.isInBoard(Position{-1,0}));
        REQUIRE_FALSE(board.isInBoard(Position{0,18}));
    }

    SECTION("Récupération des positions en fonction du matériaux") {
        std::vector<Position> rightPos {Position{8,7},Position{8,8},Position{8,9}};
        std::vector<Position> testPos {board.getAllPosMat(Matériaux::ROCK)};
        REQUIRE(testPos.size() == rightPos.size());
        REQUIRE(testPos == rightPos);
    }
}

TEST_CASE("Test des functions du Player", "[Board][Player]")
{
    Loader loader {};
    Board board {loader.getBoard(0)};


}
