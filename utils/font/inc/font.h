#ifndef FONT_H_
#define FONT_H_
/******************************************************************************/
/** \file       font.h
 *******************************************************************************
 *
 *  \brief      Fonts for writing to the epd display
 *
 *  \author     wht4
 *
 ******************************************************************************/
/*
 *  function    .
 *
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/****** Header-Files **********************************************************/
#include <stdint.h>

/****** Macros ****************************************************************/

/****** Data types ************************************************************/
typedef struct _Font_t {

    const uint8_t* pu8Table;
    uint16_t       u16Width;
    uint16_t       u16Height;

} Font_t;

extern Font_t tFont8;
extern Font_t tFont12;
extern Font_t tFont16;
extern Font_t tFont20;

/****** Function prototypes ****************************************************/

/****** Data ******************************************************************/

/****** Implementation ********************************************************/

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* FONT_H_ */
