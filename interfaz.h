#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <stdio.h>
#include "windows.h"
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

class interfaz{
  public:
    interfaz();
    virtual ~interfaz();
    void parametros();
    void vistaSimulacion(int, int, bool, bool, int, int, int);
    void vistaFinal(float, float, float, float, float, float);
    bool valiDarDato(string,int);
    void establecerVecesSimulacion(int n);
    void establecerTiempoTotal(int n);
    void establecerQuantum(int q);
    void establecerDistribucion(bool e);
    int obtenerVecesSimulacion();
    int obtenerTiempoTotal();
    int obtenerQuantum();
    bool obtenerDistribucion();
  private:
    int nVecesSimulacion;
    int tiempoTotal;
    int quantum;
    bool distribucionExponencial;
};

#endif // INTERFAZ_H
