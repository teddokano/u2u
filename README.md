# u2u

## What is this?

USB-2-UART (U2U) bridge using FRDM-MCXA153  

### What it does

An application that forward UART data between the DAP-Link interface and the Arduino shield connector (D0/D1 pins).  
The USB CDC-ACM ↔ UART conversion is handled by the on-board DAP-Link chip, not by the MCU.  
The MCU's role is to forward data between the DAP-Link UART and a second UART connected to the Arduino shield D0 (RX) / D1 (TX) pins.  

![connectors](https://github.com/teddokano/u2u/blob/main/docs/img/connectors.png)
*Board connectors: MCU-Link USB (J15) and Arduino shield D0/D1 (J1-2, J1-4)*


```
PC
 |
 | USB (CDC-ACM)
 |
DAP-Link chip        ← USB ↔ UART conversion (done by DAP-Link, not MCU)
 |
 | UART (DAP-Link side)
 |
MCU                  ← forwards data between the two UARTs
 |
 | UART (user side)
 |
Arduino D0 / D1 pins ← connect your target device here
```
*Signal flow: USB to Arduino D0/D1 pins*

### How to build
This repository can be imported into MCUXpresso IDE and MCUXpresso for VSC.  
Just import, build and run.  

### Quick check
#### LED color
Just after the program starts, the LED blinks in colors for a short time.

#### Looping back
Short the D0 and D1 pins together to create a loopback path.  
Open a terminal at 115200 baud on the MCU-Link USB port (J15) — typed characters should echo back immediately.

## Projects

### * u2u_FRDM_MCXA153
Rewritten in C++ using r01lib library API to have good extensibility.  
Bridges MCU-Link USB connector (J15) ↔ Arduino shield D0/D1 (J1-2, J1-4).

**Board:** FRDM-MCXA153  
**Environment:** MCUXpresso IDE or VS Code  

### * _r01lib_frdm_mcxa153
A library project: r01lib. This project cannot run by itself. This project is linked from `u2u_FRDM_MCXA153` project.

### * __exerciser__hello_world_generator_FRDM_MCXA153
A test tool for the bridge's RX capability.
This app transmits test data from the D1 pin continuously.

**Board:** FRDM-MCXA153  
**Environment:** MCUXpresso IDE or VS Code  

