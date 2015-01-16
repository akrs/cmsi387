GRUB=grub-0.97

all: os.iso

## ISO section
iso/boot/grub: stage2_eltorito iso/boot
	mkdir -p iso/boot/grub
	cp stage2_eltorito iso/boot/grub

iso/boot: kernel.elf
	mkdir -p iso/boot
	cp menu.lst iso/boot
	cp kernel.elf iso/boot

os.iso: iso/boot iso/boot/grub
	genisoimage -R                              \
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
kernel.elf: loader.o
	ld -T link.ld -melf_i386 loader.o -o kernel.elf

loader.o:
	nasm -f elf32 loader.s

# UTILITIES section
clean:
	rm -rf stage2_eltorito *.o kernel.elf *.tar.gz grub-0.97 iso os.iso
