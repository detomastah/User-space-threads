        global context_switch

        section .text

context_switch:
        mov [rdi], rax
        mov [rdi+8], rcx
        mov [rdi+16], rdx
        mov [rdi+24], rbx
        mov [rdi+32], rsp
        mov [rdi+40], rbp
        mov [rdi+48], rsi
        mov [rdi+56], rdi
        mov [rdi+64], r8
        mov [rdi+72], r9
        mov [rdi+80], r10
        mov [rdi+88], r11
        mov [rdi+96], r12
        mov [rdi+104], r14
        mov [rdi+112], r15

        mov rax, [rsi]
        mov rcx, [rsi+8]
        mov rdx, [rsi+16]
        mov rbx, [rsi+24]
        mov rsp, [rsi+32]
        mov rbp, [rsi+40]
        mov rdi, [rsi+56]
        mov r8,  [rsi+64]
        mov r9,  [rsi+72]
        mov r10, [rsi+80]
        mov r11, [rsi+88]
        mov r12, [rsi+96]
        mov r14, [rsi+104]
        mov r15, [rsi+112]
        mov rsi, [rsi+48]
        ret

;mov    rax, 1        ; sys_write
;mov    rdi, 1        ; stdout
;mov    rsi, message    ; message address
;mov    rdx, length    ; message string length
;syscall

        section .data
message: db 'Hello, world!',0x0A    ; message and newline
length:    equ    $-message        ; NASM definition pseudo-instruction

