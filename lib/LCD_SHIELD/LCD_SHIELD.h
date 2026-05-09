/** comentarios do script   
 * @file LCD_SHIELD.h
 * @author rogerio m (rogeriol17q2@gmail.com)
 * @brief declarar as funçoes do teclado mais display, foi adicionado o bip que a cada tecla pressionada ele emite um som, e o display mostra a tecla pressionada
 * @version 0.01         
 * @date 2026-05-04
 * 
 * @copyright Copyright (c) 2026
 * 
 */
//----------------------------------------------------------
#ifndef BUZZER_H // proteçao para nao criar duas vezes o arquivo
#define BUZZER_H

 void bip(); // funcao do bip, que emite um som a cada tecla pressionada, usando o pino 3 para o buzzer ou alto-falante
 
#endif

//----------------------------------------------------------
#ifndef LCD_SHIELD_H // proteçao para nao criar duas vezes o arquivo
#define LCD_SHIELD_H        

#include <Arduino.h>
#include <LiquidCrystal.h>

/**
 * @brief   
 * * A classe LCD_tcl é responsável por gerenciar a interação entre o teclado e o display LCD. 
 * Ela inclui métodos para iniciar o LCD, ler os botões do teclado e imprimir texto no display. 
 * O construtor da classe inicializa o objeto visor_lcd com os pinos de controle e dados do LCD, além de configurar o pino do botão (btn_pin) e as variáveis adc_tcl_entr e tcl para seus valores iniciais.    
 * @struct LCD_tcl
 * @typedef LCD_tcl
 *          
 * 
 * 
 */
class LCD_tcl {

    private:
        int adc_tcl_entr;//valor ldio no adc;
        int tcl;
        int btn_pin;
        
    
    public:
        LCD_tcl(); // construtor da classe LCD_tcl
        void begin(); // funcao para iniciar o LCD
        int ler_btn(); // funcao para ler o valor do adc e determinar qual botao foi pressionado
        void imprimeLinha(uint8_t line,const char* text);
        void selecionar(); // funcao para confirmar o botao escolhido
        LiquidCrystal visor_lcd;
};

//variaveis de direçao
/**
 * @brief   
 * * * As variáveis d, e, c, b, r e s são usadas para representar os estados dos botões de direção 
 * (direita, esquerda, acima, abaixo) e os botões de reset e selecionar.
 * * * Essas variáveis são atualizadas com base na leitura do ADC (adc_tcl_entr) na função ler_btn() da classe LCD_tcl.
 * @todo As variáveis d, e, c, b, r e s devem ser definidas e atualizadas corretamente no código principal (main.cpp) 
 *                  para refletir o estado dos botões pressionados. 
 * 
 * 
 * 
 */

extern int d; //direita
extern int e; //esquerda
extern int c; //acima
extern int b; //abaixo
// novas variaveis -- selecionar

extern int s; //selecionar

// arrays dos icones de direçao do display

extern byte setaDireita[8];
extern byte setaEsquerda[8];
extern byte setaCima[8];
extern byte setaBaixo[8];  
//--- novos icones para reset e selecionar

extern byte setaSelecionar[8]; 



#endif


