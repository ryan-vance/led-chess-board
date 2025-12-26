# Hardware Documentation

This folder contains all hardware specifications, assembly instructions, and component details for the LED Chess Board project.

## Quick Links

- [Bill of Materials](BOM.md) - Complete parts list with specifications
- [Wiring Guide](wiring-guide.md) - Pin connections and circuit assembly
- [Circuit Diagram](https://wokwi.com/projects/428952069470626817) - Interactive Wokwi simulation

## System Overview

The LED Chess Board uses an Arduino Mega 2560 to control 64 LEDs arranged in an 8×8 grid through four 16-channel multiplexers (CD74HC4067). This design reduces the required I/O pins from 64 to just 20, making the project feasible while maintaining individual control of each square.

### Architecture Summary

```
Arduino Mega 2560 (20 I/O pins)
    ↓
4× CD74HC4067 Multiplexers (16 channels each)
    ↓
64× Pre-wired SMD Micro LEDs (8×8 grid)
```

**Key Design Decision:** Using multiplexers instead of direct LED control reduced pin requirements by 69% while maintaining full individual square control.

## Hardware Components

### Control System
- **Arduino Mega 2560** - Main microcontroller with 54 digital I/O pins
- **4× CD74HC4067** - 16-channel analog/digital multiplexers for LED control
- **4× 1kΩ Resistors** - Current limiting protection (one per multiplexer signal pin)

### Display System
- **64× Pre-wired SMD Micro LEDs** - Individual square indicators
- **32× 3D Printed Chess Tiles** (each color) - Squares with LED mounting holes
- **1× Laser Cut Acrylic Base** - Housing for circuitry and board structure

### Circuit Organization
- **4× Prototyping Boards** - Organize and mount multiplexers (2 MUX per board)
- **Connecting Wires** - Color-coded for signal routing
- **Heat Shrink Tubing** - Insulation for preventing shorts in tight spaces

## Assembly Process

### 1. Prototyping Board Setup

Each prototyping board hosts two multiplexers, creating four quadrants of the chess board (16 squares each).

**Steps:**
1. Mount two CD74HC4067 multiplexers per prototyping board
2. Solder one 1kΩ resistor to each multiplexer's signal pin
3. Bridge connections on the prototyping board as needed for routing
4. **Important:** Avoid bridging connections between different multiplexers or adjacent pins

### 2. Wire Management

Proper wire management ensures reliable connections and prevents shorts.

**Best Practices:**
- Strip only enough insulation for secure connections (minimize exposed wire)
- Use consistent wire lengths where possible for clean routing
- Apply color coding to distinguish different signal types:
  - Control signals (S0-S3)
  - Signal pins
  - Enable pins
- Route wires carefully to avoid tangling in constrained spaces
- Apply heat shrink tubing to connections in tight areas

### 3. LED Installation

Each LED is soldered to wires routed from the multiplexer channels.

**Process:**
1. Route wires from multiplexer output channels to LED positions
2. Solder LED leads to the routed wires
3. Maintain consistent polarity across all LEDs
4. Position LEDs beneath chess tiles (one per square)
5. Secure connections with heat shrink where necessary

### 4. Arduino Connections

Connect the four prototyping boards to the Arduino Mega according to the [wiring guide](wiring-guide.md).

**Connection Overview:**
- 20 total pins used (4 control × 4 MUX + 4 signal pins)
- Each multiplexer requires 6 Arduino pins:
  - 4 control pins (S0-S3) for channel selection
  - 1 signal pin for LED power
  - 1 enable pin for MUX activation

### 5. Testing & Troubleshooting

After completing the physical assembly, test the system systematically.

**Startup Sequence:**
1. Upload the Arduino code
2. Run the built-in startup sequence (lights all LEDs in pattern)
3. Verify each square lights correctly
4. Check for shorts or dim LEDs indicating connection issues

**Common Issues:**
- All squares on one multiplexer lighting: Check enable pin connection
- Specific square not lighting: Verify LED polarity and solder connections
- Multiple random squares lighting: Inspect for bridged connections on prototyping board

## Circuit Design Considerations

### Multiplexer Selection Logic

Each multiplexer controls a 4×4 quadrant of the board using binary channel selection:
- 4-bit binary input (S0-S3) selects 1 of 16 channels
- Only one channel active at a time per multiplexer
- Enable pin allows Arduino to activate only the target multiplexer

### Power Requirements

- **Voltage:** 3.3V DC from Arduino Mega
- **Current per LED:** ~20mA (limited by 1kΩ resistors)
- **Total worst-case current:** 80mA (4 LEDs max simultaneously)

### Signal Integrity

The prototyping board layout minimizes:
- Wire length for control signals
- Electromagnetic interference between channels
- Voltage drops across connections

## Physical Integration

The complete chess board consists of:

1. **Base Structure** - Laser cut acrylic housing
2. **LED Layer** - 64 LEDs positioned beneath tiles
3. **Circuit Layer** - Four prototyping boards with multiplexers
4. **Control Layer** - Arduino Mega with USB connection
5. **Playing Surface** - 3D printed tiles forming 8×8 grid

## Safety Notes

- Always disconnect power before modifying connections
- Verify resistor values before connecting LEDs
- Avoid shorting Arduino pins together
- Use heat shrink tubing in congested areas to prevent accidental shorts
- Double-check polarity when soldering LEDs

## Further Reading

For detailed pin assignments and multiplexer channel mapping, see:
- [Wiring Guide](wiring-guide.md) - Complete pin connection table
- [System Architecture](../docs/system-architecture.md) - Software-hardware integration
- [Multiplexer Implementation](../docs/multiplexer-implementation.md) - Binary encoding logic
