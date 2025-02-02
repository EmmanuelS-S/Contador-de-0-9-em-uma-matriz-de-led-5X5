//Atividade da  Aula Síncrona 27/01
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/timer.h"
#include "ws2812.pio.h"

#define IS_RGBW false // Não sei para que foi usado
#define botao_A 5
#define botao_B 6
#define led_red 13
#define led_blue 12
#define matriz_pin 7
#define NUM_PIXELS 25
#define tempo 200

// Variável global para armazenar a cor (Entre 0 e 255 para intensidade)
uint8_t led_r = 10; // Intensidade do vermelho
uint8_t led_g = 10; // Intensidade do verde
uint8_t led_b = 10; // Intensidade do azul

static volatile uint32_t last_time = 0; // Armazena o tempo do último evento (em microssegundos)
static volatile uint32_t cont = 0;
volatile bool led_update_flag = true; // Variável de controle para a atualização do buffer

void config_gpio(){
    // Inicialização dos pinos
    gpio_init(botao_A);
    gpio_init(led_blue);
    gpio_init(botao_B);
    gpio_init(led_red);
    gpio_init(matriz_pin);

    // Definição de direção dos pinos
    gpio_set_dir(botao_A, GPIO_IN);
    gpio_set_dir(botao_B, GPIO_IN);
    gpio_set_dir(led_red, GPIO_OUT);
    gpio_set_dir(led_blue, GPIO_OUT);
    gpio_set_dir(matriz_pin, GPIO_OUT);

    // Configuração como pull-up (Solto 1, pressionado 0)
    gpio_pull_up(botao_A);
    gpio_pull_up(botao_B);
}

// Buffer para armazenar quais LEDs estão ligados na matriz 5x5
bool led_buffer[NUM_PIXELS] = {
    0, 0, 0, 0, 0, 
    0, 0, 1, 0, 0, 
    0, 1, 1, 1, 0, 
    0, 0, 1, 0, 0, 
    0, 0, 0, 0, 0
};

// Função para mostrar o número na matriz (modificando o buffer)
void show_number(bool led_buffer[NUM_PIXELS]) {
    switch (cont) {
        case 0:
            printf("\n Exibindo 0\n");
            bool matriz_0[NUM_PIXELS] = {
                0, 1, 1, 1, 0,
                0, 1, 0, 1, 0,
                0, 1, 0, 1, 0,
                0, 1, 0, 1, 0,
                0, 1, 1, 1, 0
            };
            for (int i = 0; i < NUM_PIXELS; i++) {
                led_buffer[i] = matriz_0[i];
            }
            break;

        case 1:
            printf("\n Exibindo 1\n");
            bool matriz_1[NUM_PIXELS] = {
                0, 1, 1, 1, 0,
                0, 0, 1, 0, 0,
                0, 0, 1, 0, 0,
                0, 1, 1, 0, 0,
                0, 0, 1, 0, 0
            };
            for (int i = 0; i < NUM_PIXELS; i++) {
                led_buffer[i] = matriz_1[i];
            }
            break;

        case 2:
            printf("\n Exibindo 2\n");
            bool matriz_2[NUM_PIXELS] = {
                0, 1, 1, 1, 0,
                0, 1, 0, 0, 0,
                0, 1, 1, 1, 0,
                0, 0, 0, 1, 0,
                0, 1, 1, 1, 0
            };
            for (int i = 0; i < NUM_PIXELS; i++) {
                led_buffer[i] = matriz_2[i];
            }
            break;

        case 3:
            printf("\n Exibindo 3\n");
            bool matriz_3[NUM_PIXELS] = {
                0, 1, 1, 1, 0,
                0, 0, 0, 1, 0,
                0, 1, 1, 1, 0,
                0, 0, 0, 1, 0,
                0, 1, 1, 1, 0
            };
            for (int i = 0; i < NUM_PIXELS; i++) {
                led_buffer[i] = matriz_3[i];
            }
            break;

        case 4:
            printf("\n Exibindo 4\n");
            bool matriz_4[NUM_PIXELS] = {
                0, 1, 0, 0, 0,
                0, 0, 0, 1, 0,
                0, 1, 1, 1, 0,
                0, 1, 0, 1, 0,
                0, 1, 0, 1, 0
            };
            for (int i = 0; i < NUM_PIXELS; i++) {
                led_buffer[i] = matriz_4[i];
            }
            break;

        case 5:
            printf("\n Exibindo 5\n");
            bool matriz_5[NUM_PIXELS] = {
                0, 1, 1, 1, 0,
                0, 0, 0, 1, 0,
                0, 1, 1, 1, 0,
                0, 1, 0, 0, 0,
                0, 1, 1, 1, 0
            };
            for (int i = 0; i < NUM_PIXELS; i++) {
                led_buffer[i] = matriz_5[i];
            }
            break;

        case 6:
            printf("\n Exibindo 6\n");
            bool matriz_6[NUM_PIXELS] = {
                0, 1, 1, 1, 0,
                0, 1, 0, 1, 0,
                0, 1, 1, 1, 0,
                0, 1, 0, 0, 0,
                0, 1, 1, 1, 0
            };
            for (int i = 0; i < NUM_PIXELS; i++) {
                led_buffer[i] = matriz_6[i];
            }
            break;

        case 7:
            printf("\n Exibindo 7\n");
            bool matriz_7[NUM_PIXELS] = {
                0, 1, 0, 0, 0,
                0, 0, 0, 1, 0,
                0, 1, 1, 0, 0,
                0, 0, 0, 1, 0,
                0, 1, 1, 1, 0
            };
            for (int i = 0; i < NUM_PIXELS; i++) {
                led_buffer[i] = matriz_7[i];
            }
            break;

        case 8:
            printf("\n Exibindo 8\n");
            bool matriz_8[NUM_PIXELS] = {
                0, 1, 1, 1, 0,
                0, 1, 0, 1, 0,
                0, 1, 1, 1, 0,
                0, 1, 0, 1, 0,
                0, 1, 1, 1, 0
            };
            for (int i = 0; i < NUM_PIXELS; i++) {
                led_buffer[i] = matriz_8[i];
            }
            break;

        case 9:
            printf("\n Exibindo 9\n");
            bool matriz_9[NUM_PIXELS] = {
                0, 1, 1, 1, 0,
                0, 0, 0, 1, 0,
                0, 1, 1, 1, 0,
                0, 1, 0, 1, 0,
                0, 1, 1, 1, 0
            };
            for (int i = 0; i < NUM_PIXELS; i++) {
                led_buffer[i] = matriz_9[i];
            }
            break;

        default:
            printf("\n Número não suportado!\n");
            break;
    }
}


// Função para transmitir o valor de cada pixel
static inline void put_pixel(uint32_t pixel_grb)
{
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

// Função para converter a cor em valor que pode ser enviado
static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
}

// Função para setar os LEDs com a cor desejada
void set_one_led(uint8_t r, uint8_t g, uint8_t b)
{
    // Define a cor com base nos parâmetros fornecidos
    uint32_t color = urgb_u32(r, g, b);
    
    // Define todos os LEDs com a cor especificada
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if (led_buffer[i])
        {
            put_pixel(color); // Liga o LED com um no buffer
        }
        else
        {
            put_pixel(0);  // Desliga os LEDs com zero no buffer
        }
    }
}

// Função de interrupção com debouncing
void gpio_irq_handler(uint gpio, uint32_t events)
{
    // Obtém o tempo atual em microssegundos
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    
    // Verifica se passou tempo suficiente desde o último evento
    if (current_time - last_time > 200000) // 20 ms de debouncing
    {
        last_time = current_time; // Atualiza o tempo do último evento

        if (gpio == botao_A) {
            // Lógica para o botão A (incrementar)
            if(cont >= 9){
                cont -= 9;
            }else{
                cont++;
            }
        
            
        } else if (gpio == botao_B) {
            // Lógica para o botão B (decrementar)
            if(cont <= 0){
                cont += 9;
            }else{
                cont--;
            }
            
        }

        led_update_flag = true; // Marca a flag para atualizar o led_buffer
    }
}

// Função principal
int main(){
    stdio_init_all();
    config_gpio();

    // Inicializar o pio para a comunicação com o WS2812
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, matriz_pin, 800000, IS_RGBW);

    gpio_set_irq_enabled_with_callback(botao_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled(botao_B, GPIO_IRQ_EDGE_FALL, true);
    
    while (1){
        gpio_put(led_red, 1);
        sleep_ms(tempo);
        gpio_put(led_red, 0);
        sleep_ms(tempo);
        if (led_update_flag) {
            show_number(led_buffer); // Atualiza os LEDs se necessário
            set_one_led(led_r, led_g, led_b); // Exibe a cor
            led_update_flag = false; // Limpa a flag após a atualização
        }
    }
}
