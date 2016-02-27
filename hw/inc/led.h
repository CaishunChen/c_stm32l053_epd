#ifndef LED_H_
#define LED_H_
/******************************************************************************/
/** \file       led.h
 *******************************************************************************
 *
 *  \brief      Module for handling the attached user led
 *              <p>
 *              There are two user led's attached to the stm32l053:
 *              <ul>
 *                  <li> LED_GREEN: I/O PB4
 *                  <li> LED_RED: I/O PA5
 *              </ul>
 *
 *  \author     wht4
 *
 ******************************************************************************/
/*
 *  function    led_init
 *              led_set
 *              led_clear
 *              led_toogle
 *
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/****** Header-Files **********************************************************/
#include "stm32l0xx.h"

/****** Macros ****************************************************************/

/****** Data types ************************************************************/
typedef enum _Led_t {

    LED_GREEN    = 0,
    LED_RED      = 1,
    LED_QUANTITY = 2

}
Led_t;

/****** Function prototypes ****************************************************/
extern void
led_init(void);

extern void
led_set(Led_t tLed);

extern void
led_clear(Led_t tLed);

extern void
led_toogle(Led_t tLed);

/****** Data ******************************************************************/

/****** Implementation ********************************************************/


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LED_H_ */
