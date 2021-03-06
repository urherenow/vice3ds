/*
 * 3dskbd.h - 3DS virtual keyboard
 *
 * Written by
 *  Sebastian Weber <me@badda.de>
 *
 * This file is part of VICE3DS
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

extern void sdl_uibottom_draw(void);
extern int sdl_uibottom_mouseevent(SDL_Event *);

extern int uibottom_kbdactive;
extern int uibottom_must_redraw;

typedef struct {
	int x,y,w,h,key,row,col,flg;
	char *name;
} uikbd_key;

extern uikbd_key uikbd_keypos[];
