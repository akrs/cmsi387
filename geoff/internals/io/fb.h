#include <stdint.h>
#include <stddef.h>

#ifndef _FB
#define _FB
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

/* Colors */
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHT_GREY 7
#define DARK_GREY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_CYAN 11
#define LIGHT_RED 12
#define LIGHT_MAGENTA 13
#define LIGHT_BROWN 14
#define WHITE 15


void fb_write_cell(uint32_t i, char c, uint8_t fg, uint8_t bg);

int fb_write(char *buf, size_t len);

int fb_write_str(char *buf);

int fb_write_hex(int32_t num);

int fb_write_num(int32_t num);

void fb_clear();
#endif
