#include <Arduino.h>
#include "LCD_SHIELD.h"
#include "UART.h"

LCD_tcl LCD_RM;
UART uart(9600);

enum AppState {
    ESCOLHER_COR,
    AJUSTAR_VALOR,
    AGUARDAR_RESPOSTA
};

AppState estadoAtual = ESCOLHER_COR;
uint8_t rgb[3] = {0, 0, 0};
uint8_t corSelecionada = 0;
int valorAjuste = 0;
unsigned long tempoEnvio = 0;

const char* nomesCores[] = {"RED", "GRN", "BLU"};

void mostrarStatus() {
    char linha0[17];
    char linha1[17];
    snprintf(linha0, sizeof(linha0), "Escolher %s", nomesCores[corSelecionada]);
    snprintf(linha1, sizeof(linha1), "R=%03d G=%03d B=%03d", rgb[0], rgb[1], rgb[2]);
    LCD_RM.imprimeLinha(0, linha0);
    LCD_RM.imprimeLinha(1, linha1);
}

void mostrarAjuste() {
    char linha0[17];
    char linha1[17];
    snprintf(linha0, sizeof(linha0), "Ajustar %s", nomesCores[corSelecionada]);
    snprintf(linha1, sizeof(linha1), "%03d / 255   %s", valorAjuste, nomesCores[corSelecionada]);
    LCD_RM.imprimeLinha(0, linha0);
    LCD_RM.imprimeLinha(1, linha1);
}

void enviarRGB() {
    uint8_t payload[3] = {rgb[0], rgb[1], rgb[2]};
    uart.envia_frame(0x10, payload, sizeof(payload));
    tempoEnvio = millis();
    LCD_RM.imprimeLinha(0, "Enviado RGB");
    LCD_RM.imprimeLinha(1, "Aguardando...");
    estadoAtual = AGUARDAR_RESPOSTA;
}

void mostrarResposta(const char* texto) {
    LCD_RM.imprimeLinha(0, "Resposta:");
    LCD_RM.imprimeLinha(1, texto);
}

void setup() {
    pinMode(3, OUTPUT);
    LCD_RM.begin();
    uart.begin();
    mostrarStatus();
}

void loop() {
    int btn = LCD_RM.ler_btn();

    if (estadoAtual == ESCOLHER_COR) {
        if (btn == 0) {
            corSelecionada = (corSelecionada + 1) % 3;
            mostrarStatus();
        } else if (btn == 3) {
            corSelecionada = (corSelecionada + 2) % 3;
            mostrarStatus();
        } else if (btn == 4) {
            valorAjuste = rgb[corSelecionada];
            estadoAtual = AJUSTAR_VALOR;
            mostrarAjuste();
        }
    } else if (estadoAtual == AJUSTAR_VALOR) {
        if (btn == 1) {
            valorAjuste = min(255, valorAjuste + 10);
            mostrarAjuste();
        } else if (btn == 2) {
            valorAjuste = max(0, valorAjuste - 10);
            mostrarAjuste();
        } else if (btn == 3) {
            estadoAtual = ESCOLHER_COR;
            mostrarStatus();
        } else if (btn == 4) {
            rgb[corSelecionada] = valorAjuste;
            enviarRGB();
        }
    } else if (estadoAtual == AGUARDAR_RESPOSTA) {
        uint8_t tipo;
        uint8_t buffer[16];
        uint8_t tamanho;

        if (uart.recebe_frame(tipo, buffer, tamanho)) {
            char texto[17];
            if (tamanho > 0) {
                int len = min((int)tamanho, 14);
                for (int i = 0; i < len; ++i) {
                    texto[i] = isprint(buffer[i]) ? buffer[i] : '.';
                }
                texto[len] = '\0';
            } else {
                snprintf(texto, sizeof(texto), "OK T=%02u", tipo);
            }
            mostrarResposta(texto);
            delay(1000);
            estadoAtual = ESCOLHER_COR;
            mostrarStatus();
        } else if (millis() - tempoEnvio > 2000) {
            mostrarResposta("Sem resp.");
            delay(1000);
            estadoAtual = ESCOLHER_COR;
            mostrarStatus();
        }
    }

    delay(150);
}

