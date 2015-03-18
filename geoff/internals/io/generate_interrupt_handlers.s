extern interrupt_handler

%macro no_error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
    push    dword 0                     ; push 0 as error code
    push    dword %1                    ; push the interrupt number
    jmp     common_interrupt_handler    ; jump to the common handler
%endmacro

%macro error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
    push    dword %1                    ; push the interrupt number
    jmp     common_interrupt_handler    ; jump to the common handler
%endmacro

common_interrupt_handler:               ; the common parts of the generic interrupt handler
    ; call the C function
    pushad
    call    interrupt_handler
    popad

    ; restore the esp because of the error code and interrupt number
    add     esp, 8

    ; return to the code that got interrupted
    iret

no_error_code_interrupt_handler 0       ; create handler for interrupt 0
no_error_code_interrupt_handler 1       ; create handler for interrupt 1
no_error_code_interrupt_handler 2       ; create handler for interrupt 1
no_error_code_interrupt_handler 3       ; create handler for interrupt 1
no_error_code_interrupt_handler 4       ; create handler for interrupt 1
no_error_code_interrupt_handler 5       ; create handler for interrupt 1
no_error_code_interrupt_handler 6       ; create handler for interrupt 1
no_error_code_interrupt_handler 7       ; create handler for interrupt 7
error_code_interrupt_handler    8       ; create handler for interrupt 8
no_error_code_interrupt_handler 9       ; create handler for interrupt 9
error_code_interrupt_handler    10      ; create handler for interrupt 10
error_code_interrupt_handler    11      ; create handler for interrupt 11
error_code_interrupt_handler    12      ; create handler for interrupt 12
error_code_interrupt_handler    13      ; create handler for interrupt 13, GP fault. If nothing else, handle this.
error_code_interrupt_handler    14      ; create handler for interrupt 14
no_error_code_interrupt_handler 15      ; create handler for interrupt 15
no_error_code_interrupt_handler 16      ; create handler for interrupt 16
error_code_interrupt_handler    17      ; create handler for interrupt 17
no_error_code_interrupt_handler 18      ; create handler for interrupt 18
no_error_code_interrupt_handler 19      ; create handler for interrupt 19
; 20 - 31 are Intel reserved. Do not touch.

; Keyboard handler.
no_error_code_interrupt_handler 33      ; create handler for interrupt 33

; Other handlers will be added as needed

global int_handler
int_handler:
    mov gs, ax
    mov dword [gs:0xB8000],') : '
    hlt
