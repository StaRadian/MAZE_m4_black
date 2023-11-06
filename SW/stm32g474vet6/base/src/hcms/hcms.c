#include "hcms.h"

#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>

#include "stm32g4xx_hal.h"

const uint8_t FontData7x5[ 0x80 ][ 5 ] =
{	
	{0x00,0x00,0x00,0x00,0x00},		// 0
	{0x00,0x00,0x00,0x00,0x00},		// 1
	{0x00,0x00,0x00,0x00,0x00},		// 2
	{0x00,0x00,0x00,0x00,0x00},		// 3
	{0x00,0x00,0x00,0x00,0x00},		// 4
	{0x00,0x00,0x00,0x00,0x00},		// 5
	{0x00,0x00,0x00,0x00,0x00},		// 6
	{0x00,0x00,0x00,0x00,0x00},		// 7
	{0x00,0x00,0x00,0x00,0x00},		// 8		
	{0x00,0x00,0x00,0x00,0x00},		// 9
	{0x00,0x00,0x00,0x00,0x00},		// a
	{0x00,0x00,0x00,0x00,0x00},		// b
	{0x00,0x00,0x00,0x00,0x00},		// c
	{0x00,0x00,0x00,0x00,0x00},		// d
	{0x00,0x00,0x00,0x00,0x00},		// e
	{0x00,0x00,0x00,0x00,0x00},		// f
	{0x00,0x00,0x00,0x00,0x00},		//  10
	{0x00,0x00,0x00,0x00,0x00},		//  11
	{0x00,0x00,0x00,0x00,0x00},		//  12
	{0x00,0x00,0x00,0x00,0x00},		//  13
	{0x00,0x00,0x00,0x00,0x00},		//  14
	{0x00,0x00,0x00,0x00,0x00},		//  15
	{0x00,0x00,0x00,0x00,0x00},		//  16
	{0x00,0x00,0x00,0x00,0x00},		//  17
	{0x00,0x00,0x00,0x00,0x00},		//  18		
	{0x00,0x00,0x00,0x00,0x00},		//  19
	{0x00,0x00,0x00,0x00,0x00},		//  1a
	{0x00,0x00,0x00,0x00,0x00},		//  1b
	{0x00,0x00,0x00,0x00,0x00},		//  1c
	{0x00,0x00,0x00,0x00,0x00},		//  1d
	{0x00,0x00,0x00,0x00,0x00},		//  1e
	{0x00,0x00,0x00,0x00,0x00},		//  1f							
	{0x00,0x00,0x00,0x00,0x00},		// 20   blank
	{0x00,0x00,0x7b,0x00,0x00},		// 21   !
	{0x00,0x70,0x00,0x70,0x00},		// 22   "
	{0x14,0x7f,0x14,0x7f,0x14},		// 23   #
	{0x24,0x2a,0x7f,0x2a,0x12},		// 24   $
	{0x23,0x13,0x08,0x64,0x62},		// 25   %
	{0x05,0x22,0x55,0x49,0x36},		// 26   &
	{0x00,0x00,0x60,0x50,0x00},		// 27   '
	{0x00,0x41,0x22,0x1c,0x00},		// 28   (
	{0x00,0x1c,0x22,0x41,0x00},		// 29   )
	{0x14,0x08,0x3e,0x08,0x14},		// 2A   *
	{0x08,0x08,0x3e,0x08,0x08},		// 2B   +
	{0x00,0x00,0x06,0x05,0x00},		// 2C   ,
	{0x08,0x08,0x08,0x08,0x08},		// 2D   -
	{0x00,0x00,0x03,0x03,0x00},		// 2E   .
	{0x20,0x10,0x08,0x04,0x02},		// 2F   / 										  
	{0x3e,0x51,0x49,0x45,0x3e},		//  30	0
	{0x00,0x01,0x7f,0x21,0x00},		//  31	1
	{0x31,0x49,0x45,0x43,0x21},		//  32	2
	{0x46,0x69,0x51,0x41,0x42},		//  33	3
	{0x04,0x7f,0x24,0x14,0x0c},		//  34	4
	{0x4e,0x51,0x51,0x51,0x72},		//  35	5
	{0x06,0x49,0x49,0x29,0x1e},		//  36	6
	{0x70,0x48,0x47,0x40,0x40},		//  37	7
	{0x36,0x49,0x49,0x49,0x36},		//  38	8
	{0x3c,0x4a,0x49,0x49,0x30},		//  39	9
	{0x00,0x00,0x36,0x36,0x00},		//  3A	:
	{0x00,0x00,0x36,0x35,0x00},		//  3B	;
	{0x00,0x41,0x22,0x14,0x08},		//  3C	<
	{0x14,0x14,0x14,0x14,0x14},		//  3D	=
	{0x08,0x14,0x22,0x41,0x00},		//  3E	>
	{0x30,0x48,0x44,0x45,0x20},		//  3F	?
	{0x32,0x49,0x79,0x41,0x3e},		// 40	@		 
	{0x3f,0x44,0x44,0x44,0x3f},		// 41	A		 
	{0x36,0x49,0x49,0x49,0x7f},		// 42	B		 
	{0x22,0x41,0x41,0x41,0x3e},		// 43	C		 
	{0x1c,0x22,0x41,0x41,0x7f},		// 44	D		 
	{0x41,0x49,0x49,0x49,0x7f},		// 45	E		 
	{0x40,0x48,0x48,0x48,0x7f},		// 46	F		 
	{0x2f,0x49,0x49,0x41,0x3e},		// 47	G		 
	{0x7f,0x08,0x08,0x08,0x7f},		// 48	H		 
	{0x00,0x41,0x7f,0x41,0x00},		// 49	I		 
	{0x40,0x7e,0x41,0x01,0x02},		// 4A	J		 
	{0x41,0x22,0x14,0x08,0x7f},		// 4B	K		 
	{0x01,0x01,0x01,0x01,0x7f},		// 4C	L		 
	{0x7f,0x20,0x18,0x20,0x7f},		// 4D	M		 
	{0x7f,0x04,0x08,0x10,0x7f},		// 4E	N		 
	{0x3e,0x41,0x41,0x41,0x3e},		// 4F	O		 
	{0x30,0x48,0x48,0x48,0x7f},		//  50	P	 
	{0x3d,0x42,0x45,0x41,0x3e},		//  51	Q	 
	{0x31,0x4a,0x4c,0x48,0x7f},		//  52	R	 
	{0x46,0x49,0x49,0x49,0x31},		//  53	S	 
	{0x40,0x40,0x7f,0x40,0x40},		//  54	T	 
	{0x7e,0x01,0x01,0x01,0x7e},		//  55	U	 
	{0x7c,0x02,0x01,0x02,0x7c},		//  56	V	 
	{0x7e,0x01,0x0e,0x01,0x7e},		//  57	W	 
	{0x63,0x14,0x08,0x14,0x63},		//  58	X	 
	{0x70,0x08,0x07,0x08,0x70},		//  59	Y	 
	{0x61,0x51,0x49,0x45,0x43},		//  5A	Z	 
	{0x00,0x41,0x41,0x7f,0x00},		//  5B	[	 
	{0x54,0x34,0x1f,0x34,0x54},		//  5C	|	 
	{0x00,0x7f,0x41,0x41,0x00},		//  5D	]	 
	{0x10,0x20,0x40,0x20,0x10},		//  5E	^	 
	{0x01,0x01,0x01,0x01,0x01},		//  5F	_	 
	{0x00,0x10,0x20,0x40,0x00},		// 60	'	 
	{0x0f,0x15,0x15,0x15,0x02},		// 61	a	 
	{0x0e,0x11,0x11,0x09,0x7f},		// 62	b	 
	{0x02,0x11,0x11,0x11,0x0e},		// 63	c	 
	{0x7f,0x09,0x11,0x11,0x0e},		// 64	d	 
	{0x0c,0x15,0x15,0x15,0x0e},		// 65	e	 
	{0x20,0x40,0x48,0x3f,0x08},		// 66	f	 
	{0x3e,0x25,0x25,0x25,0x18},		// 67	g	 
	{0x0f,0x10,0x10,0x08,0x7f},		// 68	h	 
	{0x00,0x01,0x5f,0x11,0x00},		// 69	i	 
	{0x00,0x5e,0x11,0x01,0x02},		// 6A	j	 
	{0x00,0x11,0x0a,0x04,0x7f},		// 6B	k	 
	{0x00,0x01,0x7f,0x41,0x00},		// 6C	l	 
	{0x0f,0x10,0x0c,0x10,0x1f},		// 6D	m	 
	{0x0f,0x10,0x10,0x08,0x1f},		// 6E	n	 
	{0x0e,0x11,0x11,0x11,0x0e},		// 6F	o	 
	{0x08,0x14,0x14,0x14,0x1f},		//  70	p	 
	{0x1f,0x0c,0x14,0x14,0x08},		//  71	q	 
	{0x08,0x10,0x10,0x08,0x1f},		//  72	r	 
	{0x02,0x15,0x15,0x15,0x09},		//  73	s	 
	{0x02,0x01,0x11,0x7e,0x10},		//  74	t	 
	{0x1f,0x02,0x01,0x01,0x1e},		//  75	u	 
	{0x1c,0x02,0x01,0x02,0x1c},		//  76	v	 
	{0x1e,0x01,0x0e,0x01,0x1e},		//  77	w	 
	{0x11,0x0a,0x04,0x0a,0x11},		//  78	x	 
	{0x1e,0x05,0x05,0x05,0x18},		//  79	y	 
	{0x11,0x19,0x15,0x13,0x11},		//  7A	z	 
	{0x00,0x41,0x36,0x08,0x00},		//  7B	{	 
	{0x00,0x00,0x7f,0x00,0x00},		//  7C	|	 
	{0x00,0x08,0x36,0x41,0x00},		//  7D	}	
	{0x08,0x04,0x04,0x08,0x04},		//	7E  ~    
	{0x00,0x00,0x00,0x00,0x00},		//	7F
};

//HCMS_option
#define HCMS_SECTION 	(8)

#define PIN_HCMS_CLK    (GPIO_PIN_5)
#define PIN_HCMS_DA     (GPIO_PIN_6)
#define PIN_HCMS_RS     (GPIO_PIN_7)
#define PIN_HCMS_CE     (GPIO_PIN_6)
#define PIN_HCMS_RESET  (GPIO_PIN_9)

//GPIO Set / HIGH
#define HCMS_CLK_H 		(GPIOE->BSRR = (uint32_t)PIN_HCMS_CLK)
#define HCMS_DA_H 		(GPIOB->BSRR = (uint32_t)PIN_HCMS_DA)
#define HCMS_RS_H 		(GPIOB->BSRR = (uint32_t)PIN_HCMS_RS)
#define HCMS_CE_H 		(GPIOE->BSRR = (uint32_t)PIN_HCMS_CE)
#define HCMS_RESET_H 	(GPIOB->BSRR = (uint32_t)PIN_HCMS_RESET)

//GPIO CLR / LOW
#define HCMS_CLK_L 		(GPIOE->BRR = (uint32_t)PIN_HCMS_CLK)
#define HCMS_DA_L 		(GPIOB->BRR = (uint32_t)PIN_HCMS_DA)
#define HCMS_RS_L 		(GPIOB->BRR = (uint32_t)PIN_HCMS_RS)
#define HCMS_CE_L 		(GPIOE->BRR = (uint32_t)PIN_HCMS_CE)
#define HCMS_RESET_L 	(GPIOB->BRR = (uint32_t)PIN_HCMS_RESET)

void hcms_ctl_reg_load( char ctrl_reg )
{
    HCMS_RS_H;
    HCMS_CLK_H;
    HCMS_CE_L;
	
	//Load control register
	for( int16_t cnt = 0 ; cnt < 8 ; cnt++ )
	{
		HCMS_CLK_L;
		
		if( ctrl_reg & 0x80 )	HCMS_DA_H;
		else					HCMS_DA_L;

		HCMS_CLK_H;
		ctrl_reg <<= 1;
	}
	
	//Latch data to control word
	HCMS_CE_H;
	HCMS_CLK_L;
	HCMS_RS_L;
}

void hcms_data_load( char *buf )
{
	//select Dot register
    HCMS_CLK_H;
    HCMS_CE_L;
    uint8_t data;
	//Load control register
	for( int16_t i = 0 ; i < HCMS_SECTION ; i++ )
	{
        for( int16_t j = 4 ; j >= 0 ; j-- )
        {
            HCMS_CLK_L;
            data = FontData7x5[*buf][j];
            HCMS_CLK_H;
            for( int16_t k = 0 ; k < 7 ; k++)
            {
                HCMS_CLK_L;
                if(data & 0x01)	HCMS_DA_H;
                else			HCMS_DA_L;
                HCMS_CLK_H;
                data >>= 1;
            }
        }
        buf++;
	}
	HCMS_CE_H;
	HCMS_CLK_L;
}

//making later?
void hcms_dot_load( char *buf )
{

}

void hcms_init( void )
{
	HCMS_RESET_L;
	HCMS_CE_H;
	HCMS_RS_L;
	HCMS_CLK_H;
	HCMS_RESET_H;

	hcms_ctl_reg_load( 0x81 );

	/*
	7: 0 to Select Control
	6: Sleep mode
	5:4 Peak Current Brightness Control
	3:0 PWM Brightness Control
	*/
	hcms_ctl_reg_load( 0x6d );	//non sleep mode bright level adjustment.
}

void hcmsprintf( char *pchar , ... )
{
    char buf[ 16 ] = { 0 , };
	
    va_list va_ptr;
	
    va_start( va_ptr , pchar );	 
    vsprintf( buf , pchar , va_ptr );
    va_end( va_ptr );
	
    hcms_data_load( buf );
}

