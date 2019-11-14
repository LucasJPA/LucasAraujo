/*******************************************************************************************************************************************************************************
 * 
 * Arquivo: live_capture_teste.c
 * Criador: Lucas Araujo 
 * Data: 26/08/2018
 * 
 * Teste de captura de pacotes usando libpcap 
 ******************************************************************************************************************************************************************************/

#include <stdio.h>
#include <pcap.h>
#include <time.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>

void print_packet_info(const u_char *packet, struct pcap_pkthdr packet_header);

int main(int argc, char *argv[])
{
    char *device;
    char error_buffer[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    const u_char *packet;
    struct pcap_pkthdr packet_header;
    int packet_count_limit = 1;
    int timeout_limit = 10000;      //tempo de captura em milisegundos

// =============================================================================================================================================================================

    //encontrando o dispositivo
    device = pcap_lookupdev(error_buffer);
    
    if(device == NULL)
    {
        printf("Erro ao encontrado dispositivo %s\n", error_buffer);
        return 1;
    }
// =============================================================================================================================================================================
        
    /* pcap_open_live
     * pcap_t *pcap_open_live(char *device, int snaplen, int promisc, int to_ms, char *ebuf)
     */
    
    //abrindo o dispositivo para captura
    handle = pcap_open_live(device, BUFSIZ, packet_count_limit, timeout_limit, error_buffer);
// =============================================================================================================================================================================

    //pega o proximo pacote qeu chegara no dispositivo
    packet = pcap_next(handle, &packet_header);
    
    if(packet == NULL)
    {
        printf("\nPacote nao encontrado.\n");
        return 2;
    }
    else
        printf("\nPacote capturado !\n");
// =============================================================================================================================================================================
    
    printf("\n");
    
    //mostrando as informações do pacote
    print_packet_info(packet, packet_header);
    
    return 0;
}
// =============================================================================================================================================================================

void print_packet_info(const u_char *packet, struct pcap_pkthdr packet_header)
{
    printf("Tamanho do pacote capturado: %d\n", packet_header.caplen);
    printf("Tamanho total do pacote: %d\n\n", packet_header.len);
}
