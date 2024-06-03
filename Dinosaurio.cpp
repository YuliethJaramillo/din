// archivo implementacion, cabecera(definicion) con codigo 
#include "Dinosaurio.h"

Dinosaurio::Dinosaurio() {
  estado = 0;  // reposo
  y = 0;       // no salta
}

void Dinosaurio::caminar() {    
    y = 0;
    if(estado == 1) { // mover izquierda,derecha
      estado = 2;
    } 
    else {
      estado = 1;
    } 
}

void Dinosaurio::saltar() {
  y = 1;
  estado = 3;
}

int Dinosaurio::obtenerEstado() {
  return estado;
}

int Dinosaurio::obtenerPosicion() {
  return y;
}
