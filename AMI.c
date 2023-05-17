#include "AMI.h"


void codificarAMI(unsigned char* msg, char* ami_msg) {
    int msg_size = strlen((char*)msg);
    int ultimoBit = 1; // Inicialmente, o último bit é 1
    for (int i = 0; i < msg_size ; i++) {
        unsigned char caracter = msg[i];
        int cont = 0;
        for (int j = 7; j >= 0; j--) {
            int bit = (caracter >> j) & 1;
            if (bit == 0) {
                ami_msg[cont]= 0;
                cont++;
            } else {
                if (ultimoBit == -1) {
                    ami_msg[cont]= 1;
                    ultimoBit = 1;
                } else {
                    ami_msg[cont]= -1;
                    ultimoBit = -1;
                }
                cont++;
            }
        }
    }
}

int main(){
    unsigned char msg[10];
    char[80];
    
    printf("Digite uma mensagem: ");
    return 0;
}