#include "stm32f1xx.h"
#include "stm32f103xb.h"

int main()
{
    RCC -> APB2ENR |= RCC_APB2ENR_IOPCEN;
    RCC -> APB2ENR |= RCC_APB2ENR_IOPBEN;
    GPIOC -> CRH |= GPIO_CRH_MODE13_1;
    GPIOB -> CRL = (GPIOB -> CRL | GPIO_CRL_MODE1_1) & ~GPIO_CRL_MODE1_0;
    GPIOB -> CRL &= ~GPIO_CRL_CNF1;

    while(1) {
        if (GPIOB -> IDR & GPIO_IDR_IDR1)
            GPIOC -> ODR |= GPIO_ODR_ODR13;
        else
            GPIOC -> ODR &= ~GPIO_ODR_ODR13;
    }
    return 0;
}
