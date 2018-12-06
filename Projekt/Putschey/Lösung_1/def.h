#ifndef DEF_H_
#define DEF_H_

#define PIN_RS		PB1   // Pin an dem RS ist,
#define PIN_CSB		PB2   // Pin an dem CSB ist vorher PB0
#define PIN_MOSI	PB3
#define PIN_CLK		PB5
#define BUZZER_R	DDRD
#define BUZZER_PORT	PORTD
#define BUZZER_PIN	PD5

#define CLEAR_DISPLAY    		0x01
#define FUNCTION_SET_1		  	0x38
#define FUNCTION_SET_2		  	0x39
#define BIAS_SET				0x15
#define CONTRAST_SET			0x78
#define POWER_CONTRAST_SET		0x55
#define FOLLOWER_SET			0x6D
#define DISPLAY_ON				0x0C
#define DISPLAY_OFF				0x08
#define ENTRY_MODE 				0x06
#define DISPLAY_SHIFT			0x1C


#endif /* DEF_H_ */
