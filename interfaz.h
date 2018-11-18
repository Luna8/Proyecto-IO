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
        void vistaSimulacion();
        void vistaFinal();

    protected:

    private:

    int nVecesSimulacion;
    int tiempoTotal;
    int quantum;
    bool distribucionExponencial;
    bool valiDarDato(string,int);
};

#endif // INTERFAZ_H
