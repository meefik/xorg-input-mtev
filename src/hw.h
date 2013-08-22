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

#ifndef HWDATA_H
#define HWDATA_H

#include "common.h"

struct input_event;

// Max touch points we gonna get out from kernel layer
#define HW_MAX_SLOTS 10
#define INVALID_SLOT -1
#define INVALID_TRACKING_ID -1

struct mtev_touch_point {
	int touch_major, touch_minor;
	int width_major, width_minor;
	int orientation;
	int position_x, position_y;
	int pressure;
	int tracking_id;
};

struct mtev_hw_state {
	struct mtev_touch_point slot[HW_MAX_SLOTS];
	int current_slot;
};

void hw_init(struct mtev_hw_state *hw);
bool hw_read(struct mtev_hw_state *hw, const struct input_event* ev);

#endif
