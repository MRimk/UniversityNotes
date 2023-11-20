<!-- markdownlint-disable MD010 MD041 MD001 MD036 MD029-->

## Mobile security

### Mobile security motivation

Phone on 100% CPU capacity will be on for 10min.
So everything needs to be throttled.

A lot of sensors that are carrying personal data.

More exposed to local attackers (e.g. phone left at the bar)

Mobile computing is considered as one of the computing revolutions

### Attack vectors

#### Types of malware: repackagring / look-alike Malware

Download app from app market.
Unpack and reverse endgineer app (relatively easy on Android)

Modify and add code:
add ads, require more permissions than original app to steal user data, escalate privileges using exploits to deploy ransomware ...

Pack and publish modified version.

This is not a targetted attack, just broad attack.

#### Privacy of digital content

Steal digital content from content providers.
Platform needs to support for secure audio and video playback, and premium content must not leave the device.

Streaming services usually require platform with digital rights management (DRM, e.g. Google Widevine or Microsoft PlayReady) to stream premium content.

Why do we need DRMs on the system itself?

- the system is not trusted
- to put watermarks on the stream (e.g. netflix id), since on the server it would be very expensive on the server.

#### Broader - Political instrument

there are companies that provide access to people's phone's

Usually these services, e.g. NSO, are sold to the CIAs, FBIs, other agencies that, e.g. kill journalists

### Android vs iOS

The biggest difference - **openness**.

#### Apple's iOS ecosystem is **extremely closed**:

- iOS is a closed source
- iOS and iOS apps can only run on Apple devices
- you can install apps only from Apple Store (potential change due to EU)
- Tricky to "jailbreak" iOS devices

How come they still are aroud?:
they were first, and they make great prodcuts and people know about it

#### Google's strategy

Even though they started earlier, they were late to market it.

Ecosystem is much more open:

- Android/AOSP is open source
- Android can run on many different devices, even non-Google ones
- easy to inspect Android apps/reverse/modify
- Easy to install apps you develop ("side loading")
- developers can do many more things
- quite easy to "jailbreak" Android devices

Android is likely more secure as long as you keep updating security

### ARM - ARMv8

#### ARM processor profiles

Cortex-A - full application (offers more features)
Cortex-R - real-time (industrial control, and tight scheduling bounds)
Cortex-M - embedded (small embedded chips, most IoT runs on this)

#### ARM ARMv8 privilege levels

|     | Normal world (Rich Execution Env) | Secure World (Trusted Execution Env) |
| --- | --------------------------------- | ------------------------------------ |
| EL0 | Applications                      | Trusted applications                 |
| EL1 | Rich OS                           | Trusted OS                           |
| EL2 | Hypervisor                        |                                      |
| EL3 | Secure Monitor                    | Secure Monitor                       |

x86:
ring -2 - Firmware manager
ring -1 - Hypervisor
ring 0 - OS
ring 1 - nothing (intended for drivers but they run at ring 0)
ring 2 - nothing (intended for drivers but they run at ring 0)
ring 3 - Applications

How does this relate to mobile device security:
Rich OS - apps
Trusted OS - crypto, passwords, fingerprints, keys

#### Details of ARMv8 ISA

To do computations you need to load and store first.

Instructions are 4 bytes, Load-store architecture, familiar concepts - stack pointer, frame pointer (x29), function calls (bl), stack frames...

QEMU allows to emulate other architectures.

to compile into ARM and to run it on x86

```bash
aarch64-linux-gnu-gcc -g -O0 -fPIE -pie -o main main.c
qemu-aarch64 -L /usr/aarch64-linux-gnu/ main
```

### Android ecosystem and security

#### Android Open Source Project (AOSP)

Android is "**owned**" by Google, but code is made availabe through AOSP.

OEM customizes code to their hw, adds proprietary components (e.g. for hw support)

Google Mobile Services require OEM to comply with compatibility definition document - provides this or other services, drivers, etc.

#### Chip -> phone

ARM (ISA and design creator) -> chip manufacturers (ODM - Original design manufacturer) who pay ARM for licensing, and add their extensions -> phone (OEM -> Original equipment manufacturer)

#### "Open" in AOSP

Q: “How does setting a PIN/pattern/password work?”

1. Determine component that implements feature
2. Figure out AOSP release
3. Look for component in AOSP
4. Read code until you are satisfied

#### "not-so-Open" in AOSP

Enrolling and verifying passwords is a security-sensitive feature. The backend of this feature is implemented by the **Gatekeeper subsystem**
The subsystem often uses trusted execution env (the safe space) and is usually platform-dependent (~proprietary)

It guarantees stronger confidentiality

Throttles consecutive failed attempts

#### Android devices

Many different players - many different hw OEMs

Many different Anfdroid versions:

- not all devices support all versions
- some devices never get updated
- most devices get updates only for 2/3 years
- Android versions distribution secluded

Regular Android app ships with 32-bit ARM, 64-bit ARM, and some RISC5

#### Android fragmentation

Fragmentation is the **biggest challenge** for Android security, since thousands of devices with custom hw and sw
Customization makes development and aptching tricky.

#### Lif og a security bug

Reporting:

1. Discovery: Security researcher (Google's or external) finds a bug
2. Disclosure: Report the bug to Google
3. Reception:
   - [ Hope the bug reaches the right Google employee ]
   - Google acknowledges the bug and will work on a fix

Fixing:
Coordinated Disclosure
[ Wait n days, industry standard: 90 days ]
Publicly disclose the bug

Security patch distribution
Google distributes the patches to other manufactures
Patch is published as part of the Monthly Security Bulletin

#### Perils of customization

Google sends patch to third-party company X: Company X now needs to apply the patch to their custom AOSP fork

**Project treble**

Previously: no clear interface between Android OS framework and vendor implementation
So when Android OS is updated - vendors lose time integrating the new patches and this introduces new costs and overheads and delays

Project Treble helps defining a clear interface
Note: this is useful for non-security patches as well

Introduced with Android 8.0+

#### Most devices don;t get security patches

only 2/3 years of updates because vendors are not interested in supporting old devices.

#### Role of Security researchers

Identify malware

- Once a new malware is found, it's added to blacklists
- Any app "similar" to the malware will be flagged and removed

Security vulnerabilities

- Once they are found, they are reported to Google
- Monetary rewards for security bugs: "Bug Bounties”

#### Attacker goals vs security researchers

Security researchers want to

- Identify malware (add to disallow-lists, flag apps “similar enough” to listed malware apps)
- Report security vulnerabilities for bug bounties

Attackers want to in general: run code on your device and do XYZ

Two main important topics:

- Malware analysis, detection, containment
- Vulnerability analysis, detection, prevention, patching

### Android Apps

written in Java, C/C++, Kotlin, Rust, ...

Android apps “live” in the Android context:
Android framework exposes a gigantic number of APIs
APIs somewhat equivalent to "library functions"

APIs are useful for:

- apps to interact with the “external world” (via the API)
- the Android framework to interact with the Android app, e.g., where does the execution start?
- to extend Java SDK APIs: Many APIs from the Java world are part of the Android APIs

APIs examples: HTTP request, Log message, access to GPS/location info

**Android Framework APIs** - too many to be enumerated

**Package name** - each app has a package name

#### Basics on Android apps

there is no "main" function

The user interacts via the Graphical UI - UI widgeds (EditText, Button), no CLI

Many APIs are "event-driven" - register a listener X and X's callback is invoked later on

Apps are build on combination of "components"

#### 4 Component types

##### Activity

Entry point for interacting with the user, and it represents a single screen with UI.

You can have many - each defines a UI
You can define which is the main/start one
If app allows it, an external app can start these activities at will

##### Service

Meant to perform an action in the background for some period of time, regardless of what the user is doing in foreground (the user could be switching between activities)

Services don't provide UI.

e.g. music player service

##### Broadcast receiver

Respond to system-wide events
Have well-defined entry point
System can deliver these events even to apps that are currently not running

Events example: battery charging, SMS is received

##### Content provider

Manage a shared set of app data
High-level API to access data so that other apps and services can query/interact with it
They abstract away the storing mechanism

Most often based on SQLit database (file-based)

##### Communication between components - intents

Android-defined objects that encode an "intent" (fancy IPC message)

Use cases:

- notation "A.X" refers to A's component X
- A.X wants to start A.Y (e.g. go to next activity)
- A.X wants to send data to B.Z
- user clicks on A's icon -> laucher app sends intent to A.MA
- note - each component has a life cycle - A.Y could already be started

#### Manifest file

Most important file of Android app

Specifies all key information needed by the fw to run the app:

- Package name
- Components app consists of
- Intent filters
- Main Activity ~> main() entrypoint
- Permissions

### App security

Android is based on Linux

Each app has its own Linux user ID (there are ways to setp apps so that they share the user ID)

Each app lives in its own security sandbox - standard Linux process isolation, restricted file system permissions

#### App installation

Android fw creates a new Linux user with a new user ID\*

each app is given a private dir - also call internal storage, where no other app can access it (unless it is with shared user ID)

#### Android Framework Architecture

User-space is app, android fw, native libraries, android runtime, HAL (audio, bt, camera)

Kernel space - Linux kernel (drivers, power management)

Between them there is a security boundary.

Instrumentation and analysis at these abstraction levels can be bypassed

**Pros** - syscall analysis CANNOT be bypassed (because of the security boundary)
**Cons** - bridging the semantics gap is complicated

**\*Manager** (LocationManager, TelephonyManager, PackageManager, ActivityManager)- lives on App and Android Framework levels. They run as "privileged" users.

##### asking the OS for favors, aka syscalls

Traditional OSes have two worlds - user-space vs kernel-space

user-space is where user processes and apps live - they can't do much by themselves

kernel-space is where the actual OS lives - the OS is the god of machine and information

##### Example - getLastLocation()

App invokes Android API:
`LocationManager.getLastLocation()`
We are still within the app's sandbox!

Actual implementation of the privileged API:
`LocationManagerService.getLastLocation()`
We are in a "privileged" service

To go to other side we need something

#### Crossing the bridge

Binder - one of the main Android's "extensions" over Linux
It allows for _Remote Procedure Call (RPC)_ and _Inter-Process Communication (IPC)_

##### Binder RPC

App that is run as non-privileged process sends Binder message over Binder "Proxy" -> Binder Driver, Linux Kernel -> Binder "Stub" -> service that is privileged process/service

##### Binder Details

Proxy and Stub are automatically generated starting from AIDL

Binder communication: perform ioctl syscall on /dev/binder

ioctl syscall:

- Multi-purpose syscall, to talk to drivers
- In the Binder context: kernel driver takes care of it, dispatches messages and returns replies

There is a lot of overhead in context switching to kernel, switch to service context, get caches, get data, switch to the app.
This works if the Binder calls are infrequent

#### Androind permission system

Manifest encodes what app wants.

Each of these "protects" security-sensitive capabilities:

- ability to "do" something sensitive - open Internet connection, send SMS
- ability to "access" sensitive information, e.g. location, user, contacts,...

More and more malware is moving to getting SMS permissions because of the 2FA

**READ/WRITE_EXTERNAL_STORAGE** - even though each app has access to a private dir, by default no other apps can access this dir.
Device offers an "external storage" - in the past physical "removable" SD card (because it had to have vFAT). Currently part of the file system that apps can use to share files, or "/sdcard" - where your photos and downloaded files are

### Reversing Android Apps

#### Compilation

Java/Kotlin compiler to Java bytecode (executable by the JVM)
then DEX compiler to Dalvik bytecode (executable by the DVM)
(whereas C/C++ compiles straight to machine code)

Java comes with copywrite and copywrite issues, so Google didn't want to be sued by Oracle anymore

#### Android Application Package (APK)

APK is a zip file

Content:

- AndroidManifest.xml (compressed)
- classes.dex (raw Dalvik bytecode)
- resources.arsc (compressed)
- res/\*.xml (compressed)

#### Big picture

from this zip file, you can unpack the individual components, libraries that are shipped.

You can disassemble DEX files, go from Dalvik bytecode to smali file type.

apktool can embed baksmal/smali
it unpacks/packs APKs, including resources and manifest files

#### Disassemble vs decompilation

Disassembly - binary file -> DAlvik bytecode "smali" representation

Decompilation - assembly/bytecode to source code-level representation (Dalvik bytecode -> Java code)
However obfuscation can make this difficult

Decompilation tools:
JEB (commercial, VERY expensive)
BytecodeViewer (pretty good one)
Jadx
NEW: Ghidra, open source tool developed by NSA

### Kernel security and SELinux

User-based permission model - each app has userID

Process isolation - applications are separate

Extensible mechanism for secure IPC

#### Application sandbox

apps are isolated from each other.
Sandbox is in the kernel, native code can't bypass it

To bypass the sandbox, an attacker would need to compromise linux

#### defense in depth

multiple layers of security controls throughout a system
it prevents single vulns from leading to compromise of the OS

> redundacy

#### SELinux

Security-Enhanced Linux: a Linux kernel security module

- Useful to define access control security policies
- Example: allow/prevent execution of syscall X

Prevents execution of system call.

"Deny by default" policy

Two modes:

- Permissive mode: permissions denials are logged but **NOT** enforced
- Enforcing mode: permission denials are logged **AND** enforced (in Android is this one)

"SELinux domain":

- a label identifying a process (one or more)
- all processes labeled with the same domain are treated equal (allow different processes (FB and FB messenger) to exchange data)

current version has 60+ domains (early version - installd, netd, vold, and zygote)

Kernel enforces strict set of permissions for each application.
Application can only communicate with the manager only if the permission was granted before -> manager does not have to implement security checks

90-95% of research is done on Android security, because iOS is closed-source
