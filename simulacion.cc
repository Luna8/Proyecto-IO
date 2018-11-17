#include <iostream>
#include "simulacion.h"
#include  <cstdlib>
#include <queue>  

using namespace std;

void simulacion::E1(){
  Reloj = E1;
  struct proceso p = new struct;
  p.horaInicio =  Reloj;
  if(servidorOcupado){
    colaProcesosCPU.agregar(p);
  }else{
    p.inicioCPU =  Reloj;
    int interrupcion = generarInterrupcion();
    int x;
    int tipo;
    if (interrupcion>=70) {
      x = generarTiempoOcurrencia();
      tipo = (interrupcion >=94)?3 : 2;
    }else{
      x = queantum;
      tipo = 1;
      colaProcesosCP.agregar(p);
    }
    Reloj =  E2 + x;
    p.tiempoCPU += Reloj -p-inicioCPU;
    E2(tipo)
  }
  E1 =Reloj + generarSiguienteArribo();
}

void simulacion::E2(int tipo) {
  Reloj =  E2;
  if (tipo == 3) {
    if (unidadESOcupado) {
      colaProcesosES.agregar(p);
    }else{
      double y = generarTiempoES();
      E3 = Reloj + y;
    }
  }
  if (colaProcesosCPU.tamano()>0) {
    colaProcesosCPU.remover();
    if (tipo == 1) {
      x = quantum;
    }else{
      x = Generar
    }
  }
}
