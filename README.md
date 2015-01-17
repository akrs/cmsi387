# cmsi387
Operating system devloped for CMSI 387 at LMU

# Setup directions:

We are using [Arch Linux](http://archlinux.org) for this, 
so the directions are targeted towards that OS.

## Prerequisites:

```bash
# pacman -S base-devel nasm cdrkit bochs multilib-devel
```

`cdrkit` provides `genisoimage` and `bochs` includes the
GUI debugger.

## [CAFEBABE](http://littleosbook.github.io/#hello-cafebabe)

View the `Makefile` for all the commands that need
to be run.

Run `make bochs` to build the project and launch bochs.

## Cross Compiler

View the `Makefile` for all commands that need to
be run.

Run `make` to download and build gcc and binutils.

Add `<thisdir>/cross-compiler/cc/bin` to your path.

## [Bare Bones](http://wiki.osdev.org/Bare_Bones)

This is really to make sure that your cross compiler
worked. View the makefile for the commands that need
to be run (requires `nasm` and `qemu` to work).

Check out the link above for more details. 
