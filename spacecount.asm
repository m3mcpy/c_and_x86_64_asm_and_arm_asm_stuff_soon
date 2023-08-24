section .text
  global _start
_start:
  mov rax, [rsp + 16]
  loop_start:
    cmp ax, ' '
    je increaseyo
    increaseyo:
      inc byte [spaces]
      jmp check
    check:
      inc ax
      cmp ax, 0
      jne loop_start
  add byte [spaces], 'z'
  mov rax, 1
  mov rdi, 1
  mov rsi, spaces
  mov rdx, 1
  syscall
  mov rax, 60
  mov rdi, 0
  syscall
section .data
  spaces db 0
