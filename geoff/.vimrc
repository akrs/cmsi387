let g:syntastic_c_check_header = 1
let g:syntastic_c_no_include_search = 1
let g:syntastic_c_no_default_include_dirs = 1
let g:syntastic_c_auto_refresh_includes = 1
let g:syntastic_c_include_dirs = [ 'internals/io', 'internals/mem', 'internals/util' ]
let g:syntastic_c_compiler = 'i686-elf-gcc'
let g:syntastic_c_compiler_options = ' -m32 -nostdlib -fno-builtin -fno-stack-protector -ffreestanding -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -std=c99'
