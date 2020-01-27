/**
 * Copyright (c) 2014 - 2018, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include "usb_uart.h"

#include "nrf.h"
#include "nrf_serial.h"
#include "nrf_log.h"
#include "bsp.h"

#define TX_QUEUE_SIZE 256
#define RX_QUEUE_SIZE 32
#define LOG_TX_DATA 0

NRF_SERIAL_DRV_UART_CONFIG_DEF(m_uart0_drv_config,
                      RX_PIN_NUMBER, TX_PIN_NUMBER,
                      RTS_PIN_NUMBER, CTS_PIN_NUMBER,
                      NRF_UART_HWFC_ENABLED, NRF_UART_PARITY_EXCLUDED,
                      NRF_UART_BAUDRATE_1000000,
                      UART_DEFAULT_CONFIG_IRQ_PRIORITY);
NRF_SERIAL_UART_DEF(m_serial_uart, 0);

NRF_SERIAL_QUEUES_DEF(m_serial_queues, TX_QUEUE_SIZE, RX_QUEUE_SIZE);
NRF_SERIAL_BUFFERS_DEF(m_serial_bufs, 1, 1);
NRF_SERIAL_CONFIG_DEF(m_serial_config, NRF_SERIAL_MODE_DMA,
                      &m_serial_queues, &m_serial_bufs, NULL, NULL);

void usb_uart_init(void)
{
    ret_code_t ret = nrf_serial_init(&m_serial_uart, &m_uart0_drv_config,
                                     &m_serial_config);
    APP_ERROR_CHECK(ret);
}

void usb_uart_tx(uint8_t *data, uint16_t size)
{
    if (LOG_TX_DATA) {
        NRF_LOG_INFO("%s: writing %u bytes", __func__, size);
        NRF_LOG_HEXDUMP_INFO(data, size);
    }

    ret_code_t ret = nrf_serial_write(&m_serial_uart, data, size, NULL, 0);
    if (ret == NRF_ERROR_TIMEOUT) {
        NRF_LOG_WARNING("serial write timed out; discarding the write");
    } else if (ret != NRF_SUCCESS) {
        APP_ERROR_HANDLER(ret);
    }
}
