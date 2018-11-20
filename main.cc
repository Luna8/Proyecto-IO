#include "Simulacion.h"
#include "interfaz.h"

int main(void)
{
  interfaz cInterfaz; // UI
  cInterfaz.parametros(); // Inicia obtención de parámetros del usuario
  Simulacion cSimulacion; // Variable objeto de la clase
  int n = cInterfaz.obtenerVecesSimulacion();//Veces que hace la simulacion
  for (int i = 0; i < n; i++){ 
    //Inicia los relojes
    cSimulacion.E_1 = 0;
    cSimulacion.E_2 = numeric_limits<int>::max();
    cSimulacion.E_3 = numeric_limits<int>::max();
    cSimulacion.quantum = cInterfaz.obtenerQuantum();


    //Inicia la simulacion
    while (cSimulacion.Reloj <= cInterfaz.obtenerTiempoTotal()){
      int evento = 0;
      if ((cSimulacion.E_1 <= cSimulacion.E_2) && (cSimulacion.E_1 <= cSimulacion.E_3)){ //Si el evento 1 debe ocurrir
        cSimulacion.E1(!(cInterfaz.obtenerDistribucion()));
        evento = 1;
      }else if ((cSimulacion.E_2 <= cSimulacion.E_1) && (cSimulacion.E_2 <= cSimulacion.E_3)){//Si el evento 2 debe ocurrir
        cSimulacion.E2(1);
        evento = 2;
      }else{
        cSimulacion.E3(); //Si el evento 3 debe ocurrir
        evento = 3;
      }
    //  cInterfaz.vistaSimulacion(cSimulacion.Reloj, evento, cSimulacion.servidorOcupado, cSimulacion.unidadESOcupado,
      //                cSimulacion.colaProcesosCPU.size(), cSimulacion.colaProcesosES.size(), i);
    }// Cuando el reloj de la simulacion llega al limite, termina
      
     
  }
  //Aqui debe hacer los calculos para los totales, usando los totales de cSimulacion
  float est1 = cSimulacion.tiempoProcesos/cSimulacion.cantidadProcesos;
  float est2 = cSimulacion.tiempoCPU/cSimulacion.cantidadProcesos;
  float est3 = est2/cSimulacion.tiempoTotal;
  float est4 = cSimulacion.tiempoES/cSimulacion.cantidadProcesos;
  float est5 = est1 - est2 - est4;
  float est6 = est5/est1;
  cInterfaz.vistaFinal(est1,est2, est3, est4, est5, est6);
  // LLama a Vista Final para reportar los ultimos datos cuando todas las simulaciones finalicen
  

  return 0;
}
