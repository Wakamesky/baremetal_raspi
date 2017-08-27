#include <stdint.h>

static inline uint32_t setGPIO(uint32_t register_num, uint32_t mode, uint32_t index);

/*
static inline uint32_t setGPIO(uint32_t register_num, uint32_t mode, uint32_t index){
	*((uint32_t*)(0x20200000 + register_num*0x4)) &= ~(uint32_t)(0x7  << (index * 3));
	*((uint32_t*)(0x20200000 + register_num*0x4)) |=  (uint32_t)(mode << (index * 3));
}
*/

int main(void)
{
	setGPIO(0, 0x2, 4);
	setGPIO(2, 0x3, 2);
	setGPIO(2, 0x3, 4);
	setGPIO(2, 0x3, 5);
	setGPIO(2, 0x3, 7);
	setGPIO(1, 0x4, 4);
	setGPIO(1, 0x4, 5);

	*((uint32_t*)(0x20201000 + 0x30)) &=  (uint32_t)0x0;
	*((uint32_t*)(0x20201000 + 0x30)) |=  (uint32_t)0x0;
	*((uint32_t*)(0x20201000 + 0x2c)) |=  (uint32_t)(0x0 << 4);
	*((uint32_t*)(0x20201000 + 0x2c)) |=  (uint32_t)(0x0 << 3);
	*((uint32_t*)(0x20201000 + 0x2c)) |=  (uint32_t)(0x0 << 1);
	*((uint32_t*)(0x20201000 + 0x2c)) |=  (uint32_t)(0x3 << 5);	
	*((uint32_t*)(0x20201000 + 0x30)) |=  (uint32_t)(0x1 << 8);
	*((uint32_t*)(0x20201000 + 0x30)) |=  (uint32_t)(0x1 << 9);
	*((uint32_t*)(0x20201000 + 0x24)) =  (uint32_t)0x1;
	*((uint32_t*)(0x20201000 + 0x28)) =  (uint32_t)0x28;
	*((uint32_t*)(0x20201000 + 0x30)) |=  (uint32_t)0x1;

	uint32_t i = 0;

	char str[11] = "HelloWorld";
	
	while(str[i]!='\0'){
		*((uint32_t*)(0x20201000)) = (uint32_t)(str[i]);
		for(int j=0; j<50000000; j++){}
		i++;
	}

	return 0;
}

static inline uint32_t setGPIO(uint32_t register_num, uint32_t mode, uint32_t index){
	*((uint32_t*)(0x20200000 + register_num*0x4)) &= ~(uint32_t)(0x7  << (index * 3));
	*((uint32_t*)(0x20200000 + register_num*0x4)) |=  (uint32_t)(mode << (index * 3));
}
