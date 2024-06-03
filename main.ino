#include <LiquidCrystal.h>
#include "Dinosaurio.h";
#include "Cactus.h";
#include "terodactilo.h";

LiquidCrystal lcd(22,23,5,18,19,21);
Dinosaurio dino; //(constructor sin argumentos)
Cactus cactus(16);
terodactilo terodactil(10);
bool juegoENcurso=true;
bool musicaGO=true;
int notaFrecuencias[] = {800, 704, 698, 618, 542, 476, 420};
int notaDuracion[] = {100, 100, 100, 100, 100, 100, 250};
int puntuacion = 1;
int pinBUzzer = 15;
int frecuencia = 600;
int duracion = 150;
byte dinoReposo[8] = {
      B00000,
      B00000,
      B00111,
      B00101,
      B10111,
      B10100,
      B01101,
      B01100
};
byte dinoCamina1[8] = {      
      B00000,
      B00111,
      B00101,
      B10111,
      B10100,
      B01110,
      B01100,
      B00010
};  
byte dinoCamina2[8] = {
      B00000,
      B00111,
      B00101,
      B10111,
      B10100,
      B01110,
      B01100,
      B10000
};
byte dinoSalta[8] = {      
      B00111,
      B00101,
      B10111,
      B10100,
      B01101,
      B01100,
      B10000,
      B00000
};
byte cactus1[8] = {      
      B00000,
      B00000,
      B00001,
      B10101,
      B01101,
      B00110,
      B00100,
      B00100
};


byte terodactio[8] = {      
        B00000,
        B00010,
        B00110,
        B11111,
        B10110,
        B00010,
        B00000,
        B00000

};

struct Button {  //entrada usuario
  const uint8_t PIN;
  bool pressed;
  bool pressedNJ;
  
};

Button button1 = {4, false};
Button buttonNJ = {2,false};

int velocidad = 300;


void IRAM_ATTR isr() {  
  button1.pressed = true;  
}

void IRAM_ATTR isrNJ() {  
  buttonNJ.pressedNJ = true;  
}

void setup() {
  
  lcd.begin(16, 2); 
  Serial.begin(115200);
  Serial.println("test");

  pinMode(button1.PIN, INPUT_PULLUP);
  attachInterrupt(button1.PIN, isr, FALLING);

  pinMode(buttonNJ.PIN, INPUT_PULLUP);
  attachInterrupt(buttonNJ.PIN, isrNJ, FALLING);

  lcd.createChar(0, dinoReposo);
  lcd.createChar(1, dinoCamina1);
  lcd.createChar(2, dinoCamina2);
  lcd.createChar(3, dinoSalta);
  lcd.createChar(4, cactus1);
  lcd.createChar(5,terodactio);

  lcd.setCursor(0, 1);
  lcd.write(byte(0));  

//lcd.setCursor(16, 0);
  //lcd.write(byte(5));  

  delay(4000);  

}

void loop() {

 if (juegoENcurso ==true) {

  buttonNJ.pressedNJ = false;
  musicaGO = true;

  // Se borra la pantalla
  lcd.clear();

  // Se pinta la pantalla

  if (button1.pressed) {      
      dino.saltar();
      lcd.setCursor(0, 0);
      tone (pinBUzzer,frecuencia,duracion);
     button1.pressed = false;      
  }
  else {
      lcd.setCursor(0, 1);
      dino.caminar();      
 }   
   puntuacion = puntuacion + 1;
  
  
  lcd.write(byte(dino.obtenerEstado()));  

  cactus.mover();
  lcd.setCursor(cactus.obtenerPosicion(), 1);
  lcd.write(byte(4)); 

 terodactil.volar();
  

  if (terodactil.obtenerPosicion()== cactus.obtenerPosicion() || terodactil.obtenerPosicion()== cactus.obtenerPosicion()-1 ){
    lcd.setCursor(terodactil.obtenerPosicion()+8,0);

    lcd.write(byte(5));
  }
  else {
  
  lcd.setCursor(terodactil.obtenerPosicion(),0);
  lcd.write(byte(5)); 
  }
Serial.println(puntuacion);
  
  // Comprobar la colision
  if(dino.obtenerPosicion() == 0 && cactus.obtenerPosicion()==0 ) {
   
    
    lcd.clear();
    Serial.println("Colision!");
    Serial.println(puntuacion);
    juegoENcurso = false;
  }

  if(dino.obtenerPosicion() == 1 &&  terodactil.obtenerPosicion()==0) {
    lcd.clear();
    Serial.println("Coon!");
    juegoENcurso = false;
    
  }

  delay(velocidad);
  

 
 }
 else { 
  
        lcd.setCursor(2,0);
        lcd.print("GAME OVER");
        lcd.setCursor(1,1);
        lcd.print("PUNTUACION: ");
        lcd.print(puntuacion-1);


        if (musicaGO==true){
            for (int i = 0; i < 7; i++) {
            tone(15, notaFrecuencias[i], notaDuracion[i]);
            delay(notaDuracion[i] * 1.30); // Pausa entre notas

            musicaGO=false;
        } 
  }
      
        if(buttonNJ.pressedNJ){

         
          juegoENcurso = true;
          puntuacion=0;

        } 
          
        
 }

 
}
