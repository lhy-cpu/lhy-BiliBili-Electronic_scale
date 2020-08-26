/*这是up主（刘海洋ghs）自己写的，代码不完善，还望大佬见教*/
/*仅供学习用途，若有由这些代码造成的任何损失，由使用者自行承担，开发者（刘海洋ghs）概不负责*/

#ifndef _OLED_H
#define _OLED_H

void OLED_init();     //oled初始化
void OLED_draw(unsigned char x,unsigned char y,unsigned char draw_font);     //绘图
void OLED_clear();    //清屏

#endif