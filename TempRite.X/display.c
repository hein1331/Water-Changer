#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

#include "commondefines.h"
#include "io.h"
#include "display.h"
#include "buttons.h"
#include "temperature.h"
#include "temp_regulator.h"


unsigned char buffer[BUFFER_SIZE];

int show_on_temp = 0;

// Text variables
int cursor_x = 0;
int cursor_y = 0;



void update_display(void) {
    SELECT_DISPLAY
    COMMAND_DISPLAY

    // Set page start (0) and end addresses (7)
    spi_write(SET_PAGE_ADDR);
    spi_write(0);
    spi_write(0xFF);

    // Set colum start (0) and end (WIDTH) addresses
    spi_write(SET_COL_ADDR);
    spi_write(0);
    spi_write(SCREEN_WIDTH - 1);

    // Send display buffer to display
    DATA_MODE_DISP
    int count = BUFFER_SIZE;
    unsigned char *ptr = buffer;

    while (count--)
      spi_write(*ptr++);

    DESLECT_DISPLAY
}

void clearDisplay(void) {
    for(int i = 0; i < BUFFER_SIZE; i++)
        buffer[i] = 0;
}

void set_pixel(int x, int y) {
    if ((x >= 0) && (x < SCREEN_WIDTH) && (y >= 0) && (y < SCREEN_HEIGHT)) {
        buffer[x + (y / 8) * SCREEN_WIDTH] |= 1 << (y % 8);
    }
}

void fillRect(int x, int y, int w, int h) {
  for (int i = x; i < x + w; i++) {
    for(int j = y; j < y + h; j++) {
      set_pixel(i, j);
    }
  }
}

void drawChar(int x, int y, char c) {

  if ((x >= SCREEN_WIDTH) ||              // Clip right
      (y >= SCREEN_HEIGHT) ||             // Clip bottom
      ((x + 6 * TEXT_WIDTH_MAG - 1) < 0) || // Clip left
      ((y + 8 * TEXT_HEIGHT_MAG - 1) < 0))   // Clip top
    return;

  for (int i = 0; i < 5; i++) { // Char bitmap = 5 columns
    char line = font[c * 5 + i];
    for (int j = 0; j < 8; j++, line >>= 1) {
      if (line & 1) {
        if (TEXT_WIDTH_MAG == 1 && TEXT_HEIGHT_MAG == 1)
          set_pixel(x + i, y + j);
        else
          fillRect(x + i * TEXT_WIDTH_MAG, y + j * TEXT_HEIGHT_MAG, TEXT_WIDTH_MAG, TEXT_HEIGHT_MAG);
      }
    }
  }
}

void writeString(char* str, int len) {
  for(unsigned int i = 0; i < len; i++)
  {
    char c = str[i];
    if (c == '\n') {              // Newline?
      cursor_x = 0;               // Reset x to zero,
      cursor_y += TEXT_HEIGHT_MAG * 8; // advance y one line
    } else if (c != '\r') {       // Ignore carriage returns
      drawChar(cursor_x, cursor_y, c);
      cursor_x += TEXT_WIDTH_MAG * 6; // Advance x one char
    }
  }
}


void drawBitmap(int x, int y, const unsigned char bitmap[],
                              int w, int h) {

  int byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
  unsigned char byte = 0;

  for (int j = 0; j < h; j++, y++) {
    for (int i = 0; i < w; i++) {
      if (i & 7)
        byte <<= 1;
      else {
        byte = bitmap[j * byteWidth + i / 8];
      }
      if (byte & 0x80) {
        set_pixel(x + i, y);
      }
    }
  }
}

void drawLine(int x0, int y0, int x1, int y1) {
  int steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    int temp = x0;
    x0 = y0;
    y0 = temp;

    temp = x1;
    x1 = y1;
    y1 = temp;
  }

  if (x0 > x1) {
    int temp = x0;
    x0 = x1;
    x1 = temp;

    temp = y0;
    y0 = y1;
    y1 = temp;
  }

  int dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int err = dx / 2;
  int ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;
  }

  for (; x0 <= x1; x0++) {
    if (steep) {
      set_pixel(y0, x0);
    } else {
      set_pixel(x0, y0);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}


void drawCircle(int x0, int y0, int r) {
  int f = 1 - r;
  int ddF_x = 1;
  int ddF_y = -2 * r;
  int x = 0;
  int y = r;

  set_pixel(x0, y0 + r);
  set_pixel(x0, y0 - r);
  set_pixel(x0 + r, y0);
  set_pixel(x0 - r, y0);

  while (x < y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    set_pixel(x0 + x, y0 + y);
    set_pixel(x0 - x, y0 + y);
    set_pixel(x0 + x, y0 - y);
    set_pixel(x0 - x, y0 - y);
    set_pixel(x0 + y, y0 + x);
    set_pixel(x0 - y, y0 + x);
    set_pixel(x0 + y, y0 - x);
    set_pixel(x0 - y, y0 - x);
  }
}

void init_display(void) {
    // Initialize display pixel buffer
    clearDisplay();

    // Reset the display
    DISP_RST_PORT = 1;

    SELECT_DISPLAY
    COMMAND_DISPLAY
    
    // Turn off the display
    spi_write(DISPLAY_OFF);

    // Set occilatior
    spi_write(DISPLAY_OCC_RAT);
    spi_write(OCC_SETTING);

    // Set multiplexer
    spi_write(MULTIPLEX_RAT);
    spi_write(SCREEN_HEIGHT - 1);

    // Do not set any display offset
    spi_write(DISPLAY_OFFSET);
    spi_write(0);

    // Set display start line
    spi_write(DISPLAY_START_LINE);

    // Set display power source
    spi_write(DISPLAY_POWER_SRC);
    spi_write(DISPLAY_POWERED_INTERNALLY);

    // Set display addressing mode
    spi_write(DISPLAY_ADDR_MODE);
    spi_write(HORIZ_ADDR_MODE);

    // Set segment remap
    spi_write(SEGMENT_REMAP);

    // Set COM scan direction
    spi_write(DISPLAY_SCAN_DIR);

    // Set COM pin configuration
    spi_write(COMM_PIN_CONFIG);
    spi_write(ALT_COM_DIS_REMAP);

    // Set contrast of display
    spi_write(CONTRAST_COMMAND);
    spi_write(CONTRAST);

    // Set precharge period
    spi_write(PRECHARGE_COMMAND);
    spi_write(PRECHARGE_PERIOD);

    // Set VCOM deselect voltage
    spi_write(VCOMH_DESL_COMM);
    spi_write(VCOMH_DESELECT_77_VCC);

    // Set display to RAM
    spi_write(SET_DISP_TO_RAM);

    // Set display RAM to non inverterd
    spi_write(NON_INVERTED_DISP);

    // Deactivate any scrolling
    spi_write(DEACTIVATE_SCROLL);

    // Set start up graphic
    drawBitmap((SCREEN_WIDTH- fish_width) / 2, (SCREEN_HEIGHT - fish_height) / 2,
                fish_map, fish_width, fish_height);
    
    update_display();
    
    
    // Turn on display
    SELECT_DISPLAY
    COMMAND_DISPLAY
    spi_write(DISPLAY_ON);
    DESLECT_DISPLAY
}






int line_index = 0;


void update_values(void) {
  char val_buf[10];

  // Empty the display
  clearDisplay();
  
  // Reset the text cursor to top left
  cursor_x = 0;
  cursor_y = 0;

  int curr_inc = 0;
  int line_x = (TEXT_HEIGHT - 2)/2;
  int line_y = line_x;

  // Draw icon for current temp
  for(int i = cursor_x; i < cursor_x + TEXT_HEIGHT - 2; i++)
  {
    set_pixel(i, cursor_y);
    if(curr_inc == line_index)
      drawLine(line_x, line_y, i, cursor_y);
    curr_inc++;
  }
  for(int i = cursor_y; i < cursor_y + TEXT_HEIGHT - 2; i++)
  {
    set_pixel(cursor_x  + TEXT_HEIGHT - 2, i);
    if(curr_inc == line_index)
      drawLine(line_x, line_y, cursor_x  + TEXT_HEIGHT - 2, i);
    curr_inc++;
  }
  for(int i = cursor_x + TEXT_HEIGHT - 2; i >= cursor_x; i--)
  {
    set_pixel(i, cursor_y+TEXT_HEIGHT - 2);
    if(curr_inc == line_index)
      drawLine(line_x, line_y, i, cursor_y+TEXT_HEIGHT - 2);
    curr_inc++;
  }
  for(int i = cursor_y + TEXT_HEIGHT - 2; i >= cursor_y; i--)
  {
    set_pixel(cursor_x, i);
    if(curr_inc == line_index)
      drawLine(line_x, line_y, cursor_x, i);
    curr_inc++;
  }
  
  line_index+=4;
  if(line_index >= curr_inc)
    line_index -= curr_inc;

  // Set temperature
  int temperature = get_temperature();
  int n = sprintf(val_buf, "  %d.%d", temperature/10, temperature - (temperature/10)*10);
  writeString(val_buf, n);
  drawCircle(cursor_x + TEXT_SPACE - DEGREE_SYMBOL_R - 1, cursor_y+DEGREE_SYMBOL_R, DEGREE_SYMBOL_R);
  writeString(" C\n", 3);

 
  // Draw Arrow for setpoint
  drawBitmap(cursor_x, cursor_y, arrow_data, arrow_width, arrow_height);
  
  // Set setpoint
  n = sprintf(val_buf, "  %d.0", get_temp_setpoint());
  writeString(val_buf, n);
  drawCircle(cursor_x + TEXT_SPACE - DEGREE_SYMBOL_R - 1, cursor_y+DEGREE_SYMBOL_R, DEGREE_SYMBOL_R);
  writeString(" C\n\n", 4);

  // Set status
  switch(get_status()) {
    case WATER_ON:
      writeString("Water On", 8);
      break;
    case WATER_ON_TEMP:
      if(show_on_temp)
        writeString("On Temp", 7);
      break;
    case WATER_OFF:
    default:
      writeString("Water Off", 9);
      break;
  }

  show_on_temp = !show_on_temp;

  update_display();
}
