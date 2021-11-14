#include <stdio.h>
#include <string.h>
 clear;
int main(){
	int i=0;
	int j=0;
	int mod;
	char v[7];
    char rxValue[13] = "LC3,P(CR)(LF)",
    //rxValue[15] = "LC1,A(CR)(LF)"
    //rxValue[15] = "LC2,S,B(CR)(LF)"
    //rxValue[13] = "LC3,P(CR)(LF)"
    //rxValue[27] = "LC0,X,Y,Z,P,Q,R,S,T(CR)(LF)"
    delimitador[] = ", ";
    if(strlen(rxValue)==27){
    	printf("a\n");
    	if (strncmp(rxValue,"LC0",3)==0){
    		mod=0;
    	v[0]=rxValue[4];
    	v[1]=rxValue[6];
    	v[2]=rxValue[8];
    	v[3]=rxValue[10];
    	v[4]=rxValue[12];
    	v[5]=rxValue[14];
    	v[6]=rxValue[16];
    	v[7]=rxValue[18];
    	
    	
    		printf("modo=%d\n%s\n",mod,v);
			
    		
		}

    		
    		}
	/*
		for(i=0;i<7;i++0){
			if(v[i]==A){ 
			printf("el voltaje es")
				
				
			}
		}
    	
	*/
	
	 
	 
	 
	 if(strlen(rxValue)==13){
	 	
	 	if (strncmp(rxValue,"LC1",3)==0){
    		mod=1;
    		//if(rxValue[4]=="A" || rxValue[4]=="B" ||rxValue[4]=="C"|| rxValue[4]=="D" || rxValue[4]=="F" || rxValue[4]=="G" || rxValue[4]=="H" || rxValue[4]=="I"|| rxValue[4]=="J" ||rxValue[4]=="K"){
			for(i=0;i<8;i++){
			
    		v[i]=rxValue[4];
    		}
    		printf("modo=%d\n%s\n",mod,v);
    		
    	//}
    }
    
    	
    	
    	
    	if (strncmp(rxValue,"LC3",3)==0){
    		
    		mod=3;
			v[1]=rxValue[4];
    		
    		if(v[1]=="P"){
    			for(i=0;i<8;i+2){
    				v[i]="A";
    				v[i+1]="K";
				}
				printf("modo=%d\n%s\n",mod,v);
			}
			if(v[0]=="O"){
    			for(i=0;i<8;i+2){
    				v[i]="K";
    				v[i+1]="A";
				}
				printf("modo=%d\n%s\n",mod,v);
			}
			printf("modo=%d\n%s\n",mod,v);
    	}
	 	
	 	
	 	
	 }
	 
	 if(strlen(rxValue)==15){
	 	if (strncmp(rxValue,"LC2",3)==0){
    		mod=2;
    		
    		v[0]=rxValue[4];
    		v[1]=rxValue[6];
    		
    		if(v[0]=="S"){
    			
    			for(i=0;i<4;i++){
    				v[i]=v[1];
    				//v[i+4]="A";
				}
				for(i=4;i<8;i++){
    			
    				v[i]="A";
				}
    			printf("11modo=%d\n%s\n",mod,v);
			}
			if(v[0]="R"){
				for(i=0;i<4;i++){
    				v[i]="A";
					v[i+4]=v[1];
    				
				}
    			
    			
			}
			printf("22modo=%d\n%s\n",mod,v);
    	}
	 	
	 }
}
	
