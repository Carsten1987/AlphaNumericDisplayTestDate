/*
MIT License

Copyright (c) 2020 Carsten1987

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "bsp.h"
#include "device_config.h"
#include "segment_display.h"

#define PIN_DATE RB3

static char buffer[40] = { 0 };
static volatile uint8_t in = 0;
static volatile uint8_t out = 0;

static uint8_t date_segment = 0;
static uint8_t spi_buffer[11] = { 0 };
static uint8_t out_pos = 0;

void __interrupt() isr()
{
  if(TXIF && TXIE)
  { // tx buffer empty. Next char can be send
    TXREG = buffer[out++];
    if(out == sizeof(buffer))
    {
      out = 0;
    }
    if(out == in)
    {
      TXIE = 0;
    }
  }
}

void main(void)
{
  init();
  strcpy(buffer, "Initialization successfully done\n");
  in = (uint8_t)strlen(buffer);
  TXREG = buffer[out++];
  TXIE = 1;

  while(1)
  {

    if(SSPIF) // wait until transmission completed
    {
      WCOL = 0;
      SSPIF = 0;
      if(out_pos == 6)
      {
        PIN_DATE = 0;
      }
      else if(out_pos == 8)
      {
        PIN_DATE = 1;
      }

      SSPBUF = spi_buffer[out_pos++];
      if(out_pos == sizeof(spi_buffer))
      {
        out_pos = 0;
      }
      /*
        6-7  = Datum
      */
      if(out_pos == 8)
      {
        spi_buffer[6] = (uint8_t)(1 << date_segment);
        spi_buffer[7] = get_date_data(date_segment++);
        if(date_segment == 8)
        {
          date_segment = 0;
        }
      }
    }
  }
}
