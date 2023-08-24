section .text
  global _start
  extern printf
_start:
  mov rax, num
  mov al, byte [rax]
  mul al
  mov [num], ax
  push format
  push num
  call printf
  add rsp, 16
  mov rax, 60
  mov rdi, 0
  syscall
section .data
  num db 5
  format db "%d\n"
