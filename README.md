# cmsi387
Operating system devloped for CMSI 387 at LMU

# Setup directions:

We are using [Arch Linux](http://archlinux.org) and Mac OS X for this,
so the directions are targeted towards that OS.

## Prerequisites:

Arch:
```bash
# pacman -S base-devel nasm cdrkit bochs multilib-devel
```
Mac:
* Xcode with command line tools
* [Homebrew](http://brew.sh)
```bash
$ brew install nasm cdrtools bochs
```
NB: our cross-compiler compiled fine for me using clang, your mileage may vary. I have a lot of other libs on my system, not sure which are needed.

`cdrtools` provides `genisoimage` and `bochs` includes the
GUI debugger.

## [CAFEBABE](http://littleosbook.github.io/#hello-cafebabe)

View the `Makefile` for all the commands that need
to be run.

Run `make bochs` to build the project and launch bochs.

## Cross Compiler

This cross-compiler should compile all the code we use in the repo. The makefile that download and builds it has been tested on Arch and OS X, and *should* generally work on any \*nix system.

View the `Makefile` for all commands that need to
be run.

Run `make` to download and build gcc and binutils.

Add `<thisdir>/cross-compiler/cc/bin` to your path.

## [Bare Bones](http://wiki.osdev.org/Bare_Bones)

This is really to make sure that your cross compiler
worked. View the makefile for the commands that need
to be run (requires `nasm` and `qemu` to work).

Check out the link above for more details.
