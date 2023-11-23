<!-- markdownlint-disable MD010 MD041 MD001 MD036 MD029-->

## Exercises 9

**Exercise 1**
Identify three examples to convince this guest that the software stack on his phone is only partially open source.

1. The platform-dependent parts for a given hardware platform need to be added to the AOSP to make it run on a given chipset. These platform-dependent parts are usually not opensourced.
2. OEMs usually heavily modify the AOSP to create a unique user experience on their platform, hoping to get a competitive advantage. Many components of Samsung’s "One UI" are not open-sourced.
3. The software/firmware running in the TEE, wifi chip, Bluetooth chip, and baseband chip is not open-sourced.

**Exercise 2**
Let us say you want to implement an image parser in a C/C++ native library to gain more performance and have a better user experience. When loading images directly from the web in your app that uses this library, what could go wrong?

• If there are bugs in this native library, the app might crash, resulting in a bad user experience.
• In the worst case, this bug might lead to code execution in the context of your app, given a specifically attacker-crafted image.

**Exercise 3**
Explain to the developer what a republishing scheme is and why it is possible on Android.

1. In a republishing scheme, malware authors download an existing app from an app store, reverse engineer it, and add malicious code to it. They publish this stolen app via app stores to follow their nefarious intentions.
2. For example, one way to make money for the malware author is by adding ads to the stolen app.
3. It is possible to reverse engineer Android apps because the code is delivered in an intermediate representation (Dalvik bytecode) that contains most of the original type information. The Dalvik bytecode can, thus, be translated back to a human-readable assembly representation (e.g., smali) or even to the source code (e.g., Java).

**Exercise 4**
Since you actually read (parts) of the research articles published with these prototypes, you chime in and explain that a CPU emulator alone is not enough to run these components. Come up with an argument to convince the security researcher.

PartEmu and FirmWire need to implement all the peripherals (e.g., memory-mapped input/output) the TEE OS or the baseband firmware, respectively, are interacting with. These peripherals are private, and it requires a lot of reverse-engineering effort to implement an emulation layer that works sufficiently accurate.