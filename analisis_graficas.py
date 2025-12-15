import csv
import matplotlib.pyplot as plt
import numpy as np
import os

# --- RUTA BASE (misma carpeta del script) ---
BASE = os.path.dirname(os.path.abspath(__file__))

# --- FUNCIÓN PARA LEER CSV ---
def leer_tiempos(nombre_archivo):
    tiempos = []
    ruta = os.path.join(BASE, nombre_archivo)

    if not os.path.exists(ruta):
        raise FileNotFoundError(f"No se encontró el archivo: {ruta}")

    with open(ruta, newline='') as f:
        lector = csv.DictReader(f)
        for fila in lector:
            tiempos.append(float(fila['tiempo_ms']))

    return tiempos

# --- CARGA DE DATOS ---
tiempos_secuencial      = leer_tiempos("tiempos_secuencial.csv")
tiempos_paralelo        = leer_tiempos("tiempos_paralelo.csv")
tiempos_secuencial_O2   = leer_tiempos("tiempos_secuencial02.csv")
tiempos_paralelo_O2     = leer_tiempos("tiempos_paralelo02.csv")

# --- PARÁMETROS ---
hilos = 8  # ajusta según tu CPU

# --- MÉTRICAS ---
speedup       = [ts / tp for ts, tp in zip(tiempos_secuencial, tiempos_paralelo)]
eficiencia    = [s / hilos for s in speedup]

speedup_O2    = [ts / tp for ts, tp in zip(tiempos_secuencial_O2, tiempos_paralelo_O2)]
eficiencia_O2 = [s / hilos for s in speedup_O2]

# =========================================================
# GRAFICA 1: TIEMPOS SIN OPTIMIZACIÓN
# =========================================================
plt.figure()
plt.plot(tiempos_secuencial, label="Secuencial")
plt.plot(tiempos_paralelo, label="Paralelo")
plt.title("Tiempo de ejecución por prueba (sin -O2)")
plt.xlabel("Ejecución")
plt.ylabel("Tiempo (ms)")
plt.legend()
plt.grid(True)
plt.show()

# =========================================================
# GRAFICA 2: TIEMPOS CON -O2
# =========================================================
plt.figure()
plt.plot(tiempos_secuencial_O2, label="Secuencial -O2")
plt.plot(tiempos_paralelo_O2, label="Paralelo -O2")
plt.title("Tiempo de ejecución por prueba (con -O2)")
plt.xlabel("Ejecución")
plt.ylabel("Tiempo (ms)")
plt.legend()
plt.grid(True)
plt.show()

# =========================================================
# GRAFICA 3: SPEEDUP
# =========================================================
plt.figure()
plt.plot(speedup, label="Speedup sin -O2")
plt.plot(speedup_O2, label="Speedup con -O2")
plt.title("Speedup por ejecución")
plt.xlabel("Ejecución")
plt.ylabel("Speedup")
plt.legend()
plt.grid(True)
plt.show()

# =========================================================
# GRAFICA 4: EFICIENCIA
# =========================================================
plt.figure()
plt.plot(eficiencia, label="Eficiencia sin -O2")
plt.plot(eficiencia_O2, label="Eficiencia con -O2")
plt.title("Eficiencia por ejecución")
plt.xlabel("Ejecución")
plt.ylabel("Eficiencia")
plt.legend()
plt.grid(True)
plt.show()
