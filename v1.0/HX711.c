/*这是up主（刘海洋ghs）自己写的，代码不完善，还望大佬见*/
/*仅供学习用途，若有由这些代码造成的任何损失，由使用者自行承担，开发者（刘海洋ghs）概不负责*/

#include "intrins.h"
#include "HX711.h"
#include "input.h"

/*---------------------------------Read HX711---------------------------------*/
unsigned long Redata () {
	unsigned char i,j;
	unsigned long Rdata = 0;
	HX711_SCK = 0;
	HX711_DAT = 1;
	while(HX711_DAT);
	for (i=0;i<24;i++) {
		HX711_SCK = 1;
		Rdata = Rdata<<1;
		HX711_SCK = 0;
		if (HX711_DAT) Rdata++;
	}
	for(j=0;j<Z_M;j++) {
		HX711_SCK = 1;
		_nop_();
		HX711_SCK = 0;
	}
	Rdata = Rdata^0x800000;
	return Rdata;
}

/*---------------------------------Average HX711---------------------------------*/
/*unsigned long RedataAverage(unsigned char times) {
	unsigned long Average=0;
	unsigned char time;
	for(time = 0;time < times;time++) {
		Average = (Average+Redata())/2;
	}
	return Average;
}*/