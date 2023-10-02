#include <catch2/catch.hpp>

#include "Loader.h"


TEST_CASE("Test le bon chargement du Loader", "[Loader]")
{
    Loader loader {};

    SECTION("Nombre de carte jouable == 5", "[Size()]"){
        REQUIRE(loader.getSize() == 5);
    }
}

//section qui vérifie si quand je save et que je prend la map, c'est les même choses
