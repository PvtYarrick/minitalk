# minitalk 📡

A small 42 project that implements a client-server communication program using **UNIX signals** (`SIGUSR1` / `SIGUSR2`) as the sole means of data transfer between two processes.

**Status:** ✅ Mandatory part complete — ✅ Bonus part complete

---

## 📋 Table of Contents

- [About](#about)
- [How It Works](#how-it-works)
- [Features](#features)
- [Bonus Features](#bonus-features)
- [Compilation](#compilation)
- [Usage](#usage)
- [Technical Notes](#technical-notes)
- [Norm & Leak Checks](#norm--leak-checks)

---

## About

`minitalk` explores low-level inter-process communication (IPC) using nothing but UNIX signals. A **server** program starts, prints its PID, and waits for a **client** to send it a string. The client encodes the string bit by bit and transmits it to the server exclusively via `SIGUSR1` (bit `0`) and `SIGUSR2` (bit `1`) signals — no sockets, no pipes, no shared memory.

## How It Works

1. The **server** is launched and prints its PID.
2. The **client** is launched with the server's PID and a message to send.
3. The client converts each character of the message into 8 bits and sends one signal per bit to the server:
   - `SIGUSR1` → bit `0`
   - `SIGUSR2` → bit `1`
4. The server's signal handler reconstructs each byte from the incoming bits, rebuilds the string, and prints it once a null terminator is received.
5. The server sends an acknowledgment signal back to the client after each character (and at the end of the message) so the client knows to continue/stop sending — this prevents signal loss.

## Features

- Full **client ↔ server** communication using only `SIGUSR1`/`SIGUSR2`
- Reliable transmission with acknowledgment signals (no signal loss even with fast sending)
- Handles messages of any length
- Clean handling of multiple/rapid signals without dropping bits
- Proper error handling for invalid PID or missing arguments

## Bonus Features

- 🔠 **Unicode / UTF-8 support** — correctly transmits and displays non-ASCII characters
- 👥 **Multiple client support** — the server can handle several clients sequentially without needing a restart, completing one message before accepting the next
- 📬 **Acknowledgment system** — the server confirms receipt of each character back to the client, and the client waits for this confirmation before sending the next one, guaranteeing zero data loss even for large messages

## Compilation

```bash
git clone https://github.com/PvtYarrick/minitalk minitalk
cd minitalk
make
```

This builds two executables:

- `server` — waits for and displays incoming messages
- `client` — sends a message to a given server PID

Other available targets:

```bash
make clean   # remove object files
make fclean  # remove object files and executables
make re      # fclean + make
```

## Usage

**1. Start the server** in one terminal:

```bash
./server
```

It will print something like:

```
Server PID: 12345
```

**2. Send a message from the client** in another terminal:

```bash
./client 12345 "Hello, world!"
```

The server terminal will display the received message as it arrives.

## Technical Notes

- Written in C, compiled with `cc -Wall -Wextra -Werror`
- Uses `sigaction` (not the simpler `signal`) for reliable, well-defined signal handling
- No data loss thanks to a stop-and-wait acknowledgment protocol between client and server
- Handles `SIGINT` gracefully where relevant, and validates all arguments (PID, message presence) before attempting transmission

## Norm & Leak Checks

```bash
norminette src/ include/ server/ client/
valgrind --leak-check=full --show-leak-kinds=all ./server
```

The project respects the 42 Norm and was tested for signal loss and memory leaks under stress conditions (very long messages, rapid consecutive sends, multiple clients in a row).

---

Made as part of the 42 common core curriculum. 🐧🐧🐧🐧
