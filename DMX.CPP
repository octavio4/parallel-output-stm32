void dma_dmx(void)
{
	int c1;
	if(dma_write>(&dma_bufer[33])) dma_write=dma_bufer;
	if(estado_transfer==2)
		{
      
  dma_write[1+7]=output_table[bits_transfer&15]; bits_transfer>>=4;
  dma_write[1+3]=output_table[bits_transfer&15]; bits_transfer>>=4;
  dma_write[1+6]=output_table[bits_transfer&15]; bits_transfer>>=4;
  dma_write[1+2]=output_table[bits_transfer&15]; bits_transfer>>=4;
  dma_write[1+5]=output_table[bits_transfer&15]; bits_transfer>>=4;
  dma_write[1+1]=output_table[bits_transfer&15]; bits_transfer>>=4;
  dma_write[1+4]=output_table[bits_transfer&15]; bits_transfer>>=4;
  dma_write[1+0]=output_table[bits_transfer];
   dma_write[12+7]=output_table[bits_transfer2&15]; bits_transfer2>>=4;
  dma_write[12+3]=output_table[bits_transfer2&15]; bits_transfer2>>=4;
  dma_write[12+6]=output_table[bits_transfer2&15]; bits_transfer2>>=4;
  dma_write[12+2]=output_table[bits_transfer2&15]; bits_transfer2>>=4;
  dma_write[12+5]=output_table[bits_transfer2&15]; bits_transfer2>>=4;
  dma_write[12+1]=output_table[bits_transfer2&15]; bits_transfer2>>=4;
  dma_write[12+4]=output_table[bits_transfer2&15]; bits_transfer2>>=4;
  dma_write[12+0]=output_table[bits_transfer2];
   dma_write[23+7]=output_table[bits_transfer3&15]; bits_transfer3>>=4;
  dma_write[23+3]=output_table[bits_transfer3&15]; bits_transfer3>>=4;
  dma_write[23+6]=output_table[bits_transfer3&15]; bits_transfer3>>=4;
  dma_write[23+2]=output_table[bits_transfer3&15]; bits_transfer3>>=4;
  dma_write[23+5]=output_table[bits_transfer3&15]; bits_transfer3>>=4;
  dma_write[23+1]=output_table[bits_transfer3&15]; bits_transfer3>>=4;
  dma_write[23+4]=output_table[bits_transfer3&15]; bits_transfer3>>=4;
  dma_write[23+0]=output_table[bits_transfer3];
  dma_write[9]=output_table[15]; //stop bits 
  dma_write[10]=output_table[15]; 
  dma_write[20]=output_table[15]; 
  dma_write[21]=output_table[15]; 
  dma_write[31]=output_table[15]; 
  dma_write[32]=output_table[15]; 
  dma_write+=33;
  if (!get_bits()) estado_transfer=3;
  return;
		}

	if(estado_transfer<2) //secuencia de inicio
		{
		c1=33;
		do{ *dma_write++=output_table[0];} while(--c1);
		if(estado_transfer++)
			{
			dma_write-=33;
			dma_write[18]=output_table[15];
			dma_write[19]=output_table[15];
			dma_write[20]=output_table[15];
			dma_write[21]=output_table[15];
			dma_write[31]=output_table[15];
			dma_write[32]=output_table[15];
			dma_write+=33;
			}
		return;
		}

  if(estado_transfer++>4) { estado_transfer=255;timer.pause(); dma_write+=33;return; }
  c1=33;
  do { *dma_write++=output_table[15]; } while(--c1);
  return;

}


void setup_dmx(int  cpu_clks)
{
  setup_pout(&dma_dmx,cpu_clks,66,15);
}


