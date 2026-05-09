#include <Arduino.h>
#include "LCD_SHIELD.h" 


/** 
 * @file main.cpp
 * @author Rafael M. (  
 * @brief Este código é um exemplo de uso da classe LCD_tcl para ler os botões de um shield LCD e exibir mensagens correspondentes no display.
 * @version 0.1 
 * @date 2026-05-06
 *
 * 
 *      
 * */

LCD_tcl LCD_RM;

// contadores
int d = 0, e = 0, s = 0, b = 0, c = 0;

void setup() {
    pinMode(3, OUTPUT);
    LCD_RM.begin();
}

void loop() {

    LCD_RM.imprimeLinha(0, "Comando:");

    int btn = LCD_RM.ler_btn();

    const char* textos[] = {
        "Direita",      // 0
        "Cima",         // 1
        "Baixo",        // 2
        "Esquerda",     // 3
        "Selecionar",   // 4
        
    };

    // icones correspondentes aos botões
    const byte icones[] = {
        3, // seta direita
        0, // seta cima
        1, // seta baixo
        2, // seta esquerda
        4, // selecionar
        
    };

    //ponteiros para os contadores
    int* contadores[] = {&d, &c, &b, &e, &s};

    if (btn >= 0 && btn <= 5) {
        (*contadores[btn])++; // incrementa o contador correspondente

        char msg[17];
        snprintf(msg, sizeof(msg), "%s %d", textos[btn], *contadores[btn]);
        
        LCD_RM.imprimeLinha(1, msg);
        LCD_RM.visor_lcd.write(icones[btn]); // exibe o ícone correspondente


    } else {
        LCD_RM.imprimeLinha(1, "---------------");
    }

delay(300); // pequeno delay para evitar leituras muito rápidas
}