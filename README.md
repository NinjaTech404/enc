# ENC - C++ Encode/Decode CLI Toolkit

A simple and straightforward C++ command-line interface toolkit for everyday encoding and decoding tasks.

## Features

- Command-line interface for encoding/decoding operations
- Built with modern C++20 standards
- Cross-platform compatibility
- Colorful terminal output using termcolor
- User-friendly formatting with fmt library

## Requirements

- CMake (version 3.10 to 4.1.2)
- C++20 compatible compiler
- fmt library (included as subdirectory)
- termcolor library (included as subdirectory)

## Building

```bash
# Clone the repository
git clone https://github.com/NinjaTech404/enc
cd enc

# Build the project
mkdir build && cd build
cmake ..
make
```

## Project Structure

```
enc/
├── src/           # Source files
├── include/       # Header files and dependencies
│   ├── CLI/      # Command-line interface headers
│   ├── fmt/      # Formatting library
│   └── termcolor/ # Terminal color library
└── CMakeLists.txt # Build configuration
```

## Usage

After building, run the executable:
```bash
./enc -h
```

## Dependencies

- **fmt**: Modern formatting library (included)
- **termcolor**: Cross-platform terminal color handling (included)

## License

This project was made with CMake by NinjaTech404.

For more information, visit: https://github.com/NinjaTech404/enc
