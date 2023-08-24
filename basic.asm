section .text
  global _start
_start:
  mov rax, 0
  mov rdi, 1
  mov rsi, rcx
  mov rdx, 5
  syscall
  mov rax, 60
  mov rdi, 0
  syscall
