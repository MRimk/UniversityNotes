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

## Custom instructions

### ALU

it is the heart of the microC

it receives two data (Ra, Rb) from the register-file and produces one result (Rd) to the register-file.

The operation done is selected by the control signals (Cimm, Ccsel, Cminus, Copp), that are set depending the instruction.

Note that only one operation can be selected, although all operations are performed.

E.g. this line:

```C
result = (((rgb565 & 0xF800) >> 8) * 5) >> 4;
```

would result in these operations in ALU:

```asm
l.andi r5,r5,0xF800     # rgb565 & 0xF800
l.sri r5,r5,8           # (rgb565 & 0xF800) >> 8
l.muli r5,r5,5          # ((rgb565 & 0xF800) >> 8) * 5
l.sri r5,r5,4           # (((rgb565 & 0xF800) >> 8) * 5) >> 4
```

However, in HW it's way simpler: select wires for the first instr, a\*5 translate to a\*2 + a (so only 10-bit adder), and then b>>4 which is just wiring.

### Custom instruction hw interface

The minimal set of signals that the µC provides us with to create custom instruction hardware is (note: input/output is from the perspective of the µC):

| Name     | Direction | #bits | Function                                                   |
| -------- | --------- | ----- | ---------------------------------------------------------- |
| ciStart  | output    | 1     | Indicates an active custom instruction                     |
| ciN      | output    | 8     | The custom instruction identifier code.                    |
| ciDataA  | output    | 32    | The value of register A (Ra) going into the ALU/CI.        |
| ciDataB  | output    | 32    | The value of register B (Rb) going into the ALU/CI.        |
| ciResult | input     | 32    | The result value to be written to the register file (Rd).  |
| ciDone   | input     | 1     | The signal indicating that the CI performed it’s operation |

The `ciDone` signal is a very important signal. If the µC activates a custom instruction by the `ciStart` signal it will wait (stall) till an activation of the `ciDone`. If the `ciDone` is not activated your system will **DEADLOCK**!

The signal `ciN`` indicates which custom instruction is activated. As this signal is 8-bit wide we can implement up to 256 custom instructions.

#### ci example

We can implement multiple custom instructions. Why not "multiplexing" the ciDone and the ciResult signals by using the ciN signal?

Very simple: multiplexers have more logic as simple or-gates (or and-gates, the alternative)...

This poses, however, some restrictions that we have to take into account when designing a custom instruction module....

Timing requirements: assume that the custom instruction hw has the custom instruction identifier 0x17.

When the `ciN` does not correspond to the custom instruction identifier no `done` is generated.

If it does correspond, we can have a single-cycle or a multi-cycle response (any number of cycles between the start and done). For example, stall for some delay, and the ci will stall the CPU for specified number of microseconds

> Note that in case of a multi-cycle response the µC is stalled!

### Custom instruction SW interface

To interact with the ci, we need to activate them with assembly instruction, since compiler does not know it. E.g. (note that 0x17 is the ci identifier):

```C
uint32_t result, regA, regB;
asm volatile ("l.nios_rrr %[rd],%[ra],%[rb],0x17":[rd]"=r"(result): [ra]"r"(regA),[rb]"r"(regB) );
```

Some variations:

```C
// ci with only inputs, e.g. for a flipflop outputs to another flipflop (this is defined in hw)
// :: is required because after the first : are the registers that are written, and after the second : are the registers that are read
asm volatile ("l.nios_rrr r0,%[ra],%[rb],0x1A"::[ra]"r"(regA),[rb]"r"(regB) );

// ci with only an output, e.g. output of several chained flipflop
// second : is not required here
asm volatile ("l.nios_rrr %[rd],r0,r0,0x72":[rd]"=r"(result) );
```

`r0` is used as a replacement for `rd`, since it is the dummy register in RISC arch (writing to it does nothing, reading always gives 0)

Compiler looking into this code cannot infer if it can apply any optimizations, since it does not know what it happening.

#### ci Usage

Example, for converting rgb to grayscale:

```C
void rgbToGrayscale( int width,
                     int height,
                     const uint32_t *rgb_source,
                     uint32_t *grayscale_destination ) {

   int loop;
   uint32_t temp, grayscale;

   for (loop = 0; loop < width*height; loop++) {
      temp = rgb_source[loop] & 0x3F; // red value
      grayscale = temp*77;
      temp = (rgb_source[loop] >> 8) & 0x3F; // green value
      grayscale += temp*151;
      temp = (rgb_source[loop] >> 16) & 0x3F; // blue value
      grayscale += temp*28;
      grayscale &= 0xFF00;
      grayscale_destination[loop] = (grayscale << 8) | grayscale | (grayscale >> 8);
   }
}
```

This is a lot of operations: mask, multiply, shift + mask, multiply ....

In DFG (data flow graph), we can group actions into groups:

- reading: software load of RGB-values
- putting values into expected formats: shifting and masking has no cost in hw (just wiring)
- calculating grayscale: fixed coefficient multiplication of 8x6 bits and addtition can be performed in less than 1 CPU clock cycle in hw
- result value: shifting and formatting has no cost in hw (just wiring)
- storing: software store

We reduce this algorithm to the: load, ci, store. And the speedup is the number of instructions removed.

### Profiling

Profiling is used to see the hotspots and see what the hw enhancements influence is.

Examples of it is gprof of the GNU-tool-chain, or valgrind and kcachegrind.

However these tools gives use just info on execution time, not the limitations/hotspots due to hw.

#### Profiling limitations

Software:

- It requires representative data-sets to profile as:
  1. a given data-set might not trigger some parts of the code resulting in improper profiling information
  2. a given dataset might be a corner case only banging on one function resulting in improper profiling info
  3. in general: garbage-in => garbage-out
- Profiling should be performed on the target hw, as compilers optimize different
- the program should behave properly, e.g. profiling might be useless due to the use of function pointers

Hardware:

- If profiling is done on another architecture the results can be bogus as it does not represent the dynamic behavior of the target system.
- Modeling of all parameters in the virtual prototype has to been done correctly, otherwise the real SOC can behave completely different.

#### Profiling information

- On fixed systems we are only interested in the number of cpu-cycles burned, as we cannot change the underlying architecture.
- This is very often accomplished by using performance counters. Performance counters are hardware counters that count clock-cycles (your I3/I5/i/ for example has such counters build in).
- in SOC design we have the liberty to modify the arch and the sw
- here we are often also interested in more hw speficific parameters as:
  - bus occupation (natural bottleneck)
  - cpu stall cycles
  - cache hit/miss ratio
  - cache thrashing latencies

All of this can be accomplished with performance (hw) counters

#### Performance counters limitations

Limited by the number of bits they have (hence the "time" they can measure)

They take area on the FPGA, so usually you have two versions - with and without perf counters

The hardware needs to be observable (as in our case where everything is available in verilog) in many cases it is not the case as some parts are provided as IP-cores, in which case the perf counters can use "models"

sets of models known are: worst case, typical case, best case.

## Timing closure

To get the system running at the required frequency we need to go into the phase called _timing closure_

### RTL (Register Transfer Level) design

To prevent gated clocks the flipflops are connected to the same clock source.

We know that due to transistor capacitance all gates have a date delay that causes hazards.

Hazard - change in level that are caused by time gate delays

**Critical path** - longest combinational path between two flipflops. We need to wait for critical path time to be sure on the value and that we are not hitting on the hazard.

What happens with the clock line? There are 3k flipflops in the mc and all are connected to one clock line <- the clock line thus would have a big capacitave load. The RTL-design method assumes that the rising edgeg of the clock arrives at all flipflops at same time.

#### Avoiding big capacitive load

Use binary tree of inverters because they will reduce load on each output. Howver what is the resul of this op?

We introduce at the flipflop level a clock-skew (can be positive or negative) due to the fakc that not all inverters have the same delay and line-length-mismatches

There is also jitter - due to temperature and other things transistor flips back and forth.

To reduce jitter and skew we have clock tree in form of a H-tree (fractal). Clock is inserted in the middle, and inverters are at the split points, and at the leaf points the flipflops and memory is connected.

#### Setup and hold

Flipflops particularity - output delay and setup-and-hold time.

Setup and hold time - in which the D-input needs to be kept stable (otherwise the flipflop goes into meta stable state - oscilation, which ends up into unknown state).

Problem this causes - finite state machine goes into a ghost state and stays in the ghost state.

What could cause this condition (in relation to the clock time):

1. The path between two flipflops is too fast (race-condition)
2. The path is too slow (frequency cannot be met)

#### Race condition

Putting together, the uncertainty we have - 2 \* skew + jitter

If the output of flipflop C changes before setup-time of flipflop B, hence we have a functional error as the data is too early available.

The output of flipflop C changes during tDstable of flipflop B which goes in meta stable state (Note that this situation will always happen independent of the clock frequency!).

The problem can be solved by inserting a delay between the flipflops C and B. We don't have to do this ourselves because it is done by synthesis tools

This does not prevent hazards but does not produce hazards

#### Timing not met

$t_{p,clock} = t_{clock\_to\_output} + t_{critical,max} + t_{setup} + t_{uncertainty}$

We know that during the critical path time we may have hazards on the D-input of flipflop C, and that the correct value is available after $t_{critical_path}$.

All timing analyzers are in cases: best, typical, and worst case. These models are based on the distribution of produced chips.

Tools use worst case timing model so that it makes sure that it works with the given frequency

Note that the synthesizer and/or P&R-tool might insert in front of the combinational logic some inverters to prevent flipflop C from going into meta stable state due to $t_{Dstable}$ violation caused by hazards!

Timing is not met when there exists at least one combinational logic path with a $t_{critical\_path} > t_{critical\_path,max}$.

### What is timing closure

Process of getting all $t_{critical\_paths} < t_{critical\_path,max}$.

But that's not all, we have two more timings that need attention:

1. The latest arrival of an external input signal (tlai) to the flipflop with respect to the positive clock edge. Peripherals that receive signals outside of the chip
2. The latest arrival of the signal from a flipflop to the edge of the package (tlao) with respect to the positive clock edge.

It used to be 4ns to go from chip to off-chip and same vice-versa => 8ns delay to go to chip.

These numbers depend on the chip pconnected to this one and are in general more difficult to determine.

We need to specify input-output delays

#### Timing closure off-chip

**If you go off-chip - you put a flipflop in-between, and same vice-versa**

More in detail: The later aspect is “easily” solved by not using any combinational logic between the input(s) and the fist flipflop(s) and no combinational logic between the last flipflop(s) and the output(s).
**This has the advantage that you do not have any hazards outside of your chip (good thing!).**

However, this is not always possible, in this case more advanced methods are required like:

- Usage of a PLL/DLL to synchronize the attached chip with yours (think of DDR memory).
- Adding extra delays in some of the outputs to meet external timings.

#### How to reduce critical paths

On-chip aspect synthesis tool is more intelligent.

Methods that the synthesizer does not know about:

- **Fine-grained paralyzing**
- **Multi-cycling**
- **Pipelining**

#### Speeding up your circuit

Have: 4-bit carry-riplle adder (CRA)

Assume this adder is in the critical path.

The critical path from this adder goes from Cin through the and- and or-gates up to Cout/S3 - the carry path

What are the speed-up methods:

- Trading-off bigger area/energy consumption against speed
  - This is an example of Fine-grained paralyzing
  - We cut circuit in the middle, and we calculate the top when the carry is 1, and we calculate the top when the carry is 0. We select the result with a multiplexer.
  - This circuit becomes carry select adder that is almost twice as fast - single cycle 4-bits addition
- Trading-off time against speed
  - Example of pipelining
  - In this method we divide the critical path in 2 (or more) parts and place a row of flipflops between the parts.
  - The advantage is that we can do a calculation each cycle.
  - However, we introduce latency, which could cause problems in case of a feed-back loop (e.g. data dependencies)
- Trading-off latency (performance) against area
  - Example of multi-cycle operation
  - We calculate one bit per cycle. (Of course this has an impact on the performance, as now the addition takes 4 cycles instead of a single cycle.)
  - Very often we perform a radix-N multi-cycle operation where at each cycle N-bits are determined.
  - Of course, when A and B are guaranteed to be constant between `start` and `done`, we can replace the input shift-registers by a multiplexer
  - This is nice for division because it is difficult - it is subraction and dependance. On a 32-bit CPU using a library, we need 120 cycles for Integer division.

