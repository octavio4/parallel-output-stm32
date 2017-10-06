

dma_tube_config tube_config={
  dma_bufer,
  DMA_SIZE_32BITS,
  &GPIOA->regs->BSRR,
    DMA_SIZE_32BITS,
    dma_bufer_size,
    DMA_CFG_SRC_INC | DMA_CFG_CIRC | DMA_CFG_CMPLT_IE | DMA_CFG_HALF_CMPLT_IE,
    0,
    DMA_REQ_SRC_TIM2_CH3,
  };

void setup_pout(void (*irq_transfer)(void),int time_transfer,int dma_xfers,int init)
{
  dma_bufer_size=dma_xfers;
  dma_write=dma_bufer; 
   if (DEBUG) Serial.print("preparing the DMA...");
  dma_init(DMA1); // turn DMA on
  tube_config.tube_nr_xfers =dma_xfers;  // dma_bufer_size; // configure DMA nr of transfers
  int ret = dma_tube_cfg(DMA1, DMA_CH1, &tube_config);
  if ( ret>0 ) {
 if (DEBUG)   Serial.print("FATAL ERROR: halt due to DMA configuration error: "); Serial.println(ret,HEX);
    while ( 1 );  // halted
  }
  dma_clear_isr_bits(DMA1, DMA_CH1);
  dma_attach_interrupt(DMA1,DMA_CH1,irq_transfer);
  //nvic_irq_set_priority(nvic_irq_num irqn, uint8 0(max priority)-15(no priority))
  nvic_irq_set_priority(NVIC_DMA_CH1,14);
  dma_enable(DMA1, DMA_CH1);  // Enable the DMA tube. It will now begin serving requests.
  if (DEBUG) Serial.println("done.");

  timer.pause();
  //timer.setPeriod(4);
  timer.setPrescaleFactor(1);
  timer.setOverflow(time_transfer);
  timer.setMode(3,TIMER_PWM);
  timer.setCompare(TIMER_CH3,time_transfer>>1);
  TIMER2_BASE->DIER=TIMER_DIER_CC3DE; //enable dma request
int c1=0;
long *dma_buf=dma_bufer;
while(c1++<dma_bufer_size) *dma_buf++=output_table[init];
estado_transfer=255;dma_count=0;
 }

void start_transfer(uint32_t nb)
{
while(estado_transfer<255);
dma_size=nb;
dma_count=0;
estado_transfer=0;
get_bits();
timer.resume();
}


/*
 * pin0 is d+ channel0         only the first pin can be 0
 * pin1 is d- channel0  optional,set 0 if not used
 * pin2 is d+ channel1  optional
 * ...
 * pint is d- channel3  optional
 */

void setup_output_table(int pin0,int pin1,int pin2,int pin3,int pin4,int pin5,int pin6,int pin7)
{
  long outpt;
  int c1=16;
  while(c1--){
     outpt=0;
  if (c1&1) { outpt|=1<<pin0;
	     if(pin1) outpt|=1<<(pin1+16);
	     }
  else  {
	outpt|=1<<(pin0+16);
	if(pin1) outpt|=+1<<pin1;
	}
  if (c1&2)
	{
	if(pin2) outpt|=1<<pin2;
	if(pin3) outpt|=1<<(pin3+16);
	}
  else  {
	if(pin2) outpt|=1<<(pin2+16);
	if(pin3) outpt|=+1<<pin3;
	}
  if (c1&4)
	{
	if(pin4) outpt|=1<<pin2;
	if(pin5) outpt|=1<<(pin3+16);
	}
  else  {
	if(pin4) outpt|=1<<(pin2+16);
	if(pin5) outpt|=+1<<pin3;
	}
  if (c1&8)
	{
	if(pin6) outpt|=1<<pin2;
	if(pin7) outpt|=1<<(pin3+16);
	}
  else  {
	if(pin6) outpt|=1<<(pin2+16);
	if(pin7) outpt|=+1<<pin3;
	}
   output_table[c1]=outpt;
  }
}



