#include <stdint.h>
#include <stdbool.h>

int main(void)
{
	//初期化
	*((uint32_t*)0x20200010) &= ~(uint32_t)(0x07 << (7*3));
	*((uint32_t*)0x20200010) |= (uint32_t)(0x01 << (7*3));
	
	//初期化ここまで

	while(true){
		*(uint32_t*)0x20200020 = 1 << (47 - 32);
	
		
		for(int i=0;i<500000;i++){
		}
	
		*(uint32_t*)0x2020002C = 1 << (47 - 32);

		for(int i=0;i<500000;i++){
		}
	}
	
	return 0;
}
