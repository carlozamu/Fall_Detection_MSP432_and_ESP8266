#include "acc.h"

bool fallDetection()
{
    const uint32_t max = (MAX + 3*NOISE_DEV);

    int tmp_1[AX], tmp_2[AX], i;

    tmp_1[Y] = ADC14_getResult(ADC_MEM1);
    tmp_1[Z] = ADC14_getResult(ADC_MEM2);

    _delay_cycles(10000);


    tmp_2[Y] = ADC14_getResult(ADC_MEM1);
    tmp_2[Z] = ADC14_getResult(ADC_MEM2);

    for(i = 0; i < AX; i++){
        if(tmp_1[i] > max){
            if(tmp_2[i] > max) {
                return true;
            }
        }
    }

    return false;

}
