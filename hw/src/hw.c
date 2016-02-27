/******************************************************************************/
/** @file       hw.c
 *******************************************************************************
 *
 *  @brief      Module for initializing the attached hw
 *
 *  @author     wht4
 *
 *  @remark     Last modifications
 *                 \li V1.0, February 2016, wht4, initial release
 *
 ******************************************************************************/
/*
 *  functions  global:
 *              hw_init
 *  functions  local:
 *              hw_initSysclock
 *
 ******************************************************************************/

/****** Header-Files **********************************************************/
#include "stm32l0xx.h"

#include "config.h"
#include "led.h"
#include "systick.h"
#include "btn.h"

/****** Macros ****************************************************************/

/****** Data types ************************************************************/

/****** Function prototypes ****************************************************/
static void
hw_initSysclock(void);

/****** Data ******************************************************************/

/****** Implementation ********************************************************/

/*******************************************************************************
 *  function :    hw_init
 ******************************************************************************/
void
hw_init(void) {

	#if CONFIG_SYSCLOCK == CONFIG_SYSCLOCK_16MHZ
		hw_initSysclock();
	#endif
	systick_init(CONFIG_SYSTICK_1MS);


    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    led_init();
    btn_init();
}


/*******************************************************************************
 *  function :    hw_initSysclock
 ******************************************************************************/
/** @brief        This function configures the system clock @16MHz and voltage
 *                scale 1 assuming the registers have their reset value before
 *                the call.
 *                <p>
 *                POWER SCALE   = RANGE 1
 *                SYSTEM CLOCK  = PLL MUL8 DIV2
 *                PLL SOURCE    = HSI/4
 *                FLASH LATENCY = 0
 *
 *  @copyright    Licensed under MCD-ST Liberty SW License Agreement V2,
 *                (the "License");
 *                You may not use this file except in compliance with the
 *                License. You may obtain a copy of the License at:
 *                http://www.st.com/software_license_agreement_liberty_v2
 *
 *  @type         global
 *
 *  @param[in]    in
 *  @param[out]   out
 *
 *  @return       void
 *
 ******************************************************************************/
static void
hw_initSysclock(void) {

	/* Enable power interface clock */
	RCC->APB1ENR |= (RCC_APB1ENR_PWREN);

	/* Select voltage scale 1 (1.65V - 1.95V) i.e. (01) */
	/* for VOS bits in PWR_CR */
	PWR->CR = (PWR->CR & ~(PWR_CR_VOS)) | PWR_CR_VOS_0;

	/* Enable HSI divided by 4 in RCC-> CR */
	RCC->CR |= RCC_CR_HSION | RCC_CR_HSIDIVEN;

	/* Wait for HSI ready flag and HSIDIV flag */
	while ((RCC->CR & (RCC_CR_HSIRDY |RCC_CR_HSIDIVF)) !=
			(RCC_CR_HSIRDY |RCC_CR_HSIDIVF)) {

	}

	/* Set PLL on HSI, multiply by 8 and divided by 2 */
	RCC->CFGR |= RCC_CFGR_PLLSRC_HSI | RCC_CFGR_PLLMUL8 | RCC_CFGR_PLLDIV2;

	/* Enable the PLL in RCC_CR register */
	RCC->CR |= RCC_CR_PLLON;

	/* Wait for PLL ready flag */
	while ((RCC->CR & RCC_CR_PLLRDY)  == 0) {

	}

	/* Select PLL as system clock */
	RCC->CFGR |= RCC_CFGR_SW_PLL;

	/*  Wait for clock switched on PLL */
	while ((RCC->CFGR & RCC_CFGR_SWS_PLL)  == 0) {

	}
}

