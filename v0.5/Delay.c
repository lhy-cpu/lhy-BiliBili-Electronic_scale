/*这是up主（刘海洋ghs）自己写的，代码不完善，还望大佬见教*/
/*仅供学习用途，若有由这些代码造成的任何损失，由使用者自行承担，开发者（刘海洋ghs）概不负责*/

#include "Delay.h"

void Delay1ms(unsigned char p){
	unsigned char i,h,j;
	p=p*F;
	for (h=0;h<p;h++) {
		i = 24;
		j = 85;
		do{while (--j);}
		while (--i);
	}
}