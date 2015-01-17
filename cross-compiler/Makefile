BINUTILS=binutils-2.25
ISL=isl-0.12
CLOOG=cloog-0.18.1
GMP=gmp-6.0.0
GCC=gcc-4.8.4
MPFR=mpfr-3.1.2
MPC=mpc-1.0.2
URLS=http://ftp.gnu.org/gnu/binutils/$(BINUTILS)a.tar.gz \
	 http://ftp.gnu.org/gnu/gcc/gcc-4.8.4/$(GCC).tar.gz \
	 http://www.bastoul.net/cloog/pages/download/$(CLOOG).tar.gz \
	 https://ftp.gnu.org/gnu/mpfr/$(MPFR).tar.gz \
	 http://ftp.gnu.org/gnu/gmp/$(GMP).tar.bz2 \
	 http://isl.gforge.inria.fr/$(ISL).tar.gz \
	 https://ftp.gnu.org/gnu/mpc/$(MPC).tar.gz \
	 https://ftp.gnu.org/gnu/texinfo/texinfo-5.2.tar.gz
FILES:=$(notdir $(URLS))
export PREFIX:=$(shell pwd)/cc
export TARGET:=i686-elf
export PATH:=$(PREFIX)/bin:$(PATH)

all: binutils gcc

binutils: $(ISL).tar.gz $(CLOOG).tar.gz $(BINUTILS).tar.gz
	tar xf $(BINUTILS).tar.gz
	tar xf $(ISL).tar.gz
	mv $(ISL) $(BINUTILS)/isl
	tar xf $(CLOOG).tar.gz
	mv $(CLOOG) $(BINUTILS)/cloog 
	mkdir build-binutils
	cd build-binutils; \
	PATH=$(PATH) ../$(BINUTILS)/configure --target=$(TARGET) --prefix="$(PREFIX)" --with-sysroot --disable-nls --disable-werror; \
	make -j8; \
	make install
	touch binutils

gcc: $(GCC).tar.gz $(GMP)a.tar.bz2 $(MPFR).tar.gz $(MPC).tar.gz $(ISL).tar.gz $(CLOOG).tar.gz
	tar xf $(GCC).tar.gz
	tar xf $(GMP)a.tar.bz2
	mv $(GMP) $(GCC)/gmp
	tar xf $(MPFR).tar.gz
	mv $(MPFR) $(GCC)/mpfr
	tar xf $(MPC).tar.gz
	mv $(MPC) $(GCC)/mpc
	tar xf $(ISL).tar.gz
	mv $(ISL) $(GCC)/isl
	tar xf $(CLOOG).tar.gz
	mv $(CLOOG) $(GCC)/cloog
	mkdir build-gcc
	cd build-gcc; \
	PATH=$(PATH) ../$(GCC)/configure --target=$(TARGET) --prefix="$(PREFIX)" --disable-nls --enable-languages=c,c++ --without-headers; \
	make -j8 all-gcc && \
	make -j8 all-target-libgcc && \
	make -j8 install-gcc && \
	make -j8 install-target-libgcc
	touch gcc
	
$(FILES):
	for url in $(URLS); do \
		wget -nc $$url; \
	done

clean:
	rm -rf $(FILES) */ binutils gcc
