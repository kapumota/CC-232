#pragma once

#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

namespace cc232::week14 {

enum class WorkloadDomain {
    Dictionary,
    RangeQuery,
    Sorting,
    TextIndex,
    Graph,
    ExternalMemory,
    Mixed
};

inline std::string toString(WorkloadDomain domain) {
    switch (domain) {
        case WorkloadDomain::Dictionary: return "diccionario";
        case WorkloadDomain::RangeQuery: return "consultas de rango";
        case WorkloadDomain::Sorting: return "ordenamiento";
        case WorkloadDomain::TextIndex: return "indice textual";
        case WorkloadDomain::Graph: return "grafos";
        case WorkloadDomain::ExternalMemory: return "memoria externa";
        case WorkloadDomain::Mixed: return "mixto";
    }
    return "desconocido";
}

struct WorkloadProfile {
    WorkloadDomain domain = WorkloadDomain::Mixed;
    std::size_t dataSize = 1000;
    double insertRatio = 0.0;
    double searchRatio = 0.0;
    double eraseRatio = 0.0;
    double rangeQueryRatio = 0.0;
    double updateRatio = 0.0;
    double traversalRatio = 0.0;
    double patternSearchRatio = 0.0;
    bool requiresOrderedTraversal = false;
    bool requiresPrefixSearch = false;
    bool requiresExactSearch = false;
    bool requiresRangeScan = false;
    bool requiresStaticQueries = false;
    bool requiresDynamicUpdates = false;
    bool hasSmallIntegerUniverse = false;
    bool dataMayExceedMemory = false;
    bool graphIsDense = false;
    bool graphHasWeights = false;
    bool graphNeedsMst = false;
    bool graphNeedsShortestPath = false;
    std::string label = "perfil sin nombre";

    double totalOperationRatio() const {
        return insertRatio + searchRatio + eraseRatio + rangeQueryRatio + updateRatio + traversalRatio + patternSearchRatio;
    }

    void validate() const {
        if (dataSize == 0) {
            throw std::invalid_argument("El tamano de datos debe ser positivo");
        }
        const std::vector<double> ratios = {
            insertRatio, searchRatio, eraseRatio, rangeQueryRatio, updateRatio, traversalRatio, patternSearchRatio
        };
        if (std::any_of(ratios.begin(), ratios.end(), [](double x) { return x < 0.0 || x > 1.0; })) {
            throw std::invalid_argument("Las proporciones deben estar entre 0 y 1");
        }
        const double total = totalOperationRatio();
        if (total > 1.000001) {
            throw std::invalid_argument("La suma de proporciones no debe exceder 1");
        }
    }
};

inline WorkloadProfile makeDictionaryWorkload(std::size_t n) {
    WorkloadProfile p;
    p.domain = WorkloadDomain::Dictionary;
    p.dataSize = n;
    p.insertRatio = 0.25;
    p.searchRatio = 0.60;
    p.eraseRatio = 0.10;
    p.traversalRatio = 0.05;
    p.requiresExactSearch = true;
    p.label = "diccionario dinamico";
    return p;
}

inline WorkloadProfile makePrefixWorkload(std::size_t n) {
    WorkloadProfile p;
    p.domain = WorkloadDomain::TextIndex;
    p.dataSize = n;
    p.insertRatio = 0.20;
    p.searchRatio = 0.30;
    p.patternSearchRatio = 0.30;
    p.traversalRatio = 0.10;
    p.requiresPrefixSearch = true;
    p.requiresExactSearch = true;
    p.label = "indice de prefijos";
    return p;
}

inline WorkloadProfile makeRangeWorkload(std::size_t n, bool dynamicUpdates) {
    WorkloadProfile p;
    p.domain = WorkloadDomain::RangeQuery;
    p.dataSize = n;
    p.rangeQueryRatio = dynamicUpdates ? 0.70 : 0.95;
    p.updateRatio = dynamicUpdates ? 0.25 : 0.0;
    p.requiresDynamicUpdates = dynamicUpdates;
    p.requiresStaticQueries = !dynamicUpdates;
    p.label = dynamicUpdates ? "consultas de rango dinamicas" : "consultas de rango estaticas";
    return p;
}

inline WorkloadProfile makeExternalMemoryWorkload(std::size_t n) {
    WorkloadProfile p;
    p.domain = WorkloadDomain::ExternalMemory;
    p.dataSize = n;
    p.insertRatio = 0.20;
    p.searchRatio = 0.50;
    p.rangeQueryRatio = 0.20;
    p.traversalRatio = 0.10;
    p.requiresOrderedTraversal = true;
    p.requiresRangeScan = true;
    p.dataMayExceedMemory = true;
    p.label = "indice en memoria externa";
    return p;
}

}  // namespace cc232::week14
