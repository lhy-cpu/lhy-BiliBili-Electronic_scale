/*这是up主（刘海洋ghs）自己写的，代码不完善，还望大佬见教*/
/*仅供学习用途，若有由这些代码造成的任何损失，由使用者自行承担，开发者（刘海洋ghs）概不负责*/

#ifndef _input_H
#define _input_H

#include <STC15.H>

//四个按钮
sbit set = P3^6;   //设置
sbit ac = P3^7;    //清除
sbit up = P3^3;    //上（减）
sbit down = P3^2;  //下（加）

//HX711
sbit HX711_SCK = P1^4;  //HX711_SCK
sbit HX711_DAT = P1^5;   //HX711_DATA

//0.91'OLED
sbit OLED_SCL = P1^2;
sbit OLED_SDA = P1^3;

void Swt();

#endif