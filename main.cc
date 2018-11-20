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
    cSimulacion.establecerQuantum(cInterfaz.obtenerQuantum());

    //Inicia la simulacion
    while (cSimulacion.obtenerReloj() <= cInterfaz.obtenerTiempoTotal()){
      int evento = 0;
      if ((cSimulacion.obtenerE_1() <= cSimulacion.obtenerE_2()) && (cSimulacion.obtenerE_1() <= cSimulacion.obtenerE_3())){ //Si el evento 1 debe ocurrir
        cSimulacion.E1(!(cInterfaz.obtenerDistribucion()));
        evento = 1;
      }else if ((cSimulacion.obtenerE_2() <= cSimulacion.obtenerE_1()) && (cSimulacion.obtenerE_2() <= cSimulacion.obtenerE_3())){//Si el evento 2 debe ocurrir
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
  float est1 = cSimulacion.obtenerTiempoProcesos()/cSimulacion.obtenerCantidadProcesos();
  float est2 = cSimulacion.obtenerTiempoCPU()/cSimulacion.obtenerCantidadProcesos();
  float est3 = est2/cSimulacion.obtenerTiempoTotal();
  float est4 = cSimulacion.obtenerTiempoES()/cSimulacion.obtenerCantidadProcesos();
  float est5 = est1 - est2 - est4;
  float est6 = est5/est1;
  cInterfaz.vistaFinal(est1,est2, est3, est4, est5, est6);
  // LLama a Vista Final para reportar los ultimos datos cuando todas las simulaciones finalicen
  

  return 0;
}
