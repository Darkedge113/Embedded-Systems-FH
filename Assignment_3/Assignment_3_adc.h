#ifndef Assignment_3_adc_h
#define Assignment_3_adc_h

void adc_init();
uint16_t adc_read (uint8_t channel);
void intToString(uint16_t val, char * target);

#endif
