#ifndef _lcd1602_H
#define _lcd1602_H

#define DATA_BUS P0
sbit RS =P2^0;
sbit RW =P2^1; 
sbit E  =P2^2;

// Define new types
typedef unsigned char   uchar;
typedef unsigned int    uint;

// Function Prototypes
void check_busy(void);
void write_command(uchar com);
void write_data(uchar dat);
void LCD_init(void);
void string(uchar ad ,uchar *s);
void delay(uint);

/*******************************************
    LCD1602 Driver mapped as IO peripheral
*******************************************/  
// Delay
void delay(uint j)
 { uchar i = 60;
   for(; j>0; j--)
    { while(--i);
      i = 59;
      while(--i);
      i = 60;
    }
 }



// Test the Busy bit
void check_busy(void)
 { do
    { DATA_BUS = 0xff;
      E = 0;
      RS = 0; 
      RW = 1;
      E = 1;
      delay(1); 
    } while(DATA_BUS & 0x80);
   E = 0;
 }
// Write a command
void write_command(uchar com)
 { 
 check_busy();
   RS = 0;
   RW = 0;
   E=0;
   DATA_BUS = com;
   delay(2);
   E=1;
   _nop_();
   E=0;
 }

// Write Data
void write_data(uchar dat)
 { 
 check_busy(); 
   RS=1;           
   RW=0; 
   E=0;      
   DATA_BUS=dat;          
   delay(2);      
   E=1; 
   _nop_();         
   E=0;           
 }

// Initialize LCD controller
void LCD_init(void)
 { 
   write_command(0x38); // 8-bits, 2 lines, 7x5 dots
   write_command(0x0C); // no cursor, no blink, enable display
   write_command(0x06); // auto-increment on
   write_command(0x01); // clear screen
   delay(1);
 }

// Display a string
void string(uchar ad, uchar *s)
 { 
    write_command(ad);
	while (*s){
		write_data(*s);
		s++;
	    delay(1000);

	}
	  
}
