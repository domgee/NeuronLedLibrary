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

#include "LEDEffect-Custom-Defy.h"

#include "LedModeSerializable-Rainbow.h"
#include "LedModeSerializable-SolidColor.h"
#include "LedModeCommunication.h"

/* Use this translation unit's own copies of the static serializables, so the built-in effects keep their settings */
class LEDCustomSender : public LedModeCommunication
{
  public:
    static void send( LedModeSerializable & led_mode )
    {
        sendLedMode( led_mode );
    }
};

void LEDCustomEffect::settings_set( const led_custom_t & settings )
{
    settings_ = settings;
}

void LEDCustomEffect::activate( void )
{
    /* Set every field each time, matching what the built-in effect of the same kind sends */
    if( settings_.type == LED_CUSTOM_TYPE_SOLID )
    {
        LedModeSerializable_SolidColor & led_mode = ledModeSerializableSolidColor;

        led_mode.base_settings.step = 0;
        led_mode.base_settings.brightness = 0;
        led_mode.base_settings.delay_ms = 100;
        led_mode.r_ = settings_.r;
        led_mode.g_ = settings_.g;
        led_mode.b_ = settings_.b;
        led_mode.w_ = 0;

        LEDCustomSender::send( led_mode );
    }
    else if( settings_.type == LED_CUSTOM_TYPE_RAINBOW )
    {
        LedModeSerializable_Rainbow & led_mode = ledModeSerializableRainbow;
        uint8_t speed = settings_.speed;

        /* Treat 0 as the default and keep corrupt values from running faster than the built-in Rainbow */
        if( speed == 0 )
        {
            speed = LED_CUSTOM_RAINBOW_SPEED_DEFAULT;
        }
        else if( speed < LED_CUSTOM_RAINBOW_SPEED_MIN )
        {
            speed = LED_CUSTOM_RAINBOW_SPEED_MIN;
        }

        led_mode.base_settings.step = 0;
        led_mode.base_settings.brightness = 255;
        led_mode.base_settings.delay_ms = speed;

        LEDCustomSender::send( led_mode );
    }
}

class LEDCustomEffect LEDCustomEffect;
