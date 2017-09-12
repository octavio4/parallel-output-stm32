//stm32f103cb 20k ram 128k flash
#define DEBUG 0
#include <libmaple/dma.h>
typedef unsigned char byte;
#define buf_size 3*4*64 //up to 4 strips of 64 pixels each
byte bufer1[buf_size];
#define npk 3  // >2
#define max_dma_bufer_size 48*npk
unsigned int dma_bufer_size;
long dma_bufer[max_dma_bufer_size],output_table[16];
byte *dma_read;
int frame_size ; //=npixels*3;
byte volatile estado_transfer;//=255 when transfer is complete
long volatile * dma_write; //pointer to write data in dma_bufer
unsigned long volatile dma_count,dma_size; //bytes transfered,total bytes to tranferir


HardwareTimer timer(2);

#define cpu_mhz 72
void start_transfer(uint32_t);
void (*irq_transfer)(void);
bool (*get_bits)(void);
unsigned char time_transfer,led_order;     //time betwen a dma transfer in cpu clocks

#include "LIB.CPP"
#include "POUT.CPP" 
#include "DMX.CPP"
#include "WS28.CPP"
#include "APA.CPP"

  //19804  17096
void setup()
{
  if (DEBUG) { Serial.begin(250000);delay(1000);   //+1376bytes flash
   Serial.println("serial ok");}
    pinMode(PA0,OUTPUT);
    pinMode(PA1,OUTPUT);
    pinMode(PA2,OUTPUT);
    pinMode(PA3,OUTPUT);

           frame_size=3*4*6; //4; //4 strips of 64 pixels 
           led_order=GRB;   
           setup_output_table(0,0,1,0,3,0,2,0);  //1=PA1
           get_bits=&get_rgb44;             
           setup_ws28(cpu_mhz*9/24);

/*
  //DMX 
  // pin0 is d+ channel0
 // pin1 is d- channel0 
 
          frame_size=3*2*64; //2 strips of 64 pixels
          led_order=RGB;
          setup_output_table(0,1,2,3,0,0,0,0);get_bits=&get_rgb24;
           setup_dmx(cpu_mhz*4);   
*/

/*        //apa102 PA2 is common clock     
 *        frame_size=3*3*64; //3 strips of 64 pixels
          led_order=BGR; 
          setup_output_table(0,0,1,0,3,0,0,0);get_bits=&get_rgb34;        
          setup_apa(48);
  */        
 
}
int npixel=0;
void loop()
{
    set_pixel(0,0,0);
    if(++npixel>(frame_size/3)){ npixel=0;
  set_color(20,0,0);
    dma_read=bufer1;
    start_transfer(frame_size);
    delay(2000);
  set_color(0,20,0);
    dma_read=bufer1;
    start_transfer(frame_size);
    delay(2000);
  set_color(0,0,20);
    dma_read=bufer1;
    start_transfer(frame_size);
    delay(2000);
   set_color(0,0,0);   
    }
    set_pixel(31,31,31); 
    dma_read=bufer1;
    start_transfer(frame_size);
    delay(1000);
  
 }

void set_color(char r,char g,char b)
  {
   int c1=frame_size/3; 
   dma_read=bufer1;
   while(c1--){
   *dma_read++=r; 
   *dma_read++=g;
   *dma_read++=b;
   };
   
   }

void set_pixel(char r,char g,char b)
{
  bufer1[npixel*3]=r;
  bufer1[npixel*3+1]=g;
  bufer1[npixel*3+2]=b;
}

