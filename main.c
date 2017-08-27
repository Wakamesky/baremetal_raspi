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
	// initialize GPIO
	// GPIO 14 -> TXD0 -> ALT0
	setGPIO(1, 0x4, 4);
	
	// GPIO 15 -> RXD0 -> ALT0
	setGPIO(1, 0x4, 5);
	// end initialize GPIO
	// Checked

	// initialize UART -> Base Address = 0x20201000
	// Invadidate UART -> (UARTEN =) UART_CR[0] = 0
	// *UART_CR = 0x202010000 + 0x30
	*((uint32_t*)(0x20201000 + 0x30)) &= ~(uint32_t)0x1;
	//*((uint32_t*)(0x20201000 + 0x30)) |=  (uint32_t)0x0;
	// Checked

	// Already set -> let their value hold
	// FIFO   -> 0								
	//  |---> Register address : LCRH Register -> Base Address + 0x2c	
	//  |---> 0 -> FEN : [4] bit						
	*((uint32_t*)(0x20201000 + 0x2c)) &= ~(uint32_t)(0x1 << 4);
	//*((uint32_t*)(0x20201000 + 0x2c)) |=  (uint32_t)(0x0 << 4);
	// Checked

	// Stopbit -> 1bit						
	//  |---> Register address : LCRH Register -> Base Address + 0x2c
	//  |---> Bit -> [3] bit					
	
	*((uint32_t*)(0x20201000 + 0x2c)) &= ~(uint32_t)(0x1 << 3);
	*((uint32_t*)(0x20201000 + 0x2c)) |=  (uint32_t)(0x0 << 3);

	// Parity -> 0								
	//  |---> Register address : LCRH Register -> Base Address + 0x2c	
	//  |---> 0 -> PEN : [1] bit						
	*((uint32_t*)(0x20201000 + 0x2c)) &= ~(uint32_t)(0x1 << 1);
	*((uint32_t*)(0x20201000 + 0x2c)) |=  (uint32_t)(0x0 << 1);
	
	// Databit -> 8bit
	//  |---> Register address : LCRH Register -> Base Address + 0x2c
	//  |---> Bit -> [6:5] bit -> b11

	*((uint32_t*)(0x20201000 + 0x2c)) &= ~(uint32_t)(0x3 << 5);
	*((uint32_t*)(0x20201000 + 0x2c)) |=  (uint32_t)(0x3 << 5);	

	// Control Register : Base Address + 0x30
	//  |---> TXE -> 1
	//	   |---> [8] bit
	//  |---> RXE -> 1
	//	   |---> [9] bit
	*((uint32_t*)(0x20201000 + 0x30)) &= ~(uint32_t)(0x1 << 8);
	*((uint32_t*)(0x20201000 + 0x30)) |=  (uint32_t)(0x1 << 8);
	
	*((uint32_t*)(0x20201000 + 0x30)) &= ~(uint32_t)(0x1 << 9);
	*((uint32_t*)(0x20201000 + 0x30)) |=  (uint32_t)(0x1 << 9);



	// end already set							
	
	// Needed for set
      /*######################################################################### 
	# Baudrate -> 115200							#
	#  |---> IBRD -> 1  = 0x1						#
	#         |---> Register address : IBRD Register -> Base Address + 0x24	#
	#         |---> Bit -> [15:0] bit					#
	#  |---> FBRD -> 40 = 0x28						#
	#         |---> Register address : FBRD Register -> Base Address + 0x28	#
	#         |---> Bit -> [5:0] bit					#
	#########################################################################*/

	*((uint32_t*)(0x20201000 + 0x24)) =  (uint32_t)0x1;
	*((uint32_t*)(0x20201000 + 0x28)) =  (uint32_t)0x28;
	


	// End needed for set
	
	// Vadidate UART -> (UARTEN =) UART_CR[0] = 1
	*((uint32_t*)(0x20201000 + 0x30)) &= ~(uint32_t)0x1;
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
