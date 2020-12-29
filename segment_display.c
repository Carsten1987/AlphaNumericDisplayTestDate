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

#include <stdio.h>
#include "segment_display.h"

/* 
 *  AAA
 * F   B
 * F   B
 *  GGG
 * E   C
 * E   C
 *  DDD
 * 
 * Bit 0: A
 * Bit 1: B
 * Bit 2: C
 * Bit 3: D
 * Bit 4: E
 * Bit 5: F
 * Bit 6: G
 * Bit 7: DP
 */

static const uint8_t date_segment_coding[] =
{
  /*0*/63, /*1*/6, /*2*/91, /*3*/79,/*4*/102,
  /*5*/109, /*6*/125, /*7*/7, /*8*/127, /*9*/111
};

uint8_t get_date_data(uint8_t date_segment)
{
  return date_segment_coding[8 - date_segment];
}
