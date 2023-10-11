#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "system.h"
#include "io.h"
#include "display.h"
#include "lcd.h"
#include "arm32.h"
#include "f1c100s_gpio.h"
#include "f1c100s_timer.h"
#include "f1c100s_intc.h"

volatile uint8_t tick_flag = 0;

void timer_irq_handler(void) {
    tim_clear_irq(TIM0);
    tick_flag = 1;
}

void timer_init(void) {
    // Configure timer to generate update event every 1ms
    tim_init(TIM0, TIM_MODE_CONT, TIM_SRC_HOSC, TIM_PSC_1);
    tim_set_period(TIM0, 24000000UL / 1000UL);
    tim_int_enable(TIM0);
    // IRQ configuration
    intc_set_irq_handler(IRQ_TIMER0, timer_irq_handler);
    intc_enable_irq(IRQ_TIMER0);

    tim_start(TIM0);
}


void delay(uint32_t t) {
    while(1) {
        if(t == 0) return;
        if(tick_flag == 1) {
            tick_flag = 0;
            t--;
        }
    }
}

int main(void) {
    system_init(); // Initialize clocks, mmu, cache, uart, ...
    arm32_interrupt_enable(); // Enable interrupts
    timer_init();
    printf("Hello from firmware!\r\n");

    gpio_pin_init(GPIOE, 5, GPIO_MODE_OUTPUT, GPIO_PULL_NONE, GPIO_DRV_3);
    gpio_pin_set(GPIOE, 5);
    delay(120);
    gpio_pin_clear(GPIOE, 5);
    delay(50);
    gpio_pin_set(GPIOE, 5);

    display_init();
    display_set_bl(255);
    lcd_init(0);

    lcd_printf("Hello, world!");

    lcd_fill(50, 40, 100, 100, COLOR_RED);
    lcd_fill(50, 140, 100, 100, COLOR_GREEN);
    lcd_fill(50, 240, 100, 100, COLOR_BLUE);
    lcd_fill(50, 340, 100, 100, COLOR_WHITE);

    lcd_fill(196, 46, 160, 58, COLOR_BLUE);
    lcd_set_bg_color(COLOR_BLUE);
    lcd_set_text_color(COLOR_WHITE);
    lcd_set_text_pos(200, 50);

    lcd_set_font(&clock_digits);
    lcd_printf("%02d", 12);

    lcd_set_font(&clock_dots);
    //    if (time.sec%2)
    lcd_putchar(1);
    //    else
    //        lcd_putchar(0);

    lcd_set_font(&clock_digits);
    lcd_printf("%02d", 34);

    lcd_set_font(&t_12x24_full);
    lcd_set_bg_color(COLOR_BLACK);
    lcd_set_text_color(COLOR_WHITE);
    lcd_set_text_pos(200, 200);
    for(uint16_t ch = 0; ch <= 0xFF; ch++) {
        lcd_putchar(ch & 0xFF);
        if(ch % 32 == 0) lcd_putchar('\n');
    }

    printf("try ~~!\r\n");
    while (1)
    {
        delay(220);
        /* code */
    }
    
    return 0;
}
