<div align="center">

[![ENC][enc-logo]][github-link]

<h1>ENC v2.0.0</h1>

<h3>C++ CLI encoder/decoder for daily use</h3>

<strong>Explore the docs »</strong> [![Wiki][wiki-badge]][wiki-link]
<br>
<strong>Report a bug »</strong> [![Issues][issues-badge]][issues-link]
<br>
<strong>Join the discussion »</strong> [![Discussions][discussions-badge]][discussions-link]

<br>

[![MIT License][license-badge]][license-link]
[![Latest Release][release-badge]][release-link]
<br>
[![C++20][cpp-badge]][cpp-link]
[![CMake][cmake-badge]][cmake-link]
[![Platform][platform-badge]][platform-link]
<br>
[![Last Commit][commits-badge]][commits-link]
[![GitHub Stars][stars-badge]][stars-link]

</div>

## Overview

**ENC** is a simple and straightforward C++ command-line interface toolkit for everyday encoding and decoding tasks. Built with modern C++20 standards, ENC provides a user-friendly interface with colorful terminal output.

ENC is designed to be cross-platform compatible and easy to use for common encoding and decoding operations directly from your terminal.

## Features

- **Command-line interface** for encoding/decoding operations
- **Modern C++20** implementation
- **Cross-platform compatibility** (Unix/Linux)
- **Colorful terminal output** using termcolor
- **User-friendly formatting** with fmt library
- **Easy CMake build system**
- **MIT Licensed** - free for any use

## Quick Start

### Prerequisites
- **CMake** 3.10+
- **C++20 compatible compiler** (GCC 10+, Clang 10+, MSVC 2019+)
- **Git**

### Installation & Build
```bash
# Clone the repository
git clone https://github.com/NinjaTech404/enc
cd enc

# Build with CMake
mkdir build && cd build
cmake ..
make

# Run the executable
./enc --help
```

### Quick Usage Examples
```bash
# Display help
./enc --help
```

## Project Structure
```
enc/
├── src/                    # Source code
├── include/               # Header files
│   ├── CLI/              # Command-line interface
│   ├── fmt/              # Formatting library
│   └── termcolor/        # Terminal color library
├── CMakeLists.txt        # Build configuration
├── LICENSE               # MIT License
└── README.md            # This file
```

## Dependencies

ENC includes the following dependencies as submodules:
- **[fmt](https://github.com/fmtlib/fmt)** - Modern formatting library
- **[termcolor](https://github.com/ikalnytskyi/termcolor)** - Cross-platform terminal colors

## Documentation

Detailed documentation is available in the [ENC Wiki][wiki-link], including:
- Complete command reference
- Installation guides for different platforms
- Advanced usage examples
- Building from source
- Contributing guidelines

## Contributing

We welcome contributions! Here's how you can help:

1. **Fork** the repository
2. **Create a feature branch** (`git checkout -b feature/amazing-feature`)
3. **Commit your changes** (`git commit -m 'Add some amazing feature'`)
4. **Push to the branch** (`git push origin feature/amazing-feature`)
5. **Open a Pull Request**

Please ensure your code follows the existing style and includes appropriate tests.

## Support

- **Report Issues:** [Create an issue][issues-link]
- **Ask Questions:** [Start a discussion][discussions-link]
- **Follow Updates:** Watch the repository for notifications
- **Show Support:** ⭐ Star the project if you find it useful!

## License

ENC is distributed under the **MIT License**. See the [LICENSE][license-link] file for details.

## Acknowledgments

This project was created by [NinjaTech404][author-link] using modern C++ practices and CMake.

---

<div align="center">

**ENC v2.0.0** • Built with ❤️ and C++20

[![GitHub][github-badge]][github-link] • [![License][license-icon]][license-link] • [![Release][release-icon]][release-link]

</div>

<!-- Links -->
[author-link]: https://github.com/NinjaTech404
[build-link]: https://github.com/NinjaTech404/enc/actions
[cmake-link]: https://cmake.org
[commits-link]: https://github.com/NinjaTech404/enc/commits/main
[cpp-link]: https://en.cppreference.com/w/cpp/20
[discussions-link]: https://github.com/NinjaTech404/enc/discussions
[downloads-link]: https://github.com/NinjaTech404/enc/releases
[enc-logo]: images/enc.svg
[github-link]: https://github.com/NinjaTech404/enc
[issues-link]: https://github.com/NinjaTech404/enc/issues
[license-link]: https://github.com/NinjaTech404/enc/blob/main/LICENSE
[platform-link]: https://github.com/NinjaTech404/enc
[release-link]: https://github.com/NinjaTech404/enc/releases/tag/v2.0.0
[stars-link]: https://github.com/NinjaTech404/enc/stargazers
[wiki-link]: https://github.com/NinjaTech404/enc/wiki

<!-- Badges -->
[build-badge]: https://img.shields.io/github/actions/workflow/status/NinjaTech404/enc/ci.yml?style=for-the-badge&logo=github-actions&logoColor=white&label=BUILD&color=2088FF
[commits-badge]: https://img.shields.io/github/last-commit/NinjaTech404/enc/main?style=for-the-badge&logo=git&logoColor=white&label=UPDATED&color=F05032
[cpp-badge]: https://img.shields.io/badge/C%2B%2B-20-00599C?style=for-the-badge&logo=cplusplus&logoColor=white
[cmake-badge]: https://img.shields.io/badge/CMake-3.10+-064F8C?style=for-the-badge&logo=cmake&logoColor=white
[discussions-badge]: https://img.shields.io/badge/Discussions-Join-blue?style=flat-square&logo=github-discussions
[downloads-badge]: https://img.shields.io/github/downloads/NinjaTech404/enc/total?style=for-the-badge&logo=download&logoColor=white&label=DOWNLOADS&color=green
[github-badge]: https://img.shields.io/badge/GitHub-Repository-black?style=flat-square&logo=github
[issues-badge]: https://img.shields.io/badge/Issues-Report-red?style=flat-square&logo=github
[license-badge]: https://img.shields.io/badge/License-MIT-blue?style=for-the-badge&logo=book&logoColor=white
[license-icon]: https://img.shields.io/badge/MIT-Free-brightgreen?style=flat-square&logo=opensourceinitiative
[platform-badge]: https://img.shields.io/badge/Platform-UNIX/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black
[release-badge]: https://img.shields.io/github/v/release/NinjaTech404/enc?style=for-the-badge&logo=rocket&logoColor=white&label=VERSION&color=6e5494
[release-icon]: https://img.shields.io/badge/v2.0.0-Latest-orange?style=flat-square&logo=tag
[stars-badge]: https://img.shields.io/github/stars/NinjaTech404/enc?style=for-the-badge&logo=star&logoColor=white&label=STARS&color=FFD700
[wiki-badge]: https://img.shields.io/badge/Wiki-Docs-blueviolet?style=flat-square&logo=readthedocs

