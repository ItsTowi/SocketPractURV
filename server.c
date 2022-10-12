/* Codi solucio de la practica: SERVIDOR */

/* Inclusio de fitxers .h habituals */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Inclusio de fitxers .h per als sockets */
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MIDA_BUFFER 1024
 
int main(){
 
    int s;    /* Per treballar amb el socket */
    struct sockaddr_in serv_adr, client_adr;
    char buffer[MIDA_BUFFER];
    socklen_t mida;
    int n;
    int pack1, pack2, mul;
    
    /* Volem socket d'internet i no orientat a la connexio */
    s = socket(AF_INET, SOCK_DGRAM, 0);

    /* Posem les dades del socket */
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = INADDR_ANY;
    serv_adr.sin_port = htons(44444);

    /* Enllacem el socket */
    n = bind(s, (struct sockaddr*)&serv_adr, sizeof(serv_adr));

    if (n < 0)
    {
        printf("No s'ha pogut enllacar el socket\n");
    }
    else
    {
        /* Servidor operatiu! */
        printf("Servidor operatiu!\n");

        recvfrom(s, buffer, MIDA_BUFFER, 0, (struct sockaddr*)&client_adr, &mida);
        printf("Paquet rebut!\n");

        pack1 = atoi(buffer[0]);
        printf("El primer paquete es: %d", pack1);

        recvfrom(s, buffer, MIDA_BUFFER, 0, (struct sockaddr*)&client_adr, &mida);
        printf("Paquet rebut!\n");

        pack2 = atoi(buffer[1]);
        printf("El segundo paquete es: %d", pack2);

        if ((pack1 >= 0) && (pack2 >= 0) && (pack1 <= 99) && (pack2 <= 99))
        {
            mul = pack1 * pack2;
            sprintf(buffer, "%d", mul);
            sendto(s, buffer, MIDA_BUFFER, 0, (struct sockaddr*)&client_adr, sizeof(client_adr));
        }
        else
        {
            sprintf(buffer, "-1");
            sendto(s, buffer, MIDA_BUFFER, 0, (struct sockaddr*)&client_adr, sizeof(client_adr));
        }
    }

    /* Tanquem el socket */
    close(s);
    return 0;
}
