#include "stm32f1xx.h"
#include "stm32f103xb.h"
#include <stdlib.h>

int main()
{
    RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC -> APB2ENR |= RCC_APB2ENR_IOPBEN;
    GPIOB -> CRL = (GPIOB -> CRL | GPIO_CRL_MODE0_1) & ~GPIO_CRL_MODE0_0;
    GPIOB -> CRL = (GPIOB->CRL | GPIO_CRL_CNF0_1) & ~GPIO_CRL_CNF0_0;
    GPIOA -> CRL = (GPIOA -> CRL | GPIO_CRL_MODE6_1) & ~GPIO_CRL_MODE6_0;
    GPIOA -> CRL = (GPIOA->CRL | GPIO_CRL_CNF6_1) & ~GPIO_CRL_CNF6_0;
    GPIOA -> CRL = (GPIOA -> CRL | GPIO_CRL_MODE7_1) & ~GPIO_CRL_MODE7_0;
    GPIOA -> CRL = (GPIOA->CRL | GPIO_CRL_CNF7_1) & ~GPIO_CRL_CNF7_0;
    TIM3->ARR = 99;
    TIM3->CCMR2 &= ~TIM_CCMR2_CC3S;
    TIM3->CCMR1 &= ~TIM_CCMR1_CC2S;
    TIM3->CCMR2 &= ~TIM_CCMR1_CC1S;
    TIM3->CCMR2 |= 0x6 << TIM_CCMR2_OC3M_Pos;
    TIM3->CCMR1 |= 0x6 << TIM_CCMR1_OC2M_Pos;
    TIM3->CCMR1 |= 0x6 << TIM_CCMR1_OC1M_Pos;
    TIM3->CCMR2 |= TIM_CCMR2_OC3PE;
    TIM3->CCMR1 |= TIM_CCMR1_OC2PE;
    TIM3->CCMR1 |= TIM_CCMR1_OC1PE;
    TIM3->CR1 |= TIM_CR1_ARPE;
    TIM3->EGR |= TIM_EGR_UG;
    TIM3->CR1 |= TIM_CR1_CEN;
    TIM3->CCER |= TIM_CCER_CC3E;
    TIM3->CCER |= TIM_CCER_CC2E;
    TIM3->CCER |= TIM_CCER_CC1E;
    while (1) {
        for (volatile int i = 0; i < 100000; i++);
        TIM3->CCR3 = rand() % 100;
        TIM3->CCR2 = rand() % 10;
        TIM3->CCR1 = rand() % 10;
    }
    return 0;
}
