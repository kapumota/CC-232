#include "CapituloProyectoIntegrador.h"

#include <iostream>

int main() {
    using namespace cc232::week14;
    auto profile = makeDictionaryWorkload(10000);
    DataStructureAdvisor advisor;
    const auto recommendations = advisor.recommend(profile);
    std::cout << "Escenario: " << profile.label << "\n";
    for (const auto& rec : recommendations) {
        std::cout << formatRecommendation(rec) << "\n";
    }
    return 0;
}
