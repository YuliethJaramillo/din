#ifndef terodactilo_h
#define terodactilo_h
#include "Arduino.h"

class terodactilo {
  private:    
    int x;         

  public:
    terodactilo(int posicionInicial); // pos inicial 
    void volar();
    int obtenerPosicion();    
};


#endif
