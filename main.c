#include <stdint.h>
#include <stdbool.h>

#define UART_BASE_ADDR 0x20201000

uint32_t main(void)
{
	*((uint32_t*)(UART_BASE_ADDR + 0x30)) &= ~(uint32_t)(0x1);
	
	*((uint32_t*)(UART_BASE_ADDR + 0x2c)) &= ~(uint32_t)(0xd << 1);

	*((uint32_t*)(UART_BASE_ADDR + 0x2c)) |=  (uint32_t)(0x3 << 5);

	*((uint32_t*)(UART_BASE_ADDR + 0x2c)) |=  (uint32_t)(0x3 << 5);

	*((uint32_t*)(UART_BASE_ADDR + 0x24)) &=  (uint32_t)0;
	
	*((uint32_t*)(UART_BASE_ADDR + 0x24)) |=  (uint32_t)1;
	
	*((uint32_t*)(UART_BASE_ADDR + 0x28)) &=  (uint32_t)0;
	
	*((uint32_t*)(UART_BASE_ADDR + 0x28)) |=  (uint32_t)0x28;
	
	*((uint32_t*)(UART_BASE_ADDR + 0x30)) |=  (uint32_t)(0x1);

	uint32_t i = 0;

	char str[12] = "HelloWorld\n";
	while(true){
		while(str[i]!='\0'){
			*((uint32_t*)(UART_BASE_ADDR)) = (uint32_t)(str[i]);
			for(int j=0; j<50000; j++){}
			i++;
		}
		i = 0;
	}

	return 0;
}
