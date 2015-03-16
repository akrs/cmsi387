; The loader given in the little os book is invalid
; We used a loader from
; https://github.com/littleosbook/littleosbook/issues/11
; instead
global loader                 ; the entry symbol for ELF

MAGIC           equ 0x1BADB002       ; define the magic number constant
ALIGN_MODULES   equ 0x00000001
CHECKSUM equ -(MAGIC + ALIGN_MODULES) ; calculate the checksum (magic number + flags + checksum should equal 0)
KERNEL_STACK_SIZE equ 4096                  ; size of stack in bytes

section .text                ; start of the text (code) section
align 4                       ; the code must be 4 byte aligned
    dd MAGIC                  ; write the magic number to the machine code
    dd ALIGN_MODULES
    dd CHECKSUM               ; and the checksum

loader:                       ; the loader label (defined as entry point in linker script)
    mov esp, kernel_stack + KERNEL_STACK_SIZE   ; point esp to the start of the
    ; The assembly code
    extern kernel_main   ; the function sum_of_three is defined elsewhere

    call kernel_main       ; call the function, the result will be in eax
                                                ; stack (end of memory area)

.loop:
    jmp .loop                 ; loop forever

section .bss
align 4                                     ; align at 4 bytes
kernel_stack:                               ; label points to beginning of memory
    resb KERNEL_STACK_SIZE                  ; reserve stack for the kernel
