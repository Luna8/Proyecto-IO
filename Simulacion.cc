#include "Simulacion.h"

Simulacion::Simulacion(){
  Reloj = 0;
  E_1 = 0;
  E_2 = numeric_limits<int>::max();
  E_3 = numeric_limits<int>::max();
  servidorOcupado =  false;
  unidadESOcupado = false;
  int cantidadProcesos = 0;
  double tiempoProcesos = 0;
  double tiempoES = 0;
  double tiempoCPU = 0;
  double tiempoTotal = 0;
}

Simulacion::~Simulacion(){}

void Simulacion::establecerReloj(int t){
  Reloj = t;
}
void Simulacion::establecerE_1(int E1){
  E_1 = E1;
}
void Simulacion::establecerE_2(int E2){    
  E_2 = E2;
}
void Simulacion::establecerE_3(int E3){    
  E_3 = E3;
}
void Simulacion::establecerServidorOcupado(bool o){    
  servidorOcupado = o;
}
void Simulacion::establecerUnidadESOcupado(bool o){    
  unidadESOcupado = o;
}
void Simulacion::establecerQuantum(int q){
  quantum = q;
}
void Simulacion::establecerCantidadProcesos(int n){    
  cantidadProcesos = n;
}
void Simulacion::establecerTiempoProcesos(double t){    
  tiempoProcesos = t;
}
void Simulacion::establecerTiempoES(double t){    
  tiempoES = t;
}
void Simulacion::establecerTiempoCPU(double t){    
  tiempoCPU = t;
}
void Simulacion::establecerTiempoTotal(double t){    
  tiempoTotal = t;
}
int Simulacion::obtenerReloj(){    
  return Reloj;
}
int Simulacion::obtenerE_1(){    
  return E_1;
}
int Simulacion::obtenerE_2(){    
  return E_2;
}
int Simulacion::obtenerE_3(){    
  return E_3;
}
bool Simulacion::obtenerServidorOcupado(){    
  return servidorOcupado;
}
bool Simulacion::obtenerUnidadESOcupado(){    
  return unidadESOcupado;
}
int Simulacion::obtenerQuantum(){    
  return quantum;
}
int Simulacion::obtenerCantidadProcesos(){    
  return cantidadProcesos;
}
double Simulacion::obtenerTiempoProcesos(){    
  return tiempoProcesos;
}
double Simulacion::obtenerTiempoES(){    
  return tiempoES;
}
double Simulacion::obtenerTiempoCPU(){    
  return  tiempoCPU;
}
double Simulacion::obtenerTiempoTotal(){    
  return tiempoTotal;
}
queue<proceso*> Simulacion::obtenerColaProcesoCPU(){    
  return colaProcesosCPU;
}
queue<proceso*> Simulacion::obtenerColaProcesosES(){    
  return colaProcesosES;
}


//Llegada de un nuevo proceso
void Simulacion::E1(bool exponencial){ Reloj = E_1;                                             
  proceso * p = new proceso(Reloj);                         
  if(!servidorOcupado){                                                                                          
    servidorOcupado = true;
    p->inicioCPU = Reloj;

    double x = quantum;                                     // Tiempo de ocurrencia
    double interrupcion = aleatorio.generarInterrupcion();
    if (interrupcion>=0.50){                                // Caso en que ocurre una interrupción
      p->tipoInt = (interrupcion < 0.70)?  3 : 2;           //  3 => E/S, 2 => termina.
      x = aleatorio.generarTiempoOcurrencia(quantum);       // tiempo en el que ocurre la interrupción
    }
    
    E_2 = Reloj + x;                                        
    p->tiempoCPU += E_2 - p->inicioCPU;                  
  }
  E_1 = Reloj + aleatorio.generarSiguienteArribo(exponencial);
  colaProcesosCPU.push(p); // Proceso entra a la cola por Round Robin, o por interrupción, o por no tener campo
}

void Simulacion::E2(){ Reloj = E_2;
  
  proceso * p = colaProcesosCPU.front();                    // proceso por atender
  colaProcesosCPU.pop();                                    // lo saca de la cola
  if(colaProcesosCPU.empty){
    servidorOcupado = false;                                // no hay más procesos en cola
  }

  if(p->tipoInt == 3){                                      // Si es el caso E/S
    if(!unidadESOcupado){     
      unidadESOcupado = true;                                 
      double y = aleatorio.generarTiempoES();               //Si no está ocupado genera tiempo
      E_3 = Reloj + y;                                     
    }
    colaProcesosES.push(p);
    servidorOcupado = false;                                // El proceso cambió de cola
  }else if(p->tipoInt == 2){                                // Si es el caso termina
      cantidadProcesos ++ ;
      tiempoProcesos += Reloj - p->horaInicio;
      tiempoES += p->tiempoES;
      tiempoCPU += p->tiempoCPU;
      servidorOcupado = false;                              // el proceso salió del sistema
  }else{                                                    // Si debe volver a la cola
    if(!servidorOcupado){                                                                                          
      servidorOcupado = true;
      p->inicioCPU = Reloj;
      double x = quantum;                                     // Tiempo de ocurrencia
      double interrupcion = aleatorio.generarInterrupcion();
      if (interrupcion>=0.50){                                // Caso en que ocurre una interrupción
        p->tipoInt = (interrupcion < 0.70)?  3 : 2;           //  3 => E/S, 2 => termina.
        x = aleatorio.generarTiempoOcurrencia(quantum);       // tiempo en el que ocurre la interrupción
      }
      
      E_2 = Reloj + x;                                        
      p->tiempoCPU += E_2 - p->inicioCPU;                  
    }
    colaProcesosCPU.push(p);
  }
}

void Simulacion::E3(){ Reloj = E_3;
  proceso * p = colaProcesosES.front();
  colaProcesosES.pop();
  p->inicioES = Reloj;                                                 
  double y = aleatorio.generarTiempoES();               
  E_3 = Reloj + y;              
  p->tiempoES += E_3 - p->inicioES;                         
  unidadESOcupado = false;
  
  if(colaProcesosCPU.empty){
    servidorOcupado = false;                                // no hay más procesos en cola
  }

  if(!servidorOcupado){                                                                                          
    servidorOcupado = true;
    p->inicioCPU = Reloj;
    double x = quantum;                                     // Tiempo de ocurrencia
    double interrupcion = aleatorio.generarInterrupcion();
    if (interrupcion>=0.50){                                // Caso en que ocurre una interrupción
      p->tipoInt = (interrupcion < 0.70)?  3 : 2;           //  3 => E/S, 2 => termina.
      x = aleatorio.generarTiempoOcurrencia(quantum);       // tiempo en el que ocurre la interrupción
    }
    
    E_2 = Reloj + x;                                        
    p->tiempoCPU += E_2 - p->inicioCPU;                  
  }
  colaProcesosCPU.push(p);
}
