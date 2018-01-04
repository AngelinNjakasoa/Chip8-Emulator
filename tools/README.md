# Tool: Disassembler

c8_disassembler is a tiny chip8 disassembler

...Work in progress...

## Requirements

 - cmake 3.9

## Build

$ git clone https://github.com/AngelinNjakasoa/Chip8-Emulator.git </br>
$ cd tools/disassembler  </br>
$ mkdir build  </br>
$ cd build  </br>
$ cmake ..  </br>
$ make </br>

## Example

### Usage

$ ./c8_disassembler input_rom

### Output Example

```
LD I, 0x21e
RND V2, RANDOM_BYTE AND 0x1
SE V2, 0x1
LD I, 0x21a
DRW V0, V1, nibble
ADD V0, 0x4
SE V0, 0x40
JP 0x200
LD V0, 0x0
ADD V1, 0x4
SE V1, 0x20
JP 0x200
JP 0x218
LD V0, V4
CALL 0x10
CALL 0x40
LD V0, V1
```

### Unsupported: Super Chip-48 Instructions

|Opcode|Mnemonic|Operands|
|:-----|:------:|--------:|
|00Cn|SCD|nibble|
|00FB|SCR| _No operand_ |
|00FC|SCL|_No operand_|
|00FD|EXIT|_No operand_|
|00FE|LOW|_No operand_|
|00FF|HIGH|_No operand_|
|Dxy0|DRW| Vx, Vy, 0|
|Fx30|LD| HF, Vx|
|Fx75|LD| R, Vx|
|Fx85|LD| Vx, R|
