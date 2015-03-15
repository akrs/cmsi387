GRUB = grub-0.97
LIBDIR = $(wildcard internals/*)
BUILDDIR = build
ELTORITO = stage2_eltorito
SOURCES := $(shell find -name '*.c' -or -name '*.s')
CSOURCES := $(SOURCES:%.c=%.o)
OBJECTS := $(addprefix $(BUILDDIR)/,$(CSOURCES:%.s=%.o))
CC=i686-elf-gcc
INCLUDES = $(addprefix -I, $(LIBDIR))
CFLAGS=-m32 -nostdlib -fno-builtin -fno-stack-protector -ffreestanding \
	   -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -std=gnu99 \
	   -masm=intel $(INCLUDES)
AS = nasm
ASFLAGS = -f elf
LDFLAGS = -T link.ld -ffreestanding -nostdlib -lgcc -fno-builtin


all: kernel.elf

## ISO section
$(BUILDDIR)/iso/boot/grub: $(ELTORITO) $(BUILDDIR)/iso/boot
	mkdir -p $(BUILDDIR)/iso/boot/grub
	cp $(ELTORITO) $(BUILDDIR)/iso/boot/grub
	cp menu.lst $(BUILDDIR)/iso/boot/grub

$(BUILDDIR)/iso/boot: kernel.elf
	mkdir -p $(BUILDDIR)/iso/boot
	cp $(BUILDDIR)/kernel.elf $(BUILDDIR)/iso/boot

$(BUILDDIR)/os.iso: $(BUILDDIR)/iso/boot $(BUILDDIR)/iso/boot/grub
	mkisofs     -R                              \
				-b boot/grub/stage2_eltorito    \
				-no-emul-boot                   \
				-boot-load-size 4               \
				-A os                           \
				-input-charset utf8             \
				-quiet                          \
				-boot-info-table                \
				-o build/os.iso                 \
				build/iso

## GRUB section
$(GRUB).tar.gz:
	wget ftp://alpha.gnu.org/gnu/grub/$@

$(GRUB): $(GRUB).tar.gz
	tar xf $^

#TODO: Figure out a way we don't need this
stage2_eltorito:
	wget http://littleosbook.github.com/files/$@

# KERNEL section
kernel.elf: $(OBJECTS)
	mkdir -p build
	$(CC) $(LDFLAGS) -o build/kernel.elf $(OBJECTS)

$(BUILDDIR)/%.o: %.c $(BUILDDIR)
	$(CC) $(CFLAGS)  $< -o $@ -lgcc

$(BUILDDIR)/%.o: %.s $(BUILDDIR)
	$(AS) $(ASFLAGS) $< -o $@

$(BUILDDIR):
	mkdir -p build
	cd build; mkdir -p $(LIBDIR)

# UTILITIES section
.PHONY: clean
clean:
	rm -rf build \
		   *.tar.gz \
		   grub-0.97/ \
		   bochslog.txt \
		   *.ini \
		   *.out

bochs: clean $(BUILDDIR)/os.iso
	bochs -f bochsrc.txt -q
