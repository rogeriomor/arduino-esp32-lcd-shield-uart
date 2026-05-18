#UART ENTRE ESP32 E ARDUINO UNO


## o que vai fazer essa classe?

Vai receber variaveis para montagem do pacote e o mesmo vai ser  formatado assim:

**<u>Formato do pacote:</u>**


# **[0x7E][Tamanho][Tipo][Payload...][Checksum]**

- **0x7E** → Start byte  
- **Tamanho** → Número de bytes do payload  
- **Tipo** → ID da mensagem 
    - pedido de informaçoes **(req)**, 
    - acionamento de led **(com)**, comando direto, acionar uma gpio 
    - retorno **(prt)** protocolo de comunicaçao
    - informes **(inf)** dados de sensores
    - funçoes **(fun)** mandar piscar, transmitir pesquisar
- **Payload** → Dados  
- **Checksum** → CRC8 ou XOR simples

 Entao vai montar o pacote e enviar

## 🧪 Testes e Validação

- Teste de envio contínuo de pacotes UART  
- Teste de checksum inválido  
- Teste de perda de start byte  
- Teste de reconexão física (TX/RX)  
- Teste de ruído no canal serial  

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