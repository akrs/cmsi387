GRUB=grub-0.97
OBJECTS=loader.o kmain.o
CC=i686-elf-gcc
CFLAGS=-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
	   -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
AS = nasm
ASFLAGS = -f elf
LDFLAGS = -T link.ld -ffreestanding -nostdlib -lgcc


all: kernel.elf

## ISO section
iso/boot/grub: stage2_eltorito iso/boot
	mkdir -p iso/boot/grub
	cp stage2_eltorito iso/boot/grub
	cp menu.lst iso/boot/grub

iso/boot: kernel.elf
	mkdir -p iso/boot
	cp kernel.elf iso/boot

os.iso: iso/boot iso/boot/grub
	mkisofs     -R                              \
				-b boot/grub/stage2_eltorito    \
				-no-emul-boot                   \
				-boot-load-size 4               \
				-A os                           \
				-input-charset utf8             \
				-quiet                          \
				-boot-info-table                \
				-o os.iso                       \
				iso

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
	$(CC) $(LDFLAGS) -o kernel.elf $(OBJECTS) 

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@ -lgcc

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

# UTILITIES section
.PHONY: clean
clean:
	rm -rf stage2_eltorito \
		   *.o \
		   kernel.elf \
		   *.tar.gz \
		   grub-0.97/ \
		   iso/ \
		   os.iso \
		   bochslog.txt \
		   *.ini

bochs: os.iso
	bochs -f bochsrc.txt -q #-rc - <<< c
