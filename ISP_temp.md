<!-- markdownlint-disable MD010 MD041 MD001 MD036 MD029-->

## Network security

### Best practices

**Inside** the network: segment the network physically:
Different zone for different parts of the organization
Demilitarized Zone (DMZ)\* to expose organization's external facing networks to the Internet - server that belongs to the organization but serve towards the outside.

Towards the **outside** the network: secure communication - TLS, IPSec, VPNs

### Network segmentation

Break the network down into segments based on system and data classification.

Access from zone to zone can be managed by ACLs (access control lists) in routers or firewalls. Users belong to individual areas.
May want to have central authentification service

Mainly addresses two points:

- prevents all-at-once compromise of facilities
- protects the data center from external threats

#### Rings

Concentric architecture where the most privileged services are inside, and therefore if you can access the center you access everything around it.

#### Zones

Creating containment zones aims to stops attacks from spreading between zones.
Communication between zones goes through backbone which is connected to zones by firewalls.
Closer to least privilege than rings.
The challenge is to create firewall rules for each case - easy to make mistakes.

#### Demilitarized Zone (DMZ)

Physical or logical subnetwork which contains and exposes the organizations's external-facing services
And external network node can access only what is exposed in the DMZ
The most common services is email, VPN endpoint

Two common architectures:

- firewall redirects teither to corporate network or DMZ
- firewall -> DMZ -> internal firewall

Firewall - has routing rules and decided the packet route based on different kinds of information. Can be statefull or stateless

#### Virtual segmentation

_VLANs_ - technologoy implements additional security services at layer 2 network (ethernet). Makes the virtual cables and switches that are accessible by specific accesses, even though the network goes through the the same cables and switches.

_Virtual Routing and Forwarding_ - allows a single router to be part of several IP networks with VLAN and VRF, any socket in any location can be configured to belong to any ethernet network and IP network.

_Virtual Machines_ - allows coalescing several servers and routers on a single hardware rack. The web server in the DMZ may actually be running on the same physical machine as the database of the internal back-end zone.

It would be implemented at switches and routers level.

#### "Zero trust" networks

Idea - do not trust anybody, not even internal machines.
Prevent lateral movement

Assume that any device can be compromised. So need to continuously monitor and validate everything.
Install local firewall on internal machines (LPOP, access control)
Encrypt all traffic between internal machines
Use strong authentication even internally (MFA)

More work to configure machines but with modern techniques (dockers, kubernetes) configuring and rolling out virtual machines can be automated.
Less work on configuring the network
Greatly reduces the impact if one machine is compromised.

### Protecting remote access - Virtual Private Networks

#### VPN

VPN runs a private network over a public network using two components:

- encryption to keep it private and for confidentiality (cannot hide the metadata)
- encapsulation packing IP packets inside IP packets to hide internal addresses and to transport private packets over the public network

A distant network or single machines can access a VPN thorugh a VPN gateway
A single machine can run a VPN software to create a virtual interface, where it looks like the data coming from the network card is being tunneled through the internet
Before being sent, packet is encrypted and encapsulated with IP header with the public addresses.

**Typical protocols**

- IPsec, official IETF standard
- OpenVPN, open source software, based on TLS
- WireGuard, built into the Linux kernel
- Proprietary protocols (e.g., Cisco AnyConnect, Microsoft SSTP) offer convenience in configuration and maintenance

**Typical use**

- Letting remote workers access the internal company network
- Interconnecting remote sites of a company
- For us: Accessing university resources (e.g., to download papers)
- For us: Playing CTF and bridging networks between teams

**VPN for privacy** - VPN to another country and access Internet from there
The address is hidden by the one of the VPN gateway.

Danger - the VPN provider sees your traffic

### Protecting the perimeter

#### Firewalls

Firewall enforce network level access control and limit what kind of data is being passed through.

Typically border between Internet and internal network.

Firewalls operate at the netowrk layer by analyzing metadata such as apacket headers of IP, TCP, UDP. Are oblivious of the application for which the packets are transmitted.

Within the network:
idea is to segement the network to limit lateral movement of attackers.

EPFL example:
most machines are in the generic EPFL zone
All muachines accessible from Internet are in untrust zone
Machine in uncrust cannot connect to machines in EPFL, but opposite is OK
Secret data in in Data Center zone, behind a firewall.
Zones can connect to other zones of lesser security, like MAC.

**Best practices** - allowlist

Explicitly allow certain connections and deny the rest.

Examples - allow only HTTP and HTTPS from internal zone to Internet, allow SSH from Internet only to one server.

Principle of **default deny** - the last rule denies all traffic that has not explicitly been allowed before.

Default allow is a problem because something will be missed.

> Exclusively work at metadata level

#### Proxies

**Operates at the application level**

Proxy acts as a server to the client and a client to the server - like a MITM

Proxy: client - proxy - internet - server
Reverse proxy: client - internet - reverse proxy - server

Direct proxies protect users when they access servers on the Internet
Reverse proxies protect servers when accessed by users from the Internet

##### Web proxies

Goal - protect users surfing the web against threats by reducing attack surface

Analuze all data downloaded from the web
Block access to dangerous sites

The browser must be configured to use the proxy
The firewall can be configured to only allow the proxy access web sites, users cannot surf the net if they don't go throug the proxy.

Problem: Proxy needs access to the cleartext, which means they cannot work by default for TLS.
Solution - the proxy can be configured to intercept HTTPS traffic. Rather than forwarding the handshake it pretends to be the server. (generates fake certificates like company ones - therefore all browsers would need to be configured to accept that cert)
Solution - passthrough but then proxy does not see the data

##### Mail gateways

Mail gateways act both as proxy and reverse proxy: all outgoing mail is stored on the mail gateway before being forwarded to the internet

All incoming mail is intercepted by the gateway before being forwarded to the users' mailbox

Mail gateways typically offer antivirus protection, incoming and outgoing spam protection

##### Web Application Firewall (WAF)

WAF is a typicall example of a reverse proxy with the goal of protectin a web server against maliciour requests
It analyses requests, and if it deems safe, forwards them to the real server

WAFs typically offer:

- block any request that seems to contain an attack (XSS, SQL injection)
- limit the number of requests to protect against DoS attacks
- block an IP address for certain time after attack detected
- authenticate users (CAPTCHA)

Example - modSecurity
Checks for XSS, or SQL injections.

Analyzes the HTTP traffic

##### Intrusion detection systems

IDS inspects traffic for all applications to detect potential intrustions
Generates alerts if it thinks it saw an attack and then terminates the connection

Two technologies:
Signature-based systems - false positives
Anomaly-based systems - false negatives

**Signature-based IDS**:
compares network traffic against signatures from a pattern database

Issues:

- requires previous knowledge of an attack to create a signature (false negatives for new attacks)
- matched signature does not always mean successful attack (E.g. signature for linux vulnerability in traffic of a windows server - false positives)

Signature examples:

- High number of failed login attempts
- URLs with extra long parameters (buffer overflow?)
- Exploiting a specific vulnerability: Cisco IOS invalid IKE fragment length memory corruption or exhaustion attempt

Example - Sort - sniffs traffic in front of your firewall to detect potential attacks.
Sends alarms and/or updates to frewall, blocking the attacker. Large db of free rules maintained by community.

**Anomaly-based IDS**
Goal - detect unknown attacks

IDS creates a traffic profile during normal operation to calibrate.

During monitoring, it looks for unusual packes, e.g. growth in port scans

- might not detect an SQL injection (extra characters in username)
- might notice a 200MB transwer of password hases from the db

Generates a lot of false positives and negatives (anomaly != attack)
(very hot application for machine learning)

Pr(MarkedAsMalware|IsMalware) = TPR = 0.99
Pr(IsMalware) = 0.0001
Pr(MarkedAsMalware) = 0.01
Pr(IsMalware|MarkedAsMalware) = Pr(MarkedAsMalware|IsMalware)\*Pr(IsMalware)/Pr(MarkedAsMalware) = 0.99\*0.0001/0.01 = 0.0099

### Protecting the workstation

Prevent exploitable bugs:
ensure automatic update of the OS, ensure automatic update of the applications

Prevent known malware:
install antivirus or use built-in ones, install applications from trusted sources

Antivirus usefullness has gone down - malware campaing used to be live 2-3 weeks, and now it is 2-3 hours because they assume they will be signatured and put to the database.

Prevent unknown malware:
prohibit users from installing applications, restrict write access to dirs that contain documents, not programs

#### Preventing the privilege escalation

Verify that all access rights are correctly set on programs and libraries

Typical issue - a program that is run by System is writable by any user, the attacker replaces the program by a malicious program and reboots the machine

Make sure that all programs are regularly patched to fix any known vulnerabilities
Make sure that the hard disk is encrypted, if not, attackers can boot from USB (or remove disk) and have full access rights to all files.

#### Protecting History - logging

keeping audit trails (logs) is an important part of network security to:

- identify security incidents
- monitor policy violations
- non repudiation control

Typical sources of logs:

- firewalls, proxies and IDS
- client and Server machines
- mail servers
- database applications

##### Things you should never log

- **passwords**
- religious, ideological, political or trade union-related views or activities
- health, the intimate sphere or the racial origin
- social security measures
- administrative or criminal proceedings and sanctions

Internet access logs should only be logged anonymously, nominal analysis of Internet access is only allowed if there are tangible signs of abuse

Mailboxes and logs should be protected against unauthorized access.

#### Protecting History - backups

3-2-1 rule:

- 3 copies of the data
- on 2 different types of media
- 1 stored off-site

**Backup types** - full, incremental (data that changed since last backup), differential (data that changes since last full backup)

**Backup content**: different depending on the ype of data:

- backup of (virtual) machines: allow to restore a machine without having to re-install and configure all the software
- backup of db: databases have their own tools to backup and restore the content of their tables
- file storage: data storage servers can archive every version of every file up to the last backup (e.g. one day) so that no data is lost if files are accidentally deleted during the day

**Disasted recovery plan**:
making backups is not sufficient
Backups also need to be tested regularly through _restoration tests_, i.e., to ensure we can recover data from backups

A Disaster Recovery Plan (DRP) records, in detail, how to rebuild a system in case of a major failure.
