#pragma once

#include "BenchmarkStats.h"
#include "StructureRecommendation.h"
#include "WorkloadProfile.h"

#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

namespace cc232::week14 {

class BenchmarkReport {
public:
    void setProfile(WorkloadProfile profile) {
        profile_ = profile;
        hasProfile_ = true;
    }

    void addStats(BenchmarkStats stats) {
        stats_.push_back(std::move(stats));
    }

    void addRecommendation(StructureRecommendation recommendation) {
        recommendations_.push_back(std::move(recommendation));
    }

    std::string toMarkdown() const {
        std::ostringstream out;
        out << "### Reporte experimental\n\n";
        if (hasProfile_) {
            out << "#### Perfil\n\n";
            out << "Dominio: " << toString(profile_.domain) << "\n\n";
            out << "Etiqueta: " << profile_.label << "\n\n";
            out << "Tamano: " << profile_.dataSize << "\n\n";
        }
        if (!stats_.empty()) {
            out << "#### Mediciones\n\n";
            out << "| Estructura | Muestras | Promedio ns | Min ns | Max ns |\n";
            out << "|---|---:|---:|---:|---:|\n";
            for (const auto& s : stats_) {
                out << "| " << s.name << " | " << s.samplesNanoseconds.size()
                    << " | " << static_cast<long long>(s.averageNanoseconds())
                    << " | " << s.minNanoseconds()
                    << " | " << s.maxNanoseconds() << " |\n";
            }
            out << "\n";
        }
        if (!recommendations_.empty()) {
            out << "#### Recomendaciones\n\n";
            out << "| Estructura | Puntaje | Complejidad | Justificacion | Limitacion |\n";
            out << "|---|---:|---|---|---|\n";
            for (const auto& r : recommendations_) {
                out << "| " << r.structureName << " | " << std::fixed << std::setprecision(1) << r.score
                    << " | " << r.expectedComplexity << " | " << r.reason << " | " << r.limitation << " |\n";
            }
        }
        return out.str();
    }

private:
    WorkloadProfile profile_;
    bool hasProfile_ = false;
    std::vector<BenchmarkStats> stats_;
    std::vector<StructureRecommendation> recommendations_;
};

}  // namespace cc232::week14
