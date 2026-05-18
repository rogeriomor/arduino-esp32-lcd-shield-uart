#ifndef MAQUINA_ESTADOS_H
#define MAQUINA_ESTADOS_H

// 1. Enum
enum Estado {
    MENU_INICIAL,
    SELECIONAR_COMANDO,
    SELECIONAR_COR,
    AJUSTAR_VALOR,
    CONFIRMAR_ENVIO,
    AGUARDAR_RESPOSTA
};

// 2. Variáveis globais (se necessário)s
extern Estado estadoAtual;
extern int valorSelecionado;
extern int corSelecionada;

// 3. Protótipos das funções
void executarMenuInicial();
void executarSelecionarComando();
void executarSelecionarCor();
void executarAjustarValor();
void executarConfirmarEnvio();
void executarAguardarResposta();

void atualizarMaquinaDeEstados(); // loop da máquina

#endif
