#include "interfaz.h"


interfaz::interfaz()
{
    nVecesSimulacion=0;
    tiempoTotal=0;
    quantum=0;
    distribucionExponencial=false;
}

interfaz::~interfaz()
{
    //dtor
}

void interfaz::parametros(){
    bool valido=false;
    string dato;
    while(false==valido){
        cout << "Inserte la cantidad de veces que desea correr la simulacion:" ;
        cin>>dato;
        cout <<" "<<endl;
        valido=valiDarDato(dato,1);
        if(!valido){
            cout <<"Dato invalido"<<endl;
        }
    }
    valido=false;
    while(false==valido){
        cout << "Inserte el tiempo total que desea que corra la simulacion:" ;
        cin>>dato;
        cout <<" "<<endl;
        valido=valiDarDato(dato,2);
        if(!valido){
            cout <<"Dato invalido"<<endl;
        }
    }
    valido=false;
    while(false==valido){
        cout << "Inserte el quantum del procesador:" ;
        cin>>dato;
        cout <<" "<<endl;
        valido=valiDarDato(dato,3);
        if(!valido){
            cout <<"Dato invalido"<<endl;
        }
    }
    valido=false;
    while(false==valido){
        cout << "Indique el tipo de distribucion \n 1)Exponencial 2)Normal " ;
        cin>>dato;
        cout <<" "<<endl;
        valido=valiDarDato(dato,4);
        if(!valido){
            cout <<"Dato invalido"<<endl;
        }
    }
    cout<<"# veces "<<nVecesSimulacion<<" tiempo total "<<tiempoTotal<<" quantum "<<quantum<<" distribucion "<<distribucionExponencial<<endl;
}

bool interfaz::valiDarDato(string dato, int nDato){
    bool validar=false;
    if(nDato<=3){
       if(atoi(dato.c_str())&&atoi(dato.c_str())>0){
            validar=true;
            switch(nDato) {
                case 1 : nVecesSimulacion=atoi(dato.c_str());
                case 2 : tiempoTotal=atoi(dato.c_str());
                case 3 : quantum=atoi(dato.c_str());
            }
        }
    }else{
        if( atoi(dato.c_str())&&(atoi(dato.c_str())==1 ||atoi(dato.c_str())==2)){
            validar=true;
            if(atoi(dato.c_str())==1){
                    distribucionExponencial=true;
            }
        }
    }
    return validar;
}

void interfaz::vistaSimulacion(int reloj, int evento, bool estProcesador, bool estES, int tamColaProc, int tamColaES, int progFin){
    string eventoProcesador;
    string estadoProcesador;
    string estadoES;
    switch(evento) {
        case 1 : eventoProcesador="Programa se queda sin tiempo de ejecucion";
        case 2 : eventoProcesador="Programa termina";
        case 3 : eventoProcesador="Programa pasa a dispositivo de E/S";
    }
    if(estProcesador){
        estadoProcesador="OCUPADO";
    }else{
        estadoProcesador="LIBRE";
    }
    if(estES){
        estadoES="OCUPADO";
    }else{
        estadoES="LIBRE";
    }
    cout<<"********************************************************************************"<<endl;
    cout<<"Reloj del sistema: "<<reloj<<endl;
    cout<<"Evento que procesa: "<<eventoProcesador<<endl;
    cout<<"Estado Procesador: "<<estadoProcesador<<endl;
    cout<<"Estado E/S: "<<estadoES<<endl;
    cout<<"Numero de programas en cola del procesador: "<<tamColaProc<<endl;
    cout<<"Numero de programas en cola del E/S: "<<tamColaES<<endl;
    cout<<"Numero de programas que han salido: "<<progFin<<endl;
    cout<<""<<endl;
}

void interfaz::vistaFinal(float promedioTotal, float promedioProgramaCPU, float ocupacionServidor, float promedioProgramaES, float tiempoCola, float coeficienteEficiencia){
    cout<<"*********************Estadisticas Finales*********************"<<endl;
    cout<<"Tiempo promedio de un programa en el sistema: "<<promedioTotal<<endl;
    cout<<"Tiempo promedio de un programa en el CPU: "<<promedioProgramaCPU<<endl;
    cout<<"Porcentaje de ocupacion del servidor: "<<ocupacionServidor<<endl;
    cout<<"Tiempo promedio de un programa en E/S: "<<promedioProgramaES<<endl;
    cout<<"Tiempo promedio de un programa en las colas: "<<tiempoCola<<endl;
    cout<<"Coeficiente de eficiencia: "<<coeficienteEficiencia<<endl;
}
