#include "parameters.h"
#include "kem.h"

unsigned char K_Alice[LAMBDA]; 
unsigned char K_Bob[LAMBDA];
unsigned char randomness[LAMBDA]; 
CCA_ciphertext ct;


void display_key(unsigned char* k){
    int i;
    for(i=0; i < LAMBDA; ++i){
        Serial.print(k[i],HEX);
        Serial.print(' ');
    }
    Serial.println("\n");
}

void CPA_KEM(){
    Serial.println(F("CPA KEM"));
    int i;
    for(i=0; i < LAMBDA;++i) K_Alice[i]    = random()&0xFF;
    for(i=0; i < LAMBDA;++i) randomness[i] = random()&0xFF;
   
    encaps(ct.U, ct.V, K_Alice, randomness);
    decaps(ct.U, ct.V, K_Bob);

    display_key(K_Alice);
    display_key(K_Bob);
}


void CCA_KEM(){
    Serial.println(F("CCA KEM"));
    int i;
    for(i=0; i < LAMBDA;++i) K_Alice[i]    = random()&0xFF;
    for(i=0; i < LAMBDA;++i) randomness[i] = random()&0xFF; 
                      
    CCA_encaps(&ct, K_Alice);
    CCA_decaps(&ct, K_Bob);

    display_key(K_Alice);
    display_key(K_Bob); 
}

void setup() {
    Serial.begin(9600);
    randomSeed(analogRead(0));
    
    CPA_KEM();
    CCA_KEM();
}

void loop() {
  

}
