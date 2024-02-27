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

### Memories

Accelerating in hardware - custom instructions, accelerators, stream processing. They often require some memory for temporal storage.

#### Synchronous Static Random Access Memories (SSRAMs)

SSRAMs are the only mmeory found in digital technology nodes.

These memories on-chip usually have unidirectional data-buses, hence `dataIn` and `dataOut`. Because if we have any directional bus, we need capacitors to store buffers, thus it becomes slow. The signal `address` selects the memory cell and the signal `writeEnable` indicates if the cell should be written.

There are two behaviours in case of a write (since they are synchronous):

- **write before read** - the value written to the memory cell is also available on the output. Flip flop is in the address lines.
- **read before write** - the value in the memory cell prior the write operation is available on the output. Flip flop is after the multiplexer.

Address and dataIn is stored in the flipflop at the posedge of the clock and then at the next posedge it write the data into the memory cell. Memories are completely synchronous, therefore we can use them as flipflops, which is good.

For the read, due to the synchronous behaviour, we have a delay of 1 clock cycle from when the address is put into the flipflop. This decalation of clock cycle has to be accounted.

SSRAMs can be found in different configs:

- single-ported (one address in, one data in, one data out) - this is the smallest memory, but arguably, most used.
- semi-dual-ported (A address with data in and data out, and B address with only data out) - two read-ports but only one can write
- true-dual-ported (A and B port can write and read), two complete ports that access the same memory array, but can have different clocks. This can result in undefined behaviour if the write on both busses to the same location is not prevented. Solution - block A port on the rising edge, block B port on the falling edge

##### Verilog single-ported SSRAM

SSRAM has parameters - bitwidth (how many bits data in and out have), nrOfEntries (how many entries can be stored in the memory), readAfterWrite (parametrization for later reuse)

```verilog
module singlePortSSRAM #( parameter bitwidth = 8,
                        parameter nrOfEntries = 512,
                        parameter readAfterWrite = 0 )
```

Input is clock, writeEnable (bit), address (size is log2 of number of entries), dataIn and dataOut (size of bitwidth)

```verilog
(input wire clock,
            writeEnable,
input wire [$clog2(nrOfEntries)-1 : 0] address,
input wire [bitwidth-1 : 0] dataIn,
output reg [bitwidth-1 : 0] dataOut);
```

memoryContent is a 2D array of entries of size bitwidth

```verilog
reg [bitwidth-1 : 0] memoryContent [nrOfEntries-1 : 0];
```

It works as a flipflop but is conditional on the write:

```verilog
always @(posedge clock)
   begin
      if (readAfterWrite != 0) dataOut <= memoryContent[address];
      if (writeEnable == 1’b1) memoryContent[address] <= dataIn;
      if (readAfterWrite == 0) dataOut <= memoryContent[address];
   end
```

##### Verilog semi-dual-ported

It only adds a new address and new dataOut:

```verilog
(input wire clock,
            writeEnable,
input wire [$clog2(nrOfEntries)-1 : 0] addressA, addressB
input wire [bitwidth-1 : 0] dataIn,
output reg [bitwidth-1 : 0] dataOutA, dataOutB);
```

And it has a new clock:

```verilog
always @(posedge clockB)
   dataOutB = memoryContent[addressB];
```

##### Verilog true-dual-ported

It only adds a new address and new dataOut, new writeEnable and new dataIn:

And it has a new clock:

```verilog
always @(posedge clockB)
   begin
      if (readAfterWrite != 0) dataOutB = memoryContent[addressB];
      if (writeEnableB == 1’b1) memoryContent[addressB] = dataInB;
      if (readAfterWrite == 0) dataOutB = memoryContent[addressB];
   end
```

#### SSRAMs in ASIC and FPGA

In ASIC-design the size of the SSRAms is dependent on the memory-generator and the **area** you have available. Using memory is good but it takes up space.

In FPGA-design it is more restricted as the memories are already implemented. You can only use what you have (for us it is EP4CE30) - 66 SSRAMs available.

Each of this SSRAMs can be used in such configs (all of them are 1KB in size): 8k x 1bit to 256x32bit or 256x36bit, there could also be 1k x 9bit (where the redundant 1bit is used for error detection/correction)

Other configs are possible by using partially/multiple of these SSRAMs

Synthesis tool will map verilog descriptions to these SSRAMs configs.

**However**, if the design uses more SSRAM memory bits than available on your FPGA, the synthesis tool will implement parts of the memory bits as flipflops and multiplexers. This will explode the size of the design (often it cannot be mapped any more on the FPGA) and have a sever impact on the critical path of the design (_read the speed you can operate your design_)

For small memories most FPGAs provide also the LUT-RAMs , which have most of the a 16x1bit configs.

#### LUT-RAMs

LUT-RAMs have the same synchronous write behaviour as SSRAMs but there is an asynchronous read. This is useful of softcore for the register file. This is just 16 flipflops.

To get the same behaviour on the synchronous system, you can get reads on the falling edge of the clock

##### Verilog LUT-RAMs

```verilog
module singlePortLUTRAM #( parameter bitwidth = 8,
                           parameter nrOfEntries = 32)
   ( input wire clock,
                writeEnable,
      input wire [$clog2(nrOfEntries)-1 : 0] address,
      input wire [bitwidth-1 : 0] dataIn,
      output wire [bitwidth-1 : 0] dataOut);

   reg [bitwidth-1 : 0] memoryContent [nrOfEntries-1 : 0];

   assign dataOut = memoryContent[address];

   always @(posedge clock)
     if (writeEnable == 1’b1) memoryContent[address] = dataIn;
endmodule
```

### How to use these memories?

Each of the buffers are used for particular data-accesses in the system.

#### Ping-Pong buffers

Producer writes its data in one memory whilst the consumer reads form the other memory. The moment both are done, the memories are switched.

Applications:

- data-transfer calculation overlap - calculating when transfering data (e.g. DMA transfering data when CPU is calculating)
- the acces pattern of the producer is different from the consumer. E.g. in Sobel algorithm, producer gives lines whereas consumer needs matrices
- the push/pop frequency is different hence the producer/consumer have other timely accesses. E.g. camera only getting pop only when the data is pushed which is rare.
- the consumer needs to access certain data multiple times, whilst the producer only provides it once.

Pro: they are the most versatile kind of buffers

Cons: need to have two SSRAMs and hard to derermine the size of them?

There is an inferred delay as the consumer always performs the calculations when already one set of data is provided by the producer. In the high-frequency environment this could be negligible, but it could be also important dependant on the application.

What is the influence on _area_, _performance_, _power consumption_ and _complexity_? (e.g. testing time)

Everything depends on the requirements and trade-offs.

#### LIFO buffers

It has an up/down counter that generates the addresses for the SSRAM. With a push it counts up, and with a pop you count down and that way you get the information.

Typical applications:

- data reordering (e.g. camera gives data from left to right, and screen is drawing right to left)
- temporal storage of values (stack or hardware stack)

In practice they are not that often used, more preffered are FIFO buffers.

#### FIFO buffers

SSRAM is transformed into a circular buffer. This uses binary counter which can overflow and therefore become circular.

At the beginning the FIFO is empty, so push and pop pointers are equal.

When the producer pushes, the push pointer is incremented. However, if the push pointer is equal to pop pointer - 1, the buffer is full, which makes it lose one slot.

The consumer can pop until the queue is empty.

The consumer and producer has both actions such that state of FIFO changes continuously

These are the most used buffers.

Applications:

- timely access pattern buffering
- save clock-boundary crossings (one part works at freq x, and another works at freq y, so use the FIFO buffer to pass the data in between)

### Testbenching

Design is Device under test (DUT)

At the input there is input stimuli generator, which provides test vectors

At the output, the correctness is verified by Output reachtion checker

The input generator and the output reaction checker form the test-harnas

The test-harnas is described in a new module, where DUT is used as a component.

Testbench requires a timescale - simulation for after-synthesis

`$dumpvars` indicates which signals we see: 0 - see inputs and outputs only, 1 - everything inside of the DUT, 2 - ??
