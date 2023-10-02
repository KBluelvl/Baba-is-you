#include <catch2/catch.hpp>

#include "Enume.h"
#include "Case.h"


TEST_CASE("Test du block void immuable", "[Case]")
{
    Case caseTest {};

    SECTION("Taille du tableau bien égale à 0 ", "[Size()]"){
        REQUIRE(caseTest.size() == 0);
    }

    SECTION("block immuable pas conté dans la function IsInside", "[IsInside()]") {
        REQUIRE(caseTest.isInside(Matériaux::VOID) == 0);
    }

    SECTION("Block immuable bien présent et que ça ne soit pas un autre", "[to_string()]") {
        REQUIRE(caseTest.to_string() == BlockMatériaux{"void", 0}.to_String()); // teste si c'est bien le bon block
        REQUIRE_FALSE(caseTest.to_string() == BlockMatériaux{"wall", 0}.to_String()); // test pour être sûr que ça soit le bon
    }

    SECTION("Block immuable non récupérable", "[removeLast()]") {
        bool test = false;
        if(caseTest.removeLast() == nullptr) {
            test = true;
        }
        REQUIRE(test);
    }
    SECTION("Block immuable non récupérable", "[removeAll()]") {
        REQUIRE(caseTest.removeAll().size() == 0);
    }
    SECTION("Block immuable non récupérable", "[removeAllType()]") {
        REQUIRE(caseTest.removeAllType(Matériaux::VOID).size() == 0);
    }
}

TEST_CASE("Test du add et remove des blocks", "[Case]")
{
    Case caseTest2 {};
    std::vector<Block*> add2Blocks {new BlockMatériaux{"wall", 1}, new BlockMatériaux{"wall", 1}, new BlockMatériaux{"baba", 1}};

    caseTest2.addLast(add2Blocks);

    SECTION("Taille du tableau bien égale à 3 ", "[Size()]"){
        REQUIRE(caseTest2.size() == 3);
    }

    SECTION("Nbr de blocks selon son métériaux", "[IsInside()]") {
        REQUIRE(caseTest2.isInside(Matériaux::VOID) == 0);
        REQUIRE(caseTest2.isInside(Matériaux::WALL) == 2);
        REQUIRE(caseTest2.isInside(Matériaux::BABA) == 1);
    }

    SECTION("Block visuel est bien celui du dessus", "[to_string()]") {
        REQUIRE_FALSE(caseTest2.to_string() == BlockMatériaux{"void", 0}.to_String());
        REQUIRE(caseTest2.to_string() == BlockMatériaux{"baba", 0}.to_String());
    }

    SECTION("Remove le dernier block", "[removeLast()]") {
        REQUIRE(caseTest2.removeLast()->getName() == "baba");
    }

    caseTest2.removeLast();

    SECTION("Taille du tableau bien égale à 2 suite au remove ", "[Size()]"){
        REQUIRE(caseTest2.size() == 2);
    }

    SECTION("Block immuable non récupérable", "[removeAllType()]") {
        REQUIRE(caseTest2.removeAllType(Matériaux::WALL).size() == 2);
    }
    caseTest2.removeAllType(Matériaux::WALL);

    SECTION("Taille du tableau bien égale à 0 suite au removeAllType ", "[Size()]"){
        REQUIRE(caseTest2.size() == 0);
    }

    caseTest2.addLast(add2Blocks);

    SECTION("Taille du tableau bien égale à 3 suite au rajout ", "[Size()]"){
        REQUIRE(caseTest2.size() == 3);
    }

    SECTION("Block immuable non récupérable", "[removeAll()]") {
        REQUIRE(caseTest2.removeAll().size() == 3);
    }

    caseTest2.removeAll();

    SECTION("Taille du tableau bien égale à 0 suite au removeAll ", "[Size()]"){
        REQUIRE(caseTest2.size() == 0);
    }
}


