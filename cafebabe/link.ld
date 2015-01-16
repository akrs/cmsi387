/* The loader script in The Little OS Book didn't work for me - 
 * I got this script from: 
 * https://github.com/littleosbook/littleosbook/issues/10
 */
ENTRY(loader)

SECTIONS {
    . = 1M;

    .text : ALIGN(4K) {
        *(.text)
    }

    .rodata : ALIGN(4K) {
        *(.rodata)
    }

    .data : ALIGN(4K) {
        *(.data)
    }

    .bss : ALIGN(4K) {
        *(COMMON)
        *(.bss)
    }
}
