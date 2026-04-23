#include "spi_hal.h"
#include "r_spi.h"
#include <assert.h>

void spi_init(spi_ctrl_t *p_ctrl, spi_cfg_t const *p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_SPI_Open(p_ctrl, p_cfg);
    assert(FSP_SUCCESS == err);
}

void spi_write(spi_ctrl_t *p_ctrl, const uint8_t *data, const size_t size)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_SPI_Write(p_ctrl, data, size, SPI_BIT_WIDTH_8_BITS);
    assert(FSP_SUCCESS == err);
}
