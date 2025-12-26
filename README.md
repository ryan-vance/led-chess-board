# LED Chess Board

An interactive 8×8 LED chess board that allows users to play against an AI opponent. The system uses Arduino Mega, multiplexers, and a Micro-Max based chess algorithm to create a physical chess experience with visual move feedback through LEDs.

![Chess Board Final Picture](https://github.com/user-attachments/assets/00ea255e-7983-44ea-82a8-ce04d6561e1e)


## Overview

This project was developed as the capstone for **ENGR 470: Mechatronics I** at Western Illinois University. The course focuses on the integration of mechanical systems, electronics, and computer control to create intelligent electromechanical systems. Our team applied these principles to design, create, and document a project that highlights core mechatronics concepts.

## Project Scope & Specifications

### Requirements

Our team established three core requirements for this project:

**Functionality**
- AI opponent that plays legal chess moves
- Real-time move processing and validation
- Visual feedback through LED indicators

**Integration**
- Seamless communication between hardware and software subsystems
- Efficient I/O control using multiplexers
- Reliable serial interface for user input

**Learning Objectives**
- Gain hands-on experience with embedded systems
- Implement algorithms on resource-constrained hardware
- Integrate mechanical, electrical, and software components

### Success Criteria

- ✓ Reliably play full games of chess with legal moves and full rule support
- ✓ Professional integration allowing for efficiency, functionality, and ease of use
- ✓ Fast AI response (<10 seconds) with clear visual feedback via LEDs

## Evaluation

The LED chess board successfully met all established project requirements, demonstrating a professional integration of hardware, software, and embedded algorithms. The system was evaluated based on functionality, integration quality, and resource efficiency.

### Key Achievement Metrics:

- **Functionality**: Consistent AI performance with full chess rule implementation including castling, en passant, and pawn promotion
- **Integration**: Seamless coordination between Arduino Mega, 4 multiplexers, 64 LEDs, and chess algorithm using only 20% of available memory
- **User Experience**: Intuitive serial interface with clear LED feedback creates engaging gameplay with <5 second move calculation. Longer thinking = hard difficulty

## Hardware Platform

### Components

| Component | Part Number | Quantity | Purpose |
|-----------|-------------|----------|---------|
| Arduino Mega 2560 | ELEGOO | 1 | Main microcontroller |
| Pre-wired LEDs | SMD Micro LEDs | 75 (3×25pcs) | Square indicators |
| CD74HC4067 Multiplexers | 16-channel | 4 | Expand I/O capacity |
| 1kΩ Resistors | - | 4 | Current limiting |
| Prototyping Boards | - | 4 | Circuit organization |
| Chess Pieces | Clear Pieces | 1 set | Physical game interface |
| Chess Tiles | 3D Printed | 32 each color | Squares with hole for each LED |
| Chess Board Base | Laser Cut Acrylic | 1 box | Housing for circuitry |

**Total Cost:** ~$75

### Circuit Design

The system uses **four 16-channel multiplexers** (CD74HC4067) to control all 64 board squares efficiently:

- Each multiplexer controls 16 LEDs (one 4×4 quadrant)
- 4-bit binary input selects which of the 16 channels to activate
- Total pins used: 20 (4 control × 4 MUX + 4 signal pins)

**Key Design Decision:** Using multiplexers reduced required Arduino pins from 64 to 20, making the project feasible with the Arduino Mega's 54 digital I/O pins.

```
Arduino Mega (20 pins)
    ↓
4× Multiplexers (CD74HC4067)
    ↓
64× LEDs (arranged in 8×8 grid)
```

## Our Implementation

- **Complete chess algorithm** - Micro-Max engine adapted for Arduino with full rule support
- **LED control system** - Custom multiplexer channel mapping and non-blocking LED blinking
- **Move validation** - Parser for algebraic notation with legal move verification
- **Serial interface** - User-friendly command system for gameplay
- **Memory optimization** - Efficient code using only 20% of Arduino Mega's program storage
- **System integration**
  - Multiplexer pin assignments and channel selection
  - Binary encoding for square positions
  - Board state tracking and display

## Features

- AI chess opponent using Micro-Max algorithm
- Full chess rules including castling, pawn promotion, and en passant
- LED feedback showing computer's source and destination squares
- Serial interface with intuitive commands
- Move calculation time: <10 seconds
- Efficient resource usage: ~600 lines of code, 20% memory

## How to Play

1. Connect Arduino Mega to computer via USB
2. Open Arduino IDE Serial Monitor (9600 baud)
3. Enter moves in algebraic notation (e.g., `move e2e4`)
4. Watch the LEDs light up to show the computer's response move
5. Continue playing until checkmate!

### Commands
- `show` - Display the current board state
- `move e2e4` or `e2e4` - Move a piece from e2 to e4
- `reset` - Reset the board to starting position
- `stop` - Stop LED blinking

## Demo

Go to [this](https://wokwi.com/projects/428952069470626817) link to test the simulation yourself. You can even use the controls to play. Use the show command often to remember where your pieces are, and remember that the board is inverted in this state because it had to be wired upside down!

To see pictures of our process and journey, check the [gallery](https://github.com/ryan-vance/led-chess-board/tree/main/gallery) folder. All pictures can be seen in the [README](https://github.com/ryan-vance/led-chess-board/blob/main/gallery/README.md).

A video demonstration play is posted on [YouTube](https://youtu.be/uNnXn8bJfGM).

## Software Architecture

Check out the code comments in [finalChess.ino](https://github.com/ryan-vance/led-chess-board/blob/main/src/finalChess.ino) to see the system implementation.

**Key Components:**
- Chess algorithm based on Micro-Max by H.G. Muller (adapted by Diego Cueva)
- Multiplexer control system with binary channel encoding
- Non-blocking LED blink system for move indication
- Board state tracking with captured piece management

## Team

- Hannah Stevenson
- Maria Uribe
- Ryan Vance

## Acknowledgments

- Hardware design: LED and multiplexer circuit integration
- Chess algorithm: Diego Cueva (Chessuino), H.G. Muller (Micro-Max)
- Course: ENGR 470 - Mechatronics I, Western Illinois University

## License

This project is licensed under the MIT License - see [LICENSE](LICENSE) file for details.
