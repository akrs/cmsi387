BINUTILS=binutils-2.25
ISL=isl-0.12
CLOOG=cloog-0.18.1
URLS=http://ftp.gnu.org/gnu/binutils/$(BINUTILS).tar.gz \
	 http://ftp.gnu.org/gnu/gcc/gcc-4.8.4/gcc-4.8.4.tar.gz \
	 http://www.bastoul.net/cloog/pages/download/$(CLOOG).tar.gz \
	 https://ftp.gnu.org/gnu/mpfr/mpfr-3.1.2.tar.gz \
	 http://ftp.gnu.org/gnu/gmp/gmp-6.0.0a.tar.bz2 \
	 http://isl.gforge.inria.fr/$(ISL).tar.gz \
	 https://ftp.gnu.org/gnu/mpc/mpc-1.0.2.tar.gz \
	 https://ftp.gnu.org/gnu/texinfo/texinfo-5.2.tar.gz
FILES:=$(notdir $(URLS))
export PREFIX:=$(shell pwd)/cc
export TARGET:=i686-elf
export PATH:=$(PREFIX)/bin:$(PATH)

all: binutils
	echo $(PATH)

binutils: $(ISL).tar.gz $(CLOOG).tar.gz $(BINUTILS).tar.gz
	tar xf $(BINUTILS).tar.gz
	tar xf $(ISL).tar.gz
	mv $(ISL) $(BINUTILS)/isl
	tar xf $(CLOOG).tar.gz
	mv $(CLOOG) $(BINUTILS)/cloog 
	mkdir build-binutils
	cd build-binutils; \
	PATH=$(PATH) ../$(BINUTILS)/configure --target=$(TARGET) --prefix="$(PREFIX)" --with-sysroot --disable-nls --disable-werror; \
	make; \
	make install



$(FILES):
	for url in $(URLS); do \
		wget -nc $$url; \
	done

clean:
	rm -rf $(FILES) */
