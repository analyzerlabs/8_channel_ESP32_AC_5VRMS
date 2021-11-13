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
                    Serial.print((p[3+i]);
                    Serial.println(" : Comparado");
                  }
                else {
                  return p;
                } 
            }
            for(int i=0;i<8;i++) r[i]= p[5+2*i];    //Guarda los valores del modo LC0
            return r;
        }
        //Modo LC1
        else if(p[2]=='1'){
          Serial.println("entra a 1");
            if(p[3] ==',' && p[4]>= 'A' && p[4]<='K' ){
                for(int i=0;i<8;i++)r[i]= p[5];   //Guarda el valor recibido en todos los canales
            } 
        }

        //MODO 8LC2
        else if(p[2]=='2'){
            Serial.println("entra a 2");
            if(p[4] ==',' && (p[5]== 'S' || p[5]=='R') ){
                if(p[5]=='S'){
                    for(int i=0;i<4;i++){ 
                        r[i] = 'K';  
                    }
                    for(int i=4;i<8;i++){
                         r[i] = 'A'; 
                    }

                }
            }
            
        }
        else {
              return r;
              Serial.println("salio sin cambiar");
         }
    return r;
  }
  return p;
}
void mode(int c){


}