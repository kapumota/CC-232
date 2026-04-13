#include <iostream>
#include "MorinDengBridge.h"

int main() {
    ods::DLList<int> lista;
    lista.add(4);
    lista.add(1);
    lista.add(3);
    lista.add(1);
    lista.add(2);

    cc232::stable_sort_with_deng(lista);
    int removed = cc232::dedup_with_deng(lista);

    std::cout << "DLList reforzada con Deng: ";
    for (int x : cc232::to_vector(lista)) {
        std::cout << x << ' ';
    }
    std::cout << "\nRemovido = " << removed << "\n";
}
