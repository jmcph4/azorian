![](https://img.shields.io/github/tag/jmcph4/azorian.svg)
[![Build Status](https://travis-ci.org/jmcph4/azorian.svg?branch=master)](https://travis-ci.org/jmcph4/azorian)
# Azorian #

Azorian is a library implementing the multiformat specifications in C11. Azorian aims to be clean and lightweight - both on system resources and dependency chains.

Currently, to build just the library, no additional dependencies are required - just the C standard library. To build the tests, the Unity C unit testing framework is needed.

Azorian is still in early development and, as such, is unstable right now. Codecs for most of the multiformats are already implemented though. Once stable, Azorian is ideal for C or C++ implementations of [libp2p](https://github.com/libp2p/libp2p), full [IPFS](https://github.com/ipfs/ipfs) implementations, or any other project which might want to exploit the power of the multiformat specifications for future-proof, self-describing data formats.

## Building ##

    $ git clone git@github.com:jmcph4/azorian.git
    $ cd azorian

### Release ###

    $ make

### Development ###

    $ make debug

### Tests ###

    $ git clone https://github.com/throwtheswitch/unity.git
    $ cp unity/src include/unity -r
    $ make debug
    $ make tests
    $ ./run_tests.sh

### Documentation ###

    $ make docs

Note that this requires Doxygen.

## Licensing ##
Please consult [LICENSE](LICENSE).

## Contributing ##
Azorian currently welcomes all contributors and the maintainers strive to comply with GitHub best practices.

As such, please consult [CONTRIBUTING](CONTRIBUTING.md) for all contribution information.

## Further Information ##
For any further information about the project, the wiki is the best place to go.

