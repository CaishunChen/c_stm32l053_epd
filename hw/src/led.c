/******************************************************************************/
/** @file       led.c
 *******************************************************************************
 *
 *  @brief      Module for handling the attached user led
 *              <p>
 *              There are two user led's attached to the stm32l053:
 *              <ul>
 *                  <li> LED_GREEN: I/O PB4
 *                  <li> LED_RED: I/O PA5
 *              </ul>
 *
 *  @author     wht4
 *
 *  @remark     Last modifications
 *                 \li V1.0, February 2016, wht4, initial release
 *
 ******************************************************************************/
/*
 *  functions  global:
 *              led_init
 *              led_set
 *              led_clear
 *              led_toogle
 *  functions  local:
 *              .
 *
 ******************************************************************************/

/****** Header-Files **********************************************************/
#include "led.h"
#include "gpio.h"

/****** Macros ****************************************************************/

/****** Data types ************************************************************/
GPIO_TypeDef * tUserLedPort[LED_QUANTITY] = {
    GPIOB,
    GPIOA
};

uint32_t u32UserLedPin[LED_QUANTITY] = {
    4,
    5
};

/****** Function prototypes ****************************************************/

/****** Data ******************************************************************/

/****** Implementation ********************************************************/

/*******************************************************************************
 *  function :    led_init
 ******************************************************************************/
void
led_init(void) {

    GpioInit_t tGpioInit = {
        GPIO_MODE_OUTPUT,
        GPIO_OUTPUT_PUSH_PULL,
        GPIO_SPEED_MEDIUM,
        GPIO_PULL_NONE
    };

    /* Enable the peripheral clock of GPIOA and GPIOB */
    RCC->IOPENR |= RCC_IOPENR_GPIOAEN | RCC_IOPENR_GPIOBEN;

    /* Select output mode (01) on GPIOA pin 5 */
    gpio_init(GPIOA, 5, &tGpioInit);

    /* Select output mode (01) on GPIOB pin 4 */
    gpio_init(GPIOB, 4, &tGpioInit);
}


/*******************************************************************************
 *  function :    led_set
 ******************************************************************************/
void
led_set(Led_t tLed) {

    if (tLed < LED_QUANTITY) {
        gpio_set(tUserLedPort[tLed], u32UserLedPin[tLed]);
    }
}


/*******************************************************************************
 *  function :    led_clear
 ******************************************************************************/
void
led_clear(Led_t tLed) {

    if (tLed < LED_QUANTITY) {
        gpio_clear(tUserLedPort[tLed], u32UserLedPin[tLed]);
    }
}


/*******************************************************************************
 *  function :    led_toogle
 ******************************************************************************/
void
led_toogle(Led_t tLed) {

    if (tLed < LED_QUANTITY) {
        gpio_toogle(tUserLedPort[tLed], u32UserLedPin[tLed]);
    }
}
