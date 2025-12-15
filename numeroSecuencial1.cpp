#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

string caracteres =
"abcdefghijklmnopqrstuvwxyz"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"0123456789"
"_";

bool encontrarClaveSecuencial(const string& clave) {
    int N = caracteres.size();

    for (int a = 0; a < N; a++)
        for (int b = 0; b < N; b++)
            for (int c = 0; c < N; c++)
                for (int d = 0; d < N; d++) {

                    string intento;
                    intento += caracteres[a];
                    intento += caracteres[b];
                    intento += caracteres[c];
                    intento += caracteres[d];

                    if (intento == clave)
                        return true;
                }
    return false;
}

int main() {
    string clave = "COMPparalela_123@";
    vector<double> tiempos;
    double tiempoTotal = 0.0;

    ofstream archivo("tiempos_secuencial02.csv");
    archivo << "tiempo_ms\n";

    for (int i = 0; i < 100; i++) {
        auto inicio = chrono::high_resolution_clock::now();
        encontrarClaveSecuencial(clave);
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

    cout << "\n===== RESUMEN SECUENCIAL =====" << endl;
    cout << "Tiempo total (100 ejecuciones): "
         << tiempoTotal << " ms" << endl;
    cout << "Archivo generado: tiempos_secuencial.csv" << endl;

    return 0;
}

//g++ numeroSecuencial1.cpp -o secuencial_00  
//g++ numeroSecuencial1.cpp -O2 -o secuencial_02  