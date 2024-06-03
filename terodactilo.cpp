#include "terodactilo.h"


terodactilo::terodactilo(int posicionInicial) {  
  x = posicionInicial;  
}

void terodactilo::volar() { 
  int numeroAleatorio = random(1,4);  
  if(x > 0) {
    x = x - numeroAleatorio;
  }
  else {
    x = 16;
  }  
}

int terodactilo::obtenerPosicion() {
  return x;
}
