#include <queue>

class Simulacion
{
public:
  struct proceso{
    int horaInicio;
    int inicioCPU;
    int tiempoCPU;
    int inicioES;
    int tiempoES;
  };
  int Reloj;
  int E_1;
  int E_2;
  int E_3;
  bool servidorOcupado =  false;
  bool unidadESOcupado = false;
  std::queue<proceso> colaProcesosCPU;
  std::queue<proceso> colaProcesosES;
  int quantum;
  int cantidadProcesos;
  int tiempoProcesos;
  int tiempoES;
  void E1(bool normal);
  void E2(int tipo);
  void E3();
  proceso p;

private:
};
