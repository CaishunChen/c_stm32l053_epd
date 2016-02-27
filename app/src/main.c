/******************************************************************************/
/** @file       main.c
 *******************************************************************************
 *
 *  @brief      Simple blinky application for stm32l053-discovery
 *
 *  @author     wht4
 *
 *  @remark     Last modifications
 *                 \li V1.0, May 2014, wht4, initial release
 *
 ******************************************************************************/
/*
 *  functions  global:
 *              .
 *  functions  local:
 *              .
 *
 ******************************************************************************/

/****** Header-Files **********************************************************/
#include "stm32l0xx.h"

#include "hw.h"
#include "led.h"
#include "systick.h"
#include "btn.h"

/****** Macros ****************************************************************/

/****** Data types ************************************************************/

/****** Function prototypes ****************************************************/
static void
BtnCallback (Btn_t tBtn, BtnHandlingCtx_t tBtnHandlingCtx);

/****** Data ******************************************************************/

/****** Implementation ********************************************************/

/*******************************************************************************
 *  function :    main
 ******************************************************************************/
int main(void) {

    hw_init();
    btn_registerCallback(BTN_1, BTN_HANDLING_CTX_ISR, BtnCallback);

    while (1) {

        led_set(LED_RED);
        systick_delayMs(1000);
        led_clear(LED_RED);
        systick_delayMs(1000);
    }

    return 0;
}


/*******************************************************************************
 *  function :    BtnCallback
 ******************************************************************************/
static void
BtnCallback (Btn_t tBtn, BtnHandlingCtx_t tBtnHandlingCtx) {

    (void) tBtn;
    (void) tBtnHandlingCtx;

    led_toogle(LED_GREEN);
}
