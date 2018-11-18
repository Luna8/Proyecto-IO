#include <queue>

class Simulacion
{
public:
  int Reloj;
  int E1;
  int E2;
  int E3;
  bool servidorOcupado =  false;
  bool unidadESOcupado = false;
  std::queue<proceso> colaProcesosCPU;
  std::queue<proceso> colaProcesosES;
  int quantum;
  int cantidadṔrocesos;
  int tiempoProcesos;
  int tiempoES;
  void E1();
  void E2(int tipo);
  void E3();

  struct proceso{
    int horaInicio;
    int inicioCPU;
    int tiempoCPU;
    int inicioES;
    int tiempoES;
  }

private:

}
