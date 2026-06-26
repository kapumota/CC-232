#include "CapituloProyectoIntegrador.h"

#include <iostream>

int main() {
    using namespace cc232::week14;
    DataStructureAdvisor advisor;
    auto dynamicProfile = makeRangeWorkload(20000, true);
    auto staticProfile = makeRangeWorkload(20000, false);

    std::cout << "Escenario dinamico\n";
    for (const auto& rec : advisor.recommend(dynamicProfile)) {
        std::cout << formatRecommendation(rec) << "\n";
    }

    std::cout << "\nEscenario estatico\n";
    for (const auto& rec : advisor.recommend(staticProfile)) {
        std::cout << formatRecommendation(rec) << "\n";
    }
    return 0;
}
