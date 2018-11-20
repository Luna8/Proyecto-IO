#include "Simulacion.h"

Simulacion::Simulacion(){
  Reloj = 0;
  E_1 = 0;
  E_2 = numeric_limits<int>::max();
  E_3 = numeric_limits<int>::max();
  servidorOcupado =  false;
  unidadESOcupado = false;
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
void Simulacion::E1(bool exponencial){
  Reloj = E_1;                                              // Adelantamos el reloj
  proceso * p = new proceso(Reloj);                         
  if(servidorOcupado){                                      
    colaProcesosCPU.push(p);                                
  }else{                                                    
    double x = quantum;                                     // Tiempo de ocurrencia
    p->inicioCPU =  Reloj;
    double interrupcion = aleatorio.generarInterrupcion();
    if (interrupcion>=0.50){                                // Caso en que ocurre una interrupción
      if(interrupcion < 0.70) p->tipoInt = 3;                 // * interrupción E/S
      else p->tipoInt = 2;                                    // * interrupción sale del sistema
      x = aleatorio.generarTiempoOcurrencia(quantum);       // tiempo en el que ocurre la interrupción
    }else p->tipoInt = 1;                                   // Caso en que no ocurre interrupción
    p->tiempoCPU += Reloj + x - p->inicioCPU;
    colaProcesosCPU.push(p);                                // Proceso entra a la cola por Round Robin o por interrupción
    E_2 = Reloj + x;
    E_1 = Reloj + aleatorio.generarSiguienteArribo(exponencial);
  }
}

void Simulacion::E2() {
  Reloj =  E_2;                                             // Adelantamos el reloj
  proceso * p = colaProcesosCPU.front();                    // proceso por atender
  colaProcesosCPU.pop();                                    // lo saca de la cola
  if(p->tipoInt == 3){                                        // Si es el caso E/S
    if(unidadESOcupado){                                    
      colaProcesosES.push(p);                               
    }else{                                                      
      double y = aleatorio.generarTiempoES();               //Si no está ocupado genera tiempo
      p->inicioES = Reloj;
      E_3=Reloj+y;             //Y mueve el reloj
    }
  }
  if(colaProcesosCPU.size()>0){ //Si hay procesos en cola
    
    double interrupcion = aleatorio.generarInterrupcion(); //Generamos valor aleatorio
    int tipo;
    double x;
    if (interrupcion>=0.50) {     // Caso en que ocurre una interrupcion
      x = aleatorio.generarTiempoOcurrencia(quantum);
      if(interrupcion <=0.70){  //Caso en que se va a E/S
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
              double interrupcion = aleatorio.generarInterrupcion(); //Generamos valor aleatorio
              int tipo;
              double x;
              if (interrupcion>=0.50) {     // Caso en que ocurre una interrupcion
                x = aleatorio.generarTiempoOcurrencia(quantum);
                if(interrupcion <=0.70){  //Caso en que se va a E/S
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
            tiempoProcesos = tiempoProcesos + (Reloj-p->inicioCPU);
            cantidadProcesos++;
            tiempoTotal = Reloj;
        }
}

void Simulacion::E3(){
    Reloj=E_3;
    proceso * p = colaProcesosES.front();
    colaProcesosES.pop();
    //como todos regresan al procesador luego de terminar E/S, hacen losmo que E1, sin generar un
    //nuevo proceso.
    if(servidorOcupado){
        colaProcesosCPU.push(p);
    }else{
        p->inicioCPU = Reloj;
        double interrupcion = aleatorio.generarInterrupcion();
        double x;
        int tipo;
        if(interrupcion >= 0.50){
            x = aleatorio.generarTiempoOcurrencia(quantum);
            if(interrupcion <=0.70){  //Caso en que se va a E/S
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
        p->tiempoCPU += Reloj-p->inicioCPU;
        tiempoCPU += p->tiempoCPU;
        E2(tipo); // {1=>'nada', 2=>'termina', 3=>'E/S'}
    }
    if(colaProcesosES.size()>0){
        colaProcesosES.pop();
        E_3=Reloj+aleatorio.generarTiempoES();
    }else{
        unidadESOcupado=false;
        //almacenar estadísticas
        //almacenar tiempo en ES
        p->tiempoES = Reloj-p->inicioES;
        tiempoES += p->tiempoES;
    }
}
