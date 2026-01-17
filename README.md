<div align="center">

  [![ENC][enc-logo]][github-link]

  <h3>ENC</h3>

  A simple and straightforward C++ command-line interface toolkit for everyday encoding and decoding tasks.
  <br>
  <strong>[Explore ENC docs »][wiki-link]</strong>
  <br>
  <br>
  [Report bug][issue-link]
  ·
  [Open a discussion][discussions-link]
  ·
  [GitHub][github-link]

  [![Build][build-badge]][build-link]
  [![License][license-badge]][license-link]
  <br>
  [![Release][release-badge]][release-link]
  [![Commits][commits-badge]][commits-link]

</div>

## Overview

[ENC][github-link] is a **simple and straightforward C++ command-line interface toolkit** 
for everyday encoding and decoding tasks. Built with modern C++20 standards, ENC provides 
a user-friendly interface with colorful terminal output.

ENC is designed to be **cross-platform compatible** and easy to use for common encoding 
and decoding operations directly from your terminal.

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

Building ENC is straightforward on Unix-like systems with the included CMake configuration:

```bash
# Clone the repository
git clone https://github.com/NinjaTech404/enc
cd enc

# Build the project
mkdir build && cd build
cmake ..
make
```

For detailed compilation instructions for all platforms, please refer to the 
[documentation][wiki-link].

## Files

This distribution of ENC consists of the following files:

  * [README.md][readme-link], the file you are currently reading.

  * [LICENSE][license-link], a text file containing the license information.

  * [src][src-link], a subdirectory containing the full source code.

  * [include][include-link], a subdirectory containing header files and dependencies:
    - CLI/ - Command-line interface headers
    - fmt/ - Formatting library
    - termcolor/ - Terminal color library

  * [CMakeLists.txt][cmake-link], the CMake build configuration file.

## Usage

After building, run the executable to see available options:

```bash
./enc -h
```

## Contributing

Contributions to ENC are welcome! Here's how you can help:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

Please ensure your code follows the existing style and includes appropriate tests.

## Dependencies

ENC uses the following libraries (included in the project):

  * **fmt** - Modern formatting library for C++
  * **termcolor** - Cross-platform terminal color handling

## Terms of use

ENC is distributed under its [license][license-link]. Please refer to the LICENSE 
file in the repository for detailed terms and conditions.

## Acknowledgements

This project was created by [NinjaTech404][author-link] using CMake and modern C++ practices.


[author-link]:        https://github.com/NinjaTech404
[build-link]:         https://github.com/NinjaTech404/enc/actions
[cmake-link]:         https://github.com/NinjaTech404/enc/blob/main/CMakeLists.txt
[commits-link]:       https://github.com/NinjaTech404/enc/commits/main
[discussions-link]:   https://github.com/NinjaTech404/enc/discussions/new
[enc-logo]:           https://via.placeholder.com/128x128.png?text=ENC
[github-link]:        https://github.com/NinjaTech404/enc
[include-link]:       https://github.com/NinjaTech404/enc/tree/main/include
[issue-link]:         https://github.com/NinjaTech404/enc/issues/new
[license-link]:       https://github.com/NinjaTech404/enc/blob/main/LICENSE
[readme-link]:        https://github.com/NinjaTech404/enc/blob/main/README.md
[release-link]:       https://github.com/NinjaTech404/enc/releases/latest
[src-link]:           https://github.com/NinjaTech404/enc/tree/main/src
[wiki-link]:          https://github.com/NinjaTech404/enc/wiki

[build-badge]:        https://img.shields.io/github/actions/workflow/status/NinjaTech404/enc/build.yml?branch=main&style=for-the-badge&label=build&logo=github
[commits-badge]:      https://img.shields.io/github/commits-since/NinjaTech404/enc/latest?style=for-the-badge
[license-badge]:      https://img.shields.io/github/license/NinjaTech404/enc?style=for-the-badge&label=license&color=success
[release-badge]:      https://img.shields.io/github/v/release/NinjaTech404/enc?style=for-the-badge&label=release
