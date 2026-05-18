
# DESCRIÇAO DO FUNCIONAMENTO DO MAIN

uas bibliotecas uma de urrt e uma que cuida do lcdshield para arduino uno . Quando ligar ele mostra um texto no cld -"selecionar comando", quero no teclado escolher um comando de uma lista, no caso o comando led, (com botoes subir ou descer), ele mostra um texto "selecione a cor", entao  seleciono a cor (R,G,ou b) numa lista rotativa, seelecionada a cor, ele mostra o texto cor: valor inicial seria 0, e em seguida vou ameuntando o valor da cor selecionada  de 10 em 10 com os botoes pra cima ou para baixo, esta cor é aramzenada numa variavel,  ate 255, confirmo o valor da cor, e vou para a outra cor com o teclado direita esquerda , podendo ir e voltar ci ate ter rb completo. Estando todas as cores com o valor, monta essa informaçao numa variavel "cor". Entao com dois clics rapidos em selecionar essa eu envio essa informaçao (cor r,g,b) para a uart no formato  [0x7E][Tamanho][Tipo][Payload...][Checksum] e a mesma envia pela uart. o TIPO é o nome do comando e o payload é a variavel das cores r,g,b. depois disso fica esperando uma resposta de cofnrimaçao da mensagem enviada e mostra no display o texto "comando confirmado" e volta ao menu iniciar, se nao vier nada colocar a mensagem "comando nao confirmado".

✅ 1. Estrutura geral do funcionamento
O seu sistema precisa seguir esta sequência:

Menu inicial → “Selecionar comando”

Navegar com UP/DOWN para escolher o comando (ex.: LED)

Entrar no comando → “Selecione a cor”

Navegar entre R / G / B (lista rotativa)

Selecionar uma cor → ajustar valor (0–255, passos de 10)

Confirmar valor → ir para próxima cor

Quando RGB estiver completo → montar variável cor

Enviar via UART no formato:

Código
[0x7E][Tamanho][Tipo][Payload...][Checksum]
Aguardar resposta:

Se OK → “comando confirmado”

Se timeout → “comando não confirmado”

Voltar ao menu inicial