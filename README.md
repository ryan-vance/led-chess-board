# LED Chess Board

An interactive 8×8 LED chess board that allows users to play against an AI opponent. The system uses Arduino Mega, multiplexers, and a Micro-Max based chess algorithm to create a physical chess experience with visual move feedback through LEDs.

![LED Chess Board](images/chess_board.jpg)
*Note: Add your chess board photo to an `images/` folder*

## 📋 Project Overview

This project was developed as the capstone for **ENGR 470: Mechatronics** at Western Illinois University. The board takes player input through a serial monitor, processes moves using an embedded chess algorithm, and displays the computer's moves by lighting up LEDs at the source and destination squares.

**Team Members:** Hannah Stevenson, Maria Uribe, Ryan Vance  
**Course:** ENGR 470 - Mechatronics I  
**Institution:** Western Illinois University  
**Year:** 2024

## ✨ Features

- **AI Chess Opponent** - Micro-Max chess engine adapted for Arduino (based on Chessuino by Diego Cueva)
- **Move Validation** - Only accepts legal chess moves
- **Full Chess Rules** - Supports castling, pawn promotion, en passant
- **LED Feedback** - Visual indication of computer moves via lit squares
- **Serial Interface** - User-friendly command system via serial monitor
- **Efficient Memory Usage** - ~600 lines of code using only 20% of Arduino Mega's memory
- **Multiplexed Control** - Controls 64 LEDs using only 20 Arduino pins via 4 multiplexers

## 🎮 How to Play

1. Connect Arduino Mega to computer via USB
2. Open Arduino IDE Serial Monitor (9600 baud)
3. Enter moves in algebraic notation (e.g., `move e2e4`)
4. Watch the LEDs light up to show the computer's response move
5. Continue playing until checkmate!

### Commands
- `show` - Display the current board state
- `move e2e4` - Move a piece from e2 to e4
- `reset` - Reset the board to starting position
- `stop` - Stop LED blinking

## 🔧 Hardware Components

| Component | Part Number | Quantity | Purpose |
|-----------|-------------|----------|---------|
| Arduino Mega 2560 | ELEGOO | 1 | Main microcontroller |
| Pre-wired LEDs | SMD Micro LEDs | 75 (3×25pcs) | Square indicators |
| CD74HC4067 Multiplexers | 16-channel | 4 | Expand I/O capacity |
| 1kΩ Resistors | - | 4 | Current limiting |
| Prototyping Boards | - | 4 | Circuit organization |
| Chess Board & Pieces | 3D Printed | 1 set | Physical game interface |

**Total Cost:** ~$65

## 🛠️ Circuit Design

The system uses **four 16-channel multiplexers** (CD74HC4067) to control all 64 board squares efficiently:

- Each multiplexer controls 16 LEDs (one 4×4 quadrant)
- 4-bit binary input selects which of the 16 channels to activate
- Arduino sends binary patterns to multiplexers
- Total pins used: 20 (4 control × 4 MUX + 4 signal pins)

**Key Design Decision:** Using multiplexers reduced required Arduino pins from 64 to 20, making the project feasible with the Arduino Mega's 54 digital I/O pins.

```
Arduino Mega (20 pins)
    ↓
4× Multiplexers (CD74HC4067)
    ↓
64× LEDs (arranged in 8×8 grid)
```

## 💻 Software Architecture

### Chess Algorithm
- Based on **Micro-Max** by H.G. Muller
- Adapted to Arduino by Diego Cueva (Chessuino)
- Uses recursion and iterative deepening
- Compact implementation (~2KB) optimized for limited memory
- Move calculation time: <10 seconds per move

### LED Control System
- Custom binary encoding for square selection
- Multiplexer channel mapping for all 64 squares
- Efficient pin toggling for visual feedback
- Non-blocking LED blinking for move indication

### Key Functions
- `D()` - Main chess algorithm and move evaluation
- `parseMove()` - Convert algebraic notation to board coordinates
- `updateLEDs()` - Control multiplexer outputs
- `printBoard()` - Display board state in serial monitor
- `initializeBoard()` - Set up starting position

## 📂 Repository Structure

```
led-chess-board/
├── finalChess.ino          # Main Arduino sketch (719 lines)
├── README.md               # This file
├── images/                 # Photos and diagrams
│   ├── chess_board.jpg
│   ├── circuit_diagram.png
│   └── serial_output.png
├── docs/                   # Additional documentation
│   └── Final_Report.pdf    # Complete project report
└── LICENSE                 # MIT License
```

## 🚀 Getting Started

### Prerequisites
- Arduino IDE (1.8.x or later)
- Arduino Mega 2560
- USB cable for programming

### Installation

1. Clone this repository:
```bash
git clone https://github.com/ryan-vance/led-chess-board.git
cd led-chess-board
```

2. Open `finalChess.ino` in Arduino IDE

3. Select board and port:
   - Tools → Board → Arduino Mega 2560
   - Tools → Port → (your Arduino's port)

4. Upload the sketch to your Arduino

5. Open Serial Monitor:
   - Tools → Serial Monitor
   - Set baud rate to 9600

### Hardware Setup

1. Connect multiplexers to Arduino according to pin mappings in code
2. Wire LEDs to multiplexer outputs (see LED mapping in comments)
3. Position LEDs under chess board squares
4. Connect 1kΩ resistors to multiplexer signal pins
5. Power system via USB or external 5V supply

## 🎯 Performance

- **Memory Usage:** 20% of program storage (Arduino Mega)
- **Move Calculation:** <10 seconds average
- **LED Response:** Instantaneous (<100ms)
- **Move Validation:** 100% accurate (standard chess rules)
- **Uptime:** Unlimited (system tested for 2+ hour continuous play)

## 🏆 Project Outcomes

✅ All design objectives met and exceeded:
- **Functionality** - Consistent operation throughout full games
- **Piece Management** - Accurate tracking of all pieces and positions
- **Integration** - Seamless communication between hardware and software subsystems
- **User Experience** - Intuitive serial interface with visual feedback

## 📸 Gallery

*Add photos of:*
- Completed chess board
- Circuit assembly
- Serial monitor output during gameplay
- LED patterns showing moves

## 🔮 Future Enhancements

Potential improvements identified during development:
- Physical move detection using hall effect sensors
- Standalone operation with LCD display
- Adjustable AI difficulty levels
- Move timer and game clock
- Bluetooth/WiFi connectivity for remote play
- Save/load game states to EEPROM

## 📚 References

- **Micro-Max Chess Engine** by H.G. Muller
- **Chessuino** adaptation by Diego Cueva
- Arduino Mega 2560 Documentation
- CD74HC4067 Multiplexer Datasheet

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 👥 Acknowledgments

- **Project Advisor:** Western Illinois University Engineering Faculty
- **Course:** ENGR 470 - Mechatronics I
- **Chess Algorithm:** Diego Cueva (Chessuino), H.G. Muller (Micro-Max)
- **Team Members:** Hannah Stevenson, Maria Uribe, Ryan Vance

## 📧 Contact

**Ryan Vance**  
- GitHub: [@ryan-vance](https://github.com/ryan-vance)
- Project Link: [https://github.com/ryan-vance/led-chess-board](https://github.com/ryan-vance/led-chess-board)

---

*Developed as part of the Mechatronics capstone project at Western Illinois University, Spring 2024*
