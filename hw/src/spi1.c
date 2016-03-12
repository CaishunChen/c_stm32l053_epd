/******************************************************************************/
/** @file       spi1.c
 *******************************************************************************
 *
 *  @brief      Driver for stm32l053 spi1
 *
 *  @author     wht4
 *
 *  @remark     Last modifications
 *                 \li V1.0, February 2016, wht4, initial release
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
#include "spi1.h"

/****** Macros ****************************************************************/

/****** Data types ************************************************************/

/****** Function prototypes ****************************************************/
static void
spi1_initGpio(void);

/****** Data ******************************************************************/

/****** Implementation ********************************************************/

/*******************************************************************************
 *  function :    spi1_init
 ******************************************************************************/
void
spi1_init(void) {

    spi1_initGpio();

    /* Enable the peripheral clock SPI1 */
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    /* SPI_CR1_SSI --> Software controls slave management*/
    /* SPI_CR1_BR_1 --> Prescaler fPCLK /8 */
    /* SPI_CR1_MSTR --> Master mode */
    /* SPI_CR1_CPOL --> Clock is high when idle */
    SPI1->CR1 |= SPI_CR1_SSI | SPI_CR1_BR_1 | SPI_CR1_MSTR | SPI_CR1_CPOL;

    /* Nothing to do for CR2 register */
    /* SPI1->CR2 |=; */

    /* Enable spi1 */
    SPI1->CR1 |= SPI_CR1_SPE;
}


/*******************************************************************************
 *  function :    spi1_readByte
 ******************************************************************************/
uint8_t
spi1_readByte(pfSpiCSHandler pfCSHandler) {

    uint8_t u8Data = 0x00;

    pfCSHandler(GPIO_STATE_CLEAR);

    /* wait for last transfer to complete */
    while((SPI1->SR && SPI_SR_BSY) != 0) {

    }

    /* Wait till transmit buffer is empty */
    while((SPI1->SR && SPI_SR_TXE) == 0) {

    }

    SPI1->DR = (uint16_t) 0xff;

    /* Wait till we have received the byte */
    while((SPI1->SR && SPI_SR_RXNE) == 0) {

    }

    u8Data = (uint8_t) SPI1->DR;

    pfCSHandler(GPIO_STATE_SET);

    return (u8Data);
}


/*******************************************************************************
 *  function :    spi1_writeByte
 ******************************************************************************/
void
spi1_writeByte(uint8_t u8Data, pfSpiCSHandler pfCSHandler) {

    (void) u8Data;
    pfCSHandler(GPIO_STATE_CLEAR);

    /* wait for last transfer to complete */
    while((SPI1->SR && SPI_SR_BSY) != 0) {

    }

    /* Wait till transmit buffer is empty */
    while((SPI1->SR && SPI_SR_TXE) == 0) {

    }

    SPI1->DR = (uint16_t) u8Data;

    pfCSHandler(GPIO_STATE_SET);
}


/*******************************************************************************
 *  function :    spi1_initGpio
 ******************************************************************************/
/** @brief        Initializes the required gpio's for spi1 communication
 *                <p>
 *                <ui>
 *                    <li> GPIO B3 --> SPI SCK
 *                    <li> GPIO B4 --> SPI MISO
 *                    <li> GPIO B5 --> SPIO MOSI
 *                </ui>
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
spi1_initGpio(void) {

    /* Enable the peripheral clock of GPIOB */
    RCC->IOPENR |= RCC_IOPENR_GPIOBEN;

    GpioInit_t tGpioInit = {
        GPIO_MODE_ALTERNATE,
        GPIO_OUTPUT_PUSH_PULL,
        GPIO_SPEED_HIGH,
        GPIO_PULL_UP
    };

    /* Configure the SPI SCK on GPIO B3 */
    gpio_init(GPIOB, 3, &tGpioInit);
    gpio_setAF(GPIOB, 3, GPIO_AF_0);


    /* Configure the SPI MISO on GPIO B4 */
    tGpioInit.tGpioPull = GPIO_PULL_DOWN;
    gpio_init(GPIOB, 4, &tGpioInit);
    gpio_setAF(GPIOB, 4, GPIO_AF_0);

    /* Configure the SPI MOSI on GPIO B5 */
    gpio_init(GPIOB, 5, &tGpioInit);
    gpio_setAF(GPIOB, 5, GPIO_AF_0);
}
