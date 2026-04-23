#pragma once

#include "r_spi_api.h"


void spi_init(spi_ctrl_t *p_ctrl, spi_cfg_t const *p_cfg);
void spi_write(spi_ctrl_t *p_ctrl, const uint8_t *data, size_t size);


