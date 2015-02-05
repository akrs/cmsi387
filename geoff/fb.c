#include <stdint.h>
#include <stddef.h>
#include "io.h"
#include "fb.h"
#include "utils.h"

#define BUFFER_LENGTH 2000
#define NUM_ROWS 25
#define NUM_COLS 80
#define TAB_WIDTH 4

char* fb = (char*)0x000B8000;

uint32_t current_position = 0;
/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 *
 *  @param i  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */
void fb_write_cell(uint32_t i, char c, uint8_t fg, uint8_t bg) {
    uint32_t actual_location = i * 2;
    fb[actual_location] = c;
    fb[actual_location + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

void fb_move_cursor(uint16_t pos)
{
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos & 0x00FF);
}

void fb_write_row_column(uint32_t row, uint32_t column, char c, uint8_t fg, uint8_t bg) {
    uint32_t position = row * NUM_COLS + column;
    fb_write_cell(position, c, fg, bg);
}

void fb_scroll_up() {
    for (int i = NUM_COLS * 2; i < BUFFER_LENGTH * 2; i++) {
        fb[i - NUM_COLS*2] = fb[i];
        fb[i] = 0;
    }
    current_position -= NUM_COLS;
}

int fb_write(char *buf, size_t len) {
    if (len > BUFFER_LENGTH) {
        return -1;
    }
    uint32_t i = 0;
    
    while (i < len) {
        if (current_position >= BUFFER_LENGTH) {
            fb_scroll_up();
        } 
        switch (buf[i]) {
            case '\n':
                current_position += NUM_COLS - (current_position % NUM_COLS);
                fb_move_cursor(current_position);
                break;
            case '\t':
                current_position += TAB_WIDTH - (current_position % TAB_WIDTH);
                fb_move_cursor(current_position);
                break;
            default:
                fb_write_cell(current_position, buf[i], BLACK, LIGHT_GREY);
                fb_move_cursor(current_position++);
                break;
        }
        i++;
    }
    if (len > 1) {
        current_position--;
    }

    return i;
}



int fb_write_str(char *buf) {
    return fb_write(buf, strlen(buf));
}

void fb_clear() {
    for (int i = 0; i < NUM_ROWS * NUM_COLS; i++) {
        fb_write_cell(i, ' ', BLACK, LIGHT_GREY);
    }
}
