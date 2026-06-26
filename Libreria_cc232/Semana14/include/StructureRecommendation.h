#pragma once

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

namespace cc232::week14 {

struct StructureRecommendation {
    std::string structureName;
    double score = 0.0;
    std::string reason;
    std::string limitation;
    std::string expectedComplexity;
};

inline std::vector<StructureRecommendation> sortRecommendations(std::vector<StructureRecommendation> recommendations) {
    std::sort(recommendations.begin(), recommendations.end(), [](const auto& a, const auto& b) {
        if (a.score == b.score) {
            return a.structureName < b.structureName;
        }
        return a.score > b.score;
    });
    return recommendations;
}

inline std::string formatRecommendation(const StructureRecommendation& recommendation) {
    std::ostringstream out;
    out << recommendation.structureName << " | puntaje=" << recommendation.score
        << " | complejidad=" << recommendation.expectedComplexity
        << " | razon=" << recommendation.reason;
    if (!recommendation.limitation.empty()) {
        out << " | limite=" << recommendation.limitation;
    }
    return out.str();
}

}  // namespace cc232::week14
