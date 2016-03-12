/******************************************************************************/
/** @file       btn.c
 *******************************************************************************
 *
 *  @brief      Module for handling user push buttons.
 *              <p>
 *              Each push button is initialized to generate a interrupt on
 *              rising edge. There is currently one user push button attached
 *              to the stm32l053:
 *              <ul>
 *                  <li> BTN_1: I/O PA0
 *              </ul>
 *              <p>
 *              The user can register a callback fct for handling the button
 *              either in isr context or background context.
 *
 *  @author     wht4
 *
 *  @remark     Last modifications
 *                 \li V1.0, February 2016, wht4, initial release
 *
 ******************************************************************************/
/*
 *  functions  global:
 *              btn_init
 *              btn_registerCallback
 *              btn_isPressed
 *              btn_isr
 *  functions  local:
 *              .
 *
 ******************************************************************************/

/****** Header-Files **********************************************************/
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "stm32l0xx.h"

#include "config.h"
#include "btn.h"
#include "gpio.h"

/****** Macros ****************************************************************/

/****** Data types ************************************************************/

/****** Function prototypes ****************************************************/

/****** Data ******************************************************************/
static pfBtnHandlingFct pfHandlingFct[BTN_QUANTITY] = {
    NULL
};

static volatile bool bIsrFlag[BTN_QUANTITY] = {
    false
};

static BtnHandlingCtx_t tHandlingCtx[BTN_QUANTITY] = {
    BTN_HANDLING_CTX_INVALID
};

/****** Implementation ********************************************************/

/*******************************************************************************
 *  function :    btn_init
 ******************************************************************************/
void
btn_init(void) {

    GpioInit_t tGpioInit = {
        GPIO_MODE_INPUT,
        GPIO_OUTPUT_PUSH_PULL,
        GPIO_SPEED_MEDIUM,
        GPIO_PULL_NONE
    };

    /* Enable the peripheral clock of GPIOA */
    RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

    /* configure GPIOA pin 0 as btn */
    gpio_init(GPIOA, 0, &tGpioInit);

    /* Line 0 is not masked */
    EXTI->IMR |= EXTI_IMR_IM0;

    /* Set interrupt for rising edge */
    EXTI->RTSR |= EXTI_RTSR_TR0;

    /* Enable interrupt for EXTI Line 0 and 1 */
    NVIC_EnableIRQ(EXTI0_1_IRQn);

    NVIC_SetPriority(EXTI0_1_IRQn, CONFIG_BTN_ISR_PRIO);
}


/*******************************************************************************
 *  function :    btn_registerCallback
 ******************************************************************************/
void
btn_registerCallback(Btn_t tBtn,
                     BtnHandlingCtx_t tBtnHandlingCtx,
                     pfBtnHandlingFct pfCallback) {

    assert(pfCallback != NULL);
    assert(tBtnHandlingCtx < BTN_HANDLING_CTX_INVALID);
    assert(tBtn < BTN_QUANTITY);

    tHandlingCtx[tBtn] = tBtnHandlingCtx;
    pfHandlingFct[tBtn] = pfCallback;
}

/*******************************************************************************
 *  function :    btn_isPressed
 ******************************************************************************/
void
btn_isPressed(Btn_t tBtn) {

    assert(tBtn < BTN_QUANTITY);

    if ((bIsrFlag[tBtn] == true) &&
            (tHandlingCtx[tBtn] == BTN_HANDLING_CTX_BACKGROUND) &&
            (pfHandlingFct[tBtn] != NULL)) {

        pfHandlingFct[tBtn](tBtn, tHandlingCtx[tBtn]);
        bIsrFlag[tBtn] = false;
    }
}

/*******************************************************************************
 *  function :    btn_isr
 ******************************************************************************/
void
btn_isr(Btn_t tBtn) {

    if ((tHandlingCtx[tBtn] == BTN_HANDLING_CTX_ISR) &&
            (pfHandlingFct[tBtn] != NULL)) {

        pfHandlingFct[tBtn](tBtn, tHandlingCtx[tBtn]);

    } else if(tHandlingCtx[tBtn] == BTN_HANDLING_CTX_BACKGROUND) {

        bIsrFlag[tBtn] = true;
    }
}

