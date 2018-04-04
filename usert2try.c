#include "stm32f1xx.h"
#include "stm32f103xb.h"

int main()
{
    RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;n
    RCC -> APB1ENR |= RCC_APB1ENR_USART2EN;
    GPIOA->CRL = (GPIOA->CRL | GPIO_CRL_MODE2_1) & ~GPIO_CRL_MODE2_0;
    GPIOA->CRL = (GPIOA->CRL | GPIO_CRL_CNF2_1) & ~GPIO_CRL_CNF2_0;
    USART2->CR1 |= USART_CR1_UE;
    USART2->CR1 |= USART_CR1_TE;
    USART2->BRR = 0x341;
    USART2->CR1 |= USART_CR1_RE;
    while (1) {
        if (USART2->SR & USART_SR_RXNE)
            USART2->DR = USART2->DR;
        for (volatile int i = 0; i < 500000; i++);
    }
    return 0;
}

