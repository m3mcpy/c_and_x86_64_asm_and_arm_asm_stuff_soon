section .text
  global _start
_start:
  mov rax, [rsp + 16]
  mov rdx, 0
  get_length:
    inc rdx
    cmp byte [rax + rdx], 0
    jne get_length
  mov rcx, 0
  loop_start:
    mov rax, [rsp + 16]
    mov rax, [rax + rcx]
    mov [buf + rcx], al
    inc rcx
    cmp rcx, rdx
    jne loop_start
  mov rax, 1
  mov rdi, 1
  mov rsi, buf
  syscall
  mov rax, 60
  mov rdi, 0
  syscall
section .data
  buf db 100
