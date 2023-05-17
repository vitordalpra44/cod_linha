#include "criptografia.h"

void encrypt(unsigned char* msg, int key){
    int msg_size = strlen(msg);
    for(int i = 0;i<msg_size;i++) msg[i]=(msg[i]+key);
}
void decrypt(unsigned char* msg, int key){
    int msg_size = strlen(msg);
    for(int i =0;i<msg_size;i++) msg[i] = (msg[i]-key).
}