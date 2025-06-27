section .text
global my_exit_asm

%ifdef USE_SYSCALL
my_exit_asm:
    mov rax, 60    ; numéro de l'appel système pour exit
    syscall        ; appel système

%else
extern exit
my_exit_asm:
    call exit

%endif

section .note.GNU-stack