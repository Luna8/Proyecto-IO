#ifndef SIMULACION_H
#define SIMULACION_H

#include "Simulacion.h"
#include "generarAleatorios.h"
#include <cstdlib>
#include <stdio.h>
#include <queue>
#include <limits>

using namespace std;

struct proceso{
  int horaInicio;
  int inicioCPU;
  int tiempoCPU;
  int inicioES;
  int tiempoES;
  proceso(int hi = 0){
    horaInicio = hi;
    inicioCPU = 0;
    tiempoCPU = 0;
    inicioES = 0;
    tiempoES = 0;
  }
};

class Simulacion{
  public:
    Simulacion();
    virtual ~Simulacion();
    void E1(bool normal);
    void E2(int tipo);
    void E3();
    void establecerReloj(int t);
    void establecerE_1(int E1);
    void establecerE_2(int E2);
    void establecerE_3(int E3);
    void establecerServidorOcupado(bool o);
    void establecerUnidadESOcupado(bool o);
    void establecerQuantum(int q);
    void establecerCantidadProcesos(int n);
    void establecerTiempoProcesos(double t);
    void establecerTiempoES(double t);
    void establecerTiempoCPU(double t);
    void establecerTiempoTotal(double t);
    int obtenerReloj();
    int obtenerE_1();
    int obtenerE_2();
    int obtenerE_3();
    bool obtenerServidorOcupado();
    bool obtenerUnidadESOcupado();
    int obtenerQuantum();
    int obtenerCantidadProcesos();
    double obtenerTiempoProcesos();
    double obtenerTiempoES();
    double obtenerTiempoCPU();
    double obtenerTiempoTotal();
    queue<proceso*> obtenerColaProcesoCPU();
    queue<proceso*> obtenerColaProcesosES();
  private:
    int Reloj;
    int E_1;
    int E_2;
    int E_3;
    bool servidorOcupado =  false;
    bool unidadESOcupado = false;
    int quantum;
    int cantidadProcesos;
    double tiempoProcesos;
    double tiempoES;
    double tiempoCPU;
    double tiempoTotal;

    queue<proceso*> colaProcesosCPU;
    queue<proceso*> colaProcesosES;

    generarAleatorios aleatorio;
};

#endif //SIMULACION_H