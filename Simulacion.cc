#include <iostream>
#include "Simulacion.h"
#include "generarAleatorios.h"
#include  <cstdlib>


using namespace std;

generarAleatorios aleatorio;
//Llegada de un nuevo proceso
void Simulacion::E1(bool normal){
  Reloj = E_1;                 //Adelantamos el reloj
  int x;
  int interrupcion;
  int tipo;
  p = proceso();    //Creamos proceso
  p.horaInicio =  Reloj;
  if(servidorOcupado){          //Si está ocupado el servidor
    colaProcesosCPU.push(p);    //se va a la cola.
  }else{
    p.inicioCPU =  Reloj;           //Si no está ocupado el servidor
    interrupcion = aleatorio.generarInterrupcion(); //Generamos valor aleatorio
    if (interrupcion>=50) {     // Caso en que ocurre una interrupcion
      x = aleatorio.generarTiempoOcurrencia(quantum);
      if(interrupcion <=70){  //Caso en que se va a E/S
        tipo = 3;
      }
      else{               //Caso en que sale del sistema
        tipo = 2;
      }
    }else{                      //Caso en que no ocurren interrupción
      x = quantum;
      tipo = 1;
      colaProcesosCPU.push(p);
    }
    E_2 = Reloj + x;
    p.tiempoCPU += Reloj - p.inicioCPU;
    E2(tipo);
  }
}

void Simulacion::E2(int tipo) {
  Reloj =  E_2;                      //Movemos reloj.
  if(tipo==3){                       //Si es el caso E/S
          if(unidadESOcupado==true){    //Revisamos si está ocupado
              colaProcesosES.push(p);
          }else{
              int y= aleatorio.generarTiempoES();    //Si no está ocupado genera tiempo
              E_3=Reloj+y;             //Y mueve el reloj
          }
      }
  if(colaProcesosCPU.size()>0){ //Si hay procesos en cola
    colaProcesosCPU.pop();
    int interrupcion = aleatorio.generarInterrupcion(); //Generamos valor aleatorio
    int tipo;
    int x;
    if (interrupcion>=50) {     // Caso en que ocurre una interrupcion
      x = aleatorio.generarTiempoOcurrencia(quantum);
      if(interrupcion <=70){  //Caso en que se va a E/S
        tipo = 3;
      }
      else{               //Caso en que sale del sistema
        tipo = 2;
      }
      }else{                      //Caso en que no ocurren interrupción
        x = quantum;
        tipo = 1;
        colaProcesosCPU.push(p);
    }
    E_2 = Reloj + x;
    if(tipo==1){
              colaProcesosCPU.push(p);
          }
    }else{
            if(tipo==1){
              int interrupcion = aleatorio.generarInterrupcion(); //Generamos valor aleatorio
              int tipo;
              int x;
              if (interrupcion>=50) {     // Caso en que ocurre una interrupcion
                x = aleatorio.generarTiempoOcurrencia(quantum);
                if(interrupcion <=70){  //Caso en que se va a E/S
                  tipo = 3;
                }
                else{               //Caso en que sale del sistema
                  tipo = 2;
                }
              }else{                      //Caso en que no ocurren interrupción
                x = quantum;
                tipo = 1;
                colaProcesosCPU.push(p);
              }
              E_2 = Reloj + x;


            }else{
              servidorOcupado = false;
            }
        }
        if(tipo==2){
            //almacenar estadísticas
            // almacenar duración del proceso
            // aumentar número de procesos
            tiempoProcesos = tiempoProcesos + (Reloj-p.inicioCPU);
            cantidadProcesos++;

        }
}

void Simulacion::E3(){
    Reloj=E_3;
    //como todos regresan al procesador luego de terminar E/S, hacen losmo que E1, sin generar un
    //nuevo proceso.
    if(servidorOcupado){
        colaProcesosCPU.push(p);
    }else{
        p.inicioCPU = Reloj;
        int interrupcion = aleatorio.generarInterrupcion();
        int x;
        int tipo;
        if(interrupcion >= 50){
            x = aleatorio.generarTiempoOcurrencia(quantum);
            if(interrupcion <=70){  //Caso en que se va a E/S
              tipo = 3;
            }
            else{               //Caso en que sale del sistema
              tipo = 2;
            }
        }else{
            x = quantum;
            tipo = 1;
            colaProcesosCPU.push(p);
        }
        E_2 = Reloj + x;
        p.tiempoCPU += Reloj-p.inicioCPU;
        E2(tipo); // {1=>'nada', 2=>'termina', 3=>'E/S'}
    }
    if(colaProcesosES.size()>0){
        colaProcesosES.pop();
        E_3=Reloj+aleatorio.generarTiempoES();
    }else{
        unidadESOcupado=false;
        //almacenar estadísticas
        //almacenar tiempo en ES
    }
}
