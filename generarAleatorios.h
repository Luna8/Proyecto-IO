#ifndef GENERAR_ALEATORIOS_H
#define GENERAR_ALEATORIOS_H

#include <math.h>
#include <stdio.h>      /* NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>  

class generarAleatorios {
  public:
    generarAleatorios();
    virtual ~generarAleatorios();
    double generarSiguienteArribo(bool normal);
    double generarTiempoOcurrencia(int quantum);
    int generarInterrupcion();
    double generarTiempoES();
};

#endif //GENERAR_ALEATORIOS_H