Contador de 0 até 9 usando uma matriz de led's 5x5
--
📋 **Sobre**
O código implementa o controle de uma matriz de LEDs WS2812 (uma matriz de 5x5 LEDs) 
utilizando o Raspberry Pi Pico w e os botões físicos conectados a placa da BitDogLab para exibir números de 0 a 9.
--
**Funcionamento**
1 - Configuração de GPIOs:

Inicializa os pinos dos botões e LEDs, configurando-os como entrada/saída e ativando os resistores pull-up nos botões.

2 - Controle da matriz de LEDs:

Usa um buffer para armazenar quais LEDs da matriz estão acesos. Cada número (de 0 a 9) é representado por um padrão de LEDs correspondente.

3 - Controle de botões:

Botão A incrementa o número exibido na matriz (0 a 9).
Botão B decrementa o número exibido (9 a 0).
Um sistema de debounce evita múltiplos acionamentos indesejados dos botões.
