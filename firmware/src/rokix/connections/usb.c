/*
The MIT License (MIT)
Copyright (c) 2020 Rohm Semiconductor

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#include "usb.h"
#include "usb_uart.h"
#include "usb_serial.h"


void usb_init(void)
{
#if defined(BOARD_PCA10040)
    usb_uart_init();
#elif defined(BOARD_PCA10056) || defined(K2_BOARD_CUSTOM)
    usb_serial_init();
#else
#error "unsupported board"
#endif
}

void usb_tx(uint8_t *data, uint16_t size)
{
#if defined(BOARD_PCA10040)
    usb_uart_tx(data, size);
#elif defined(BOARD_PCA10056) || defined(K2_BOARD_CUSTOM)
    usb_serial_tx(data, size);
#else
#error "unsupported board"
#endif
}


bool usb_process_queue(void)
{
#if defined(BOARD_PCA10040)
    // The nRF52832 uses UART, which doesn't have its own event queue.
    return false;
#elif defined(BOARD_PCA10056) || defined(K2_BOARD_CUSTOM)
    return usb_serial_process_queue();
#else
#error "unsupported board"
#endif
}
