# parallel-output-stm32
This code is designed for stm32f103cb microcontroller.
This library is for sending data to leds strips,up to 4 led strips are written in parallel.It supports ws2812,apa102 and dmx protocols.
This library is non blocking ,it uses dma and irq to send the data while the main program can do other tasks.
