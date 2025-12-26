# Technical Documentation

This folder contains detailed technical documentation for the LED Chess Board project, explaining system architecture, implementation details, and design decisions.

## Documentation Index

### [System Architecture](system-architecture.md)
High-level overview of how the hardware and software integrate to create the chess board. Start here for a quick understanding of the complete system.

**Topics covered:**
- System overview and data flow
- Hardware-software integration
- Component interaction
- Design rationale

### [Multiplexer Implementation](multiplexer-implementation.md)
Deep-dive into the multiplexer control system, including binary channel selection and LED control logic.

**Topics covered:**
- Binary encoding for channel selection
- Multiplexer enable/disable logic
- Non-blocking LED blinking implementation
- Performance optimizations

### [LED Mapping](led-mapping.md)
Explanation of how chess board squares map to multiplexer channels, including the algorithmic approach to position translation.

**Topics covered:**
- Chess notation to MUX/channel conversion
- Quadrant-based mapping strategy
- Position lookup algorithm
- Move visualization system

## Quick Reference

### System Specifications

- **Microcontroller:** Arduino Mega 2560 (ATmega2560)
- **I/O Pins Used:** 20 (out of 54 available)
- **Multiplexers:** 4× CD74HC4067 (16-channel each)
- **LED Control:** Binary channel selection via 4-bit input
- **Memory Usage:** ~20% of available flash (600+ lines of code)
- **Response Time:** <10 seconds for move calculation

### Key Technical Achievements

1. **Pin Efficiency:** Reduced from 64 direct pins to 20 using multiplexers (69% reduction)
2. **Memory Optimization:** Full chess engine in <20% of available memory
3. **Real-time Control:** Non-blocking LED animation during move processing
4. **Complete Chess Rules:** All standard rules including castling, en passant, and promotion

## Design Philosophy

The LED Chess Board demonstrates several embedded systems principles:

**Resource Optimization**
- Multiplexing reduces hardware requirements
- Efficient code enables complex algorithms on constrained hardware
- Binary encoding minimizes signal complexity

**Modular Design**
- Separate functions for MUX control, chess logic, and user interface
- Hardware abstraction allows code portability
- Clear separation of concerns

**Real-time Responsiveness**
- Non-blocking LED updates maintain system interactivity
- Efficient move calculation keeps response time under 10 seconds
- Serial interface provides immediate feedback

## For Employers & Evaluators

This project demonstrates competency in:

- **Embedded Systems:** Arduino programming, hardware control, resource management
- **Digital Logic:** Binary encoding, multiplexer operation, signal routing
- **Algorithm Implementation:** Chess engine adaptation, move validation
- **Circuit Design:** Component selection, pin assignment, power management
- **Documentation:** Clear technical writing, systematic organization
- **Problem-solving:** Pin limitation workarounds, memory optimization
- **Team Collaboration:** Hardware/software integration, task coordination

## For Students & Learners

If you're building something similar or learning from this project:

1. **Start with system-architecture.md** - Understand the big picture first
2. **Read multiplexer-implementation.md** - Learn the core control mechanism
3. **Study led-mapping.md** - See how abstract concepts map to hardware
4. **Review the code** - Located in `/src/finalChess.ino`
5. **Check the hardware folder** - Physical implementation details

## Related Resources

### In This Repository
- [Main README](../README.md) - Project overview and features
- [Source Code](../src/finalChess.ino) - Complete Arduino implementation
- [Hardware Documentation](../hardware/README.md) - Assembly and wiring
- [Bill of Materials](../hardware/BOM.md) - Component list
- [Wiring Guide](../hardware/wiring-guide.md) - Pin connections

### External Resources
- [Wokwi Simulation](https://wokwi.com/projects/428952069470626817) - Interactive circuit
- [Micro-Max Chess Engine](http://home.hccnet.nl/h.g.muller/max-src2.html) - Original algorithm
- [CD74HC4067 Datasheet](https://www.ti.com/lit/ds/symlink/cd74hc4067.pdf) - Multiplexer specs
- [Arduino Mega Documentation](https://docs.arduino.cc/hardware/mega-2560/) - Board reference

## Project Context

**Course:** ENGR 470 - Mechatronics I, Western Illinois University  
**Semester:** Spring 2025  
**Team:** Hannah Stevenson, Maria Uribe, Ryan Vance

**Learning Objectives:**
- Integration of mechanical, electrical, and software systems
- Embedded systems design and implementation
- Real-world problem-solving with constrained resources
- Professional documentation and presentation

## Feedback & Questions

This documentation aims to be clear and comprehensive. If you find sections unclear or have suggestions for improvement, we'd appreciate feedback!

## License

This documentation and associated code are licensed under the MIT License - see [LICENSE](../LICENSE) file for details.
