bits 64
section .text
global printf

%include "../macros.inc"
%include "../syscalls.inc"
%include "../messages.inc"

%macro clear_clobbered 0
; no-op
%endmacro

%include "../user/putchar.asm"
%include "../printf.asm"

; Inputs:
; rdi = format
; rsi = pointer to va_list structure
; 
; va_list:
; 0. gp_offset
; 4. fp_offset
; 8. overflow_arg_area
; 16. reg_save_area
;
; When in printf, we want the stack to contain the relevant values from
; overflow_arg_area, and want all the GP registers to be loaded with values
; from reg_save_area(?). Do we know how much data is saved in either place?
vprintf:
	jmp	puts
