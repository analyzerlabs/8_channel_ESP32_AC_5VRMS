char *changeValues(char *p){
    char *r;

    if(&p[0] == "L" && &p[1]== "C"){
        if(&p[2]=="0"){
            for(int i=0;i<16;i=i+2){                   //evalua la trama para el modo LC0
                if(&p[4+i] =="," && &p[5+i]>= "A" && &p[5+i]<="K" ){}
                else {return r;} 
            }
            for(int i=0;i<8;i++) r[i]= p[4];    //Guarda los valores del modo LC0
 
        }
        else if(&p[2]=="1"){
            if(&p[4] =="," && &p[5]>= "A" && &p[5]<="K" ){

        }
            
    }

    else{
        return r;
    }
    return r;
}

void mode(int c){


}