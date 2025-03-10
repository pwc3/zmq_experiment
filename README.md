# C++/Python IPC Experiment via ZMQ

## C++

The following walks through building and running the C++ code.

### Install dependencies

On macOS:

```bash
brew install cmake pkg-config zeromq cppzmq
```

On Raspberry Pi:

```bash
sudo apt update && sudo apt install -y cmake pkg-config libzmq3-dev libczmq-dev
```

### Build

```bash
mkdir -p build && cd build
cmake ..
make
```

### Run

To start the publisher:

```bash
build/bin/publisher
```

To start the subscriber:

```bash
build/bin/subscriber
```

## Python

The following walks through running the Python code.

### Install tooling

Install [pipx](https://github.com/pypa/pipx).

On macOS:

```bash
brew install pipx
pipx ensurepath
```

On Raspberry Pi:

```bash
sudo apt update
sudo apt install pipx
pipx ensurepath
```

Install [Poetry](https://python-poetry.org/).

On macOS:

```bash
pipx install poetry
```

Configure Poetry to include its virtual environments in the project directory:

```bash
poetry config virtualenvs.in-project true
```

On Raspberry Pi, disable keyring, which causes a hang:

```bash
poetry config keyring.enabled false
```

### Install dependencies

```bash
poetry install
```

### Run

First, create an editable installation of this package:

```bash
poetry run pip install --editable .
```

To start the publisher:

```bash
poetry run python -m zmq_experiment.pub
```

To start the subscriber:

```bash
poetry run python -m zmq_experiment.sub
```

You can delete the editable installation of the package when you are done:

```bash
poetry run pip uninstall zmq_experiment
```
