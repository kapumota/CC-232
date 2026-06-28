#include <algorithm>
#include <array>
#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <exception>
#include <cstdlib>
#include <numeric>
#include <random>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using Clock = std::chrono::high_resolution_clock;
using Microseconds = std::chrono::duration<double, std::micro>;

struct TimerResult {
    std::string label;
    double microseconds = 0.0;
};

class Bench {
public:
    template <typename F>
    static TimerResult run(const std::string& label, F&& fn, int repeat = 1) {
        volatile std::size_t sink = 0; // evita optimizaciones agresivas del compilador
        double best = std::numeric_limits<double>::max();
        for (int i = 0; i < repeat; ++i) {
            const auto start = Clock::now();
            sink ^= static_cast<std::size_t>(fn());
            const auto end = Clock::now();
            const double elapsed = std::chrono::duration_cast<Microseconds>(end - start).count();
            best = std::min(best, elapsed);
        }
        if (sink == 42u) {
            std::cerr << "";
        }
        return {label, best};
    }

    static void print_table(const std::string& title, const std::vector<TimerResult>& results) {
        std::cout << "\n "<< title << "\n";
        std::cout << std::left << std::setw(35) << "Caso" << std::right << std::setw(15) << "Tiempo (us)" << "\n";
        std::cout << std::string(50, '-') << "\n";
        for (const auto& r : results) {
            std::cout << std::left << std::setw(35) << r.label
                      << std::right << std::setw(15) << std::fixed << std::setprecision(2)
                      << r.microseconds << "\n";
        }
    }
};

struct Student {
    int id = 0;
    int score = 0;
    std::string name;

    bool operator<(const Student& other) const {
        if (score != other.score) return score > other.score; // descendente por score
        return id < other.id;
    }
};

std::mt19937 make_rng() {
    try {
        std::random_device rd;
        std::seed_seq seq{rd(), rd(), rd(), rd(), rd(), rd()};
        return std::mt19937(seq);
    } catch (...) {
        const auto now = static_cast<unsigned>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        return std::mt19937(now ^ 0x9E3779B9u);
    }
}

std::size_t scaled(std::size_t base, int scale_percent) {
    const std::size_t v = (base * static_cast<std::size_t>(scale_percent)) / 100;
    return std::max<std::size_t>(v, 1000);
}

std::vector<int> random_ints(std::size_t n, int low, int high, std::mt19937& rng) {
    std::uniform_int_distribution<int> dist(low, high);
    std::vector<int> data;
    data.reserve(n);
    for (std::size_t i = 0; i < n; ++i) {
        data.push_back(dist(rng));
    }
    return data;
}

std::vector<Student> random_students(std::size_t n, std::mt19937& rng) {
    std::uniform_int_distribution<int> score_dist(0, 1000000);
    std::vector<Student> data;
    data.reserve(n);
    for (std::size_t i = 0; i < n; ++i) {
        data.push_back(Student{static_cast<int>(i), score_dist(rng), "s" + std::to_string(i)});
    }
    return data;
}

std::size_t checksum(const std::vector<int>& data) {
    std::size_t h = 0;
    for (int x : data) {
        h = h * 1315423911u + static_cast<std::size_t>(x + 1000003);
    }
    return h;
}

std::size_t checksum_students(const std::vector<Student>& data, std::size_t limit = 30) {
    std::size_t h = 0;
    const std::size_t end = std::min(limit, data.size());
    for (std::size_t i = 0; i < end; ++i) {
        h ^= static_cast<std::size_t>(data[i].id * 239 + data[i].score * 31 + data[i].name.size());
    }
    return h;
}


int g_scale_percent = 100;

void print_section(const std::string& title, const std::string& idea) {
    std::cout << "\n\n \n";
    std::cout << title << "\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << idea << "\n";
}

std::size_t demo_reserve_vs_no_reserve() {
    print_section(
        "1. reserve() vs crecimiento incremental del vector",
        "Idea algoritmica: si conocemos o estimamos el tamano final, reserve() reduce realocaciones y copias."
    );

    const std::size_t N = scaled(250000, g_scale_percent);
    std::vector<TimerResult> results;

    results.push_back(Bench::run("push_back sin reserve", [=]() -> std::size_t {
        std::vector<int> v;
        for (std::size_t i = 0; i < N; ++i) {
            v.push_back(static_cast<int>(i));
        }
        return checksum(v);
    }, 5));

    results.push_back(Bench::run("push_back con reserve", [=]() -> std::size_t {
        std::vector<int> v;
        v.reserve(N);
        for (std::size_t i = 0; i < N; ++i) {
            v.push_back(static_cast<int>(i));
        }
        return checksum(v);
    }, 5));

    results.push_back(Bench::run("resize y asignacion por indice", [=]() -> std::size_t {
        std::vector<int> v(N);
        for (std::size_t i = 0; i < N; ++i) {
            v[i] = static_cast<int>(i);
        }
        return checksum(v);
    }, 5));

    Bench::print_table("Vector growth", results);
    std::cout << "Comentario: reserve() no cambia el Big-O amortizado de push_back, pero si mejora la constante oculta.\n";
    return static_cast<std::size_t>(results.size());
}

std::size_t demo_emplace_vs_push() {
    print_section(
        "2. emplace_back() vs push_back() en objetos",
        "Idea algoritmica: emplace_back construye el objeto directamente en el contenedor y evita temporales innecesarios."
    );

    const std::size_t N = scaled(120000, g_scale_percent);
    std::vector<TimerResult> results;

    results.push_back(Bench::run("push_back(Student{...})", [=]() -> std::size_t {
        std::vector<Student> v;
        v.reserve(N);
        for (std::size_t i = 0; i < N; ++i) {
            v.push_back(Student{static_cast<int>(i), static_cast<int>(i % 1000), "name_" + std::to_string(i)});
        }
        return checksum_students(v);
    }, 4));

    results.push_back(Bench::run("emplace_back(...) directo", [=]() -> std::size_t {
        std::vector<Student> v;
        v.reserve(N);
        for (std::size_t i = 0; i < N; ++i) {
            v.emplace_back(Student{static_cast<int>(i), static_cast<int>(i % 1000), "name_" + std::to_string(i)});
        }
        return checksum_students(v);
    }, 4));

    results.push_back(Bench::run("emplace_back con objeto ya formado", [=]() -> std::size_t {
        std::vector<Student> v;
        v.reserve(N);
        for (std::size_t i = 0; i < N; ++i) {
            auto s = Student{static_cast<int>(i), static_cast<int>(i % 1000), "name_" + std::to_string(i)};
            v.emplace_back(std::move(s));
        }
        return checksum_students(v);
    }, 4));

    Bench::print_table("Construccion de objetos", results);
    std::cout << "Comentario: en tipos simples el efecto puede ser pequeno; en objetos pesados puede ayudar mass.\n";
    return static_cast<std::size_t>(results.size());
}

std::size_t demo_nth_element_vs_sort(std::mt19937& rng) {
    print_section(
        "3. nth_element() vs sort() para k-esimo elemento",
        "Idea algoritmica: si solo quieres la mediana o el k-esimo menor, nth_element evita ordenar todo el arreglo."
    );

    const std::vector<int> base = random_ints(scaled(180000, g_scale_percent), 1, 1000000000, rng);
    const std::size_t k = base.size() / 2;

    std::vector<TimerResult> results;

    results.push_back(Bench::run("sort completo y tomar mediana", [&]() -> std::size_t {
        auto data = base;
        std::sort(data.begin(), data.end());
        return static_cast<std::size_t>(data[k]);
    }, 4));

    results.push_back(Bench::run("nth_element para mediana", [&]() -> std::size_t {
        auto data = base;
        std::nth_element(data.begin(), data.begin() + static_cast<std::ptrdiff_t>(k), data.end());
        return static_cast<std::size_t>(data[k]);
    }, 4));

    Bench::print_table("Seleccion estadistica", results);
    std::cout << "Comentario: nth_element suele comportarse en O(n) promedio; sort requiere O(n log n).\n";
    return static_cast<std::size_t>(results.size() + base[k % base.size()]);
}

std::size_t demo_top_k_partial_sort(std::mt19937& rng) {
    print_section(
        "4. partial_sort() para Top-K",
        "Idea algoritmica: si solo interesa el Top-K, partial_sort puede ser mejor que ordenar todo."
    );

    const std::vector<Student> base = random_students(scaled(100000, g_scale_percent), rng);
    constexpr std::size_t K = 50;

    std::vector<TimerResult> results;

    results.push_back(Bench::run("sort completo y tomar top-K", [&]() -> std::size_t {
        auto data = base;
        std::sort(data.begin(), data.end());
        return checksum_students(data, K);
    }, 4));

    results.push_back(Bench::run("partial_sort top-K", [&]() -> std::size_t {
        auto data = base;
        std::partial_sort(data.begin(), data.begin() + static_cast<std::ptrdiff_t>(K), data.end());
        return checksum_students(data, K);
    }, 4));

    results.push_back(Bench::run("nth_element + sort solo top-K", [&]() -> std::size_t {
        auto data = base;
        std::nth_element(data.begin(), data.begin() + static_cast<std::ptrdiff_t>(K), data.end());
        std::sort(data.begin(), data.begin() + static_cast<std::ptrdiff_t>(K));
        return checksum_students(data, K);
    }, 4));

    Bench::print_table("Top-K", results);
    std::cout << "Comentario: Top-K aparece mucho en ranking, busqueda, recomendacion y seleccion parcial.\n";
    return static_cast<std::size_t>(results.size());
}

std::size_t demo_lower_bound_binary_search(std::mt19937& rng) {
    print_section(
        "5. lower_bound() en vector ordenado vs busqueda lineal",
        "Idea algoritmica: mantener ordenado un vector permite consultas en O(log n) con excelente localidad de memoria."
    );

    auto data = random_ints(scaled(250000, g_scale_percent), 0, 1000000000, rng);
    std::sort(data.begin(), data.end());

    std::vector<int> queries = random_ints(scaled(30000, g_scale_percent), 0, 1000000000, rng);
    std::vector<TimerResult> results;

    results.push_back(Bench::run("busqueda lineal", [&]() -> std::size_t {
        std::size_t found = 0;
        for (int q : queries) {
            if (std::find(data.begin(), data.end(), q) != data.end()) {
                ++found;
            }
        }
        return found;
    }, 2));

    results.push_back(Bench::run("binary_search / lower_bound", [&]() -> std::size_t {
        std::size_t found = 0;
        for (int q : queries) {
            auto it = std::lower_bound(data.begin(), data.end(), q);
            if (it != data.end() && *it == q) {
                ++found;
            }
        }
        return found;
    }, 4));

    Bench::print_table("Consultas en secuencias ordenadas", results);
    std::cout << "Comentario: vector ordenado + lower_bound es una herramienta muy poderosa en DSA y programacion competitiva.\n";
    return static_cast<std::size_t>(results.size());
}

std::size_t demo_sort_unique_dedup(std::mt19937& rng) {
    print_section(
        "6. sort + unique para eliminar duplicados",
        "Idea algoritmica: deduplicar con sort+unique puede ser muy competitivo y deja los elementos ordenados."
    );

    auto base = random_ints(scaled(220000, g_scale_percent), 1, 50000, rng); // muchos duplicados a proposito
    std::vector<TimerResult> results;

    results.push_back(Bench::run("unordered_set para deduplicar", [&]() -> std::size_t {
        std::unordered_set<int> s;
        s.reserve(base.size());
        for (int x : base) {
            s.insert(x);
        }
        return s.size();
    }, 4));

    results.push_back(Bench::run("sort + unique + erase", [&]() -> std::size_t {
        auto data = base;
        std::sort(data.begin(), data.end());
        data.erase(std::unique(data.begin(), data.end()), data.end());
        return data.size();
    }, 4));

    Bench::print_table("Deduplicacion", results);
    std::cout << "Comentario: sort+unique no siempre gana, pero da orden y muchas veces excelente rendimiento practico.\n";
    return static_cast<std::size_t>(results.size());
}

std::size_t demo_partition_filter(std::mt19937& rng) {
    print_section(
        "7. partition() para filtrar sin preservar orden",
        "Idea algoritmica: si el orden no importa, partition suele ser mejor opcion que copiar uno por uno a otro vector."
    );

    auto base = random_ints(scaled(300000, g_scale_percent), 0, 1000000, rng);
    std::vector<TimerResult> results;

    results.push_back(Bench::run("copiar solo pares a nuevo vector", [&]() -> std::size_t {
        std::vector<int> evens;
        evens.reserve(base.size() / 2);
        for (int x : base) {
            if ((x & 1) == 0) {
                evens.push_back(x);
            }
        }
        return checksum(evens);
    }, 4));

    results.push_back(Bench::run("partition in-place", [&]() -> std::size_t {
        auto data = base;
        auto mid = std::partition(data.begin(), data.end(), [](int x) {
            return (x & 1) == 0;
        });
        data.erase(mid, data.end());
        return checksum(data);
    }, 4));

    Bench::print_table("Filtrado", results);
    std::cout << "Comentario: partition es util cuando solo importa separar elementos por predicado.\n";
    return static_cast<std::size_t>(results.size());
}

std::size_t demo_prefix_sum_queries(std::mt19937& rng) {
    print_section(
        "8. partial_sum() para consultas de rango",
        "Idea algoritmica: preprocesar con prefix sums cambia consultas O(n) por O(1)."
    );

    auto data = random_ints(scaled(180000, g_scale_percent), 1, 50, rng);
    std::vector<int> lq, rq;
    lq.reserve(80000);
    rq.reserve(80000);
    std::uniform_int_distribution<int> dist(0, static_cast<int>(data.size() - 1));
    for (int i = 0; i < 80000; ++i) {
        int l = dist(rng);
        int r = dist(rng);
        if (l > r) std::swap(l, r);
        lq.push_back(l);
        rq.push_back(r);
    }

    std::vector<TimerResult> results;

    results.push_back(Bench::run("sumas de rango simple", [&]() -> std::size_t {
        long long total = 0;
        for (std::size_t i = 0; i < lq.size(); ++i) {
            long long s = 0;
            for (int j = lq[i]; j <= rq[i]; ++j) {
                s += data[static_cast<std::size_t>(j)];
            }
            total += s;
        }
        return static_cast<std::size_t>(total);
    }, 1));

    results.push_back(Bench::run("prefix sums con partial_sum", [&]() -> std::size_t {
        std::vector<long long> pref(data.size() + 1, 0);
        for (std::size_t i = 0; i < data.size(); ++i) {
            pref[i + 1] = pref[i] + data[i];
        }
        long long total = 0;
        for (std::size_t i = 0; i < lq.size(); ++i) {
            total += pref[static_cast<std::size_t>(rq[i]) + 1] - pref[static_cast<std::size_t>(lq[i])];
        }
        return static_cast<std::size_t>(total);
    }, 4));

    Bench::print_table("Preprocesamiento para consultas", results);
    std::cout << "Comentario: este patron conecta STL con tecnica algoritmica clasica de prefijos.\n";
    return static_cast<std::size_t>(results.size());
}

std::size_t demo_merge_inplace_merge(std::mt19937& rng) {
    print_section(
        "9. merge() para combinar secuencias ordenadas",
        "Idea algoritmica: si ya tienes subresultados ordenados, merge evita reordenar todo desde cero."
    );

    auto a = random_ints(scaled(90000, g_scale_percent), 0, 1000000000, rng);
    auto b = random_ints(scaled(90000, g_scale_percent), 0, 1000000000, rng);
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    std::vector<TimerResult> results;

    results.push_back(Bench::run("concatenar y sort", [&]() -> std::size_t {
        std::vector<int> c;
        c.reserve(a.size() + b.size());
        c.insert(c.end(), a.begin(), a.end());
        c.insert(c.end(), b.begin(), b.end());
        std::sort(c.begin(), c.end());
        return checksum(c);
    }, 4));

    results.push_back(Bench::run("std::merge", [&]() -> std::size_t {
        std::vector<int> c;
        c.reserve(a.size() + b.size());
        std::merge(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(c));
        return checksum(c);
    }, 4));

    Bench::print_table("Combinar resultados", results);
    std::cout << "Comentario: merge aparece en mergesort, intervalos, k-way merge y procesamiento offline.\n";
    return static_cast<std::size_t>(results.size());
}

std::size_t demo_transform_accumulate(std::mt19937& rng) {
    print_section(
        "10. transform() y accumulate() para pipelines simples",
        "Idea algoritmica: STL permite expresar transformaciones y agregaciones con codigo compacto y menos errores."
    );

    auto data = random_ints(scaled(300000, g_scale_percent), -1000, 1000, rng);
    std::vector<TimerResult> results;

    results.push_back(Bench::run("for manual: cuadrados positivos", [&]() -> std::size_t {
        long long total = 0;
        for (int x : data) {
            if (x > 0) total += 1LL * x * x;
        }
        return static_cast<std::size_t>(total);
    }, 4));

    results.push_back(Bench::run("copy_if + transform + accumulate", [&]() -> std::size_t {
        std::vector<int> positive;
        positive.reserve(data.size());
        std::copy_if(data.begin(), data.end(), std::back_inserter(positive), [](int x) {
            return x > 0;
        });
        std::vector<long long> sq;
        sq.reserve(positive.size());
        std::transform(positive.begin(), positive.end(), std::back_inserter(sq), [](int x) {
            return 1LL * x * x;
        });
        return static_cast<std::size_t>(std::accumulate(sq.begin(), sq.end(), 0LL));
    }, 4));

    Bench::print_table("Pipelines STL", results);
    std::cout << "Comentario: a veces el for manual gana; la leccion es elegir claridad sin perder de vista el costo.\n";
    return static_cast<std::size_t>(results.size());
}

void print_build_instructions() {
    std::cout << "\n\n------Instrucciones-------\n";
    std::cout << "Windows (MSVC):\n";
    std::cout << "  cl /EHsc /std:c++17 /O2 cc232_stl_optimization_demo.cpp\n\n";
    std::cout << "Windows (MinGW g++):\n";
    std::cout << "  g++ -std=c++17 -O2 -Wall -Wextra -pedantic cc232_stl_optimization_demo.cpp -o demo.exe\n\n";
    std::cout << "Linux/macOS:\n";
    std::cout << "  g++ -std=c++17 -O2 -Wall -Wextra -pedantic cc232_stl_optimization_demo.cpp -o demo\n";
}

void print_class_notes() {
    std::cout << "\n\n---------Ideas-----------\n";
    std::cout << "1. Optimizar no es solo micro-optimizar: muchas mejoras vienen de elegir mejor algoritmo.\n";
    std::cout << "2. STL encapsula algoritmos muy potentes: nth_element, partial_sort, lower_bound, merge.\n";
    std::cout << "3. Big-O manda, pero constantes, cache y realocaciones importan mucho.\n";
    std::cout << "4. Medir ayuda, pero medir mal tambien engana: los benchmarks deben interpretarse con cuidado.\n";
    std::cout << "5. La mejor herramienta depende del problema: Top-K, deduplicacion, consultas, filtrado, etc.\n";
}

int main(int argc, char** argv) {
    try {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);

        for (int i = 1; i < argc; ++i) {
            const std::string arg = argv[i];
            if (arg == "--light") {
                g_scale_percent = 35;
            } else if (arg == "--medium") {
                g_scale_percent = 60;
            } else if (arg == "--full") {
                g_scale_percent = 100;
            } else if (arg.rfind("--scale=", 0) == 0) {
                g_scale_percent = std::max(10, std::min(100, std::atoi(arg.substr(8).c_str())));
            }
        }

        std::mt19937 rng = make_rng();

        std::cout << "CC232 - Demostracion avanzada de optimizacion con STL en C++17\n";
        std::cout << "Este programa muestra patrones utiles para algoritmos y estructuras de datos.\n";
        std::cout << "Los tiempos son ilustrativos y pueden variar segun CPU, compilador y sistema operativo.\n";
        std::cout << "Escala de datos: " << g_scale_percent << "% (usa --light, --medium o --full).\n";

        std::size_t summary = 0;
        summary += demo_reserve_vs_no_reserve();
        summary += demo_emplace_vs_push();
        summary += demo_nth_element_vs_sort(rng);
        summary += demo_top_k_partial_sort(rng);
        summary += demo_lower_bound_binary_search(rng);
        summary += demo_sort_unique_dedup(rng);
        summary += demo_partition_filter(rng);
        summary += demo_prefix_sum_queries(rng);
        summary += demo_merge_inplace_merge(rng);
        summary += demo_transform_accumulate(rng);

        print_build_instructions();
        print_class_notes();

        std::cout << "\nChecksum resumen: " << summary << "\n";
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "Error en ejecucion: " << ex.what() << "\n";
        std::cerr << "Prueba correr con --light si tu entorno tiene poca memoria o limites de tiempo.\n";
        return 1;
    } catch (...) {
        std::cerr << "Error desconocido en ejecucion.\n";
        std::cerr << "Prueba correr con --light si tu entorno tiene poca memoria o limites de tiempo.\n";
        return 1;
    }
}
