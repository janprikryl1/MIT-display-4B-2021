#include "stm8s.h"
#include "milis.h"
#include "stm8_hd44780.h"

/*#include "delay.h"*/
#include <stdio.h>
/*#include "../lib/uart.c"*/

#define _ISOC99_SOURCE
#define _GNU_SOURCE

#define LED_PORT GPIOC
#define LED_PIN  GPIO_PIN_5
#define LED_ON   GPIO_WriteHigh(LED_PORT, LED_PIN)
#define LED_OFF  GPIO_WriteLow(LED_PORT, LED_PIN)
#define LED_FLIP GPIO_WriteReverse(LED_PORT, LED_PIN)

#define BTN_PORT GPIOE
#define BTN_PIN  GPIO_PIN_4
#define BTN_PUSH (GPIO_ReadInputPin(BTN_PORT, BTN_PIN)==RESET) 


void init(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // taktovani MCU na 16MHz - stm má možnost nastavit různé clcoky - má 16 Mhz krystal, může to dělit různě, výchozí je dělení 8. Dáme 1, aby to bylo 16 MHz.
    GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_LOW_SLOW); //Inicializuje pin, port, módy: IN - PU - bude to ve vzduchu nebo tam bude pull up rezistor - open drain, nebo push pull - chceme ledku rožínat. Můžeme ještě vybrat fast slow.
    GPIO_Init(BTN_PORT, BTN_PIN, GPIO_MODE_IN_FL_NO_IT); // U tlačítka není potřeba, u lcd je to v lcd_init();
    
    
    
    init_milis();
}


int main(void)
{
    uint32_t time = 0;
    init();
    /*init_uart();*/

    uint16_t pocitadlo = 0;
    char text[16];

    lcd_init();
    lcd_gotoxy(0,0);
    lcd_puts("ahoj svete");

     

    while (1) {

        if (milis() - time > 333 && BTN_PUSH) {
            LED_FLIP;
            time = milis();

            


            lcd_gotoxy(0,1);
            sprintf(text, "Pocet: %d", pocitadlo++);
            lcd_puts(text);
          
        }

        /*LED_FLIP; */
        /*_delay_ms(333);*/
        /*printf("Funguje to!!!\n");*/
    }
}

/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
