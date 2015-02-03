#include "io.h"
#include "fb.h"

#define BUFFER_LENGTH 2000
#define NUM_ROWS 25
#define NUM_COLS 80
#define TAB_WIDTH 4

char* fb = (char*)0x000B8000;

unsigned int current_position = 0;
/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 *
 *  @param i  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {
    unsigned int actual_location = i * 2;
    fb[actual_location] = c;
    fb[actual_location + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

void fb_move_cursor(unsigned short pos)
{
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos & 0x00FF);
}

void fb_write_row_column(unsigned int row, unsigned int column, char c, unsigned char fg, unsigned char bg) {
    unsigned int position = row * NUM_COLS + column;
    fb_write_cell(position, c, fg, bg);
}

void fb_scroll_up() {
    for (int i = NUM_COLS * 2; i < BUFFER_LENGTH * 2; i++) {
        fb[i - NUM_COLS*2] = fb[i];
        fb[i] = 0;
    }
    current_position -= NUM_COLS;
}

int fb_write(char *buf, unsigned int len) {
    if (len > BUFFER_LENGTH) {
        return -1;
    }
    unsigned int i = 0;
    
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
                current_position = current_position + TAB_WIDTH - (current_position % TAB_WIDTH);
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

int fb_strlen(char *str) {
    int i = 0;
    while (str[i++] != '\0') {}
    return i;
}

int fb_write_str(char *buf) {
    return fb_write(buf, fb_strlen(buf));
}

void fb_clear() {
    for (int i = 0; i < NUM_ROWS * NUM_COLS; i++) {
        fb_write_cell(i, ' ', BLACK, LIGHT_GREY);
    }
}
