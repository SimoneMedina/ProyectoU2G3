#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <algorithm>
#include <fstream>
#include <omp.h>

using namespace std;

string caracteres =
"abcdefghijklmnopqrstuvwxyz"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"0123456789"
"_";

bool encontrarClaveParalelo(const string& clave) {
    int N = caracteres.size();
    bool encontrada = false;
    int hilos = omp_get_max_threads();

#pragma omp parallel shared(encontrada)
    {
        int id = omp_get_thread_num();
        int inicio = (N * id) / hilos;
        int fin = (N * (id + 1)) / hilos;

        for (int a = inicio; a < fin && !encontrada; a++)
            for (int b = 0; b < N && !encontrada; b++)
                for (int c = 0; c < N && !encontrada; c++)
                    for (int d = 0; d < N && !encontrada; d++) {

                        string intento;
                        intento += caracteres[a];
                        intento += caracteres[b];
                        intento += caracteres[c];
                        intento += caracteres[d];

                        if (intento == clave) {
#pragma omp critical
                            encontrada = true;
                        }
                    }
    }
    return encontrada;
}

int main() {
    string clave = "COMPparalela_123@";
    vector<double> tiempos;
    double tiempoTotal = 0.0;

    ofstream archivo("tiempos_paralelo02.csv");
    archivo << "tiempo_ms\n";

    omp_set_num_threads(omp_get_max_threads());

    for (int i = 0; i < 100; i++) {
        auto inicio = chrono::high_resolution_clock::now();
        encontrarClaveParalelo(clave);
        auto fin = chrono::high_resolution_clock::now();

        double tiempo =
            chrono::duration<double, milli>(fin - inicio).count();

        tiempos.push_back(tiempo);
        tiempoTotal += tiempo;

        archivo << tiempo << "\n";

        cout << "Ejecucion " << i + 1
             << " | Tiempo: " << tiempo << " ms" << endl;
    }

    archivo.close();

    sort(tiempos.begin(), tiempos.end());

    cout << "\n===== RESUMEN PARALELO =====" << endl;
    cout << "Tiempo total (100 ejecuciones): "
         << tiempoTotal << " ms" << endl;
    cout << "Archivo generado: tiempos_paralelo.csv" << endl;

    return 0;
}

//g++ numeroParalelo1.cpp -fopenmp -o paralelo_00
//g++ numeroParalelo1.cpp -fopenmp -O2 -o paralelo_02