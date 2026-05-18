# Arduino → ESP32-S3 via UART com LCD Shield

Este projeto implementa a comunicação entre um **Arduino Uno** equipado com um **LCD Keypad Shield** e um **ESP32-S3**, utilizando **UART** com protocolo próprio.  
O objetivo é enviar comandos estruturados do Arduino para o ESP32, garantindo confiabilidade, sincronização e fácil expansão.

---

## 📡 Objetivo do Projeto

- Ler entradas do LCD Shield (botões e display)
- Montar pacotes UART com start byte, tamanho e checksum
- Enviar comandos para o ESP32-S3
- Implementar máquina de estados para recepção confiável
- Criar uma base modular para expansão futura

-vai:

   - gerenciar as cores do led interno do esp32s3, 
   - pedir horas (da internet)
   - pedir outras informaçoes

## como vai funcionar?

- o arduino inicializa e envia uma mensagem onde pede as horas para o outro lado, espera alguns segundos pela resposta, se nao vier, ele mostra que nao veio.
- mostra a mensagem no display " Escolher a cor ";
- coloca no display que estamos na cor red;
- se continuar digitando para direita ou esquerda vai ficar rodando R,G, B;
- inicia todas as cores em 0;
- vai mostrar no display  R=0,G=0,B=0
- uma vez escolhido a cor no display, aperta selecionar;
- agora fica esperando digitar para cima ou para baixo;
- cada vez que selecionar acima ou abaixo:
   - começando em 0 (se teclar pra baixo nao faz nada);
   - se teclar pra cima cada vez adiciona 10 e vai dando a intensidade de cor;
   - dai se coloca um valor em cada letra de 0 a 255, dando no final uma cor
   - terminando aperta selecionar, ao selecionar a variavel rgb é disponibilizada para a outra classe da uart enviar.
   - o arduino vai esperar


pode ser que seja interesante fazer uma lista com mais comandos, pegando






---

## 🧩 Hardware Utilizado

- Arduino Uno  
- LCD Keypad Shield  
- ESP32-S3  
- Cabos jumper  
- Comunicação UART (TX/RX)

---




## 📁 Estrutura do Projeto (PlatformIO)

```
/src
   main.cpp
/include
/lib
/docs
   protocolo_uart.md
   arquitetura.md
platformio.ini
```

---



## 📬 Contato

Criado por **Rogério**.  
Se quiser trocar ideias sobre firmware, UART ou ESP32, fique à vontade para abrir uma issue no repositório.

