/*
###############################################################################
# Copyright (c) 2017, PulseRain Technology LLC 
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License (LGPL) as 
# published by the Free Software Foundation, either version 3 of the License,
# or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but 
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
# or FITNESS FOR A PARTICULAR PURPOSE.  
# See the GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
###############################################################################
*/


#include <M10ADC.h>

//============================================================================
// Example:
//     Taking measurement from onchip TSD (temperature sensing diode) 
//============================================================================


void setup() {

   delay(1000);
   Serial.begin(115200);
   ADC.begin();
   ADC.getCelsius();
   
} // End of setup() 

void loop() {

   int16_t temp;

   uint32_t sec;
   uint32_t ms;
      
   delay(1000);
   
   temp = ADC.getCelsius();
     
   ms = millis();
   sec = ms / 1000;
   ms -= sec * 1000;
    
   Serial.write ("Time: ");
   Serial.print (sec, DEC);
   Serial.write (".");
   Serial.print (ms, DEC);
   Serial.write (" second, \tTemperature: ");
   Serial.print(temp, DEC);
   Serial.write (" Degree C ");

   Serial.write("\n\n");
   
} // End of loop()

