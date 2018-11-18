#ifndef INTERFAZ_H
#define INTERFAZ_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

class interfaz
{
    public:
        interfaz();
        virtual ~interfaz();
        void parametros();
        void vistaSimulacion(int, int, bool, bool, int, int, int);
        void vistaFinal(float, float, float, float, float, float);

    protected:

    private:

    int nVecesSimulacion;
    int tiempoTotal;
    int quantum;
    bool distribucionExponencial;
    bool valiDarDato(string,int);
};

#endif // INTERFAZ_H
