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

#ifndef CAPABILITIES_H
#define CAPABILITIES_H

#include "common.h"
#include <linux/input.h>

struct mtev_caps {
	bool has_left, has_middle;
	bool has_right, has_mtdata;
	bool has_touch_major, has_touch_minor;
	bool has_width_major, has_width_minor;
	bool has_orientation, has_tracking_id;
	bool has_position_x, has_position_y;
	struct input_absinfo abs_touch_major;
	struct input_absinfo abs_touch_minor;
	struct input_absinfo abs_width_major;
	struct input_absinfo abs_width_minor;
	struct input_absinfo abs_orientation;
	struct input_absinfo abs_position_x;
	struct input_absinfo abs_position_y;
	struct input_absinfo abs_tracking_id;
};

int caps_read(struct mtev_caps *caps, int fd);
void caps_output(const struct mtev_caps *caps);

#endif
