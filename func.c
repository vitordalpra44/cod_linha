#include "func.h"


void encrypt(unsigned char* msg, int key){
    int msg_size = strlen(msg);
    for(int i = 0;i<msg_size;i++) msg[i]=(msg[i]+key);
}

void decrypt(unsigned char* msg, int key){
    int msg_size = strlen(msg);
    for(int i =0;i<msg_size;i++) msg[i] = (msg[i]-key);
}

void printBin(unsigned char* msg, int msg_size) {
    printf("\t");
    while (msg_size) {
        unsigned char *msg_buf;
        unsigned char c = *msg++;
        for (int i = 7; i >= 0; i--) {
            printf("\t%d", (c >> i) & 1);
        }
        msg_size--;
    }
    printf("\n");
}

void amiCode(unsigned char* msg, char* ami_msg, int msg_size) {
    int lastBit = 1; // Inicialmente, o último bit é 1
    int i, j, cont=0;
    for (i = 0; i < msg_size ; i++) {
        unsigned char character = msg[i];
        for (j = 7; j >= 0; j--) {
            int bit = (character >> j) & 1;
            if (bit == 0) {
                ami_msg[cont]= 0;
                cont++;
            } else {
                if (lastBit == -1) {
                    ami_msg[cont]= 1;
                    lastBit = 1;
                } else {
                    ami_msg[cont]= -1;
                    lastBit = -1;
                }
                cont++;
            }
        }
    }
    ami_msg[cont] = '@'; //condicão de final da string;
}

void amiDecode(char* ami_msg, int msg_size, unsigned char* msg) {
    int i=0, j=0, a=0, cont=0;
    char binary[msg_size*8];
    // Decodificar valores AMI para binário
    for (i = 0; i < msg_size*8; i++) {
        binary[i] = ami_msg[i];
        if (binary[i] == -1)
            binary[i] = 1;
    }

    // Converter binário para decimal
    for (i = 0; i < msg_size; i++) {
        for(j=i*8, a = 128;j<=i*8+7;j++, a/=2){
            msg[cont] +=a*binary[j];
        }
        cont++;
    }
}

void printAMI(char* msg) {
    for (int i = 0; msg[i]!= '@'; i++) {
        printf("\t%d", msg[i]);
    }
    printf("\n");
}

