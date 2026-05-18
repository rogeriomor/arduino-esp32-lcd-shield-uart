/** informaçoes Gerais do Script
 * @file LCD_SHIELD.cpp
 * @author rogerio m (rogeriol17q2@gmail.com)
 * @brief cpp para colocar bip, e para ler teclado e mostrar no display, 
 *          foi adicionado o bip que a cada tecla pressionada ele emite um som, e o display mostra a tecla pressionada, 
 *          tambem foram adicionadas tecla selecionar e reset, 
 *              **a selecionar serve para confirmar a escolha do botao, e 
 *              **o reset serve para limpar o display e voltar para a tela inicial
 * @version 0.1
 * @date 2026-05-04
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include <Arduino.h>
#include "LCD_SHIELD.h"

/** comentario do bip
 * @brief Emite um bip através do pino 3
 * * A função digitalWrite é usada para definir o pino 3 como HIGH (ligado) por 50 milissegundos,
 * depois é definido como LOW (desligado) para criar o efeito de bip.
 * @note Certifique-se de que um buzzer ou alto-falante esteja conectado ao pino 3 para ouvir o som.
 * @param None
 *  */
void bip() {
    digitalWrite(3, HIGH);
    delay(50);
    digitalWrite(3, LOW);
}
/** comentario do construtor
 * @brief Construct a new lcd tcl::lcd tcl object   
 * * O construtor da classe LCD_tcl inicializa o objeto visor_lcd com os pinos de controle e dados do LCD,
 * além de configurar o pino do botão (btn_pin) e as variáveis adc_tcl_entr e tcl para seus valores iniciais.
 * 
 * @note O visor_lcd é configurado para usar os pinos 8, 9, 4, 5, 6 e 7 para controle e dados do LCD.
 * 
 * 
 * 
 */
LCD_tcl::LCD_tcl()
    :visor_lcd(8, 9, 4, 5, 6, 7), btn_pin(A0), adc_tcl_entr(0), tcl(-1) {}

void LCD_tcl::begin() {
    visor_lcd.begin(16, 2);
    visor_lcd.print("LCD Teclado RM");
    delay(300);
    visor_lcd.clear();
    visor_lcd.createChar(0, setaCima);//131
    visor_lcd.createChar(1, setaBaixo);//307
    visor_lcd.createChar(2, setaEsquerda);//480
    visor_lcd.createChar(3, setaDireita);//00
    visor_lcd.createChar(4, setaSelecionar);//720
    
    

}

int LCD_tcl::ler_btn() {
    adc_tcl_entr = analogRead(btn_pin);

    if (adc_tcl_entr > 1000) return -1;  // nenhum botão

    if (adc_tcl_entr < 50)  { bip(); return 0; }//
    if (adc_tcl_entr < 250) { bip(); return 1; }
    if (adc_tcl_entr < 450) { bip(); return 2; }
    if (adc_tcl_entr < 650) { bip(); return 3; }
    if (adc_tcl_entr < 850) { bip(); return 4; }

    // nenhum botão pressionado
    return -1;
}

void LCD_tcl::imprimeLinha(uint8_t line, const char* text) {
    visor_lcd.setCursor(0, line);
    visor_lcd.print("                "); // limpa a linha
    visor_lcd.setCursor(0, line);
    visor_lcd.print(text);
}
//---------------------------------------------------------------------------
/** comentario
 * @brief  Definição dos caracteres personalizados para as setas e os botões de selecionar e reset
 * * * As variáveis setaCima, setaBaixo, setaEsquerda, setaDireita, setaSelecionar e setaReset 
 *      são arrays de bytes que definem os padrões de pixels para os caracteres personalizados usados no display LCD.
 * 
 */
byte setaCima[8] = {
  B00100,
  B01110,
  B11111,
  B00100,
  B00100,
  B00100,
  B00000,
  B00000,
};

byte setaBaixo[8] = {
  B00000,
  B00000,
  B00100,
  B00100,
  B00100,
  B11111,
  B01110,
  B00100,
};

byte setaEsquerda[8] = {
  B00000,
  B00100,
  B01100,
  B11111,
  B01100,
  B00100,
  B00000,
  B00000,
  
};

byte setaDireita[8] = {
  B00000,
  B00100,
  B00110,
  B11111,
  B00110,
  B00100,
  B00000,
  B00000,

};

byte setaSelecionar[8] = {
  B00000,
  B00000,
  B00100,
  B00010,
  B10010,
  B01010,
  B00100,
  B00000
};



//----------------------------------------------------------------------------
