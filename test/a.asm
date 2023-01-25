default rel

extern printf

segment .rdata
    msg db `Hello world!\r\n`, 0

segment .text

global main
main:
    sub     rsp, 40

    lea     rcx, [msg]
    call    printf

    xor     rax, rax
    add     rsp, 40
    ret
