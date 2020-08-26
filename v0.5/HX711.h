/*这是up主（刘海洋ghs）自己写的，代码不完善，还望大佬见教*/
/*仅供学习用途，若有由这些代码造成的任何损失，由使用者自行承担，开发者（刘海洋ghs）概不负责*/

#ifndef _HX711_H
#define _HX711_H

#define K_M 0.96
#define B_M 0
#define Z_M 1     //A通道128增益
//#define Z_M 2     //B通道32增益
//#define Z_M 3     //A通道64增益
unsigned long Redata ();     //读取数据
//unsigned long RedataAverage(unsigned char times);     //读取数据并计算times次的平均值（速度慢，慎用）

#endif