#include <stdint.h>
#include <stdbool.h>

static inline uint32_t setGPIO(uint32_t register_num, uint32_t mode, uint32_t index){
	*((uint32_t*)(0x20200000 + register_num*0x4)) |= (uint32_t)(mode << (index * 3));
}

int main(void)
{
	//初期化
		
	//GPIO  4 : ALT 5 -> GPFSEL[0] 14-12 bit -> 010
	setGPIO(0, 0x2, 4);
	
	//GPIO 22 : ALT 4 -> GPFSEL[2]   8-6 bit -> 011
	setGPIO(2, 0x3, 2);
	
	//GPIO 24 : ALT 4 -> GPFSEL[2] 14-12 bit -> 011
	setGPIO(2, 0x3, 4);
	
	//GPIO 25 : ALT 4 -> GPFSEL[2] 17-15 bit -> 011
	setGPIO(2, 0x3, 5);

	//GPIO 27 : ALT 4 -> GPFSEL[2] 23-21 bit -> 011
	setGPIO(2, 0x3, 7);
	
	

	//初期化ここまで
	return 0;
}
