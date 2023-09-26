<!-- markdownlint-disable MD010 MD041 MD001 MD036 MD029-->

# Information Security and Privacy

## Introduction to cyber threats

**Cyber threats**
Def 1: potential cause of an unwanted incident, which can result in harm to a system or organization

Types of threats:

- environmental threats: fire, water, pollution, earthquakes...
- loss of essential services: power, cooling, communication
- technical failures: disk failure
- cyber: malicious software, denial of service, social engineering, software vulnerabilities/exploits

### Motivation for attacks

Originally - curiosity, fun, fame

Now:

- profit - small crime, organized crime, industrial espionage
- beliefs (hacktivism) - e.g. Anonymous, Lulzec, Guardians of Peace
- national security - police forces, national intelligence

Profit (dark side):

- getting clicks on spam or ads
- resale of accounts, credit card numbers
- rental of hacked PCs (botnets)
- demand of ransom

Profit (gray side) - sell the vulnerabilities you discover to some broker

### Value of a hacked PC

Hacked PC has a lot of value for various exploits (see slide 0x01 6)

### Cyber attack lifecycle

Preparation:

- define target, from broad (everyone) to focused (individual)
- find and organize accomplices
- build and/or acquire tools
- research target (infra & people)
- test for detection

Gain access:

- deployment (social engineering, exploits, etc)
- initial intrusion
- outbound connection extablished

Maintain access:

- strengthen foothold - persistence, lateral movement
- expand access, obtain credentials

Complete mission:

- exfiltrate data
- manipulate, sabotage data

Cover tracks - delete log data

### Commodity threats

they are non-targeted ("shotgun" approach)
usually non-stealth and fully automated
goal is often short-term financial gains
often considered low-risk for the attackers
possible starting point for more sophisticated attacks

Forms:

- malware infected spam
- extorsion spam
- malicious ads
- computer worm

#### Malware spam

It is sent broadly to many people (i.e. not targeted)
Crude customization (e.g. Swiss Post, Linkedin)
Attachment contains well-known malware
Campaigns are life hours to days

#### Extorsion

Sent broadly to many people (i.e. not targeted)
Relies on leaked information, e.g. password lists
Convinces user of "hack"

### Hacktivism

Several meanings such as: politically moticated hacking, variant of (anarchic) civil disobedience

Good options:

- create software to encrypt communications
- create tools to bypass censorship

Cyber threats:

- website defacement (e.g. Anonymous, Lulzsec)
- Anonymous publication of confidential data (wikileaks, i guess)
- DDoS

#### Examples of Hacktivism

Panama Papers (2016):
Somebody stole and published documents about 214,000 offshore companies incorporated in Panama

Epik data breach (2021):
A group of hacktivists exposed customer personal and credit card information, company emails, etc. from websites hosting extremist content, called the ‘Panama papers of hate groups’

OpRussia (2022):
Anonymous launched cyber operations against the Russian Federation in retaliation for the invasion of Ukraine. Website defacement, email leaks from weapon manufacturers, hacked TV channels and surveillance cameras, etc.

### Advanced Persistent Threat

**Advanced** - targeted, multi-step attack, often uses specialized tools, often starts with spear-phishing (targeted phishing attack)

**Persistent** - 'low and slow' approach, prioritize long-term over short-term goals, conitnuous monitoring and interaction (attacks are known to have lasted 5 years)

**Threat** - human coordinated attack; attackers are skilled, motivated and well-funded (e.g. industrial espionage). No 'fire and forget' approach, not fully automated

#### Example of APT: RUAG

### Classes of Malware

Virus - spreads by infecting other files

Worm: spreads automatically to other systems

Trojan: malware hidden in useful software

Rootkit: hides presence of malware on computer

Ransomware: encrypts files and requests payment for decryption

Nation state malware: malware developed by a nation-state

#### Virus

Virus is a malware that infects a file and replicates by infecting other files

By definition, it does not propage automatically to other computers.

(Also, generic term for malware)

#### Worm

Worm is a piece of malware that propagates automatically

_Morris worm_:

- first internet worm, written by R T Morris at Cornell in 1988
- used vulneravilities in sendmail, finger and rsh software to propagate
- inteded goal - map the existing internet
- accidental side effect - computers could be infected multiple times, overloading them until they were unusable
- infected 10% of the internet (estimate)
- Morris got 400 hours of community service and 10k fine

#### Trojan

Strictly, a malware hidden in a useful software or file (e.g. pirated game)

More generally, a malware that stays on the victim's computer and communicates with a control center to carry out malicious activity

_ZeuS Trojan_:

- sold as kit for 3-4k
- infected millions of computers
- captures passwords and other information
- steals money through online banking
- over 100 people arrested (money mules)
- alleged mastermind was arrested in 2013

#### Rootkit

Rootkit hides the presence of malware on a computer

It patches the OS such that malicious files, processes, communications are not shown anymore

It makes it very difficult to detect and eliminate the malware

This is why you should boot from clean OS to search for malware on your system

Modern OSes verify the integrity of all privileged code (kernel, drivers, modules) before running them

Modern rootkits therefore modify the OS before it boots by infecting the boot sector or by infecting the BIOS!

#### Ransomware

Ransomware encrypts the files and requests payment for decryption

After payment is received, the decryption key is (often) obtained

Bitcoin has made it possible for malicious software developers to make a lot of money with little effort or risk

according to Symantec, in 2014 CryptoLocker extorted about 23mil

Typical ransom for private users are ~500, companies pay much more

Simple way of limiting rist are recent (offline, protected) backups

#### Nation-stae Malware: Stuxnet

Highly advanced malware

Used for targeted sabotage of Iran's nuclear program

Supposedly developed by an American-Israeli team

Exploited for 0-day exploits in Windows

Accidentally spread beyond its intended target due to a programming error

#### Botnets - compute for hire

Mirai botnet consists of 150k IoT cameras

Used to sell compute for, e.g. DDoS

DoS overwhelms target computer with large amount of requests

### Social engineering

"Hacking Humans" - use psychological tricks to manipulate another human

Social engineers use phishing, pretexting, baiting or tailgating

May target employees, customers or vendors

Intent to obtain sensitive information, gain unauthorized access, commit fraud

Prevented by awareness, training, and robust security measures

### Vulnerabilities and exploits

**Vulnerability** - weakness in logic, the software or hardware of a system (bugs)

**Exploit** - method/tool to take advantage of a vulnerability

Vulnerabilities can be fixed by patching a system

**Zero day exploit** - exploit which no patch exists yet because the developers don't know about it yet (since 0 days)

They can be mitigated by making them difficult to exploit - isolate the system or add multiple layers of security

#### Typical software vulnerabilities

Buffer / heap / stack overflows - violating memory safety

Unvalidated input, including SQL injection: mixing code and data

Race conditions: changes of the order of events cause a change in behaviour

Insecure file operations: incorrect assumptions about ownership, location or attributes

Side-channel leakage: leaking information via time, power, sound, etc.

Weaknesses in the implementation of access control: authentication and authorization flaws
