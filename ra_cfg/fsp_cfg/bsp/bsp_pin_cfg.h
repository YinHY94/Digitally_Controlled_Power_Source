/* generated configuration header file - do not edit */
#ifndef BSP_PIN_CFG_H_
#define BSP_PIN_CFG_H_
#include "r_ioport.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

#define oled_reset (BSP_IO_PORT_01_PIN_00)
#define oled_dc (BSP_IO_PORT_01_PIN_03)
#define oled_cs (BSP_IO_PORT_01_PIN_05)
#define KEY_X3 (BSP_IO_PORT_04_PIN_07)
#define KEY_Y3 (BSP_IO_PORT_04_PIN_08)
#define KEY_X2 (BSP_IO_PORT_04_PIN_09)
#define KEY_Y2 (BSP_IO_PORT_04_PIN_10)
#define KEY_X1 (BSP_IO_PORT_04_PIN_11)
#define KEY_Y1 (BSP_IO_PORT_04_PIN_12)
#define KEY_X0 (BSP_IO_PORT_04_PIN_13)
#define KEY_Y0 (BSP_IO_PORT_04_PIN_14)

extern const ioport_cfg_t g_bsp_pin_cfg; /* R7FA6M5BF3CFP.pincfg */

void BSP_PinConfigSecurityInit();

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER
#endif /* BSP_PIN_CFG_H_ */
