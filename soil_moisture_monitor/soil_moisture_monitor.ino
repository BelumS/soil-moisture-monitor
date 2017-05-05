/* trackuino copyright (C) 2010  EA5HAV Javi
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

// Refuse to compile on arduino version 21 or lower. 22 includes an 
// optimization of the USART code that is critical for real-time operation.
#if ARDUINO < 22
#error "Oops! We need Arduino 22 or later"
#endif

// Trackuino custom libs
#include "aprs.h"
#include "pin.h"
#include "ax25.h"
#include "config.h"
#include "modem.h"
#include "radio.h"
#include "radio_hx1.h"
#include "power.h"
#include "sensors.h"

// Arduino/AVR libs
#include <Arduino.h>
#include <avr/power.h>
#include <avr/sleep.h>

static uint32_t next_tx_millis;    // Counter for delay between position and telemetry reports

enum packets
{
  PACKET_POS,
  PACKET_TELEMETRY,
  PACKET_UNITS
};

// Public Functions
void setup()
{
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(BAUDRATE);
  #ifdef DEBUG_RESET
   Serial.println("RESET");
  #endif
  modem_setup();
  sensors_setup();

  #ifdef APRS_TELEMETRY
   aprs_setup();
  #endif
  
  // Schedule the next transmission within APRS_DELAY ms
  next_tx_millis = millis() + APRS_DELAY;
}

void loop()
{
  uint8_t c;
  static uint8_t packet_type = PACKET_POS;
  static uint8_t config_count = 0;

  #ifdef DEBUG_SENS
  int soil = measureSoilMoisture();
  #endif

  if (millis() >= next_tx_millis)
  {
    /*  Reload the timer for the next transmission, do it first so we don't
        add the processing and transmit delays to our interval period */
     next_tx_millis = millis() + APRS_PERIOD;

    // Show modem ISR stats from the previous transmission if enabled
    #ifdef DEBUG_MODEM
      modem_debug();
    #endif

    /*  periodically send the APRS telemetry configuration data, set to approx
        every 40th packet (10mins) */
    if(config_count > APRS_TELEM_CFG_CNT)
    {
      packet_type = PACKET_UNITS;
      config_count = 0;
    }
    else
    {
      config_count += 1;
    }

    /*  Now we can actually get around to sending the packet, so we will send position
        and raw telemetry values on an alternating scheme. Every 40th packet we will
        send the telemetry config packets.  The order in which packets are sent is via
        very simple state machine */
    switch(packet_type)
    {
      case PACKET_POS:  // Send Position Report
             aprs_send();
             packet_type = PACKET_TELEMETRY;
             break;
              
      case PACKET_TELEMETRY:  // Send Telemetry Data
             //aprs_telemetry_data();
             packet_type = PACKET_POS;
             break;

      case PACKET_UNITS: // Send Telemetry Information
             //aprs_telemetry_params();
             packet_type = 0;
             break;
    }
  }
    power_save();
}


