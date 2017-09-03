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

#ifndef M10ADC_H
#define M10ADC_H

#include "Arduino.h"

#define ADC_DATA_READY_FLAG 0x2
#define ADC_ENABLE_BIT 0x1
#define ADC_CHANNEL_INDEX_SHIFT 3

// channel 0 is not used. So all the channel numbers will be shifted by 1 
// i.e. pin 0 is actually using channel 1
// TSD channel is actually 17, but index-ed as 16
// Recal channel is actually 31, but is index-ed as 30
#define ADC_TEMP_SENSOR_CHANNEL    16
#define ADC_RECALIBRATION_CHANNEL  30


extern uint16_t analogRead(uint8_t channel_index) __reentrant;

typedef struct {
    void (*begin)() __reentrant;
    uint16_t (*read) (uint8_t index) __reentrant;
    int16_t (*getCelsius)() ;
    void (*end)() __reentrant;
}ADC_STRUCT;

extern const ADC_STRUCT ADC;
#endif

