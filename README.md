![](https://img.shields.io/github/tag/jmcph4/azorian.svg)
[![Build Status](https://travis-ci.org/jmcph4/azorian.svg?branch=master)](https://travis-ci.org/jmcph4/azorian)
# Azorian #

Azorian is a library implementing the multiformat specifications in C11.




## Building ##

    $ git@github.com:jmcph4/azorian.git
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

