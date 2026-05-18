#include "UART.h"

UART::UART(long baud) : _baud(baud) {}

void UART::begin() {
    Serial.begin(_baud);
}

/* ============================================================
   CHECKSUM (XOR)
   ============================================================ */
uint8_t UART::calcula_checksum(uint8_t tipo, const uint8_t* payload, uint8_t tamanho) {
    uint8_t cs = tipo;
    for (uint8_t i = 0; i < tamanho; i++) {
        cs ^= payload[i];
    }
    return cs;
}

/* ============================================================
   ENVIO DO FRAME
   Formato:
   [0x7E][Tamanho][Tipo][Payload...][Checksum]
   ============================================================ */
void UART::envia_frame(uint8_t tipo, const uint8_t* payload, uint8_t tamanho) {
    uint8_t checksum = calcula_checksum(tipo, payload, tamanho);

    Serial.write(0x7E);               // Start
    Serial.write(tamanho);            // Tamanho do payload
    Serial.write(tipo);               // Tipo
    Serial.write(payload, tamanho);   // Payload
    Serial.write(checksum);           // Checksum
}

/* ============================================================
   RECEPÇÃO DO FRAME COM TIMEOUT
   ============================================================ */
bool UART::recebe_frame(uint8_t& tipo, uint8_t* buffer, uint8_t& tamanho) {

    static enum {
        AGUARDA_START,
        AGUARDA_TAM,
        AGUARDA_TIPO,
        AGUARDA_PAYLOAD,
        AGUARDA_CHECKSUM
    } estado = AGUARDA_START;

    static uint8_t tam_temp = 0;
    static uint8_t tipo_temp = 0;
    static uint8_t index = 0;

    static unsigned long tempo_inicio = 0;
    const unsigned long TIMEOUT = 50; // 50 ms é ideal para UART

    while (Serial.available()) {

        uint8_t byte_lido = Serial.read();

        // Timeout: se demorou demais, reseta tudo
        if (estado != AGUARDA_START && (millis() - tempo_inicio > TIMEOUT)) {
            estado = AGUARDA_START;
            return false;
        }

        // Atualiza o tempo sempre que chega um byte válido
        tempo_inicio = millis();

        switch (estado) {

            case AGUARDA_START:
                if (byte_lido == 0x7E) {
                    estado = AGUARDA_TAM;
                }
                break;

            case AGUARDA_TAM:
                tam_temp = byte_lido;
                index = 0;
                estado = AGUARDA_TIPO;
                break;

            case AGUARDA_TIPO:
                tipo_temp = byte_lido;
                estado = (tam_temp > 0) ? AGUARDA_PAYLOAD : AGUARDA_CHECKSUM;
                break;

            case AGUARDA_PAYLOAD:
                buffer[index++] = byte_lido;
                if (index >= tam_temp) {
                    estado = AGUARDA_CHECKSUM;
                }
                break;

            case AGUARDA_CHECKSUM: {
                uint8_t checksum_recebido = byte_lido;
                uint8_t checksum_calc = calcula_checksum(tipo_temp, buffer, tam_temp);

                estado = AGUARDA_START; // Reset da máquina de estados

                if (checksum_calc == checksum_recebido) {
                    tipo = tipo_temp;
                    tamanho = tam_temp;
                    return true; // Frame válido
                }

                return false; // Checksum inválido
            }
        }
    }

    return false; // Ainda não terminou o frame
}
