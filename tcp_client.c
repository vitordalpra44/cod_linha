#include "include.h"
#define MAXCHAR 200
#define MAXBUFFER MAXCHAR*8

int main(int argc, char *argv[]){

    if(argc<3){
        fprintf(stderr, "usage: tcp_client hostname port\n");
        return 1;
    }

    //Bloco que configura o endereço remoto...
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    struct addrinfo *peer_address;
    if(getaddrinfo(argv[1], argv[2], &hints, &peer_address)){
        fprintf(stderr, "Falha ao configurar endereço remoto. getaddrinfo() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }


    //Bloco que cria o socket
    SOCKET socket_peer;
    socket_peer = socket(peer_address->ai_family,
                        peer_address->ai_socktype, peer_address->ai_protocol);
    if(!ISVALIDSOCKET(socket_peer)){
        fprintf(stderr,"Socket falhou. (%d)\n", GETSOCKETERRNO());
        return 1;
    }


    //Bloco que conecta o socket criado com o endereço indicado
    if(connect(socket_peer, peer_address->ai_addr, peer_address->ai_addrlen)){
        fprintf(stderr, "Conexão falhou. (%d)", GETSOCKETERRNO());
        return 1;
    }
    freeaddrinfo(peer_address);
    printf("Conectado...");
    
    

    //Recebendo e enviando informação enquanto a conexão estiver aberta...
    while(1){
        fd_set reads;
        FD_ZERO(&reads);
        FD_SET(socket_peer, &reads);
        FD_SET(0, &reads);
        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 100000; //limite de espera
        if(select(socket_peer+1, &reads, 0, 0, &timeout)<0){
            fprintf(stderr, "select() falhou. (%d)", GETSOCKETERRNO());
            return 1;
        }

        //Recebendo dados do servidor
        if(FD_ISSET(socket_peer, &reads)){
            unsigned char read[MAXBUFFER];
            int bytes_received = recv(socket_peer, read, MAXBUFFER, 0);
            if (bytes_received<1){
                printf("Conexão interrompida pelo peer\n");
                break;
            }
            printf("\n%.*s",bytes_received, read);
        }



        /*Esse bloco efetivamente pega uma string digitada pelo usuário,
         criptografa, transforma em bits, faz a codificação de linha AMI,
        e envia para o servidor que fará o processo inverso.*/
        if(FD_ISSET(0, &reads)){
            unsigned char read[MAXBUFFER];
            printf("\nDigite a mensagem: ");
            if(!fgets(read, 4096, stdin)) break;
            printf("Mensagem original: %s", read);
            

            int bytes_sent = send(socket_peer, read, strlen(read), 0);

        }
    }

    //Fechando socket
    CLOSESOCKET(socket_peer);
    printf("\nEncerrado\n");
    return 0;
}