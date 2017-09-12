
void dma_ws28(void)
{
  int c1;
  if(dma_write>(&dma_bufer[24*npk])) dma_write=dma_bufer;
  if(estado_transfer<3)
  {
  if(estado_transfer<2)
    {
    ++estado_transfer;
    c1=24;
    while(c1--) dma_write[c1*npk]=output_table[15];
    }
  dma_write[1+7*npk]=output_table[bits_transfer&15]; bits_transfer>>=4;
  dma_write[1+3*npk]=output_table[bits_transfer&15]; bits_transfer>>=4;
  dma_write[1+6*npk]=output_table[bits_transfer&15]; bits_transfer>>=4;
  dma_write[1+2*npk]=output_table[bits_transfer&15]; bits_transfer>>=4;
  dma_write[1+5*npk]=output_table[bits_transfer&15]; bits_transfer>>=4;
  dma_write[1+1*npk]=output_table[bits_transfer&15]; bits_transfer>>=4;
  dma_write[1+4*npk]=output_table[bits_transfer&15]; bits_transfer>>=4;
  dma_write[1+0*npk]=output_table[bits_transfer];
   dma_write[1+15*npk]=output_table[bits_transfer2&15]; bits_transfer2>>=4;
  dma_write[1+11*npk]=output_table[bits_transfer2&15]; bits_transfer2>>=4;
  dma_write[1+14*npk]=output_table[bits_transfer2&15]; bits_transfer2>>=4;
  dma_write[1+10*npk]=output_table[bits_transfer2&15]; bits_transfer2>>=4;
  dma_write[1+13*npk]=output_table[bits_transfer2&15]; bits_transfer2>>=4;
  dma_write[1+9*npk]=output_table[bits_transfer2&15]; bits_transfer2>>=4;
  dma_write[1+12*npk]=output_table[bits_transfer2&15]; bits_transfer2>>=4;
  dma_write[1+8*npk]=output_table[bits_transfer2];
   dma_write[1+23*npk]=output_table[bits_transfer3&15]; bits_transfer3>>=4;
  dma_write[1+19*npk]=output_table[bits_transfer3&15]; bits_transfer3>>=4;
  dma_write[1+22*npk]=output_table[bits_transfer3&15]; bits_transfer3>>=4;
  dma_write[1+18*npk]=output_table[bits_transfer3&15]; bits_transfer3>>=4;
  dma_write[1+21*npk]=output_table[bits_transfer3&15]; bits_transfer3>>=4;
  dma_write[1+17*npk]=output_table[bits_transfer3&15]; bits_transfer3>>=4;
  dma_write[1+20*npk]=output_table[bits_transfer3&15]; bits_transfer3>>=4;
  dma_write[1+16*npk]=output_table[bits_transfer3];
  dma_write+=npk*24;
  if (!get_bits()) estado_transfer=3;
  return;
  }
  if(estado_transfer++>4) { estado_transfer=255;timer.pause();  dma_write+=npk*24;;return; }
  c1=24*npk;
  while(c1--) *dma_write++=output_table[0];
  return;
}

//cpu_clks=cpu_mhz/(bps*3)-1
 void setup_ws28(int  cpu_clks)
  {
   setup_pout(&dma_ws28,cpu_clks,48*npk,0);
  }



