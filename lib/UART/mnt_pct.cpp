// ---------------------------------------------------------
//  ENVIO DE PACOTE (TRANSMISSOR)
//  Formato do pacote:
//  [0x7E][size][type][payload...][checksum]
// ---------------------------------------------------------

#include <Arduino.h>

void uart_write(uint8_t b) {
    Serial.write(b);   // ou sua UART real
}

// ---------------------------------------------------------
// Função que envia um pacote completo
// ---------------------------------------------------------
void sendPacket(uint8_t type, uint8_t *payload, uint8_t size) {

    // 1) Inicia checksum com o TYPE
    uint8_t checksum = type;

    // 2) XOR com cada byte do payload
    for (int i = 0; i < size; i++)
        checksum ^= payload[i];

    // 3) Envia o pacote byte a byte
    uart_write(0x7E);      // Start
    uart_write(size);      // Tamanho do payload
    uart_write(type);      // Tipo da mensagem

    for (int i = 0; i < size; i++)
        uart_write(payload[i]);  // Payload

    uart_write(checksum);  // Checksum final
}

// ---------------------------------------------------------
//  AQUI ENTRA A MONTAGEM DO PAYLOAD E DO SIZE
// ---------------------------------------------------------

typedef struct {
    uint8_t id;
    uint16_t valor;
} Pacote;

void setup() {
    Serial.begin(115200);
}

void loop() {

    // 1) MONTA O PAYLOAD (a struct)
    Pacote p;
    p.id = 1;
    p.valor = 500;

    // 2) CALCULA O SIZE AUTOMATICAMENTE
    uint8_t size = sizeof(Pacote);   // size = 3 bytes

    // 3) ENVIA O PACOTE COMPLETO
    sendPacket(0x03, (uint8_t*)&p, size);

    delay(1000);
}
