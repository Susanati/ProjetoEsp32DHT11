
# Projeto com placa de desenvolvimento ESP32






## Documentação

 - [Documentação de laçamento mais recente](https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/)

# Construindo com make
- [Wokwi é um simulador de eletrônica online](https://docs.wokwi.com/pt-BR/)
# Arduino Esp32

ESP32 é um único SoC (System On a Chip) Wi-Fi e Bluetooth de 2,4 GHz projetado pela Espressif Systems .

ESP32 foi projetado para aplicativos móveis, eletrônicos vestíveis e Internet das Coisas (IoT). Ele apresenta todas as características de última geração de chips de baixo consumo de energia, incluindo clock gating refinado, vários modos de energia e escala de potência dinâmica. Por exemplo, em um cenário de aplicação de hub de sensor IoT de baixa potência, o ESP32 é ativado periodicamente e somente quando uma condição especificada é detectada. O ciclo de trabalho baixo é usado para minimizar a quantidade de energia que o chip gasta.

A saída do amplificador de potência também é ajustável, contribuindo assim para um equilíbrio ideal entre alcance de comunicação, taxa de dados e consumo de energia.

A série ESP32 está disponível como chip ou módulo.


## Primeiros passos
Aqui estão os primeiros passos para colocar o suporte do Arduino ESP32 em execução.

Para instalar o Arduino-ESP32, consulte a seção dedicada no Guia de instalação. Recomendamos que você instale-o usando o gerenciador de placas.

## Como Instalar

 - [Antes de instalar](https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/installing.html#before-installing/)

- [Instalando usando Arduino IDE](https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/installing.html#installing-using-arduino-ide/)

- [Instalando usando PlatformIO](https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/installing.html#installing-using-platformio/)

- [Windows (instalação manual)](https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/installing.html#windows-manual-installation/)

- [Linux](https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/installing.html#linux/)

- [Mac OS](https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/installing.html#macos/)

## Conselhos de Desenvolvimento

 - [Conselhos de Desenvolvimento](https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/boards/boards.html#development-boards/)

- [Expresso](https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/boards/boards.html#espressif/)

- [Terceiro](https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/boards/boards.html#third-party/)

- [Ficha de dados](https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/boards/boards.html#datasheet/)

- [Recursos](https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/boards/boards.html#resources/)

## Conteúdo sobre ESP32

### Pinagem correta para eu utilizar meu ESP32.

O ESP32, em um datasheet, como neste acima, temos nos destaques a identificação correta dos pinos. Muitas vezes o rótulo no chip não coincide com o número real do pino, já que temos três situações: o GPIO, o número seriado e ainda o código da própria placa.


### INPUT / OUTPUT

Ao realizar testes de INPUT e OUTPUT nos pinos, obtivemos os seguintes resultados:
INPUT não funcionou apenas no GPIO0.
OUTPUT não funcionou apenas nos pinos GPIO34 e GPIO35, que são VDET1 e VDET2 respectivamente.
*Os pinos VDET, pertencem ao domínio de energia do RTC. Significa que eles podem ser usados como pinos ADC e que o ULP-coprocessador pode lê-los. Podem ser apenas entradas e nunca saídas.

### GPIO

Analog-to-Digital Converter (ADC)
O Esp32 integra ADCs de 12 bits e suporta medições em 18 canais (analog-enabled pins). O ULP-coprocessador no ESP32 também é projetado para medir as tensões enquanto opera em modo sleep, que permite o baixo consumo de energia. A CPU pode ser despertada por uma configuração de limite e/ou através de outros gatilhos.

Digital-to-Analog Converter (DAC)
Dois canais DAC de 8 bits podem ser usados para converter dois sinais digitais em duas saídas de tensão analógica. Estes DAC duplos suportam a fonte de alimentação como referência de tensão de entrada e pode conduzir outros circuitos. Os canais duplos suportam conversões independentes.

### Sensores

Touch Sensor
O ESP32 tem 10 GPIOs de detecção capacitiva que detectam variações induzidas ao tocar ou aproximar de um GPIO com um dedo ou outros objetos.

O ESP32 ainda possui um sensor de Temperatura e um Sensor Hall interno, porém, para trabalhar com eles devem-se mudar as configurações dos registradores.

### SWatchdog

O ESP32 tem três temporizadores de vigilância: um em cada um dos dois módulos de temporizador (chamado o Temporizador de Watchdog Principal, ou MWDT) e um no módulo RTC (chamado RTC Watchdog Timer ou RWDT).

### Bluetooth

Interface Bluetooth v4.2 BR/EDR e Bluetooth LE (low energy)
O ESP32 integra um controlador de ligação Bluetooth e Bluetooth baseband, que executam os protocolos de banda base e outras rotinas de links de baixo nível, como modulação/desmodulação, processamento de pacotes, processamento de fluxo de bits, saltos de frequência, etc.
O controlador de ligação opera em três estados principais: standby, connection e sniff. Permite múltiplas conexões e outras operações, como inquiry, page e secure simple-pairing, e, portanto, permite a Piconet e Scatternet.

### Boot

Em muitas placas de desenvolvimento com USB/Serial incorporado o esptool.py pode redefinir automaticamente a placa para o modo de inicialização.
O ESP32 entrará no carregador de inicialização serial quando o GPIO0 for mantido baixo na reinicialização. Caso contrário, ele executará o programa em flash.



# Projeto ESP32 com Sensor DHT11 e WI-FI

## Sensor DHT11
O DHT11 é um sensor de temperatura e umidade que permite fazer leituras de temperaturas entre 0 a 50 Celsius e umidade entre 20 a 90%.

### Bibliotecas de sensores DHT
Para ler o sensor DHT, usaremos a  biblioteca DHT da Adafruit . Para usar esta biblioteca você também precisa instalar a  biblioteca Adafruit Unified Sensor . Siga as próximas etapas para instalar essas bibliotecas.

1. Abra seu Arduino IDE e vá para  Sketch  >  Incluir Biblioteca  >  Gerenciar Bibliotecas . O Gerenciador da Biblioteca deve abrir.

2. Pesquise “ DHT ” na caixa Pesquisar e instale a biblioteca DHT da Adafruit.

3. Após instalar a biblioteca DHT da Adafruit, digite “ Adafruit Unified Sensor ” na caixa de pesquisa. Role até o fim para encontrar a biblioteca e instalá-la.

Após instalar as bibliotecas, reinicie seu Arduino IDE.
