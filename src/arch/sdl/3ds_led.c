/*
 * 3ds_led.c - Notification LED control functions for Nintendo 3DS
 *
 * Written by
 *  Sebastian Weber <me@badda.de>
 *
 * This file is part of VICE, the Versatile Commodore Emulator.
 * See README for copyright notice.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307  USA.
 *
 */

#include <3ds.h>
#include <string.h>

#include "3ds_led.h"

static Handle ptmsysmHandle = 0;
static unsigned char ledpattern[100] =
"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";

static int LED3DS_Init() {
	if (ptmsysmHandle == 0) {
		srvInit();
		Result res = srvGetServiceHandle(&ptmsysmHandle, "ptm:sysm");
		srvExit();
		if (res < 0) return -1;
	}
	return 0;
}

int LED3DS_On(unsigned char r, unsigned char g, unsigned char b) {
	int i;
	for (i=0;i<4;++i) ledpattern[i]=0;
	for (i=4;i<36;++i) ledpattern[i]=r;
	for (i=36;i<68;++i) ledpattern[i]=g;
	for (i=68;i<100;++i) ledpattern[i]=b;

	if (LED3DS_Init() < 0) return -1;

	u32* ipc = getThreadCommandBuffer();
    ipc[0] = 0x8010640;
    memcpy(&ipc[1], ledpattern, 0x64);
    Result ret = svcSendSyncRequest(ptmsysmHandle);
    if(ret < 0 || ipc[1]<0) return -1;
	return 0;
}

int LED3DS_Off() {
	return LED3DS_On(0,0,0);
}
