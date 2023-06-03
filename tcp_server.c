#include "include.h"
#include "func.h"

#define MYPORT "8080"
int main(){

    //Configurando endereço local;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *bind_address;
    getaddrinfo(0, MYPORT, &hints, &bind_address);

    //Criando socket
    SOCKET socket_listen;
    socket_listen = socket(bind_address->ai_family,
                            bind_address->ai_socktype, bind_address->ai_protocol);
    if(!ISVALIDSOCKET(socket_listen)){
        fprintf(stderr, "Socket falhou (%d)", GETSOCKETERRNO());
        return 1;
    }

    //Vinculando o socket com o endereço local
    if(bind(socket_listen, bind_address->ai_addr, bind_address->ai_addrlen)){
        fprintf(stderr, "Bind falhou (%d)", GETSOCKETERRNO());
        return 1;
    }

    freeaddrinfo(bind_address);

    //Esperando por conexão
    if(listen(socket_listen, 10)<0){
        fprintf(stderr, "Listen falhou (%d)", GETSOCKETERRNO());
        return 1;
    }

    fd_set master;
    FD_ZERO(&master);
    FD_SET(socket_listen, &master);
    SOCKET max_socket = socket_listen;

    printf("Esperando por conexões...\n");
    while(1){
        fd_set reads;
        reads = master;
        if(select(max_socket+1, &reads, 0, 0, 0)<0){
            fprintf(stderr, "Select falhou (%d)", GETSOCKETERRNO());
            return 1;
        }
        
        SOCKET i;
        for(i=1; i<=max_socket; ++i){
            if(FD_ISSET(i, &reads)){
                if( i== socket_listen){
                    struct sockaddr_storage client_address;
                    socklen_t client_len = sizeof(client_address);
                    SOCKET socket_client = accept(socket_listen, (struct sockaddr*) &client_address, &client_len);
                    if(!ISVALIDSOCKET(socket_client)){
                        fprintf(stderr, "accept falhou (%d)", GETSOCKETERRNO());
                        return 1;                   
                    }
                    FD_SET(socket_client, &master);
                    if(socket_client>max_socket)
                        max_socket= socket_client;
                    
                    char address_buffer[100];
                    getnameinfo((struct sockaddr*) &client_address, client_len, address_buffer, sizeof(address_buffer), 0, 0, NI_NUMERICHOST);
                    printf("Nova conexão de %s\n", address_buffer);

                
                }else{
                    char msg_ami[MAXBUFFER]={0};
                    unsigned char msg[MAXBUFFER]={0};
                    int ami_msg_size=0;
                    ami_msg_size= recv(i, msg_ami, MAXBUFFER, 0);
                    if(ami_msg_size<1){
                        FD_CLR(i, &master);
                        CLOSESOCKET(i);
                        continue;
                    }
                    ami_msg_size -=1; //Tirando o '@' do final
                    printf("\n\n");
                    printf("Mensagem criptografada e codificada AMI:");
                    printAMI(msg_ami);
                    amiDecode(msg_ami, ami_msg_size/8, msg);
                    printf("Mensagem criptografada em binário:");
                    printBin(msg, ami_msg_size/8);
                    printf("Mensagem criptografada: %s", msg);
                    decrypt(msg, 1);
                    printf("\nMensagem original: %s", msg);
                    fflush(stdout);
                }

            }

        }

    }

    printf("\nFechando o socket...");
    CLOSESOCKET(socket_listen);
    printf("\nEncerrado...\n");





    return 0;
}