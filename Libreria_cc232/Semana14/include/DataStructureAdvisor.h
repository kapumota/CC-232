#pragma once

#include "StructureRecommendation.h"
#include "WorkloadProfile.h"

#include <string>
#include <vector>

namespace cc232::week14 {

class DataStructureAdvisor {
public:
    std::vector<StructureRecommendation> recommend(const WorkloadProfile& profile) const {
        profile.validate();
        std::vector<StructureRecommendation> result;
        switch (profile.domain) {
            case WorkloadDomain::Dictionary:
                addDictionaryRecommendations(profile, result);
                break;
            case WorkloadDomain::RangeQuery:
                addRangeRecommendations(profile, result);
                break;
            case WorkloadDomain::Sorting:
                addSortingRecommendations(profile, result);
                break;
            case WorkloadDomain::TextIndex:
                addTextRecommendations(profile, result);
                break;
            case WorkloadDomain::Graph:
                addGraphRecommendations(profile, result);
                break;
            case WorkloadDomain::ExternalMemory:
                addExternalMemoryRecommendations(profile, result);
                break;
            case WorkloadDomain::Mixed:
                addDictionaryRecommendations(profile, result);
                addRangeRecommendations(profile, result);
                addTextRecommendations(profile, result);
                break;
        }
        return sortRecommendations(result);
    }

private:
    static void addDictionaryRecommendations(const WorkloadProfile& p, std::vector<StructureRecommendation>& out) {
        if (p.requiresExactSearch && !p.requiresOrderedTraversal && !p.requiresRangeScan) {
            out.push_back({"HashTable", 94.0, "busqueda exacta dominante con orden no requerido", "costo esperado, sensible a hashing", "O(1) esperado"});
        }
        if (p.requiresOrderedTraversal || p.requiresRangeScan) {
            out.push_back({"RedBlackTree", 88.0, "mantiene claves ordenadas y peor caso logaritmico", "menor localidad que B+Tree", "O(log n)"});
            out.push_back({"AVLTree", 84.0, "busqueda estrictamente balanceada", "rotaciones mas frecuentes", "O(log n)"});
        }
        out.push_back({"Treap", 78.0, "balance esperado y codigo compacto", "depende de prioridades aleatorias", "O(log n) esperado"});
        out.push_back({"BST", 42.0, "sirve como linea base didactica", "puede degenerar a O(n)", "O(h)"});
    }

    static void addRangeRecommendations(const WorkloadProfile& p, std::vector<StructureRecommendation>& out) {
        if (p.requiresStaticQueries && p.updateRatio == 0.0) {
            out.push_back({"SparseTable", 95.0, "consultas estaticas idempotentes como min, max o gcd", "no soporta actualizaciones eficientes", "O(1) consulta, O(n log n) preproceso"});
            out.push_back({"PrefixSums", 89.0, "sumas de rango estaticas", "solo para operaciones invertibles simples", "O(1) consulta, O(n) preproceso"});
        }
        if (p.requiresDynamicUpdates || p.updateRatio > 0.0) {
            out.push_back({"FenwickTree", 91.0, "sumas dinamicas con actualizacion puntual", "menos general que SegmentTree", "O(log n)"});
            out.push_back({"SegmentTree", 90.0, "consultas y actualizaciones dinamicas generales", "usa mas memoria y codigo", "O(log n)"});
            out.push_back({"LazySegmentTree", 96.0, "actualizaciones por rango y consultas por rango", "mayor complejidad de implementacion", "O(log n)"});
        }
    }

    static void addSortingRecommendations(const WorkloadProfile& p, std::vector<StructureRecommendation>& out) {
        if (p.hasSmallIntegerUniverse) {
            out.push_back({"CountingSort", 93.0, "dominio entero pequeno", "no aplica a claves generales", "O(n + k)"});
            out.push_back({"RadixSort", 88.0, "enteros o cadenas con representacion por digitos", "depende del modelo de claves", "O(d(n + b))"});
        }
        out.push_back({"IntroSort", 92.0, "ordenamiento general robusto", "no es estable", "O(n log n)"});
        out.push_back({"MergeSort", 85.0, "estable y predecible", "requiere memoria auxiliar", "O(n log n)"});
        out.push_back({"InsertionSort", p.dataSize <= 64 ? 82.0 : 40.0, "excelente para datos pequenos o casi ordenados", "no escala a n grande", "O(n^2) peor caso"});
    }

    static void addTextRecommendations(const WorkloadProfile& p, std::vector<StructureRecommendation>& out) {
        if (p.requiresPrefixSearch) {
            out.push_back({"Trie", 97.0, "busqueda por prefijo y autocompletado", "memoria alta si el alfabeto es grande", "O(longitud)"});
        }
        out.push_back({"KMP", 82.0, "un patron exacto con garantia lineal", "no es ideal para muchos patrones", "O(n + m)"});
        out.push_back({"AhoCorasick", 94.0, "muchos patrones simultaneos", "preproceso mas costoso", "O(texto + coincidencias)"});
        out.push_back({"SuffixArray", 88.0, "texto estatico y busqueda de substrings", "construccion mas compleja", "O(m log n) busqueda basica"});
    }

    static void addGraphRecommendations(const WorkloadProfile& p, std::vector<StructureRecommendation>& out) {
        if (p.graphIsDense) {
            out.push_back({"AdjacencyMatrix", 90.0, "grafo denso o muchas consultas de adyacencia", "memoria O(n^2)", "O(1) adyacencia"});
        } else {
            out.push_back({"AdjacencyList", 94.0, "grafo disperso y recorridos", "consulta de adyacencia puede costar grado", "O(n + m) recorrido"});
        }
        if (p.graphNeedsShortestPath) {
            out.push_back({"Dijkstra", 91.0, "pesos no negativos y caminos minimos", "no soporta pesos negativos", "O((n + m) log n)"});
        }
        if (p.graphNeedsMst) {
            out.push_back({"KruskalDSU", 89.0, "MST con aristas ordenadas y DSU", "requiere ordenar aristas", "O(m log m)"});
            out.push_back({"Prim", 86.0, "MST desde vertices y cola de prioridad", "depende de representacion", "O(m log n)"});
        }
    }

    static void addExternalMemoryRecommendations(const WorkloadProfile& p, std::vector<StructureRecommendation>& out) {
        if (p.dataMayExceedMemory || p.requiresRangeScan) {
            out.push_back({"BPlusTree", 98.0, "busquedas y range scans con hojas enlazadas", "implementacion mas compleja", "O(log_B n + k/B) I/O"});
            out.push_back({"BTree", 91.0, "reduce altura y accesos a bloques", "range scan menos directo que B+Tree", "O(log_B n) I/O"});
        }
        out.push_back({"BST", 30.0, "linea base para contrastar altura", "mala localidad y altura grande", "O(h) I/O"});
    }
};

}  // namespace cc232::week14
