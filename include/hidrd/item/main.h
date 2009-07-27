/** @file
 * @brief HID report descriptor - main item
 *
 * Copyright (C) 2009 Nikolai Kondrashov
 *
 * This file is part of hidrd.
 *
 * Hidrd is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Hidrd is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with hidrd; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * @author Nikolai Kondrashov <spbnick@gmail.com>
 *
 * @(#) $Id$
 */

#ifndef __HIDRD_ITEM_MAIN_H__
#define __HIDRD_ITEM_MAIN_H__

#include "hidrd/item/short.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HIDRD_ITEM_MAIN_TAG_MIN 0x8

typedef enum hidrd_item_main_tag {
    HIDRD_ITEM_MAIN_TAG_INPUT           = HIDRD_ITEM_MAIN_TAG_MIN,
    HIDRD_ITEM_MAIN_TAG_OUTPUT,
    HIDRD_ITEM_MAIN_TAG_COLLECTION,
    HIDRD_ITEM_MAIN_TAG_FEATURE,
    HIDRD_ITEM_MAIN_TAG_END_COLLECTION
} hidrd_item_main_tag;

#define HIDRD_ITEM_MAIN_TAG_MAX HIDRD_ITEM_SHORT_TAG_MAX

#define HIDRD_ITEM_MAIN_TAG_KNOWN_MAX   HIDRD_ITEM_MAIN_TAG_END_COLLECTION

#define HIDRD_ITEM_MAIN_TAG_RESERVED_MIN \
            (HIDRD_ITEM_MAIN_TAG_KNOWN_MAX + 1)
#define HIDRD_ITEM_MAIN_TAG_RESERVED_MAX \
            HIDRD_ITEM_MAIN_TAG_MAX


static inline bool
hidrd_item_main_tag_valid(hidrd_item_main_tag tag)
{
    return (tag >= HIDRD_ITEM_MAIN_TAG_MIN) &&
           (tag <= HIDRD_ITEM_MAIN_TAG_MAX);
}

static inline bool
hidrd_item_main_tag_known(hidrd_item_main_tag tag)
{
    assert(hidrd_item_main_tag_valid(tag));
    return (tag <= HIDRD_ITEM_MAIN_TAG_KNOWN_MAX);
}

static inline bool
hidrd_item_main_tag_reserved(hidrd_item_main_tag tag)
{
    assert(hidrd_item_main_tag_valid(tag));
    return (tag >= HIDRD_ITEM_MAIN_TAG_RESERVED_MIN) &&
           (tag <= HIDRD_ITEM_MAIN_TAG_RESERVED_MAX);
}


static inline bool
hidrd_item_main_valid(const hidrd_item *item)
{
    return hidrd_item_short_valid(item) &&
           (hidrd_item_short_get_type(item) ==
            HIDRD_ITEM_SHORT_TYPE_MAIN) &&
           hidrd_item_main_tag_valid(hidrd_item_short_get_tag(item));
}

static inline hidrd_item_main_tag
hidrd_item_main_get_tag(const hidrd_item *item)
{
    assert(hidrd_item_main_valid(item));
    return hidrd_item_short_get_tag(item);
}


static inline hidrd_item *
hidrd_item_main_set_tag(hidrd_item *item, hidrd_item_main_tag tag)
{
    assert(hidrd_item_main_valid(item));
    return hidrd_item_short_set_tag(item, tag);
}


#define HIDRD_ITEM_MAIN_GEN_FUNCS(_name, _NAME) \
    static inline bool                                  \
    hidrd_item_##_name##_valid(const hidrd_item *item)  \
    {                                                   \
        return hidrd_item_main_valid(item) &&           \
               hidrd_item_main_get_tag(item) ==         \
               HIDRD_ITEM_MAIN_TAG_##_NAME;             \
    }

#define HIDRD_ITEM_MAIN_BIT_FUNCS(_name) \
    hidrd_item_##_name##_get_bit(const hidrd_item *item,    \
                                 uint8_t idx)               \
    {                                                       \
        assert(hidrd_item_##_name##_valid(item));           \
        assert(idx <= 31);                                  \
        return hidrd_item_short_get_bit(item, idx);         \
    }                                                       \
                                                            \
    hidrd_item_##_name##_set_bit(hidrd_item *item,          \
                                 uint8_t idx, bool val)     \
    {                                                       \
        assert(hidrd_item_##_name##_valid(item));           \
        assert(idx <= 31);                                  \
        return hidrd_item_short_set_bit(item, idx, val);    \
    }

#define HIDRD_ITEM_MAIN_BIT_ACC(_name, _idx, _off_name, _on_name) \
    static inline bool                                                  \
    hidrd_item_##_name##_is_##_off_name(const hidrd_item *item)         \
    {                                                                   \
        return !hidrd_item_##_name##_get_bit(item, _i);                 \
    }                                                                   \
                                                                        \
    static inline bool                                                  \
    hidrd_item_##_name##_is_##_on_name(const hidrd_item *item)          \
    {                                                                   \
        return hidrd_item_##_name##_get_bit(item, _i);                  \
    }                                                                   \
                                                                        \
    static inline hidrd_item *                                          \
    hidrd_item_##_name##_set_##_off_name(hidrd_item *item,              \
                                         bool is_##_off_name)           \
    {                                                                   \
        return hidrd_item_##_name##_set_bit(item, _i, !is_##_off_name); \
    }                                                                   \
                                                                        \
    static inline hidrd_item *                                          \
    hidrd_item_##_name##_set_##_on_name(hidrd_item *item,               \
                                        bool is_##_on_name)             \
    {                                                                   \
        return hidrd_item_##_name##_set_bit(item, _i, !is_##_on_name);  \
    }

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __HIDRD_ITEM_MAIN_H__ */