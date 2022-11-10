# ft_irc 🌐🏃🐱

## 42-ft_irc Summary
42's project to build a custom IRC server. IRC stands for Internet Relay Chat, and is one of the first chat protocol on the internet, made around 1988. Twitch still uses an IRC chat nowadays, and a network of servers still hosts thousands of channels.

## Mandatory Instructions
- The server must be capable of handling multiple clients at the same time and never
hang.
- Forking is not allowed. All I/O operations must be non-blocking.
- Only 1 poll() (or equivalent) can be used for handling all these operations (read,
write, but also listen, and so forth).
- Several IRC clients exist. You have to choose one of them as a reference. We chose *irssi*.
- Your reference client must be able to connect to your server without encountering
any error.
- Communication between client and server has to be done via TCP/IP (v4 or v6).
- Using your reference client with your server must be similar to using it with any
official IRC server. However, you only have to implement the following features:
	- You must be able to authenticate, set a nickname, a username, join a channel,
send and receive private messages using your reference client.
	- All the messages sent from one client to a channel have to be forwarded to
every other client that joined the channel.
	- You must have operators and regular users.
	- Then, you have to implement the commands that are specific to operators.

## How to Use
Clone the repository in the location of your choice, go inside it, then compile using make command:
```
cd 42-ft_irc
make
```
Launch the server. Usage:
```
./ircserv <port> <password>
```
Then, launch your irssi client, and connect to the server (locally if you want to test on the same machine).

Enjoy!

## Credits
Made with love 💗 by [ajealcat](https://github.com/ajealcat), [fahima8897](https://github.com/fahima8897) and [smaugdela](https://github.com/smaugdela).
