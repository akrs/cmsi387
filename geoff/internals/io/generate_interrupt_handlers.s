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

    ; restore the esp because o fthe error code and interrupt number
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
error_code_interrupt_handler    7       ; create handler for interrupt 7
