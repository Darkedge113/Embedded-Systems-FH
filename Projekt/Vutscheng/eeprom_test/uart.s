	.file	"uart.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.stabs	"/home/dominik/Desktop/eeprom_test/",100,0,2,.Ltext0
	.stabs	"uart.c",100,0,2,.Ltext0
	.text
.Ltext0:
	.stabs	"gcc2_compiled.",60,0,0,0
	.stabs	"int:t(0,1)=r(0,1);-32768;32767;",128,0,0,0
	.stabs	"char:t(0,2)=r(0,2);0;127;",128,0,0,0
	.stabs	"long int:t(0,3)=@s32;r(0,3);020000000000;017777777777;",128,0,0,0
	.stabs	"unsigned int:t(0,4)=r(0,4);0;0177777;",128,0,0,0
	.stabs	"long unsigned int:t(0,5)=@s32;r(0,5);0;037777777777;",128,0,0,0
	.stabs	"long long int:t(0,6)=@s64;r(0,6);01000000000000000000000;0777777777777777777777;",128,0,0,0
	.stabs	"long long unsigned int:t(0,7)=@s64;r(0,7);0;01777777777777777777777;",128,0,0,0
	.stabs	"short int:t(0,8)=r(0,8);-32768;32767;",128,0,0,0
	.stabs	"short unsigned int:t(0,9)=r(0,9);0;0177777;",128,0,0,0
	.stabs	"signed char:t(0,10)=@s8;r(0,10);-128;127;",128,0,0,0
	.stabs	"unsigned char:t(0,11)=@s8;r(0,11);0;255;",128,0,0,0
	.stabs	"float:t(0,12)=r(0,1);4;0;",128,0,0,0
	.stabs	"double:t(0,13)=r(0,1);4;0;",128,0,0,0
	.stabs	"long double:t(0,14)=r(0,1);4;0;",128,0,0,0
	.stabs	"short _Fract:t(0,15)=r(0,1);1;0;",128,0,0,0
	.stabs	"_Fract:t(0,16)=r(0,1);2;0;",128,0,0,0
	.stabs	"long _Fract:t(0,17)=r(0,1);4;0;",128,0,0,0
	.stabs	"long long _Fract:t(0,18)=r(0,1);8;0;",128,0,0,0
	.stabs	"unsigned short _Fract:t(0,19)=r(0,1);1;0;",128,0,0,0
	.stabs	"unsigned _Fract:t(0,20)=r(0,1);2;0;",128,0,0,0
	.stabs	"unsigned long _Fract:t(0,21)=r(0,1);4;0;",128,0,0,0
	.stabs	"unsigned long long _Fract:t(0,22)=r(0,1);8;0;",128,0,0,0
	.stabs	"_Sat short _Fract:t(0,23)=r(0,1);1;0;",128,0,0,0
	.stabs	"_Sat _Fract:t(0,24)=r(0,1);2;0;",128,0,0,0
	.stabs	"_Sat long _Fract:t(0,25)=r(0,1);4;0;",128,0,0,0
	.stabs	"_Sat long long _Fract:t(0,26)=r(0,1);8;0;",128,0,0,0
	.stabs	"_Sat unsigned short _Fract:t(0,27)=r(0,1);1;0;",128,0,0,0
	.stabs	"_Sat unsigned _Fract:t(0,28)=r(0,1);2;0;",128,0,0,0
	.stabs	"_Sat unsigned long _Fract:t(0,29)=r(0,1);4;0;",128,0,0,0
	.stabs	"_Sat unsigned long long _Fract:t(0,30)=r(0,1);8;0;",128,0,0,0
	.stabs	"short _Accum:t(0,31)=r(0,1);2;0;",128,0,0,0
	.stabs	"_Accum:t(0,32)=r(0,1);4;0;",128,0,0,0
	.stabs	"long _Accum:t(0,33)=r(0,1);8;0;",128,0,0,0
	.stabs	"long long _Accum:t(0,34)=r(0,1);8;0;",128,0,0,0
	.stabs	"unsigned short _Accum:t(0,35)=r(0,1);2;0;",128,0,0,0
	.stabs	"unsigned _Accum:t(0,36)=r(0,1);4;0;",128,0,0,0
	.stabs	"unsigned long _Accum:t(0,37)=r(0,1);8;0;",128,0,0,0
	.stabs	"unsigned long long _Accum:t(0,38)=r(0,1);8;0;",128,0,0,0
	.stabs	"_Sat short _Accum:t(0,39)=r(0,1);2;0;",128,0,0,0
	.stabs	"_Sat _Accum:t(0,40)=r(0,1);4;0;",128,0,0,0
	.stabs	"_Sat long _Accum:t(0,41)=r(0,1);8;0;",128,0,0,0
	.stabs	"_Sat long long _Accum:t(0,42)=r(0,1);8;0;",128,0,0,0
	.stabs	"_Sat unsigned short _Accum:t(0,43)=r(0,1);2;0;",128,0,0,0
	.stabs	"_Sat unsigned _Accum:t(0,44)=r(0,1);4;0;",128,0,0,0
	.stabs	"_Sat unsigned long _Accum:t(0,45)=r(0,1);8;0;",128,0,0,0
	.stabs	"_Sat unsigned long long _Accum:t(0,46)=r(0,1);8;0;",128,0,0,0
	.stabs	"void:t(0,47)=(0,47)",128,0,0,0
	.stabs	"/usr/lib/avr/include/avr/io.h",130,0,0,0
	.stabs	"/usr/lib/avr/include/avr/sfr_defs.h",130,0,0,0
	.stabs	"/usr/lib/avr/include/inttypes.h",130,0,0,0
	.stabs	"/usr/lib/gcc/avr/4.9.2/include/stdint.h",130,0,0,0
	.stabs	"/usr/lib/avr/include/stdint.h",130,0,0,0
	.stabs	"int8_t:t(5,1)=(0,10)",128,0,121,0
	.stabs	"uint8_t:t(5,2)=(0,11)",128,0,122,0
	.stabs	"int16_t:t(5,3)=(0,1)",128,0,123,0
	.stabs	"uint16_t:t(5,4)=(0,4)",128,0,124,0
	.stabs	"int32_t:t(5,5)=(0,3)",128,0,125,0
	.stabs	"uint32_t:t(5,6)=(0,5)",128,0,126,0
	.stabs	"int64_t:t(5,7)=(0,6)",128,0,128,0
	.stabs	"uint64_t:t(5,8)=(0,7)",128,0,129,0
	.stabs	"intptr_t:t(5,9)=(5,3)",128,0,142,0
	.stabs	"uintptr_t:t(5,10)=(5,4)",128,0,147,0
	.stabs	"int_least8_t:t(5,11)=(5,1)",128,0,159,0
	.stabs	"uint_least8_t:t(5,12)=(5,2)",128,0,164,0
	.stabs	"int_least16_t:t(5,13)=(5,3)",128,0,169,0
	.stabs	"uint_least16_t:t(5,14)=(5,4)",128,0,174,0
	.stabs	"int_least32_t:t(5,15)=(5,5)",128,0,179,0
	.stabs	"uint_least32_t:t(5,16)=(5,6)",128,0,184,0
	.stabs	"int_least64_t:t(5,17)=(5,7)",128,0,192,0
	.stabs	"uint_least64_t:t(5,18)=(5,8)",128,0,199,0
	.stabs	"int_fast8_t:t(5,19)=(5,1)",128,0,213,0
	.stabs	"uint_fast8_t:t(5,20)=(5,2)",128,0,218,0
	.stabs	"int_fast16_t:t(5,21)=(5,3)",128,0,223,0
	.stabs	"uint_fast16_t:t(5,22)=(5,4)",128,0,228,0
	.stabs	"int_fast32_t:t(5,23)=(5,5)",128,0,233,0
	.stabs	"uint_fast32_t:t(5,24)=(5,6)",128,0,238,0
	.stabs	"int_fast64_t:t(5,25)=(5,7)",128,0,246,0
	.stabs	"uint_fast64_t:t(5,26)=(5,8)",128,0,253,0
	.stabs	"intmax_t:t(5,27)=(5,7)",128,0,273,0
	.stabs	"uintmax_t:t(5,28)=(5,8)",128,0,278,0
	.stabn	162,0,0,0
	.stabn	162,0,0,0
	.stabs	"int_farptr_t:t(3,1)=(5,5)",128,0,77,0
	.stabs	"uint_farptr_t:t(3,2)=(5,6)",128,0,81,0
	.stabn	162,0,0,0
	.stabn	162,0,0,0
	.stabs	"/usr/lib/avr/include/avr/fuse.h",130,0,0,0
	.stabs	"__fuse_t:t(6,1)=(6,2)=s3low:(0,11),0,8;high:(0,11),8,8;extended:(0,11),16,8;;",128,0,244,0
	.stabn	162,0,0,0
	.stabn	162,0,0,0
	.stabs	"uart_init:F(0,47)",36,0,3,uart_init
	.stabs	"baudrate:P(5,6)",64,0,3,18
.global	uart_init
	.type	uart_init, @function
uart_init:
	.stabd	46,0,0
	.stabn	68,0,3,.LM0-.LFBB1
.LM0:
.LFBB1:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	movw r18,r22
	movw r20,r24
	.stabn	68,0,4,.LM1-.LFBB1
.LM1:
	ldi r22,lo8(-128)
	ldi r23,lo8(-124)
	ldi r24,lo8(30)
	ldi r25,0
	call __udivmodsi4
	subi r18,1
	sbc r19,__zero_reg__
	.stabn	68,0,5,.LM2-.LFBB1
.LM2:
	sts 197,r19
	.stabn	68,0,6,.LM3-.LFBB1
.LM3:
	sts 196,r18
	.stabn	68,0,7,.LM4-.LFBB1
.LM4:
	ldi r24,lo8(2)
	sts 192,r24
	.stabn	68,0,8,.LM5-.LFBB1
.LM5:
	ldi r24,lo8(24)
	sts 193,r24
	ret
	.size	uart_init, .-uart_init
	.stabs	"ubrr:r(5,4)",64,0,4,18
	.stabn	192,0,0,.LFBB1-.LFBB1
	.stabn	224,0,0,.Lscope1-.LFBB1
.Lscope1:
	.stabs	"",36,0,0,.Lscope1-.LFBB1
	.stabd	78,0,0
	.stabs	"uart_transmit:F(0,47)",36,0,11,uart_transmit
	.stabs	"c:P(5,2)",64,0,11,24
.global	uart_transmit
	.type	uart_transmit, @function
uart_transmit:
	.stabd	46,0,0
	.stabn	68,0,11,.LM6-.LFBB2
.LM6:
.LFBB2:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
.L3:
	.stabn	68,0,12,.LM7-.LFBB2
.LM7:
	lds r25,192
	sbrs r25,5
	rjmp .L3
	.stabn	68,0,13,.LM8-.LFBB2
.LM8:
	sts 198,r24
	ret
	.size	uart_transmit, .-uart_transmit
.Lscope2:
	.stabs	"",36,0,0,.Lscope2-.LFBB2
	.stabd	78,0,0
	.stabs	"uart_receive:F(5,2)",36,0,16,uart_receive
.global	uart_receive
	.type	uart_receive, @function
uart_receive:
	.stabd	46,0,0
	.stabn	68,0,16,.LM9-.LFBB3
.LM9:
.LFBB3:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
.L8:
	.stabn	68,0,18,.LM10-.LFBB3
.LM10:
	lds r24,192
	sbrs r24,7
	rjmp .L8
	.stabn	68,0,21,.LM11-.LFBB3
.LM11:
	lds r24,198
	.stabn	68,0,22,.LM12-.LFBB3
.LM12:
	ret
	.size	uart_receive, .-uart_receive
.Lscope3:
	.stabs	"",36,0,0,.Lscope3-.LFBB3
	.stabd	78,0,0
	.stabs	"uart_receive_nonblocking:F(5,2)",36,0,24,uart_receive_nonblocking
	.stabs	"command:P(0,48)=*(5,2)",64,0,24,24
.global	uart_receive_nonblocking
	.type	uart_receive_nonblocking, @function
uart_receive_nonblocking:
	.stabd	46,0,0
	.stabn	68,0,24,.LM13-.LFBB4
.LM13:
.LFBB4:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.stabn	68,0,25,.LM14-.LFBB4
.LM14:
	lds r18,192
	sbrs r18,7
	rjmp .L12
	.stabn	68,0,26,.LM15-.LFBB4
.LM15:
	lds r18,198
	movw r30,r24
	st Z,r18
	.stabn	68,0,27,.LM16-.LFBB4
.LM16:
	ldi r24,lo8(1)
	ret
.L12:
	.stabn	68,0,29,.LM17-.LFBB4
.LM17:
	ldi r24,0
	.stabn	68,0,31,.LM18-.LFBB4
.LM18:
	ret
	.size	uart_receive_nonblocking, .-uart_receive_nonblocking
.Lscope4:
	.stabs	"",36,0,0,.Lscope4-.LFBB4
	.stabd	78,0,0
	.stabs	"uart_sendstring:F(0,47)",36,0,35,uart_sendstring
	.stabs	"str:P(0,49)=*(0,2)",64,0,35,24
.global	uart_sendstring
	.type	uart_sendstring, @function
uart_sendstring:
	.stabd	46,0,0
	.stabn	68,0,35,.LM19-.LFBB5
.LM19:
.LFBB5:
	push r28
	push r29
/* prologue: function */
/* frame size = 0 */
/* stack size = 2 */
.L__stack_usage = 2
	movw r28,r24
.L14:
	.stabn	68,0,36,.LM20-.LFBB5
.LM20:
	ld r24,Y+
	tst r24
	breq .L16
	.stabn	68,0,37,.LM21-.LFBB5
.LM21:
	call uart_transmit
	rjmp .L14
.L16:
/* epilogue start */
	.stabn	68,0,40,.LM22-.LFBB5
.LM22:
	pop r29
	pop r28
	ret
	.size	uart_sendstring, .-uart_sendstring
.Lscope5:
	.stabs	"",36,0,0,.Lscope5-.LFBB5
	.stabd	78,0,0
	.stabs	"",100,0,0,.Letext0
.Letext0:
	.ident	"GCC: (GNU) 4.9.2"
