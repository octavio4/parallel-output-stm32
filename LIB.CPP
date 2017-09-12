uint32_t red,green,blue,bits_transfer,bits_transfer2,bits_transfer3;
enum {RGB,GRB,RBG,BRG,BGR,GBR};
void transpose() {
  uint32_t  t,x,y,z;
switch(led_order)
  {
   case 0:
    x=red;y=green;z=blue;break;
   case 1:
    y=red;x=green;z=blue;break;
   case 2:
    x=red;z=green;y=blue;break;
   case 3:
    y=red;z=green;x=blue;break;
   case 4:
    z=red;y=green;x=blue;break;
   case 5:
    z=red;x=green;y=blue;break;
       
  }
   // pre-transform x
  t = (x ^ (x >> 7)) & 0x00AA00AA;  x = x ^ t ^ (t << 7);
  t = (x ^ (x >>14)) & 0x0000CCCC;
  bits_transfer = x ^ t ^ (t <<14);
   t = (y ^ (y >> 7)) & 0x00AA00AA;  y = y ^ t ^ (t << 7);
  t = (y ^ (y >>14)) & 0x0000CCCC;
  bits_transfer2 = y ^ t ^ (t <<14);
   t = (z ^ (z >> 7)) & 0x00AA00AA;  z = z ^ t ^ (t << 7);
  t = (z ^ (z >>14)) & 0x0000CCCC;
  bits_transfer3 = z ^ t ^ (t <<14);
}

#define R red
#define G green
#define B blue

bool get_rgb44(void)
{
  if (dma_count<dma_size)
  {
  R=dma_read[0]+(dma_read[3]<<8)+(dma_read[6]<<16)+(dma_read[9]<<24);
  G=dma_read[1]+(dma_read[4]<<8)+(dma_read[7]<<16)+(dma_read[10]<<24);
  B=dma_read[2]+(dma_read[5]<<8)+(dma_read[8]<<16)+(dma_read[11]<<24);
  dma_read+=12;
  dma_count+=12;
  transpose();
  return true;
  }
return false;
}

bool get_rgb34(void)
{
 if (dma_count<dma_size)
  {
  R=dma_read[0]+(dma_read[3]<<8)+(dma_read[6]<<16);
  G=dma_read[1]+(dma_read[4]<<8)+(dma_read[7]<<16);
  B=dma_read[2]+(dma_read[5]<<8)+(dma_read[8]<<16);
  dma_read+=9;
  dma_count+=9;
  transpose();
  return true;
  }
 return false;

}

bool get_rgb24(void)
{
  if (dma_count<dma_size)
  {
  R=dma_read[0]+(dma_read[3]<<8);
  G=dma_read[1]+(dma_read[4]<<8);
  B=dma_read[2]+(dma_read[5]<<8);
  dma_read+=6;
  dma_count+=6;

  transpose();
  return true;
  }
return false;
}
bool get_rgb14(void)
{
  if (dma_count<dma_size)
  {
  R=dma_read[0];
  G=dma_read[1];
  B=dma_read[2];
  dma_read+=3;
  dma_count+=3;
  transpose();
  return true;
  }
return false;
}

 




