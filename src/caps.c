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

#include "caps.h"
#include <errno.h>
#include <string.h>
#include <xf86.h>
#include <xf86Xinput.h>

#define SETABS(c, x, map, key, fd)					\
	c->has_##x = getbit(map, key) && getabs(&c->abs_##x, key, fd)

#define ADDCAP(s, c, x) strcat(s, c->has_##x ? " " #x : "")

static const int bits_per_long = 8 * sizeof(long);

static inline int nlongs(int nbit)
{
	return (nbit + bits_per_long - 1) / bits_per_long;
}

static inline bool getbit(const unsigned long* map, int key)
{
	return (map[key / bits_per_long] >> (key % bits_per_long)) & 0x01;
}

static bool getabs(struct input_absinfo *abs, int key, int fd)
{
	int rc;
	SYSCALL(rc = ioctl(fd, EVIOCGABS(key), abs));
	return rc >= 0;
}

int caps_read(struct mtev_caps *caps, int fd)
{
	unsigned long evbits[nlongs(EV_MAX)];
	unsigned long absbits[nlongs(ABS_MAX)];
	unsigned long keybits[nlongs(KEY_MAX)];
	int rc;

	memset(caps, 0, sizeof(struct mtev_caps));

	SYSCALL(rc = ioctl(fd, EVIOCGBIT(EV_SYN, sizeof(evbits)), evbits));
	if (rc < 0) {
		xf86Msg(X_ERROR, "mtev: EV_SYN needed but missing\n");
		return rc;
	}

	SYSCALL(rc = ioctl(fd, EVIOCGBIT(EV_KEY, sizeof(keybits)), keybits));
	if (rc < 0) {
		xf86Msg(X_ERROR, "mtev: EV_KEY needed but missing\n");
		return rc;
	}
	SYSCALL(rc = ioctl(fd, EVIOCGBIT(EV_ABS, sizeof(absbits)), absbits));
	if (rc < 0) {
		xf86Msg(X_ERROR, "mtev: EV_ABS needed but missing\n");
		return rc;
	}

	caps->has_left = getbit(keybits, BTN_LEFT);
	caps->has_middle = getbit(keybits, BTN_MIDDLE);
	caps->has_right = getbit(keybits, BTN_RIGHT);

	SETABS(caps, touch_major, absbits, ABS_MT_TOUCH_MAJOR, fd);
	SETABS(caps, touch_minor, absbits, ABS_MT_TOUCH_MINOR, fd);
	SETABS(caps, width_major, absbits, ABS_MT_WIDTH_MAJOR, fd);
	SETABS(caps, width_minor, absbits, ABS_MT_WIDTH_MINOR, fd);
	SETABS(caps, orientation, absbits, ABS_MT_ORIENTATION, fd);
	SETABS(caps, position_x, absbits, ABS_MT_POSITION_X, fd);
	SETABS(caps, position_y, absbits, ABS_MT_POSITION_Y, fd);
	SETABS(caps, tracking_id, absbits, ABS_MT_TRACKING_ID, fd);

	caps->has_mtdata = caps->has_position_x && caps->has_position_y;

	return 0;
}

void caps_output(const struct mtev_caps *caps)
{
	char line[1024];
	memset(line, 0, sizeof(line));
	ADDCAP(line, caps, left);
	ADDCAP(line, caps, middle);
	ADDCAP(line, caps, right);
	ADDCAP(line, caps, mtdata);
	ADDCAP(line, caps, touch_major);
	ADDCAP(line, caps, touch_minor);
	ADDCAP(line, caps, width_major);
	ADDCAP(line, caps, width_minor);
	ADDCAP(line, caps, orientation);
	ADDCAP(line, caps, tracking_id);
	ADDCAP(line, caps, position_x);
	ADDCAP(line, caps, position_y);

	xf86Msg(X_INFO, "mtev: caps:%s\n", line);
	if (caps->has_touch_major)
		xf86Msg(X_INFO, "mtev: touch major: %d %d\n",
			caps->abs_touch_major.minimum,
			caps->abs_touch_major.maximum);
	if (caps->has_touch_minor)
		xf86Msg(X_INFO, "mtev: touch minor: %d %d\n",
			caps->abs_touch_minor.minimum,
			caps->abs_touch_minor.maximum);
	if (caps->has_width_major)
		xf86Msg(X_INFO, "mtev: width: %d %d\n",
			caps->abs_width_major.minimum,
			caps->abs_width_major.maximum);
	if (caps->has_orientation)
		xf86Msg(X_INFO, "mtev: orientation: %d %d\n",
			caps->abs_orientation.minimum,
			caps->abs_orientation.maximum);
	if (caps->has_tracking_id)
		xf86Msg(X_INFO, "mtev: tracking_id: %d %d\n",
			caps->abs_tracking_id.minimum,
			caps->abs_tracking_id.maximum);
	if (caps->has_position_x)
		xf86Msg(X_INFO, "mtev: position_x: %d %d\n",
			caps->abs_position_x.minimum,
			caps->abs_position_x.maximum);
	if (caps->has_position_y)
		xf86Msg(X_INFO, "mtev: position_y: %d %d\n",
			caps->abs_position_y.minimum,
			caps->abs_position_y.maximum);
}
