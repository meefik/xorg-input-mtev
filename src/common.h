/***************************************************************************
 *
 * Multitouch protocol X driver
 * Copyright (C) 2008 Henrik Rydberg <rydberg@euromail.se>
 * Copyright (C) 2009,2010 Nokia Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 **************************************************************************/

#ifndef COMMON_H
#define COMMON_H

typedef unsigned char bool;

// includes available in 2.6.30-rc5

#ifndef ABS_MT_PRESSURE
#define BTN_TOOL_QUADTAP	0x14f	/* Four fingers on trackpad */
#define ABS_MT_TOUCH_MAJOR	0x30	/* Major axis of touching ellipse */
#define ABS_MT_TOUCH_MINOR	0x31	/* Minor axis (omit if circular) */
#define ABS_MT_WIDTH_MAJOR	0x32	/* Major axis of approaching ellipse */
#define ABS_MT_WIDTH_MINOR	0x33	/* Minor axis (omit if circular) */
#define ABS_MT_ORIENTATION	0x34	/* Ellipse orientation */
#define ABS_MT_POSITION_X	0x35	/* Center X ellipse position */
#define ABS_MT_POSITION_Y	0x36	/* Center Y ellipse position */
#define ABS_MT_TOOL_TYPE	0x37	/* Type of touching device */
#define ABS_MT_BLOB_ID		0x38	/* Group a set of packets as a blob */
#define ABS_MT_TRACKING_ID      0x39    /* Unique ID of initiated contact */
#define ABS_MT_PRESSURE         0x3a    /* Pressure on contact area */
#define SYN_MT_REPORT		2
#define MT_TOOL_FINGER		0
#define MT_TOOL_PEN		1
#endif

#define SYSCALL(call) while (((call) == -1) && (errno == EINTR))

#define GETBIT(m, x) ((m>>(x))&1U)
#define SETBIT(m, x) (m|=(1U<<(x)))
#define CLEARBIT(m, x) (m&=~(1U<<(x)))

#endif
