# Chip-8 Emulator

Yet another Chip8 emulator and tools.

Work in progress

| Tool | Description |
|:-----|-----------:|
|c8-disassembler|Translates chip8 opcode to chip8 assembly language|

## Emulator

CHIP-8 emulator

WIP: display using SDL2

### Requirements

 - cmake >= 3.9
 - SDL2

```
$ sudo apt-get install cmake libsdl2-dev
```

### Build

```
$ git clone https://github.com/lem2clide/Chip8-Emulator.git
$ cd Chip8-Emulator
$ mkdir build && cd build
$ cmake .. && make
```

## Disassembler

Disassembles CHIP-8 ROM into instructions

### Build

```
$ cd tools
$ mkdir build && cd build
$ cmake .. && make
```

### Example

```
$ ./tools/build/bin/c8-disassembler pong.rom

file_size: 246 bytes

LD Va, 0x2
LD Vb, 0xc
LD Vc, 0x3f
LD Vd, 0xc
LD I, 0x2ea
DRW Va, Vb, nibble
DRW Vc, Vd, nibble
LD Ve, 0x0
CALL 0x2d4
LD V6, 0x3
LD V8, 0x2
LD V0, 0x60
LD DT, V0
LD V0, DT
SE V0, 0x0
JP 0x21a
RND V7, RANDOM_BYTE AND 0x17
ADD V7, 0x8
LD V9, 0xff
LD I, 0x2f0
DRW V6, V7, nibble
LD I, 0x2ea
DRW Va, Vb, nibble
DRW Vc, Vd, nibble
LD V0, 0x1
SKNP V0
ADD Vb, 0xfe
LD V0, 0x4
SKNP V0
ADD Vb, 0x2
LD V0, 0x1f
AND Vb, V0
DRW Va, Vb, nibble
LD Vd, V7
RND V0, RANDOM_BYTE AND 0xa
ADD Vd, 0xfe
SNE V0, 0x0
ADD Vd, 0x2
LD V0, 0x0
LD V0, 0x1f
AND Vd, V0
DRW Vc, Vd, nibble
LD I, 0x2f0
DRW V6, V7, nibble
ADD V6, V8
ADD V7, V9
LD V0, 0x3f
AND V6, V0
LD V1, 0x1f
AND V7, V1
SNE V6, 0x2
JP 0x278
SNE V6, 0x3f
JP 0x282
SNE V7, 0x1f
LD V9, 0xff
SNE V7, 0x0
LD V9, 0x1
DRW V6, V7, nibble
JP 0x22a
LD V8, 0x2
LD V3, 0x1
LD V0, V7
SUB V0, Vb
JP 0x28a
LD V8, 0xfe
LD V3, 0xa
LD V0, V7
SUB V0, Vd
SE Vf, 0x1
JP 0x2a2
LD V1, 0x2
SUB V0, V1
SE Vf, 0x1
JP 0x2ba
SUB V0, V1
SE Vf, 0x1
JP 0x2c8
SUB V0, V1
SE Vf, 0x1
JP 0x2c2
LD V0, 0x20
LD ST, V0
CALL 0x2d4
ADD Ve, V3
CALL 0x2d4
LD V6, 0x3e
SE V3, 0x1
LD V6, 0x3
LD V8, 0xfe
SE V3, 0x1
LD V8, 0x2
JP 0x216
ADD V9, 0xff
SNE V9, 0xfe
LD V9, 0xff
JP 0x2c8
ADD V9, 0x1
SNE V9, 0x2
LD V9, 0x1
LD V0, 0x4
LD ST, V0
ADD V6, 0x1
SNE V6, 0x40
ADD V6, 0xfe
JP 0x26c
LD I, 0x2f2
LD B, Ve
LD V2, [I]
LD F, V1
LD V4, 0x14
LD V5, 0x0
DRW V4, V5, nibble
ADD V4, 0x15
LD F, V2
DRW V4, V5, nibble
LD V0, V8
LD V0, V8
LD V0, V8
LD V0, V0
```

## References

 * Documentation: http://devernay.free.fr/hacks/chip8/C8TECH10.HTM
