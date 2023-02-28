/*
 * Copyright (C) Guangzhou FriendlyELEC Computer Tech. Co., Ltd.
 * (http://www.friendlyelec.com)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you can access it online at
 * http://www.gnu.org/licenses/gpl-2.0.html.
 */

#include <config.h>
#include <common.h>
#include <adc.h>
#include <asm/io.h>
#include <asm/gpio.h>

/*
 * ID info:
 *  ID : Volts : ADC value :   Bucket
 *  ==   =====   =========   ===========
 *   0 : 0.102V:        58 :    0 -   81
 *   1 : 0.211V:       120 :   82 -  150
 *   2 : 0.319V:       181 :  151 -  211
 *   3 : 0.427V:       242 :  212 -  274
 *   4 : 0.542V:       307 :  275 -  342
 *   5 : 0.666V:       378 :  343 -  411
 *   6 : 0.781V:       444 :  412 -  477
 *   7 : 0.900V:       511 :  478 -  545
 *   8 : 1.023V:       581 :  546 -  613
 *   9 : 1.137V:       646 :  614 -  675
 *  10 : 1.240V:       704 :  676 -  733
 *  11 : 1.343V:       763 :  734 -  795
 *  12 : 1.457V:       828 :  796 -  861
 *  13 : 1.576V:       895 :  862 -  925
 *  14 : 1.684V:       956 :  926 -  989
 *  15 : 1.800V:      1023 :  990 - 1023
 */
static const int id_readings[] = {
	 81, 150, 211, 274, 342, 411, 477, 545,
	613, 675, 733, 795, 861, 925, 989, 1023
};

static int cached_board_id = -1;

static uint32_t get_adc_index(int chn)
{
	int i;
	u32 adc_reading = 0;

	if (cached_board_id != -1)
		return cached_board_id;

	adc_channel_single_shot("saradc", chn, &adc_reading);

	/* rockchip-saradc-v2 */
	adc_reading >>= 2;

	for (i = 0; i < ARRAY_SIZE(id_readings); i++) {
		if (adc_reading <= id_readings[i]) {
			debug("ADC reading %d, ID %d\n", adc_reading, i);
			cached_board_id = i;
			return i;
		}
	}

	/* should die for impossible value */
	return 0;
}

/*
 * Board revision by ADC_IN5
 *  0b01 - NanoPi-R6S
 */
static int pcb_rev = -1;

void bd_hwrev_init(void)
{
	if (pcb_rev >= 0)
		return;

	pcb_rev = get_adc_index(5);
}

/* To override __weak symbols */
u32 get_board_rev(void)
{
	return pcb_rev;
}

const char *get_board_name(void)
{
	bd_hwrev_init();

	switch (pcb_rev) {
		case 0x01:
			return "NanoPi R6S";
		default:
			return "FriendlyELEC RK3588 board";
	}
}

