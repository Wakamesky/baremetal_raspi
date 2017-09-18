.align 4
.global _start


.global init_vectortable_s
.global init_vectortable_e

.global irq_handler

_start:
    bl jtag_setup_asm
    bl cpy_vectortable
    // invalidate interrupt
    // cpsid aif <= Comment out

    ldr sp, =0x1c000000 // set stack pointer

    // clear bss
    ldr r0, =__bss_start    // set bss start point
    ldr r1, =__bss_end  // set bss end point
    mov r2, #0      // set register r2 = 0
    cmp r0, r1      // if __bss_start is equal to __bss_end
    beq pre_main        // then jump to "main:" branch
loop:
    str r2 , [r0], #4   // write 0 and rewrite r0 = r0 + 4 (=__bss_start + 4)
    cmp r1, r0      // why #4? because 4byte = 4*8bit = 32bit = sizeof(int)
    ble loop

pre_main:
    svc #0x1
    bl main
    b .

jtag_setup_asm:
    ldr r1, =0x20200000 @ load GPFSEL address
    ldr r2, =0xffff8fff @ load GPIO4 mask
    ldr r3, =0xff1c0e3f @ load GPIO22,24,25,27 mask
    ldr r4, [r1, #0]    @ load GPFSEL0 value
    ldr r5, [r1, #8]    @ load GPFSEL2 value
    and r4, r4, r2      @ clear GPIO4 mode
    and r5, r5, r3      @ clear GPIO22,24,25,27 mode
    ldr r2, =0x00002000 @ load GPIO4 ALT4
    ldr r3, =0x0061b0c0 @ load GPIO22,24,25,27 ALT5
    orr r4, r4, r2      @ set GPIO4 mode to ALT4
    orr r5, r5, r3      @ set GPIO22,24,25,27 mode to ALT5
    str r4, [r1, #0]    @ save GPFSEL0 value
    str r5, [r1, #8]    @ save GPFSEL2 value
    bx lr

// Ref. Learn Assembler with ARM, p.156
init_vectortable_s:
    ldr PC, reset_handler_addr    // Reset
    ldr PC, undef_handler_addr    // Undefined
    ldr PC, swi_handler_addr      // SWI
    ldr PC, pabt_handler_addr     // Prefetch
    ldr PC, dabt_handler_addr     // Abort
    NOP                            // Reserved
    ldr PC, irq_handler_addr      // IRQ
    ldr PC, fiq_handler_addr      // FIQ

reset_handler_addr:	.word	reset_handler
undef_handler_addr:	.word	undef_handler
swi_handler_addr:	.word	swi_handler
pabt_handler_addr:	.word	pabt_handler
dabt_handler_addr:	.word	dabt_handler
irq_handler_addr:	.word	irq_handler
fiq_handler_addr:	.word	fiq_handler
init_vectortable_e:
nop

cpy_vectortable:
    // Set vectortable
    MOV r0, #0x00
    LDR r1, =init_vectortable_s
    LDR r3, =init_vectortable_e
keep_loading:
    LDR r2, [r1, #0x0]
    STR r2, [r0, #0x0]
    ADD r0, r0, #0x4
    ADD r1, r1, #0x4
    CMP r1, r3
    BNE keep_loading
    bx lr

hangup:
reset_handler:
undef_handler:
pabt_handler:
dabt_handler:
irq_handler:
fiq_handler:
  b .

swi_handler:
  b .
