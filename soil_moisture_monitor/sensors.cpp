/* soil_moisture_monitor copyright (C) 2017  KR3ESE Bel

   Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "config.h"
#include "pin.h"
#include "sensors.h"
#include "ax25.h"
#if (ARDUINO + 1) >= 100
#  include <Arduino.h>
#else
#include <WProgram.h>
#endif

void sensors_setup()
{
  pinMode(SOIL_TXD, INPUT);
}

int measure_soil_moisture()
{
  int rawValue = analogRead(SOIL_TXD);
  byte soilMoistureContent = (AIR_VALUE - rawValue) / 10;
 
  #ifdef DEBUG_SENS
  Serial.print("Soil Moisture Content: ");
  Serial.print(soilMoistureContent);
  Serial.print("% [");

  if(soilMoistureContent >= 20)
  {
    Serial.print("VERY WET");
  }
  else if(soilMoistureContent >= 15 && soilMoistureContent < 20)
  {
    Serial.print("WET");
  }
  else if(soilMoistureContent >= 10 && soilMoistureContent < 15)
  {
    Serial.print("MOIST");
  }
  else if(soilMoistureContent >= 5 && soilMoistureContent < 10)
  {
    Serial.print("DRY");
  }
  else if(soilMoistureContent <= 5)
  {
    Serial.print("VERY DRY");
  }
  Serial.println("]");
  #endif

  return soilMoistureContent;
}

int sensors_dfr193_soil()
{
  return measure_soil_moisture();
}
