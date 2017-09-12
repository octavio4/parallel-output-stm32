byte apa_brightness=31;
void dma_apa(void)
{
  int c1;
  if(dma_write>(&dma_bufer[32])) dma_write=dma_bufer;

  if(estado_transfer<3)
  {
  if(estado_transfer<2)
  {
  ++estado_transfer;
  dma_write[0]=output_table[15];
  dma_write[1]=output_table[15];
  dma_write[2]=output_table[15];
  if(apa_brightness&16) dma_write[3]=output_table[15];
  else dma_write[3]=output_table[0];
  if(apa_brightness&8) dma_write[4]=output_table[15];
  else dma_write[4]=output_table[0];
  if(apa_brightness&4) dma_write[5]=output_table[15];
  else dma_write[5]=output_table[0];
  if(apa_brightness&2) dma_write[6]=output_table[15];
  else dma_write[6]=output_table[0];
  if(apa_brightness&1) dma_write[7]=output_table[15];
  else dma_write[7]=output_table[0];
  }
  dma_write[8+7]=output_table[bits_transfer&15]; bits_transfer>>=4;
  dma_write[8+3]=output_table[bits_transfer&15]; bits_transfer>>=4;
  dma_write[8+6]=output_table[bits_transfer&15]; bits_transfer>>=4;
  dma_write[8+2]=output_table[bits_transfer&15]; bits_transfer>>=4;
  dma_write[8+5]=output_table[bits_transfer&15]; bits_transfer>>=4;
  dma_write[8+1]=output_table[bits_transfer&15]; bits_transfer>>=4;
  dma_write[8+4]=output_table[bits_transfer&15]; bits_transfer>>=4;
  dma_write[8+0]=output_table[bits_transfer];
   dma_write[16+7]=output_table[bits_transfer2&15]; bits_transfer2>>=4;
  dma_write[16+3]=output_table[bits_transfer2&15]; bits_transfer2>>=4;
  dma_write[16+6]=output_table[bits_transfer2&15]; bits_transfer2>>=4;
  dma_write[16+2]=output_table[bits_transfer2&15]; bits_transfer2>>=4;
  dma_write[16+5]=output_table[bits_transfer2&15]; bits_transfer2>>=4;
  dma_write[16+1]=output_table[bits_transfer2&15]; bits_transfer2>>=4;
  dma_write[16+4]=output_table[bits_transfer2&15]; bits_transfer2>>=4;
  dma_write[16+0]=output_table[bits_transfer2];
   dma_write[24+7]=output_table[bits_transfer3&15]; bits_transfer3>>=4;
  dma_write[24+3]=output_table[bits_transfer3&15]; bits_transfer3>>=4;
  dma_write[24+6]=output_table[bits_transfer3&15]; bits_transfer3>>=4;
  dma_write[24+2]=output_table[bits_transfer3&15]; bits_transfer3>>=4;
  dma_write[24+5]=output_table[bits_transfer3&15]; bits_transfer3>>=4;
  dma_write[24+1]=output_table[bits_transfer3&15]; bits_transfer3>>=4;
  dma_write[24+4]=output_table[bits_transfer3&15]; bits_transfer3>>=4;
  dma_write[24+0]=output_table[bits_transfer3];
  dma_write+=32;
  if (!get_bits()) estado_transfer=3;
  return;
  }
  if(estado_transfer++>4) { estado_transfer=255;timer.pause();  dma_write+=32;return; }
  c1=32;
  do { *dma_write++=output_table[0]; } while(--c1);
  return;
}

//cpu_clks=cpu_mhz/bps-1
void setup_apa(int  cpu_clks)
{
  pinMode(PA2,PWM);
  setup_pout(&dma_apa,cpu_clks,64,0);
  }

