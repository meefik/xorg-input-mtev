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
#include <errno.h>
#include <unistd.h>
#include <xf86.h>

#include "mtouch.h"

int mtouch_configure(struct mtev_mtouch *mt, int fd)
{
	int rc = caps_read(&mt->caps, fd);
	if (rc < 0)
		return rc;
	caps_output(&mt->caps);
	return 0;
}

int mtouch_open(struct mtev_mtouch *mt, int fd)
{
	memset(&mt->ev, 0, sizeof(mt->ev));
	memset(&mt->dev, 0, sizeof(mt->dev));
	mt->num_events = 0;
	hw_init(&mt->hw_state);
	return mtdev_open(&mt->dev, fd);
}

int mtouch_close(struct mtev_mtouch *mt, int fd)
{
	mtdev_close(&mt->dev);
	memset(&mt->dev, 0, sizeof(mt->dev));
	memset(&mt->ev, 0, sizeof(mt->ev));
	mt->num_events = 0;
	hw_init(&mt->hw_state);
	return 0;
}

const struct input_event* mtouch_read_event(struct mtev_mtouch *mt, int fd)
{
	struct input_event *ev;

	/* Read in bursts from input subsystem, then feed to caller one
	 * at a time, only reading the next burst when the queue is empty */
	if (mt->num_events_read >= mt->num_events) {
		int n;

		SYSCALL(n = mtdev_get(&mt->dev, fd, mt->ev, MAX_EVENTS));
		if (n <= 0)
			return NULL;

		mt->num_events = n;
		mt->num_events_read = 0;
	}

	if (mt->num_events > mt->num_events_read) {
		ev = &mt->ev[mt->num_events_read];
		mt->num_events_read++;
		return ev;
	}

	// This should not happen
	xf86Msg(X_ERROR, "mtev: got read_event without event!\n");
	return NULL;
}

bool mtouch_read_synchronized_event(struct mtev_mtouch *mt, int fd)
{
	const struct input_event* ev;

	while ((ev = mtouch_read_event(mt, fd))) {
		if (hw_read(&mt->hw_state, ev))
			return 1;
	}

	return 0;
}

const struct mtev_touch_point* mtouch_get_contact(const struct mtev_mtouch *mt, int n)
{
	int i = 0;
	do {
		if (mt->hw_state.slot[i].tracking_id != INVALID_TRACKING_ID && (n--) == 0)
			return &mt->hw_state.slot[i];
	} while (++i < HW_MAX_SLOTS);

	return NULL;
}
