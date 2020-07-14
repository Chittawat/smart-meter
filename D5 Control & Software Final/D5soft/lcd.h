/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *           View this license at http://creativecommons.org/about/licenses/
 */

#include <stdint.h>

#define LCDWIDTH	240
#define LCDHEIGHT	320

/* Colour definitions RGB565 */
#define WHITE       0xFFFF
#define BLACK       0x0000
#define BLUE        0x001F
#define GREEN       0x07E0
#define CYAN        0x07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define YELLOW      0xFFE0
#define ORANGE		0b1111101011100000 /*(255,184,0)*/ 
#define SKYBLUE		0b0000010000011111 /*(0,255,255)*/
#define CHOCO		0b0111001010101100

typedef enum {North, West, South, East} orientation;

typedef struct {
	uint16_t width, height;
	orientation orient;
	uint16_t x, y;
	uint16_t foreground, background;
} lcd;

extern lcd display;

typedef struct {
	uint16_t left, right;
	uint16_t top, bottom;
} rectangle;

void init_lcd();
void set_orientation(orientation o);
void clear_screen();
void fill_rectangle(rectangle r, uint16_t col);
void fill_rectangle_indexed(rectangle r, uint16_t* col);
void display_char(char c);
void display_string(char *str);