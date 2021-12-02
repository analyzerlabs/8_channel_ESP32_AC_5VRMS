#include <SPI.h>
#include "EEPROM.h"

int addr = 0;
#define EEPROM_SIZE 200

int voltage[8] = {0,0,0,0,0,0,0,0}; 
int pot_values[8][11] = {{255 , 233 ,209 ,187 ,163 ,143 ,120 ,98  ,74  ,53,  29},
                         {255 , 232 ,209 ,185 ,162 ,141 ,117 ,97  ,73  ,52,  28}, //CH2 CALIBRADO
                         {255 , 233 ,209 ,188 ,165 ,144 ,120 ,99  ,76  ,54,  30},  // CH3 
                         {255 , 233 ,211 ,188 ,165 ,143 ,121 ,98  ,76  ,52,  28},  //CH4 CALIBRADO
                         {255 , 233 ,209 ,188 ,165 ,144 ,120 ,99  ,75  ,54,  29},  //CH5 CALIBRADO
                         {255 , 233 ,209 ,187 ,165 ,145 ,120 ,98  ,75  ,52,  26},  //CH6 CALIBRADO
                         {255 , 231 ,216 ,187 ,160 ,138 ,118 ,95  ,73  ,50,  24},  //CH7  CALIBRADO
                         {255 , 231 ,209 ,186 ,165 ,142 ,120 ,97  ,75  ,53,  29}}; //CH8 CALIBRADO


int demo_voltages[7][8] ={{ 0, 0, 0, 0,10,10,10,10},
                          {10,10,10,10, 0, 0, 0, 0},
                          { 0, 0, 0, 0,10,10,10,10},
                          {10,10,10,10, 0, 0, 0, 0},
                          { 0,10, 0,10, 0,10, 0,10},
                          { 10,0,10, 0,10, 0,10, 0},
                          { 0, 0, 0, 0, 0, 0, 0, 0}};

void eepromSetValues(int channel , int pos, int value){
  EEPROM.write(channel *11 + pos ,value);
  EEPROM.commit(); 
}

int eepromReadValues(int channel , int pos){
  int readed = EEPROM.read(channel*11 + pos);
  return readed;
}   
void eepromInit(){
    Serial.println("start...");
    if (!EEPROM.begin(EEPROM_SIZE)){
      Serial.println("failed to initialise EEPROM");
    }
    Serial.println(" bytes read from Flash . Values are:");
    for (int i = 0; i < EEPROM_SIZE; i++)
    {
      Serial.print(byte(EEPROM.read(i))); Serial.print(" ");
    }
    for(int i = 0 ;i<8;i++){
        for (int j=0;j<11;j++){
            //eepromSetValues( i ,  j, pot_values[i][j]);
            pot_values[i][j] = eepromReadValues(i , j);
          }
      }
    
}

                      
void setPot(int ch ,  int value){ 
  if(ch>=4 && ch<=8){
    digitalWrite(16, LOW);
    SPI.transfer(ch-4);
    SPI.transfer(pot_values[ch][value]);
    digitalWrite(16, HIGH);
    delay(10);
  }
  else if(ch>=0 && ch<4){
    digitalWrite(15, LOW);
    SPI.transfer(ch);
    SPI.transfer(pot_values[ch][value]);
    digitalWrite(15, HIGH);
    delay(10);
  }
}


char *changeValues(char *p){
    char *r;
    Serial.println("llama a funcion");
    if(p[0] == 'L' && p[1]== 'C'){
        //MODO LC0
        if(p[2]=='0'){
            Serial.println("entra a 0");
            for(int i=0;i<16;i=i+2){                   //evalua la trama para el modo LC0
                if(p[3+i] ==',' && p[4+i]>= 'A' && p[4+i]<='K' ){
                    Serial.print("Dato ");
                    Serial.print(&p[4+i]);
                    Serial.println(" : Comparado");
                  }
                else {
                  return p;
                } 
            }
            Serial.println("a llenar");
            for(int i=0;i<8;i++) {
              //r[i]= p[5+2*i];    //Guarda los valores del modo LC0
              voltage[i] = p[4+2*i] - 65;
              Serial.print(voltage[i]);
              Serial.print("\t|\t");
              Serial.println( p[4+2*i]);
            }

            return r;
        }
        //Modo LC1
        else if(p[2]=='1'){
          Serial.println("entra a 1");
            if(p[3] ==',' && p[4]>= 'A' && p[4]<='K' ){
                Serial.println("guarda");
                for(int i=0;i<8;i++){
                  voltage[i] = p[4] - 65;
                  //r[i]= p[4]-65;   //Guarda el valor recibido en todos los canales
                }
            } 
        }

        //MODO 8LC2
        else if(p[2]=='2'){
            Serial.println("entra a 2");
            if(p[3] ==',' && p[4]== 'S' && p[5]==','&& p[6]>= 'A' && p[6]<='K' ){
                    for(int i=0;i<4;i++){ 
                        voltage[i] = p[6] - 65;
                        //r[i] = p[7]-65;  
                    }
                    for(int i=4;i<8;i++){
                         //r[i] = 'A'; 
                         voltage[i] = 0;
                    }      
            }
            else if (p[3] ==',' && p[4]== 'R' && p[5]==','&& p[6]>= 'A' && p[6]<='K' ) {
                    Serial.println("LC2 , R ");
                    for(int i=0;i<4;i++){ 
                        voltage[i] = 0;
                    }
                    for(int i=4;i<8;i++){
                         voltage[i] = p[6] - 65;
            
                    }
            }
         
      }
      // evens and odds
      //MODO 8LC3
        else if(p[2]=='3'){
            Serial.println("entra a 2");
            if(p[3] ==',' && p[4]=='P'&& p[5]==','&& p[6]>= 'A' && p[6]<='K' ){
                    for(int i=0;i<4;i++){ 
                        voltage[2*i] = 0;
                    }
                    for(int i=0;i<4;i++){ 
                        voltage[2*i+1] = p[6] - 65;
                     }
            }
            else if (p[3] ==',' && p[4]=='O'&& p[5]==','&& p[6]>= 'A' && p[6]<='K' ){
                    for(int i=0;i<4;i++){ 
                        voltage[2*i+1] = 0;
                     }
                    for(int i=0;i<4;i++){ 
                        voltage[2*i] = p[6] - 65;
                    }
         }
      }
      else{
        return r;
        }
        
    return r;
  }
  else if(p[0] == 'C' && p[1]== 'H'){
      int a = p[8] - 48;
      int b = p[9] - 48;
      int c = p[10] - 48;
      int newValue = 100* a + 10 * b + c;
      int Vref = (p[5]- 48)*10 + p[6]- 48;
      int Ch = p[2] - 48;
      pot_values[Ch][Vref] = newValue; 
      eepromSetValues(Ch,Vref,newValue);
      Serial.print("Nuevo Valor: ");
      Serial.println(newValue);
     
      return r;
    }
  else {
    return p;
  }
  
}
