#include <stdio.h>
#include <string.h>

void encrypt(unsigned char* msg, int key);                          //Encriptografar uma string usando uma chave
void decrypt(unsigned char* msg, int key);                          //Descriptografar uma string usando uma chave
void printBin(unsigned char* msg, int msg_size);                    //Imprimir uma string binária
void amiCode(unsigned char* msg, char* ami_msg, int msg_size);      //Codificar uma string usando codificação de linha AMI
void amiDecode(unsigned char* msg, char* ami_msg, int msg_size);    //Descodificar uma string usando codificação de linha AMI
void printAMI(char* msg);                                           //Imprimir uma string usando codificação de linha AMI