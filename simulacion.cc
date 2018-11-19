#include <iostream>
#include "simulacion.h"
#include  <cstdlib>


using namespace std;

//Llegada de un nuevo proceso
void simulacion::E1(){
  Reloj = E1;                 //Adelantamos el reloj
  struct proceso p = new struct;    //Creamos proceso
  p.horaInicio =  Reloj;
  if(servidorOcupado){          //Si está ocupado el servidor
    colaProcesosCPU.push(p);    //se va a la cola.
  }else{
    p.inicioCPU =  Reloj;           //Si no está ocupado el servidor
    int interrupcion = generarInterrupcion(); //Generamos valor aleatorio
    int x;
    int tipo;
    if (interrupcion>=50) {     // Caso en que ocurre una interrupcion
      x = generarTiempoOcurrencia();
      if(interrupcion <=70){  //Caso en que se va a E/S
        tipo = 3;
      }
      else{               //Caso en que sale del sistema
        tipo = 2;
      }
    }else{                      //Caso en que no ocurren interrupción
      x = quantum;
      tipo = 1;
      colaProcesosCP.push(p);
    }
    E2 = Reloj + x;
    p.tiempoCPU += Reloj - p.inicioCPU;
    E2(tipo);
  }
  E1 =Reloj + generarSiguienteArribo();
}

void simulacion::E2(int tipo) {
  Reloj =  E2;                      //Movemos reloj.
  if(tipo==3){                       //Si es el caso E/S
          if(unidadESOcupado==true){    //Revisamos si está ocupado
              colaProcesosES.push(p);
          }else{
              y=generarTiempoES();    //Si no está ocupado genera tiempo
              E3=Reloj+y;             //Y mueve el reloj
          }
      }
  if(tipo==1){                      //Caso cuando no hay interrupción
    if(servidorOcupado==true){    //Si está ocupado
          colaProcesosCPU.push(p);
    }else{                        //Si no
          x=quantum;
          colaProcesosCPU.push(p);    //Deberíamos meterlo?
    }
    Reloj=Reloj+x;                //Ajustamos el reloj
    }
  if(colaProcesosCPU.tamano()>0){ //Si hay procesos en cola
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
