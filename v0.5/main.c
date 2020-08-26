/*这是up主（刘海洋ghs）自己写的，代码不完善，还望大佬见教*/
/*仅供学习用途，若有由这些代码造成的任何损失，由使用者自行承担，开发者（刘海洋ghs）概不负责*/
/*元件清单

	测试MCU型号：
			STC15W408AS——DIP16---------------*1
	ADC转换：
			HX711模块------------------------*1
	显示：
			0.91'OLED模块（I2C通讯）---------*1
	传感器：
			HL-8型称重传感器-----------------*1
	按钮：
			轻触开关-------------------------*4
	洞洞板、电池、支架等……
*/

/*由于up主特殊原因（主要因为懒[doge]），整个源码中注释比较少，相信来看源码的观众个个都是大神*/
/*经测试可用*/

#include <STC15.H>
#include <math.h>
#include "HX711.h"
#include "OLED.h"
#include "Delay.h"
#include "input.h"

bit set_last,set_now,ac_last,ac_now,up_last,up_now,down_last,down_now,isset,seter_2;
float k;
char b;
unsigned char line,seter_1;
unsigned long ADC_value,weight,chu,wmax,wmin;

void main() {
	line = 0;
	k = K_M;
	b = B_M;
	seter_1 = 0;
	seter_2 = 0;
	wmax = 0;
	wmin = 0;
	set_last=1;
	ac_last=1;
	up_last=1;
	down_last=1;
	isset = 0;
	OLED_init();
	chu = Redata();                                //不同之处
	while (1) {
		Swt();
		if(!seter_2) seter_1++;
		else seter_1--;
		if(seter_1 == 2) seter_2 = 1;
		if(seter_1 == 0) seter_2 = 0;
		ADC_value = Redata();                      //不同之处
		weight = abs(ADC_value-chu)/100*k+b;       //不同之处
		if(weight > wmax) wmax=weight;
		if(weight < wmin) wmin=weight;
		
		
/*---------------------------------page1---------------------------------*/
	
		if(line == 0) {
			OLED_draw(120,0,10);
			OLED_draw(120,2,11);
			OLED_draw(0,0,25);     //"m"
			OLED_draw(9,0,16);     //"="
			OLED_draw(104,2,24);     //"k"
			OLED_draw(113,2,22);     //"g"
			OLED_draw(45,2,weight%100000/10000);
			OLED_draw(54,2,weight%10000/1000);
			OLED_draw(63,2,18);     //"."
			OLED_draw(72,2,weight%1000/100);
			OLED_draw(81,2,weight%100/10);
			OLED_draw(90,2,weight%10/1);
			
		}
		
		
/*---------------------------------page2---------------------------------*/
		
		if(line==1 || line==2) {
			OLED_draw(120,0,12);
			OLED_draw(120,2,13);
			OLED_draw(9,0,25);     //"m"
			OLED_draw(18,0,20);     //"a"
			OLED_draw(27,0,27);     //"x"
			OLED_draw(36,0,16);     //"="
			
			OLED_draw(9,2,25);     //"m"
			OLED_draw(18,2,23);     //"i"
			OLED_draw(27,2,26);     //"n"
			OLED_draw(36,2,16);     //"="
			
			OLED_draw(104,0,24);     //"k"
			OLED_draw(113,2,22);     //"g"
			
			OLED_draw(104,0,24);     //"k"
			OLED_draw(113,2,22);     //"g"
			
			OLED_draw(45,0,wmax%100000/10000);
			OLED_draw(54,0,wmax%10000/1000);
			OLED_draw(63,0,18);     //"."
			OLED_draw(72,0,wmax%1000/100);
			OLED_draw(81,0,wmax%100/10);
			OLED_draw(90,0,wmax%10/1);
			OLED_draw(45,2,wmin%100000/10000);
			OLED_draw(54,2,wmin%10000/1000);
			OLED_draw(63,2,18);     //"."
			OLED_draw(72,2,wmin%1000/100);
			OLED_draw(81,2,wmin%100/10);
			OLED_draw(90,2,wmin%10/1);
			if(line == 1) {
				OLED_draw(0,2,19);     //">"
				OLED_draw(0,0,17);     //" "
			}
			if(line == 2) {
				OLED_draw(0,0,19);     //">"
				OLED_draw(0,2,17);     //" "
			}
		}
		
		
/*---------------------------------page3---------------------------------*/

		if(line==3 || line==4) {
			OLED_draw(120,0,14);
			OLED_draw(120,2,15);
			if(k<0) OLED_draw(27,0,28);     //"-"
			else OLED_draw(27,0,19);     //" "
			if(b<0) OLED_draw(27,2,28);     //"-"
			else OLED_draw(27,2,19);     //" "
			OLED_draw(9,0,24);     //"k"
			OLED_draw(18,0,16);     //"="
			OLED_draw(9,2,21);     //"b"
			OLED_draw(18,0,16);     //"="
			OLED_draw(45,0,18);     //"."
			OLED_draw(36,0,abs(k*100)%1000/100);
			OLED_draw(54,0,abs(k*100)%100/10);
			OLED_draw(63,0,abs(k*100)%10/1);
			OLED_draw(36,2,abs(b)/100);
			OLED_draw(45,2,abs(b)/10%10);
			OLED_draw(54,2,abs(b)%10);
			if(line == 3) {
				if(!isset) OLED_draw(0,0,17);     //">"
				OLED_draw(0,2,19);     //" "
				if(isset && seter_2) OLED_draw(0,0,19);     //" "
				if(isset && !seter_2) OLED_draw(0,0,17);     //">"
			}
			if(line == 4) {
				if(!isset) OLED_draw(0,2,17);     //">"
				OLED_draw(0,0,19);     //" "
				if(isset && seter_2) OLED_draw(0,2,17);     //">"
				if(isset && !seter_2) OLED_draw(0,2,19);     //" "
			}
		}
	}
}

/*---------------------------------switches---------------------------------*/

void Swt() {
	Delay1ms(1);
	set = 1;
	ac = 1;
	up = 1;
	down = 1;
	set_now = set;
	ac_now = ac;
	up_now = up;
	down_now = down;
/*---------------------------------switch set---------------------------------*/
	if(set_now != set_last) {
		set_last = set_now;
		if(!set_now) {
			Delay1ms(1);
			if(line==3 || line==4) {
				if(isset) isset = 0;
				else isset = 1;
			}
		}
	}
/*---------------------------------switch AC---------------------------------*/
	if(ac_now != ac_last) {
		ac_last = ac_now;
		if(!ac_now) {
			Delay1ms(1);
			if(line == 0) chu=Redata();        //不同之处
			if(line == 1) wmax=0;
			if(line == 2) wmin=0;
			if(line == 3) k=K_M;
			if(line == 4) b=B_M;
		}
	}
/*---------------------------------switch up---------------------------------*/
	if(up_now != up_last) {
		up_last = up_now;
		if(!up_now) {
			Delay1ms(1);
			if(line==0 || line==2) OLED_clear();
			if(line<4 && line!=3 && line!=4) line++;
			else {
				if(line == 3) {
					if(isset) k=k+0.01;
					else line++;
				}
				if(line == 4) {
					if(isset) b++;
				}
			}
		}
	}
/*---------------------------------switch down---------------------------------*/
	if(down_now != down_last) {
		down_last = down_now;
		if(!down_now) {
			Delay1ms(1);
			if(line==1 || line==3 && !isset) OLED_clear();
			if(line>0 && line!=3 && line!=4) line--;
			else {
				if(line == 3) {
					if(isset) k=k-0.01;
					else line--;
				}
				if(line == 4) {
					if(isset) b--;
					else line--;
				}
			}
		}
	}
}