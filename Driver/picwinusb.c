#include <18F4550.h>
#device ADC=10
#fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL5,CPUDIV1,VREGEN
#use delay(clock=48000000)

#define USB_HID_DEVICE     FALSE             
#define USB_EP1_TX_ENABLE  USB_ENABLE_BULK   
#define USB_EP1_RX_ENABLE  USB_ENABLE_BULK   
#define USB_EP1_TX_SIZE    32                
#define USB_EP1_RX_SIZE    32                 

  
#include <PicWinUSB.h>     
          
#use fast_io(a) 
#use fast_io(b)
#use fast_io(c)
#use fast_io(d)


static unsigned int16 adc=0;

static unsigned int16 adc1=0;
static unsigned int16 adc2=0;
static unsigned int16 adc3=0;
static unsigned int16 adc4=0;
static unsigned int16 adc5=0;
static unsigned int16 adc6=0;
static unsigned int16 adc7=0;
static unsigned int16 adc8=0;
static unsigned int16 adc9=0;
static unsigned int16 adc10=0;
static unsigned int16 adc11=0;
static unsigned int16 adc12=0;
static unsigned int16 adc13=0;


unsigned int16 ADC_Read(byte channel)
{
   unsigned int16 value=0;
   set_adc_channel(channel);
   delay_us(10);
   value = read_adc();
   return value;
} 

void main(void) {

   int8 iBuff[32];                   //buffers
   int8 oBuff[32];
      
   setup_adc_ports(ALL_ANALOG);
   setup_adc(ADC_CLOCK_INTERNAL);
   set_tris_a(0xFF);
   set_tris_b(0xFF);
   set_tris_c(0xFF);
   set_tris_d(0x00);
   
   output_low(pin_d0);
   output_low(pin_d1);
   output_low(pin_d2);

   usb_init();

   usb_task();
   
   usb_wait_for_enumeration();//Wait until the device is ready
   
   int k=0;  
   int i=0;
   while (TRUE)
   {
      if(usb_enumerated())// PicWinUSB is enumerated?
      {
      output_high(pin_d0);
         if (usb_kbhit(1))// EP has data?
         {
            usb_get_packet(1, iBuff, 32); // Read 4 byte packet from EP 1            
         }
               if(iBuff[0] == 1)//Connect., if equal zero, disconnect
               {
                    output_high(pin_d1);
                        if(iBuff[1]==1)
                        {                       
                           output_high(pin_d2);
                           //ch-0
                           adc1=ADC_Read(0);
                           oBuff[0] = make8(adc1,0);
                           oBuff[1] = make8(adc1,1);
                           adc1=0;
                           //ch-1
                           adc2=ADC_Read(1);
                           oBuff[2] = make8(adc2,0);
                           oBuff[3] = make8(adc2,1);
                           adc2=0;
                           //ch-2
                           adc3=ADC_Read(2);
                           oBuff[4] = make8(adc3,0);
                           oBuff[5] = make8(adc3,1);
                           adc3=0;
                           //ch-3
                           adc4=ADC_Read(3);
                           oBuff[6] = make8(adc4,0);
                           oBuff[7] = make8(adc4,1);
                           adc4=0;
                           //ch-4
                           adc5=ADC_Read(4);
                           oBuff[8] = make8(adc5,0);
                           oBuff[9] = make8(adc5,1);
                           adc5=0;
                           //ch-5
                           adc6=ADC_Read(5);
                           oBuff[10] = make8(adc6,0);
                           oBuff[11] = make8(adc6,1);
                           adc6=0;
                           //ch-6
                           adc7=ADC_Read(6);
                           oBuff[12] = make8(adc7,0);
                           oBuff[13] = make8(adc7,1);
                           adc7=0;
                           //ch-7
                           adc8=ADC_Read(7);
                           oBuff[14] = make8(adc8,0);
                           oBuff[15] = make8(adc8,1);
                           adc8=0;
                           //ch-8
                           adc9=ADC_Read(8);
                           oBuff[16] = make8(adc9,0);
                           oBuff[17] = make8(adc9,1);
                           adc9=0;
                           //ch-9
                           adc10=ADC_Read(9);
                           oBuff[18] = make8(adc10,0);
                           oBuff[19] = make8(adc10,1);
                           adc10=0;
                           //ch-10
                           adc11=ADC_Read(10);
                           oBuff[20] = make8(adc11,0);
                           oBuff[21] = make8(adc11,1);
                           adc11=0;
                           //ch-11
                           adc12=ADC_Read(11);
                           oBuff[22] = make8(adc12,0);
                           oBuff[23] = make8(adc12,1);
                           adc12=0;
                           //ch-12
                           adc13=ADC_Read(12);
                           oBuff[24] = make8(adc13,0);
                           oBuff[25] = make8(adc13,1);
                           adc13=0; 
              
                           usb_put_packet(1, oBuff, 32, USB_DTS_TOGGLE); // Send 4 byte packet to EP 1
                        }
                        else
                        {
                           output_low(pin_d2);
                        }
                  }
                  else
                  {
                     output_low(pin_d1);
                  }
         }        
      }     
   }

