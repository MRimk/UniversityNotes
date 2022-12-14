<!--Martynas Rimkevicius - curr: ~21.5-->

# Assignment 2 - Vulnerabilities

<!--2 + 1.5 + 2 = 5.5-->

## Vulnerability 1

**Program nummber:** 1 TODO: test whether this is a problem elsewhere as well

**Type of a vulnerability:** authentication error

**Impact of a vulnerability:**

- [ ] None
- [x] Loss of availability - users cannot see that the user, who is still online, is online
- [ ] Data leak
- [ ] Data corruption
- [ ] Code execution

**Cause:** \
No check for multiple instances of the same user logging in to different clients simultaniously. This would be correct if user was still shown as logged in, when one client logs out but the other is still on.

_Location_: worker.c `void handle_logout` line 259

**Steps to reproduce:** \
Client 1: `/register gahsd adsad` (user gets registered) \
Client 2: `/login gahsd adsad` (while terminal 1 is still running, response is _authentication succeeded_) \
Client 3: `/register aha test` (while terminal 1 and 2 are still running) \
Client 3: `@gahsd test message` - message is delivered to both running user _gahsd_ clients. \
Client 2: quits \
Client 3: `/users` command shows only _aha_; `@gahsd test 2` command shows _error: invalid credentials_ \
To test if the Client 1 works general message from _gahsd_ gets delivered to the Client 3, but in `/users` command it does not show **all** the users that are online.

**How it was found:** \
Trying the functional security requirements of the program - manual testing. In particular trying registering and logging in with the same username on multiple clients. It was discovered when one client was quit from and then the other two clients were used to continue test if the user was still connected. Which was not the case, proven by opening the database to check whether the value representing the "logged in" condition was not set to true for user _gahsd_.

<!--2 + 2 + 1 = 5-->

## Vulnerability 2

**Program nummber:** 2

**Type of a vulnerability:** cryptography used incorrectly

**Impact of a vulnerability:**

- [ ] None
- [ ] Loss of availability
- [x] Data leak - Mallory can brute force other user's password and leak their private messages.
- [ ] Data corruption
- [ ] Code execution

**Cause:** Not using salt to generate a password and using just hashing (SHA224)

_Location_: client.c client_process_command() lines 119-139

**Steps to reproduce:** \
This vulnerability was found through the code, but it will can be exploited with simple brute force password guesser. If user is known to be registered, the password can be put in over and over, and thus be guessed over time.

**How it was found:** \
In the database Users table there is no field for salt for the hash, thus this raised a suspicion that salt might not be used and once the hashing part of the code was located, it could be seen that it is not used.

<!--2 + 2 + 2 = 6-->

## Vulnerability 3

**Program nummber:** 2

**Type of a vulnerability:** Incorrect error handling

**Impact of a vulnerability:**

- [ ] None
- [ ] Loss of availability
- [x] Data leak - users can see partial password of a new user if their created password is longer than (213 - length of username - 9 ("/register") - 2 (for spaces))
- [ ] Data corruption
- [ ] Code execution

**Cause:** Setting a strict boundary for read, but not checking if there is something left over, thus the rest of the information ending up in a general message after registration (since by then user that is being registered is already logged in).

_Location_: client.c client_process_command() lines 69-71 - here it reads 213 characters from the stdin, but it never flushes the input, therefore with the next read it ends up being a general message.

**Steps to reproduce:** \
using /register command, have a short username (the maximum is set as 30 for it), and have a long password (for example generate 256 character length string). After putting this string in, one can see the part of that string being sent as a public message:

```bash
/register abs rSAxVCA9DCdQcCnAK9TZGUA4gb4om4RfB5WDnswv7eMWbgl4qfNUQEb79FP063A9lswwenqx8APAuhi5bSWjpM6CqvJpWXGRxJAtLcFZgrgUsOyWfH9PjFAffAUEyXNsmdD5vSTguuDHEiu2riuLS7Ug91d5Siks50QYcHYOThp9d0cJ2k50clYR2gieB9Q0BTWAVhmF2orPkorRdsYxiuVsEI3gpd4rqVOg4defCTyt4MEpirjIloF9nCS9glDY
registration succeeded
2022-12-13 10:46:01 abs: F2orPkorRdsYxiuVsEI3gpd4rqVOg4defCTyt4MEpirjIloF9nCS9glDY
```

**How it was found:** \
In the code I noticed limit on the read buffer from stdin, therefore I wanted to try a long password input to see how it is handled. Therefore I generated 256 character string and saw that it was not handled correctly.

<!-- 2 + 1.5 + 1.5 = 5-->

## Vulnerability 4

**Program nummber:** 6

**Type of a vulnerability:** error handling incorrect/malloc/free problem

**Impact of a vulnerability:**

- [ ] None (1pt)
- [x] Loss of availability (1.5pts) - user is unable to relogin or register after there are a lot of messages sent in the server.
- [ ] Data leak (2pts)
- [ ] Data corruption (2pts)
- [ ] Code execution (2.5pts)

**Cause:** printing client certificates? or malloc problem

_Location_:

**Steps to reproduce:** \
The conversation of 3 clients was as follows:

```bash
2022-12-13 12:19:41 test2: test
2022-12-13 12:19:45 this1: test
2022-12-13 12:21:10 this1: lets send a lot of messages
2022-12-13 12:21:22 test2: this is a lot of messages
2022-12-13 12:21:28 test2: this is again
2022-12-13 12:21:31 test2: again
2022-12-13 12:21:33 test2: and again
2022-12-13 12:21:39 this1: a lot of messages
2022-12-13 12:21:45 test3: sent from you
2022-12-13 12:21:46 test3: to me
```

After this, user _test3_ logged out and tried to relogin, but after having received feedback from the server "authentication succeeded", the client exited. User _test2_ used `/users` command and got following output:

```bash
/users
this1
test2
test3
```

This means that user is logged in, but the client does not work. New user _test4_ tried to register, received the message "registration succeeded", and the client crashed.

**How it was found:** \
It was found after testing long messages with 3 users, after having noticed that after 2 messages sent, other messages are showing the certificates of users who are logged in.

<!-- +  +  = -->

## Vulnerability 5

**Program nummber:** 6

**Type of a vulnerability:** double free!!!!!!!

**Impact of a vulnerability:**

- [ ] None
- [ ] Loss of availability
- [ ] Data leak
- [ ] Data corruption
- [ ] Code execution

**Cause:**

_Location_:

**Steps to reproduce:** \

**How it was found:** \

<!-- +  +  = -->

## Vulnerability 6

**Program nummber:** 2, 4 (find more later) - this can be separated into few vulnerabilities

**Type of a vulnerability:** cryptography not used when it is necessary

**Impact of a vulnerability:**

- [ ] None
- [ ] Loss of availability
- [x] Data leak - Mallory can impersonate and read the messages that are sent for the user
- [ ] Data corruption
- [ ] Code execution

**Cause:** Not encrypting private messages and not having signatures (this can be separate)

_Location_:

**Steps to reproduce:** \

**How it was found:** \
Looking through the code.
