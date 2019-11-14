/*******************************************************************************************************************************************************************************
 * 
 * Arquivo: loop_pcap_teste.c
 * Criador: Lucas Araujo
 * Data: 28/08/2018
 * 
 * Teste de função pcap_loop para captura de todos os pacotes usando libpcap
 * ******************************************************************************************************************************************************************************/

#include <stdio.h>
#include <time.h>
#include <pcap.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>

// =============================================================================================================================================================================    

void my_packet_handle(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);
void print_packet_info(const u_char *packet, struct pcap_pkthdr packet_header);
// =============================================================================================================================================================================    


int main(int agrc, char argv[])
{
    char *device;
    char error_buffer[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    int timeout_limit = 10000;
    
    device = pcap_lookupdev(error_buffer);

// =============================================================================================================================================================================    
    //encontrando dispositivo
    if(device == NULL)
    {
        printf("Erro ao encontrar dispositivo: %s\n", error_buffer);
        return 1;
    }
    
// =============================================================================================================================================================================
    //abrindo dispositivo para captura
    handle = pcap_open_live(device, BUFSIZ, 0, timeout_limit, error_buffer);
    
    if(handle == NULL)
    {
        fprintf(stderr, "Não foi possivel abrir o dispositivo: %s: %s\n", device, error_buffer);
        return 2;
    }

// =============================================================================================================================================================================
    //pcap_loop
    pcap_loop(handle, 0, my_packet_handle, NULL);
    
    return 0;
}

// =============================================================================================================================================================================
void my_packet_handle(u_char *args, const struct pcap_pkthdr *packet_header, const u_char *packet_body)
{
    print_packet_info(packet_body, *packet_header);
    return;
}

// =============================================================================================================================================================================
void print_packet_info(const u_char *packet, struct pcap_pkthdr packet_header)
{
    printf("Tamanho do pacote capturado: %d\n", packet_header.caplen);
    printf("Tamanho total do pacote: %d\n\n", packet_header.len);
}
