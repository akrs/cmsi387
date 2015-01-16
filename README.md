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
to be run. **Note:** We use Arch's patch for fixing the
configure, rather than replacing it entirely.


