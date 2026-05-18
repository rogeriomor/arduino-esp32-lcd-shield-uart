/** comentarios do script   
 * @file LCD_SHIELD.h
 * @author rogerio m (rogeriol17q2@gmail.com)
 * @brief Declarar as funções do teclado e display LCD, incluindo bip sonoro a cada tecla pressionada.
 * @version 0.02
 * @date 2026-05-04
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef LCD_SHIELD_H
#define LCD_SHIELD_H

#include <Arduino.h>
#include <LiquidCrystal.h>

void bip();

/**
 * @brief A classe LCD_tcl gerencia a interação entre o teclado e o display LCD.
 */
class LCD_tcl {

    private:
        int adc_tcl_entr; // valor lido no ADC
        int tcl;
        int btn_pin;

    public:
        LCD_tcl();
        void begin();
        int ler_btn();
        void imprimeLinha(uint8_t line, const char* text);
        void selecionar();
        LiquidCrystal visor_lcd;
};

// arrays dos ícones de direção do display
extern byte setaDireita[8];
extern byte setaEsquerda[8];
extern byte setaCima[8];
extern byte setaBaixo[8];
extern byte setaSelecionar[8];

#endif


