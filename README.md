# Ehtimam – Emergency Support Circle Network

Real-time emergency communication system allowing users to instantly notify a trusted circle during urgent situations.

## Authors
- Rola ElReedy
- Christine Selwanes
- Omar Abdelaaty

## Technologies
- Boost.Asio (Networking)
- SQLite3 (Database)
- nlohmann/json (JSON parsing)
- Anthropic Claude API (LLM)
- CMake (Build System)

## Milestone 3 Features
- TCP client-server communication
- Emergency alert broadcasting
- Circle management (add/remove/list)
- **SQLite database** — all messages logged persistently to `ehtimam.db`
- **LLM suggestions** — type `suggest <situation>` for AI-powered emergency advice

## Build & Run
```bash
brew install sqlite3 nlohmann-json boost
mkdir build && cd build
cmake .. && make
```

### Terminal 1 – Server
```bash
export ANTHROPIC_API_KEY=your_key_here
./server_app
```

### Terminal 2+ – Client
```bash
./client_app
```

## Commands
| Command | Description |
|---|---|
| `alert` | Broadcasts emergency alert to all connected users |
| `suggest <situation>` | Gets AI emergency advice from Claude |
| `add <name>` | Adds person to your circle |
| `remove <name>` | Removes person from circle |
| `list` | Shows your circle members |
