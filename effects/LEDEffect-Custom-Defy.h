/* LEDEffect-Custom-Defy - LED effect with settings from a custom effect slot.
 * Copyright (C) 2026  DygmaLabs, S. L.
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <stdint.h>

#include "LEDEffect.h"

/* Keep this header free of keyscanner communication includes, since the Kaleidoscope adapter includes it */

#define LED_CUSTOM_SLOT_COUNT               16
#define LED_CUSTOM_SLOT_NONE                0xFF
#define LED_CUSTOM_RAINBOW_SPEED_DEFAULT    40      /* Built-in Rainbow delay_ms */
#define LED_CUSTOM_RAINBOW_SPEED_MIN        40      /* No slot runs faster than the built-in Rainbow */

typedef enum : uint8_t
{
    LED_CUSTOM_TYPE_UNUSED = 0,
    LED_CUSTOM_TYPE_SOLID,
    LED_CUSTOM_TYPE_RAINBOW,
    LED_CUSTOM_TYPE_RAINBOW_WAVE,
    LED_CUSTOM_TYPE_STALKER,
    LED_CUSTOM_TYPE_LAYERS,
    LED_CUSTOM_TYPE_OFF,

    LED_CUSTOM_TYPE_LAST = LED_CUSTOM_TYPE_OFF,
} led_custom_type_t;

typedef struct
{
    uint8_t type;       /* led_custom_type_t */
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t speed;      /* Rainbow delay_ms, 0 = LED_CUSTOM_RAINBOW_SPEED_DEFAULT */
} led_custom_t;

/* Solid and Rainbow slots. The slot types without settings use the built-in effects */
class LEDCustomEffect : public LEDEffect
{
  public:
    LEDCustomEffect( void ) : LEDEffect( LED_EFFECT_TYPE_CUSTOM ) {}

    void settings_set( const led_custom_t & settings );

    void activate() final;

  private:
    led_custom_t settings_ = {};
};

extern class LEDCustomEffect LEDCustomEffect;
