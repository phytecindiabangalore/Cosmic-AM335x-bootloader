/*
 * File:         arch/blackfin/lib/ashldi3.c
 * Based on:
 * Author:
 *
 * Created:
 * Description:
 *
 * Rev:          $Id: ashldi3.c 2775 2007-02-21 13:58:44Z hennerich $
 *
 * Modified:
 *               Copyright 2004-2006 Analog Devices Inc.
 *
 * Bugs:         Enter bugs at http://blackfin.uclinux.org/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "gcclib.h"

#ifdef CONFIG_ARITHMETIC_OPS_L1
DItype __ashldi3(DItype u, word_type b)__attribute__((l1_text));
#endif

DItype __ashldi3(DItype u, word_type b)
{
	DIunion w;
	word_type bm;
	DIunion uu;

	if (b == 0)
		return u;

	uu.ll = u;

	bm = (sizeof(SItype) * BITS_PER_UNIT) - b;
	if (bm <= 0) {
		w.s.low = 0;
		w.s.high = (USItype) uu.s.low << -bm;
	} else {
		USItype carries = (USItype) uu.s.low >> bm;
		w.s.low = (USItype) uu.s.low << b;
		w.s.high = ((USItype) uu.s.high << b) | carries;
	}

	return w.ll;
}
