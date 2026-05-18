/**
 * @file UART.h
 * @author 
 * @brief Classe para envio e recepção de frames UART no formato:
 *        [0x7E][Tamanho][Tipo][Payload...][Checksum]
 *
 * @version 1.0
 * @date 2026-05-08
 */

#ifndef UART_H
#define UART_H

#include <Arduino.h>

class UART {

public:

    /**
     * @brief Construtor da classe UART
     * @param baud Velocidade da UART (ex: 115200)
     */
    UART(long baud);
    void begin();

    /**
     * @brief Envia um frame no formato:
     *        [0x7E][Tamanho][Tipo][Payload...][Checksum]
     *
     * @param tipo Tipo da mensagem
     * @param payload Ponteiro para os dados
     * @param tamanho Quantidade de bytes no payload
     */
    void envia_frame(uint8_t tipo, const uint8_t* payload, uint8_t tamanho);

    /**
     * @brief Recebe um frame completo
     *
     * @param tipo (saída) Tipo da mensagem recebida
     * @param buffer (saída) Buffer onde o payload será armazenado
     * @param tamanho (saída) Tamanho real do payload recebido
     *
     * @return true se um frame válido foi recebido
     * @return false se ainda não terminou ou se houve erro
     */
    bool recebe_frame(uint8_t& tipo, uint8_t* buffer, uint8_t& tamanho);

private:

    long _baud;

    /**
     * @brief Calcula o checksum XOR do frame
     *
     * @param tipo Tipo da mensagem
     * @param payload Dados do payload
     * @param tamanho Tamanho do payload
     * @return uint8_t Checksum calculado
     */
    uint8_t calcula_checksum(uint8_t tipo, const uint8_t* payload, uint8_t tamanho);
};

#endif
