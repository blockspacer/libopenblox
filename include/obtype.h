/*
 * Copyright (C) 2016 John M. Harris, Jr. <johnmh@openblox.org>
 *
 * This file is part of OpenBlox.
 *
 * OpenBlox is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenBlox is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with OpenBlox. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef OB_OBTYPE
#define OB_OBTYPE

/**
 * @file obtype.h
 * @author John M. Harris, Jr.
 * @date May 2016
 *
 * This file defines internal types used by the OpenBlox game engine.
 */

/**
 * This type is used for 64 bit integers, specifically for use with
 * time.
 *
 * @author John M. Harris, Jr.
 */
typedef long long int ob_int64;

/**
 * This type is used for 64 bit unsigned integers, for example network
 * identifiers.
 *
 * @author John M. Harris, Jr.
 */
typedef unsigned long long int ob_uint64;

/**
 * Internal type representing a rectangle.
 *
 * @author John M. Harris, Jr.
 */
struct _ob_rect{
	int x1;
	int y1;
	int x2;
	int y2;
};

#define OB_NETID_START 100

#define OB_NETID_UNASSIGNED 0
#define OB_NETID_NOT_REPLICATED 1
#define OB_NETID_NULL 2

#define OB_NETID_DATAMODEL 5
#define OB_NETID_WORKSPACE 6
#define OB_NETID_LIGHTING 7
#define OB_NETID_REPLICATEDFIRST 8
#define OB_NETID_REPLICATEDSTORAGE 9
#define OB_NETID_STARTERGUI 10
#define OB_NETID_COREGUI 11
#define OB_NETID_PLAYERS 12
#define OB_NETID_HTTPSERVICE 13

#define OB_NET_MAX_PEERS 300
#define OB_NET_CHANNELS 3

#define OB_NET_CHAN_PROTOCOL 0
#define OB_NET_CHAN_REPLICATION 1
#define OB_NET_CHAN_LUA 2

// CHAN_REPLICATION Packets

#define OB_NET_PKT_CREATE_INSTANCE 4
#define OB_NET_PKT_SET_PARENT 5
#define OB_NET_PKT_SET_PROPERTY 6

// CHAN_PROTOCOL Packets

#define OB_NET_PKT_FIRE_REMOTE_EVENT 2

#define OB_NET_TYPE_COLOR3 5
#define OB_NET_TYPE_VECTOR3 6
#define OB_NET_TYPE_VECTOR2 7
#define OB_NET_TYPE_LUAENUM 8
#define OB_NET_TYPE_LUAENUMITEM 9
#define OB_NET_TYPE_UDIM 10
#define OB_NET_TYPE_UDIM2 11

#endif // OB_OBTYPE

// Local Variables:
// mode: c++
// End:
