section .text
global my_exit_asm

my_exit_asm:
    mov rax, 60       ; numéro de l'appel système pour exit
    syscall           ; appel système

section .note.GNU-stack