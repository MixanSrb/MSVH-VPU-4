# MSVH-VPU-4 Manual

## Overview

MSVH-VPU-4 is a 4-bit virtual CPU that executes a simple assembly-like instruction set.

All values are limited to 4 bits (0–15). Overflow wraps automatically.

---

## CPU Components

### Registers
- **A** → primary accumulator register
- **B** → secondary register

### Flags
- **Z (Zero)** → set to 1 when result equals 0
- **C (Carry)** → set when overflow/underflow occurs

### Program Counter (PC)
Tracks the current instruction being executed.

---

## Instruction Set

### Data Movement

- `MOV A X` → set register A to value X
- `MOV B X` → set register B to value X

---

### Arithmetic (ALU)

- `ADD` → A = A + B
- `SUB` → A = A - B
- `MUL` → A = A * B
- `DIV` → A = A / B (safe division, division by zero is handled)

All results are masked to 4-bit range.

---

### Logic / Compare

- `CMP` → compares A and B  
  - sets `Z = 1` if A == B  
  - sets `C = 1` if A < B  

---

### Control Flow

- `JMP n` → jump to instruction at index n
- `JZ n` → jump to n if Z flag is set
- `JNZ n` → jump to n if Z flag is NOT set

---

### Output

- `GET A` → prints value of register A
- `GET B` → prints value of register B

---

## Execution Model

1. Program is loaded into memory (instruction list)
2. Program Counter (PC) starts at 0
3. CPU executes instruction at PC
4. PC increments automatically
5. Control flow instructions may modify PC

---

## Example Program

### Simple addition

MOV A 3
MOV B 5
ADD
GET A


---

### Conditional loop

MOV A 1
MOV B 1
SUB
CMP
JZ 0
GET A


---

### Infinite loop example

MOV A 1
ADD
JMP 0


---

## Notes

- All values are 4-bit (0–15)
- Arithmetic wraps using bit masking
- This is a software CPU simulation, not physical hardware
