#include <StateMachine.h>
#include <Globals.h>
#include <UART.h>
#include <Display.h>
#include <Beep.h>

enum Estado {
    ESPERANDO,
    PROCESSANDO_COMANDO,
    ATUALIZANDO_DISPLAY,
    TOCANDO_BEEP
};

Estado estadoAtual = ESPERANDO;

void runStateMachine() {
    switch (estadoAtual) {

        case ESPERANDO:
            if (UART_temComando()) {
                estadoAtual = PROCESSANDO_COMANDO;
            }
            break;

        case PROCESSANDO_COMANDO:
            processarComando();
            estadoAtual = ATUALIZANDO_DISPLAY;
            break;

        case ATUALIZANDO_DISPLAY:
            atualizarDisplay();
            estadoAtual = TOCANDO_BEEP;
            break;

        case TOCANDO_BEEP:
            tocarBeep();
            estadoAtual = ESPERANDO;
            break;
    }
}
