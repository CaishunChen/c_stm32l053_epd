#ifndef SYSTICK_H_
#define SYSTICK_H_
/******************************************************************************/
/** \file       systick.h
 *******************************************************************************
 *
 *  \brief      General systick module for stm32l0
 *              <p>
 *              Allows to generate delays in busy loop
 *
 *  \author     wht4
 *
 ******************************************************************************/
/*
 *  function    systick_init
 *              systick_delayMs
 *              systick_getTick
 *              systick_irq
 *
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/****** Header-Files **********************************************************/
#include <stdint.h>

/****** Macros ****************************************************************/

/****** Data types ************************************************************/

/****** Function prototypes ****************************************************/
extern void
systick_init(uint32_t u32Ticks);

extern void
systick_delayMs(uint32_t u32DelayMs);

extern uint32_t
systick_getTick(void);

extern void
systick_irq(void);

/****** Data ******************************************************************/

/****** Implementation ********************************************************/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SYSTICK_H_ */
