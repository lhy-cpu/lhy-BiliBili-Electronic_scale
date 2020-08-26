/*这是up主（刘海洋ghs）自己写的，代码不完善，还望大佬见教*/
/*仅供学习用途，若有由这些代码造成的任何损失，由使用者自行承担，开发者（刘海洋ghs）概不负责*/

#include <STC15.H>
#include "OLED.h"
#include "OLEDfont.h"
#include "input.h"

/*---------------------------------I2C---------------------------------*/
//Basic
void I2C_start () {
	OLED_SCL = 1;
	OLED_SDA = 1;
	OLED_SDA = 0;
	OLED_SCL = 0;
}

void I2C_stop () {
	OLED_SCL = 1;
	OLED_SDA = 0;
	OLED_SDA = 1;
}

void I2C_byte (unsigned char Send_byte) {
	unsigned char times;
	OLED_SCL = 0;
	for(times=0;times<8;times++) {
		OLED_SDA = Send_byte&0x80;
		Send_byte<<=1;
		OLED_SCL = 1;
		OLED_SCL = 0;
	}
}

//Write Command
void I2C_cmd (unsigned char Send_cmd) {
	I2C_start();
	I2C_byte(0x78);
	OLED_SCL = 1;
	OLED_SCL = 0;
	I2C_byte(0x00);
	OLED_SCL = 1;
	OLED_SCL = 0;
	I2C_byte(Send_cmd);
	OLED_SCL = 1;
	OLED_SCL = 0;
	I2C_stop();
}

//Write Data
void I2C_data (unsigned char Send_data) {
	I2C_start();
	I2C_byte(0x78);
	OLED_SCL = 1;
	OLED_SCL = 0;
	I2C_byte(0x40);
	OLED_SCL = 1;
	OLED_SCL = 0;
	I2C_byte(Send_data);
	OLED_SCL = 1;
	OLED_SCL = 0;
	I2C_stop();
}


/*---------------------------------OLED---------------------------------*/
//OLED Initialize
void OLED_init () {
	I2C_cmd(0xAE);
	I2C_cmd(0x40);
	I2C_cmd(0xB0);
	I2C_cmd(0xC8);
	I2C_cmd(0x81);
	I2C_cmd(0xFF);
	I2C_cmd(0xA1);
	I2C_cmd(0xA6);
	I2C_cmd(0xA8);
	I2C_cmd(0x1F);
	I2C_cmd(0xD3);
	I2C_cmd(0x00);
	I2C_cmd(0xD5);
	I2C_cmd(0xF0);
	I2C_cmd(0xD9);
	I2C_cmd(0x22);
	I2C_cmd(0xDA);
	I2C_cmd(0x02);
	I2C_cmd(0xDB);
	I2C_cmd(0x49);
	I2C_cmd(0x8D);
	I2C_cmd(0x14);
	I2C_cmd(0xAF);
	OLED_clear ();
}



//OLED Clear
void OLED_clear () {
	unsigned char m,n;
	for(m=0;m<8;m++) {
		I2C_cmd(0xB0+m);
		I2C_cmd(0x00);
		I2C_cmd(0x10);
		for(n=0;n<128;n++) I2C_data(0x00);
	}
}

//OLED Set Cur   x:0~127    y:0~31
void OLED_cur (unsigned char x,unsigned char y) {
	I2C_cmd(0xB0+y);
	I2C_cmd(((x&0xF0)>>4)|0x10);
	I2C_cmd(x&0x0F);
}

//OLED Draw 8*16 Char
void OLED_draw (unsigned char x,unsigned char y,unsigned char draw_font) {
	unsigned char m;
	OLED_cur(x,y);
	for(m=0;m<8;m++) I2C_data(font[draw_font][m]);
	OLED_cur(x,y+1);
	for(m=8;m<16;m++) I2C_data(font[draw_font][m]);
}