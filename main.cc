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
        cSimulacion.E1(cInterfaz.obtenerDistribucion());
        evento = 1;
      }else if ((cSimulacion.obtenerE_2() <= cSimulacion.obtenerE_1()) && (cSimulacion.obtenerE_2() <= cSimulacion.obtenerE_3())){//Si el evento 2 debe ocurrir
        cSimulacion.E2();
        evento = 2;
      }else{
        cSimulacion.E3(); //Si el evento 3 debe ocurrir
        evento = 3;
      }
          cInterfaz.vistaSimulacion(cSimulacion.Reloj, evento, cSimulacion.servidorOcupado, cSimulacion.unidadESOcupado,
                        cSimulacion.colaProcesosCPU.size(), cSimulacion.colaProcesosES.size(), i);
      }// Cuando el reloj de la simulacion llega al limite, termina
      float est1 = cSimulacion.tiempoProcesos/cSimulacion.cantidadProcesos;
      float est2 = cSimulacion.tiempoCPU/cSimulacion.cantidadProcesos;
      float est3 = est2/cSimulacion.tiempoTotal;
      float est5 = est1 - est2 - est4;
      float est4 = cSimulacion.tiempoES/cSimulacion.cantidadProcesos;
      float est6 = est5/est1;
      est1Total += est1;
      est3Total += est3;
      est2Total += est2;
      est4Total += est4;
      est5Total += est5;
      est6Total += est6;
  }
  cInterfaz.vistaFinal(est1Total/10,est2Total/10, est3Total/10, est4Total/10, est5Total/10, est6Total/10);
  // LLama a Vista Final para reportar los ultimos datos cuando todas las simulaciones finalicen



  return 0;
}
