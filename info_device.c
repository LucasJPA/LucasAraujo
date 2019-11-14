/*******************************************************************************************************************************************************************************
 * 
 * Arquivo: info_device.c
 * Criador: Lucas Araujo
 * Data: 25/08/2018
 * 
 * Obtendo informações do dispositivo de rede encontrado usando libpcap
 ******************************************************************************************************************************************************************************/

#include <stdio.h>
#include <pcap.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *device;
    char ip[13];
    char subnet_mask[13];
    bpf_u_int32 ip_raw;     //endereço de ip e um inteiro
    bpf_u_int32 subnet_mask_raw;    //mascara da subrede e um inteiro
    int lookup_return_code;
    char error_buffer[PCAP_ERRBUF_SIZE];    //tamanho definido em pcap.h
    struct in_addr address;     //usado para ip e mascara da subrede

// =============================================================================================================================================================================
    
    //encontrando o dispositivo
    device = pcap_lookupdev(error_buffer);
    
    if(device == NULL)
    {
        printf("Erro ao encontrar dispositivo: %s\n", error_buffer);
        return 1;
    }
// =============================================================================================================================================================================
    
    //obtendo informações do dispositivo
    lookup_return_code = pcap_lookupnet(device, &ip_raw, &subnet_mask_raw, error_buffer);
    
    if(lookup_return_code == -1)
    {
        printf("%s\n", error_buffer);
        return 1;
    }
// =============================================================================================================================================================================

    //obtendo ip de forma legivel
    address.s_addr = ip_raw;
    strcpy(ip, inet_ntoa(address));
    
    if(ip == NULL)
    {
        perror("inet_ntoa");
        return 1;
    }
// =============================================================================================================================================================================

    //obtendo a mascara da subrede de forma legivel
    address.s_addr = subnet_mask_raw;
    strcpy(subnet_mask, inet_ntoa(address));
    
    if(subnet_mask == NULL)
    {
        perror("inet_ntoa");
        return 1;
    }
// =============================================================================================================================================================================

    printf("\n");
    
    printf("Dispositivo: %s\n", device);
    printf("Endereço de IP: %s\n", ip);
    printf("Mascara da subrede: %s\n", subnet_mask);
    
    printf("\n");
    
    return 0;
}
