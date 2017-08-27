#include <stdint.h>
#include <stdbool.h>

static inline uint32_t setGPIO(uint32_t register_num, uint32_t mode, uint32_t index);

static inline uint32_t setUART(uint32_t register_num, uint32_t mode, uint32_t index);

int main(void)
{
	// initialize GPIO
	setGPIO(1, 0x4, 4);
	setGPIO(1, 0x4, 5);
	// end initialize GPIO

	// initialize UART -> Base Address = 0x202010000
      /*#########################################################################
	# Already set -> let their value hold				 	#
	# Control Register : TXE -> 1 , RXE -> 1			 	#
	# Stopbit -> 1bit						 	#
	#  |---> Register address : LCRH Register -> Base Address + 0x2c	#
	#  |---> Bit -> [3] bit							#
	# Parity -> 0								#
	#  |---> Register address : LCRH Register -> Base Address + 0x2c	#
	#  |---> 0 -> PEN : [1] bit						#
	# FIFO   -> 0								#
	#  |---> Register address : LCRH Register -> Base Address + 0x2c	#
	#  |---> 0 -> FEN : [4] bit						#
	# end already set							#
	#########################################################################*/
	
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
	
	*((uint32_t*)(0x20201000 + 0x24)) |=  (uint32_t)1;
	*((uint32_t*)(0x20201000 + 0x28)) |=  (uint32_t)0x28;
	
	// Databit -> 8bit
	//  |---> Register address : LCRH Register -> Base Address + 0x2c
	//  |---> Bit -> [6:5] bit

	*((uint32_t*)(0x20201000 + 0x2c)) &= ~(uint32_t)(0x3 << 5);
	*((uint32_t*)(0x20201000 + 0x2c)) |=  (uint32_t)(0x3 << 5);

	// End needed for set


	int i = 0;

	char str[11] = "HelloWorld";
	
	while(str[i]!='\0'){
		*((uint32_t*)(0x20201000)) = (uint32_t)(str[i]);
		for(int j=0; j<500000; j++){}
		i++;
	}

	return 0;
}

static inline uint32_t setGPIO(uint32_t register_num, uint32_t mode, uint32_t index){
	*((uint32_t*)(0x20200000 + register_num*0x4)) &= ~(uint32_t)(0x7  << (index * 3));
	*((uint32_t*)(0x20200000 + register_num*0x4)) |=  (uint32_t)(mode << (index * 3));
}
