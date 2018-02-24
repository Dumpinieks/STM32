#include "stm32f1xx.h"
#include "stm32f103xb.h"

int main()
{
    RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC -> APB2ENR |= RCC_APB2ENR_IOPCEN;
    RCC -> APB2ENR |= RCC_APB2ENR_AFIOEN;
    GPIOA -> CRL = (GPIOA -> CRL | GPIO_CRL_MODE5_1) & ~GPIO_CRL_MODE5_0;
    GPIOA -> ODR |= GPIO_ODR_ODR5;
    GPIOA -> CRL = (GPIOA -> CRL | GPIO_CRL_MODE6_1) & ~GPIO_CRL_MODE6_0;
    GPIOA -> ODR |= GPIO_ODR_ODR6;
    GPIOA -> CRL = (GPIOA -> CRL | GPIO_CRL_MODE7_1) & ~GPIO_CRL_MODE7_0;
    GPIOA -> ODR |= GPIO_ODR_ODR7;
    GPIOC -> CRH = (GPIOC -> CRH | GPIO_CRH_MODE13_1) & ~GPIO_CRH_MODE13_0;
    GPIOC -> ODR ^= GPIO_ODR_ODR13;
    AFIO -> EXTICR[1] |= AFIO_EXTICR2_EXTI5_PA;
    EXTI -> IMR |= EXTI_IMR_MR5;
    EXTI -> FTSR |= EXTI_FTSR_TR5;
    NVIC_EnableIRQ(EXTI9_5_IRQn);
    while (1);
    return 0;
}

void EXTI9_5_IRQHandler(void) {
    for (volatile int i = 0; i < 6000; i++);
    if (GPIOA -> IDR & GPIO_IDR_IDR6) {
        GPIOC -> ODR &= ~GPIO_ODR_ODR13;
    } else {
        GPIOC -> ODR ^= GPIO_ODR_ODR13;
    }
    EXTI->PR |= EXTI_PR_PR5;
}
