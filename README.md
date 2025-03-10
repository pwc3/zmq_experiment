# C++/Python IPC Experiment via ZMQ

## Dependencies

On macOS:

```bash
brew install cmake pkg-config zeromq cppzmq
```

On Raspberry Pi:

```bash
sudo apt update && sudo apt install -y cmake pkg-config libzmq3-dev libczmq-dev
```

## Build the C++ code

```bash
cd src/cpp
mkdir build && cd build
cmake ..
make
```