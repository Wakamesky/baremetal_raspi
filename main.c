#include <stdint.h>
#define GPIO_BASEADDR 0x20200000
#define UART_BASEADDR 0x20201000
static inline uint32_t setGPIO(uint32_t register_num, uint32_t mode, uint32_t index);

static inline uint32_t setUART(uint32_t register_num, uint32_t mode, uint32_t index);

uint32_t main(void)
{
	setGPIO(1, 0x4, 4);
	setGPIO(1, 0x4, 5);
	
	// UARTEN -> 0
	*((uint32_t*)(UART_BASEADDR + 0x30)) &= ~(uint32_t)(0x1);

	// FIFO    -> None
	*((uint32_t*)(UART_BASEADDR + 0x2c)) &= (uint32_t)(0x0 << 4);
	// DataBit -> 8bit
	*((uint32_t*)(UART_BASEADDR + 0x2c))  = (uint32_t)0x0;
	*((uint32_t*)(UART_BASEADDR + 0x2c)) |= (uint32_t)(0x3 << 5);
	// StopBit -> 1bit
	//*((uint32_t*)(UART_BASEADDR + 0x2c)) &= (uint32_t)(0x0 << 3)
	// Parity  -> None
	//*((uint32_t*)(UART_BASEADDR + 0x2c)) &= (uint32_t)(0x0 << 1)

	// Baudrate IBRD->1 FBRD->40
	*((uint32_t*)(UART_BASEADDR + 0x24)) &= (uint32_t)0x1;
	*((uint32_t*)(UART_BASEADDR + 0x28)) &= (uint32_t)0x28;

	// UARTEN -> 1
	*((uint32_t*)(UART_BASEADDR + 0x30)) |= (uint32_t)(0x1);
	
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
	*((uint32_t*)(GPIO_BASEADDR + register_num*0x4)) &= ~(uint32_t)(0x7  << (index * 3));
	*((uint32_t*)(GPIO_BASEADDR + register_num*0x4)) |=  (uint32_t)(mode << (index * 3));
}
