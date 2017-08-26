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

#include "M10ADC.h"

#define ADC_TSD_TABLE_SIZE 166

static uint16_t ADC_TSD_Lookup[ADC_TSD_TABLE_SIZE] = {
      3798  ,
      3796  ,
      3795  ,
      3793  ,
      3792  ,
      3790  ,
      3788  ,
      3786  ,
      3785  ,
      3782  ,
      3781  ,
      3780  ,
      3779  ,
      3777  ,
      3775  ,
      3773  ,
      3771  ,
      3770  ,
      3768  ,
      3766  ,
      3765  ,
      3764  ,
      3762  ,
      3759  ,
      3756  ,
      3754  ,
      3752  ,
      3751  ,
      3750  ,
      3748  ,
      3746  ,
      3744  ,
      3742  ,
      3740  ,
      3738  ,
      3736  ,
      3733  ,
      3732  ,
      3731  ,
      3730  ,
      3727  ,
      3725  ,
      3721  ,
      3720  ,
      3719  ,
      3717  ,
      3715  ,
      3713  ,
      3711  ,
      3709  ,
      3707  ,
      3704  ,
      3703  ,
      3702  ,
      3700  ,
      3699  ,
      3698  ,
      3697  ,
      3696  ,
      3695  ,
      3688  ,
      3684  ,
      3682  ,
      3680  ,
      3678  ,
      3677  ,
      3676  ,
      3673  ,
      3670  ,
      3667  ,
      3666  ,
      3664  ,
      3662  ,
      3660  ,
      3658  ,
      3656  ,
      3654  ,
      3651  ,
      3648  ,
      3645  ,
      3643  ,
      3642  ,
      3641  ,
      3640  ,
      3638  ,
      3636  ,
      3634  ,
      3632  ,
      3630  ,
      3628  ,
      3625  ,
      3622  ,
      3619  ,
      3616  ,
      3613  ,
      3610  ,
      3607  ,
      3604  ,
      3601  ,
      3598  ,
      3595  ,
      3594  ,
      3593  ,
      3592  ,
      3591  ,
      3590  ,
      3589  ,
      3585  ,
      3582  ,
      3579  ,
      3576  ,
      3573  ,
      3570  ,
      3567  ,
      3564  ,
      3561  ,
      3558  ,
      3555  ,
      3552  ,
      3551  ,
      3550  ,
      3549  ,
      3548  ,
      3547  ,
      3546  ,
      3542  ,
      3538  ,
      3534  ,
      3530  ,
      3526  ,
      3525  ,
      3524  ,
      3522  ,
      3519  ,
      3516  ,
      3513  ,
      3510  ,
      3507  ,
      3504  ,
      3501  ,
      3500  ,
      3498  ,
      3496  ,
      3494  ,
      3492  ,
      3490  ,
      3489  ,
      3486  ,
      3483  ,
      3480  ,
      3477  ,
      3474  ,
      3471  ,
      3468  ,
      3465  ,
      3461  ,
      3460  ,
      3459  ,
      3456  ,
      3451  ,
      3450  ,
      3449  ,
      3445  ,
      3440  ,
      3432  ,
      3431
      
}; // End of ADC_TSD_Lookup[]


//----------------------------------------------------------------------------
// ADC_set_active_channel()
//
// Parameters:
//      channel_index : index for ADC channel
//
// Return Value:
//      None
//
// Remarks:
//      set the active channel for ADC
//----------------------------------------------------------------------------

static void ADC_set_active_channel (uint8_t channel_index) __reentrant
{
  uint8_t csr = (channel_index << ADC_CHANNEL_INDEX_SHIFT) + ADC_ENABLE_BIT;

  ADC_CSR = csr;
  
  __asm__ ("nop");
  __asm__ ("nop");
  __asm__ ("nop");
 
  __asm__ ("nop");
  __asm__ ("nop");
  __asm__ ("nop");
 
} // End of ADC_set_active_channel()

//----------------------------------------------------------------------------
// ADC_disable()
//
// Parameters:
//      None
//
// Return Value:
//      None
//
// Remarks:
//      disable all ADC channels
//----------------------------------------------------------------------------

static void ADC_disable() __reentrant
{
  ADC_CSR = 0;
} // End of ADC_disable()


//----------------------------------------------------------------------------
// ADC_read_data()
//
// Parameters:
//      None
//
// Return Value:
//      value read rrom the active ADC channel
//
// Remarks:
//      read data from the active ADC channel 
//----------------------------------------------------------------------------

static uint16_t ADC_read_data () 
{
  uint8_t high, low;
  uint16_t ret;
  
  low = ADC_CSR;
  __asm__ ("nop");
  __asm__ ("nop");
  __asm__ ("nop");
 
  while (!(ADC_CSR & ADC_DATA_READY_FLAG));

  low = ADC_CSR;
  __asm__ ("nop");
  __asm__ ("nop");
  __asm__ ("nop");
  
  while (!(ADC_CSR & ADC_DATA_READY_FLAG));
  __asm__ ("nop");
  __asm__ ("nop");
  __asm__ ("nop");
  
  high = ADC_DATA_HIGH;
  low  = ADC_DATA_LOW;
  
  ret = (high << 8) + low;
  return ret;
  
} // End of ADC_read_data()

//----------------------------------------------------------------------------
// ADC_recalibration()
//
// Parameters:
//      None
//
// Return Value:
//      None
//
// Remarks:
//      Function to calibrate the ADC
//----------------------------------------------------------------------------

static void ADC_recalibration() __reentrant
{
  ADC_set_active_channel (ADC_RECALIBRATION_CHANNEL);
  ADC_read_data();
  ADC_disable();
} // End of ADC_recalibration()

//----------------------------------------------------------------------------
// analogRead()
//
// Parameters:
//      channel_index : channel_index (0 - 5, or ADC_TEMP_SENSOR_CHANNEL,
//                                            or ADC_RECALIBRATION_CHANNEL)
//
// Return Value:
//      None
//
// Remarks:
//      Function to calibrate the ADC
//----------------------------------------------------------------------------

uint16_t analogRead(uint8_t channel_index) __reentrant
{
    uint16_t t;
    ADC_set_active_channel(channel_index + 1);
    t = ADC_read_data();
    return t;
    
} // End of analogRead()


//----------------------------------------------------------------------------
// ADC_TSD_table_search()
//
// Parameters:
//      value : value read from ADC TSD channel
//
// Return Value:
//      converted value in degree Celsius
//
// Remarks:
//      Function to convert ADC value from TSD channel to degree Celsius
//----------------------------------------------------------------------------

static int16_t ADC_TSD_table_search() 
{
   int16_t ret;
   
   uint16_t left, right, index, t;

   uint16_t value;
   
    ADC_set_active_channel(ADC_TEMP_SENSOR_CHANNEL + 1);
    
    __asm__ ("nop");
    __asm__ ("nop");
    __asm__ ("nop");
    
    for (index = 0; index < 65535; ++index) {
        __asm__ ("nop");
    }

    __asm__ ("nop");
    __asm__ ("nop");
    __asm__ ("nop");
    
    value = ADC_read_data();
    
    __asm__ ("nop");
    __asm__ ("nop");
    __asm__ ("nop");
    
   ADC_CSR = 0;
   
   left = 0;
   right = ADC_TSD_TABLE_SIZE - 1;
    
   do {
     
     index = (left + right + 1) >> 1;

     t = ADC_TSD_Lookup[index];
     
     if ( t > value) {
        left = index;
     } else if (t < value) {
        right = index;
     } else {
        break;
     }
   } while ((left + 1) < right);
   
   ret = (int16_t)index - 40;

   return ret;
  
} // End of ADC_TSD_table_search()


const ADC_STRUCT ADC = {ADC_recalibration,     // begin
                        analogRead,            // read,
                        ADC_TSD_table_search,  // getCelsius
                        ADC_disable            // end
};
