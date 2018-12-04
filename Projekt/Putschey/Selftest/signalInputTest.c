/*
Read in the InfraRed Signal via Sensor

Sensor standy-by output = logical high
Sensor receives -> output = logical low

First falling edge -> Timer 1 starts

Rising edge -> Save time in array and reset Timer 1
Falling edge -> Save time in array and reset Timer 1
Repeat until Array full, or Signal ends
Signal end = Output of Sensor is logical high
*/
