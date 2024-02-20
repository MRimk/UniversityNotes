---
title: Embedded System Design
---

<!-- markdownlint-disable MD010 MD041 MD001 MD036 MD029 MD034-->

## Embedded System

There is no exact definition, but the embedded system is a type of computer designed to solve a specific problem or task.

It typically use a microprocessor combined with other hw and sw to solve a specific computing problem. Microprocessor range from simple 8-big verision to 64-bit or multi-cores.

Embedded system software ranges from a small executive to a large real-time operating system with a GUI.

Typically, the embedded system software must respond to events and must not crash.

### How to design the system

Waterfall model:

1. System specification
2. ASIC design (black boxes drawings)
3. HW prototype design
4. Firmware design
5. Software design
6. System integration and test
7. Industrialisation (optimize for production)
8. Support and maintain the product in the market

This takes way too long. Nowadays time to market is very important.

Therefore now a different method is used: Hardware/Software co-design:

1. System specification
2. Architecture exploration and Hw/Sw parititioning using virtual prototyping
3. In parallel: \
   ASIC design -> hardware prototype design \
   Firmware design -> Software design
4. System integration and test
5. Industrialisation (optimize for production)
6. Support and maintain the product in the market

### Virtual prototype

A system that emulates the complete system on a functional level (not necessarily cycle-true).

VP is based on the OpenRISC micro-controller. Is completely written Verilog and is running on the GECKO4Education EPFL-Edition.

### Embedded system components

The VP has similar components to the usual systems.

It has:

- RS232 UART which is used to debug and control the system.
- Simple 32-bit based bus architecture, to which it is easy to attach own systems (e.g. DMA controller)
- VGA text and GUI controller (720p)
- SPI-flash interface wher you can store the program
- OpenRISC CPU, which has instruction cache and 4kByte Scratch pad memory

### HW/SW partitioning

For now it is usual to take one microcontroller (usually an overkill) and then put as much software as it requires. The problem is when it is put under a battery power.

Standard hardware is not sufficient, so application-specific hw is necessary. To have this, hardware/software partitioning is used, and trade-offs are adhered to.

There is no one way to partition the system.

#### The tradeoffs

Performance, Area, Energy, and the biggest - Time-to-market

The most expensive is the engineer.

#### How to do it - example

Take a camera module. It provides data in RGB565 (because we are most sensitive to green). It gives an image of 640x480 pixels. It produces 15 images each second.

Storage inside the chip is very expensive, thus we transfer the date using DMA-master to SDRAM controller.

We also have VGA controller that has HDMI connector of 60 images each second. DMA-master transfers the information from SDRAM controller.

We want to have edge detection on the live stream.

It is done on the OpenRISC processor. Make the grayscale and then with the Sobel algorithm we get the edges.

How does edge detection work: if there is a big difference between two columns (or rows) of the pixels, and if the contrast is above the threshold, then there is an edge. This is Sobel algorithm.

For vertical edges there is a matrix filter (note that it shrinks the image by an removing outer pixels):

$$
\begin{matrix}
-1 & 0 & 1 \\
-2 & 0 & 2 \\
-1 & 0 & 1
\end{matrix}
$$

And for horizontal edges there is this filter:

$$
\begin{matrix}
-1 & -2 & -1 \\
0 & 0 & 0 \\
-1 & -2 & -1
\end{matrix}
$$

And then the pixels with edges are estimated $\sqrt{dX^^2 + dY^^2}$ with $|dX| + |dY|$. And then put this estimation on the threshold, which either gives a 1 or 0 (draws the pixel or does not).

This is an inefficient way of doing this algorithm, because you need to read the image twice (transfer the image over the bus twice).

To optimize this algorithm: we take the 9 pixels, compute dX, dY in registers, compute the threshold, and save the pixel. Thus it saves the work for DRAM and the bus.

It is still impossible to do this, because the cpu cycles per pixel for the Sobel algorithm is 30 cycles, and the available cycles (calculated for hw), it is only 16 cycles. So it is not real time edge detection.
