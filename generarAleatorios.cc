#include "generarAleatorios.h"

generarAleatorios::generarAleatorios(){
  srand(time(NULL));
}
  
generarAleatorios::~generarAleatorios(){}

double generarAleatorios::generarSiguienteArribo(bool normal){
  double result;
  if(normal){
    double sum = 0;
    for (int i = 0; i < 12; i++) {
      sum += 1/(double)(rand() % 100 + 1);
    }
    result = 2*(sum-6)+25;
  }else{
      double x = 1/(double)(rand() % 100 +1);
      while(x = 1){
        x = 1/(double)(rand() % 100 + 1);
      }
      result = -30*log(1-x);
  }
  return result;
}

double generarAleatorios::generarTiempoOcurrencia(int quantum){
  double x = 1/(double)(rand() % 100 + 1);
  return (quantum*x)/2;
}

int generarAleatorios::generarInterrupcion(){
  return rand()%100;
}

double generarAleatorios::generarTiempoES(){
  double x = 1/(double)(rand() % 100 + 1);
  return 20*sqrt(3*x+1);
}
