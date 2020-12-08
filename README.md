# parallel-output-stm32
This code is designed for stm32f103cb microcontroller.
This library is for sending data to leds strips,up to 4 led strips are written in parallel.It supports ws2812,apa102 and dmx protocols.
This library is non blocking ,it uses dma and irq to send the data while the main program can do other tasks.There are some problems with ws2812 signals,related to dma and memory speed (In stm32f1 bus arbitration is slow),so it is recommended to not use more dma channels or access to ports (slower memory bus) while the dma transfer is running. 
