.align 4
.global _start
_start:
    bl jtag_setup_asm
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
    bl init_vectortable
    svc 2
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

// Added following
init_vectortable:
    ldr PC, =hangup         // Reset
    ldr PC, =hangup         // Undefined
    ldr PC, =hangup         // SWI
    ldr PC, =hangup         // Prefetch
    ldr PC, =hangup         // Abort
    NOP                     // Reserved
    ldr PC, =hangup         // IRQ
    ldr PC, =hangup         // FIQ

hangup:
    wfi
    b hangup
