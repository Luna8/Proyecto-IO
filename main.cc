#include <stdio.h>
#include "generarAleatorios.h"
#include "Simulacion.h"
#include "interfaz.h"



int main(void)
{
  interfaz cInterfaz;
  float est1Total;
  float est2Total;
  float est3Total;
  float est4Total;
  float est5Total;
  float est6Total;

  cInterfaz.parametros();


  for (int i = 0; i < cInterfaz.nVecesSimulacion; i++) //Veces que hace la simulacion
  {
      Simulacion cSimulacion; //Variable objeto de la clase

      //Inicia los relojes
      cSimulacion.E_1 = 0;
      cSimulacion.E_2 = std::numeric_limits<int>::max();
      cSimulacion.E_3 = std::numeric_limits<int>::max();
      cSimulacion.quantum = cInterfaz.quantum;


      //Inicia la simulacion
      while (cSimulacion.Reloj <= cInterfaz.tiempoTotal)
      {
          int evento = 0;
          if ((cSimulacion.E_1 <= cSimulacion.E_2) && (cSimulacion.E_1 <= cSimulacion.E_3)) //Si el evento 1 debe ocurrir
          {
              cSimulacion.E1(!(cInterfaz.distribucionExponencial));
              evento = 1;
          }
          else
          {
              if ((cSimulacion.E_2 <= cSimulacion.E_1) && (cSimulacion.E_2 <= cSimulacion.E_3))//Si el evento 2 debe ocurrir
              {
                  cSimulacion.E2(1);
                  evento = 2;
              }
              else
              {
                  cSimulacion.E3(); //Si el evento 3 debe ocurrir
                  evento = 3;
              }
          }
          cInterfaz.vistaSimulacion(cSimulacion.Reloj, evento, cSimulacion.servidorOcupado, cSimulacion.unidadESOcupado,
                        cSimulacion.colaProcesosCPU.size(), cSimulacion.colaProcesosES.size(), i);

      }// Cuando el reloj de la simulacion llega al limite, termina
      //Aqui debe hacer los calculos para los totales, usando los totales de cSimulacion
      float est1 = cSimulacion.tiempoProcesos/cSimulacion.cantidadProcesos;
      float est2 = cSimulacion.tiempoCPU/cSimulacion.cantidadProcesos;
      float est3 = est2/cSimulacion.tiempoTotal;
      float est4 = cSimulacion.tiempoES/cSimulacion.cantidadProcesos;
      float est5 = est1 - est2 - est4;
      float est6 = est5/est1;

      est1Total += est1;
      est2Total += est2;
      est3Total += est3;
      est4Total += est4;
      est5Total += est5;
      est6Total += est6;
  }
  cInterfaz.vistaFinal(est1Total/10,est2Total/10, est3Total/10, est4Total/10, est5Total/10, est6Total/10);
  // LLama a Vista Final para reportar los ultimos datos cuando todas las simulaciones finalicen



  return 0;
}
