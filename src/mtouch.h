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

#ifndef MTOUCH_H
#define MTOUCH_H

#include <mtdev.h>
#include <mtdev-mapping.h>

#include "caps.h"
#include "hw.h"

#define MT_AXIS_PER_FINGER   5

/*
 * How many fingers we export to upwards
 * The MAX_VALUATORS limits these.
 * MT_NUM_VALUATORS needs to be less or equal than MAX_VALUATORS
 */

#define MT_NUM_FINGERS       6
#define MT_NUM_VALUATORS     (MT_NUM_FINGERS * MT_AXIS_PER_FINGER)

#define MT_NUM_BUTTONS       1

/* Axis labels */

#define AXIS_LABEL_PROP_ABS_MT_TOUCH_MAJOR "Abs MT Touch Major"
#define AXIS_LABEL_PROP_ABS_MT_TOUCH_MINOR "Abs MT Touch Minor"
#define AXIS_LABEL_PROP_ABS_MT_WIDTH_MAJOR "Abs MT Width Major"
#define AXIS_LABEL_PROP_ABS_MT_WIDTH_MINOR "Abs MT Width Minor"
#define AXIS_LABEL_PROP_ABS_MT_ORIENTATION "Abs MT Orientation"
#define AXIS_LABEL_PROP_ABS_MT_POSITION_X  "Abs MT Position X"
#define AXIS_LABEL_PROP_ABS_MT_POSITION_Y  "Abs MT Position Y"
#define AXIS_LABEL_PROP_ABS_MT_TOOL_TYPE   "Abs MT Tool Type"
#define AXIS_LABEL_PROP_ABS_MT_BLOB_ID     "Abs MT Blob ID"
#define AXIS_LABEL_PROP_ABS_MT_TRACKING_ID "Abs MT Tracking ID"
#define AXIS_LABEL_PROP_ABS_MT_PRESSURE    "Abs MT Pressure"

#define MAX_EVENTS 256

struct mtev_mtouch {
	struct input_event ev[MAX_EVENTS];
	unsigned long num_events;
	unsigned long num_events_read;

	struct mtev_hw_state hw_state;
	struct mtev_caps caps;

	bool invert_x;
	bool invert_y;
	bool swap_xy;
        int rotation;
	struct mtdev dev;
};

int mtouch_configure(struct mtev_mtouch *mt, int fd);
int mtouch_open(struct mtev_mtouch *mt, int fd);
int mtouch_close(struct mtev_mtouch *mt, int fd);

bool mtouch_read_synchronized_event(struct mtev_mtouch *mt, int fd);
int mtouch_num_contacts(const struct mtev_mtouch *mt);
const struct mtev_touch_point* mtouch_get_contact(const struct mtev_mtouch *mt, int n);

#endif
