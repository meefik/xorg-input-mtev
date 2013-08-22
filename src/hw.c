/***************************************************************************
 *
 * Multitouch protocol X driver
 * Copyright (C) 2008 Henrik Rydberg <rydberg@euromail.se>
 * Copyright (C) 2009,2010 Nokia Corporation
 *
 * Adaptation to libmtdev and Linux multi-touch-protocol B (slotted)
 * Copyright (C) 2010 Intel Corporation
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

#include <string.h>
#include <linux/input.h>
#include <xf86.h>
#include <mtdev.h>

#include "hw.h"

void hw_init(struct mtev_hw_state *hw)
{
	int i;
	memset(hw, 0, sizeof(struct mtev_hw_state));
	for (i = 0; i < HW_MAX_SLOTS; i++)
	    hw->slot[i].tracking_id = INVALID_TRACKING_ID;
}

bool hw_read(struct mtev_hw_state *hw, const struct input_event* ev)
{
	// xf86Msg(X_INFO, "event: %d %d %d\n", ev->type, ev->code, ev->value);

	switch (ev->type) {
	case EV_SYN:
		switch (ev->code) {
		case SYN_REPORT:
			return 1;

		case SYN_MT_REPORT:
			xf86Msg(X_ERROR, "libmtdev sent SYN_MT_REPORT");
			break;
		}
		break;

	case EV_ABS:
		if (ev->code == ABS_MT_SLOT) {
			if (ev->value >= HW_MAX_SLOTS) {
				xf86Msg(X_ERROR, "Slot usage (%d) exceeds limit of %d", ev->value, HW_MAX_SLOTS);
				hw->current_slot = INVALID_SLOT;
			} else
				hw->current_slot = ev->value;
			break;
		}

		if (hw->current_slot == INVALID_SLOT)
			break;

		switch (ev->code) {
		case ABS_MT_POSITION_X:
			hw->slot[hw->current_slot].position_x = ev->value;
			break;
		case ABS_MT_POSITION_Y:
			hw->slot[hw->current_slot].position_y = ev->value;
			break;
		case ABS_MT_TOUCH_MAJOR:
			hw->slot[hw->current_slot].touch_major = ev->value;
			break;
		case ABS_MT_TOUCH_MINOR:
			hw->slot[hw->current_slot].touch_minor = ev->value;
			break;
		case ABS_MT_WIDTH_MAJOR:
			hw->slot[hw->current_slot].width_major = ev->value;
			break;
		case ABS_MT_WIDTH_MINOR:
			hw->slot[hw->current_slot].width_minor = ev->value;
			break;
		case ABS_MT_ORIENTATION:
			hw->slot[hw->current_slot].orientation = ev->value;
			break;
		case ABS_MT_PRESSURE:
			hw->slot[hw->current_slot].pressure = ev->value;
			break;
		case ABS_MT_TRACKING_ID:
			if (ev->value == -1) /* Slot contact has been released */
				hw->slot[hw->current_slot].tracking_id = INVALID_TRACKING_ID;
			else
				hw->slot[hw->current_slot].tracking_id = hw->current_slot;//ev->value;
			break;
		}
	}

	return 0;
}
