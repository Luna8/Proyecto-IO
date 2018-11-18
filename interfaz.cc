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
