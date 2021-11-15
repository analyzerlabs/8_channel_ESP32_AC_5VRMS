#include <SPI.h>
/*
Secuencia Demo
Presiona botón y hace esta secuencia:
Todo On - 1seg
Todo Off - 1 seg
Todo On - 1 seg
Todo Off - 1 seg
Half 1al 4 - 1 seg
Half 5 al 8 - 1 seg
Half 1al 4 - 1 seg
Half 5 al 8 - 1 seg
Evens - 1 seg
Odds - 1 seg
Evens - 1 seg
Odds - 1 seg
Roller up -500ms
Roller down - 500ms 
Roller up -500ms
Roller down - 500ms
(finaliza y vuelve a hacerlo en bucle)
Al presionar otra vez el botón se detiene y se apagan todos los blinds
*/
void setPot(int v[]){ 
  for(int i =0; i<4;i++){
    digitalWrite(15, LOW);
    SPI.transfer(i);
    SPI.transfer(v[i]*32);
    digitalWrite(15, HIGH);
  }
  for(int i =4; i<8;i++){
  digitalWrite(16, LOW);
  SPI.transfer(i-4);
  SPI.transfer(v[i]*32);
  digitalWrite(16, HIGH);
  }
}

void demo(){
    int v_demo[8]={5,5,5,5,5,5,5,5};
    for(int j=0 ;j<2 ;j++){
      for(int i = 0; i<8 ;i++)v_demo[i]=5;
      setPot(v_demo);
      for(int i = 0; i<8 ;i++)v_demo[i]=0;
      setPot(v_demo);
    }

    for(int j=0 ;j<2 ;j++){
      for(int i = 0; i<4 ;i++)v_demo[i]=5;
      setPot(v_demo);
      for(int i = 4; i<8 ;i++)v_demo[i]=5;
      setPot(v_demo);
      for(int i = 0; i<4 ;i++)v_demo[i]=0;
      setPot(v_demo);
      for(int i = 4; i<8 ;i++)v_demo[i]=0;
      setPot(v_demo);
    }

   
}