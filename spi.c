#include "stm32f1xx.h"
#include "stm32f103xb.h"

void spi_init();
void spi_send_byte(char byte);
void led(int x, int y);
void draw_column(int x);
void draw_line(int y);

int main()
{
    spi_init();
    SysTick_Config(0xF);
    while (1) {

    }
    return 0;
}

void SysTick_Handler(void) {
    led(0, 3);
    led(1, 2);
    draw_column(2);
    draw_line(2);
}

void spi_init() {
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN);
    SET_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI2EN);
    MODIFY_REG(GPIOA->CRH, GPIO_CRH_MODE9 | GPIO_CRH_CNF9, GPIO_CRH_MODE9_1);
    MODIFY_REG(GPIOB->CRH, GPIO_CRH_MODE15 | GPIO_CRH_CNF15, GPIO_CRH_CNF15_1 | GPIO_CRH_MODE15_1);//ds(mosi)
    MODIFY_REG(GPIOB->CRH, GPIO_CRH_MODE13 | GPIO_CRH_CNF13, GPIO_CRH_CNF13_1 | GPIO_CRH_MODE13_1);//sh(sck)
    SET_BIT(SPI2->CR1, SPI_CR1_MSTR);
    SET_BIT(SPI1->CR2, SPI_CR2_SSOE);
    SET_BIT(SPI2->CR1, SPI_CR1_SPE);
    //SET_BIT(SPI2->CR1, SPI_CR1_DFF);
    SET_BIT(SPI2->CR1, SPI_CR1_LSBFIRST);
}

void spi_send_byte(char byte) {
    GPIOA->ODR &= ~GPIO_ODR_ODR9;
    MODIFY_REG(SPI2->DR, 0b11111111, byte);
    while (!(SPI2->SR & SPI_SR_TXE));
    GPIOA->ODR |= GPIO_ODR_ODR9;

}

void led(int x, int y) {
    char byte = 0;
    byte += 1 << (3 - x);
    byte += 0b11110000;
    byte -= 1 << (7 - y);
    spi_send_byte(byte);
}

void draw_column(int x) {
    char byte = 0b11110000;
    byte += 1 << (3 - x);
    for (int i = 0; i<4; i++){
        spi_send_byte(byte - (1 << (7 - i)));
    }
}

void draw_line(int y) {
    char byte = 0b11111111;
    byte -= 1 << (7 - y);
    for (int i = 0; i<4; i++){
        spi_send_byte(byte - (1 << (3 - i)));
    }
}
