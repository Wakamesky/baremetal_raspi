.align 4
.global _start
_start:
	cpsid aif		// invalidate interrupt
	ldr sp, =0x1c000000	// set stack pointer, next clear bss
	ldr r0, =__bss_start	// set bss start point
	ldr r1, =__bss_end	// set bss end point
	mov r2, #0		// set register r2 = 0
	cmp r0, r1		// if __bss_start is equal to __bss_end
	beq main		// then jump to "main:" branch

loop:
	str r2 , [r0], #4	// write 0 and rewrite r0 = r0 + 4 (=__bss_start + 4)
	cmp r0, r1		// why #4? because 4byte = 4*8bit = 32bit = sizeof(int)
	ble loop		// r0 - r1 <= 0 then goto loop

main:
	bl main
	bx lr
