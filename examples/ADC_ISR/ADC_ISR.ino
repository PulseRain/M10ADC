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
//     Taking measurement from an analog channel (0 - 5) with ISR 
//============================================================================


//----------------------------------------------------------------------------
// adc_isr_handler()
//
// Parameters:
//      None
//
// Return Value:
//      None
//
// Remarks:
//      isr handler for ADC (IRQ 5)
//----------------------------------------------------------------------------

uint16_t adc_value;

void adc_isr_handler()
{
   uint8_t high, low;
   
   high = ADC_DATA_HIGH;
   low  = ADC_DATA_LOW;

   adc_value = (high << 8) + low;
   low = ADC_CSR;

} // End of adc_isr_handler()





//============================================================================
// setup()
//============================================================================

void setup() {

   delay(1000);
   Serial.begin(115200);
   ADC.begin();

   analogRead(0); // setup active ADC channel here
   
   attachIsrHandler (ADC_INT_INDEX, adc_isr_handler);
   
} // End of setup() 


//============================================================================
// loop()
//============================================================================

void loop() {
   uint16_t t;
   int16_t temp;

   delay(1000);
   
   noInterrupts();
   t = adc_value;
   interrupts();

   Serial.println(t);
   
} // End of loop()

