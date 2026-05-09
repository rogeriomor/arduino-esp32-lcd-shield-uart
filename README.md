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

---

## 🧩 Hardware Utilizado

- Arduino Uno  
- LCD Keypad Shield  
- ESP32-S3  
- Cabos jumper  
- Comunicação UART (TX/RX)

---

## 🔌 Conexões UART

| Arduino Uno | ESP32-S3 |
|-------------|----------|
| TX (D1)     | RX       |
| RX (D0)     | TX       |
| GND         | GND      |

Baud rate recomendado: **115200**

---

## 🧱 Estrutura do Protocolo UART

Formato do pacote:

```
[0x7E][Tamanho][Tipo][Payload...][Checksum]
```

- **0x7E** → Start byte  
- **Tamanho** → Número de bytes do payload  
- **Tipo** → ID da mensagem  
- **Payload** → Dados  
- **Checksum** → CRC8 ou XOR simples  

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

## 🚀 Como compilar e executar

1. Instale o **PlatformIO** no VS Code  
2. Abra a pasta do projeto  
3. Compile com **PlatformIO: Build**  
4. Faça upload para o Arduino Uno  
5. Faça upload do firmware correspondente no ESP32-S3  
6. Abra o monitor serial para depuração

---

## 🧪 Testes e Validação

- Teste de envio contínuo de pacotes UART  
- Teste de checksum inválido  
- Teste de perda de start byte  
- Teste de reconexão física (TX/RX)  
- Teste de ruído no canal serial  

---

## 📜 Licença

Este projeto está sob a licença **MIT**.  
Você pode usar, modificar e distribuir livremente.

---

## 🤝 Contribuições

Contribuições são bem-vindas.  
Para mudanças maiores, abra uma *issue* antes para discutirmos o que deseja alterar.

---

## 📬 Contato

Criado por **Rogério**.  
Se quiser trocar ideias sobre firmware, UART ou ESP32, fique à vontade para abrir uma issue no repositório.

