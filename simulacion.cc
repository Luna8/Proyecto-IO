#include <iostream>
#include "simulacion.h"
#include  <cstdlib>


using namespace std;

void simulacion::E1(){
  Reloj = E1;
  struct proceso p = new struct;
  p.horaInicio =  Reloj;
  if(servidorOcupado){
    colaProcesosCPU.push(p);
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
      colaProcesosCP.push(p);
    }
    Reloj =  E2 + x;
    p.tiempoCPU += Reloj -p-inicioCPU;
    E2(tipo)
  }
  E1 =Reloj + generarSiguienteArribo();
}

void simulacion::E2(int tipo) {
  Reloj =  E2;
  if(tipo==3){
          if(unidadESOcupado==true){
              colaProcesosES.push(p);
          }else{
              y=generarTiempoES();
              E3=Reloj+y;
          }
      }
  if(tipo==1){
          if(servidorOcupado==true){
              colaProcesosCPU.push(p);
          }else{
              x=quantum;
              colaProcesosCPU.push(p);
          }
          Reloj=Reloj+x;
     }
  if(colaProcesosCPU.tamano()>0){
          colaProcesosCPU.pop();
          if(tipo==1){
              x=quantum;
          }else{
              x=GeneraTiempoSevicio();
          }
          Reloj=Reloj+x;
          if(tipo==1){
              colaProcesosCPU.push(p);
          }
        }else{
            if(tipo==1){
                x=quantum;
            }else{
                x=GeneraTiempoSevicio();
            }                              //u1
            Reloj=Reloj+x;
            if(tipo==1){
                colaProcesosCPU.push(p);
            }else{
                servidorOcupado=false;
            }
        }
        if(tipo==2){
            //almacenar estadísticas
            // almacenar duración del proceso
            // aumentar número de procesos
            tiempoProcesos = tiempo Procesos + (Reloj-inicipCPU);
            cantidadProcesos++;

        }
}

void E3(){
    Reloj=E3;
    //como todos regresan al procesador luego de terminar E/S, hacen losmo que E1, sin generar un
    //nuevo proceso.
    if(servidorOcupado){
        colaProcesosCPU.push(p);
    }else{
        p.InicioCPU = Reloj;
        int interrupcion = generarInterrupcion();
        int x;
        int tipo;
        if(interrupcion >= 70){
            x = generarTiempoOcurrencia();
            tipo = (interrupcion >= 94)? 3 : 2;
        }else{
            x = quantum;
            tipo = 1;
            colaProcesosCPU.push(p);
        }
        E2 = Reloj + x;
        p.tiempoCPU += Reloj-p.InicioCPU;
        E2(tipo) // {1=>'nada', 2=>'termina', 3=>'E/S'}
    }
    if(colaProcesosES.size()>0){
        colaProcesosES.pop(0);
        E3=Reloj+generarTiempoES();
    }else{
        unidadESOcupada=false;
        //almacenar estadísticas
        //almacenar tiempo en ES
    }
}
