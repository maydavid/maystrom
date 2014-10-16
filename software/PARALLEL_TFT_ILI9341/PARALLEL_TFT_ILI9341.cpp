#include "PARALLEL_TFT_ILI9341.h"
#include "mbed.h"

#define BPP         16                  // Bits per pixel    



PARALLEL_TFT_ILI9341::PARALLEL_TFT_ILI9341(
    PinName cs,
    PinName reset,
    PinName dc,
    PinName wr,
    PinName rd,
    PinName im0,
    PortName dp,
    PortName dp2,
    unsigned int p0,
    unsigned int p1,
    unsigned int p2,
    unsigned int p3,
    unsigned int p4,
    unsigned int p5,
    unsigned int p6,
    unsigned int p7,
    unsigned int p8,
    unsigned int p9,
    unsigned int p10,
    unsigned int p11,
    unsigned int p12,
    unsigned int p13,
    unsigned int p14,
    unsigned int p15,
    const char *name)
    : _CS(cs),
      _RESET(reset),
      _DC(dc),
      _WR(wr),
      _RD(rd),
      _IM0(im0),
      _dp(dp),
      _dp2(dp2),
      _p0(p0), _p1(p1),_p2(p2),_p3(p3),_p4(p4),_p5(p5),_p6(p6),_p7(p7),_p8(p8), _p9(p9),_p10(p10),_p11(p11),_p12(p12),_p13(p13),_p14(p14),_p15(p15),
      GraphicsDisplay(name)
{

    portmask = 0;
    portmask |= 1 << _p0;
    portmask |= 1 << _p1;
    portmask |= 1 << _p2;
    portmask |= 1 << _p3;
    portmask |= 1 << _p4;
    portmask |= 1 << _p5;
    portmask |= 1 << _p6;
    portmask |= 1 << _p7;
    port_init(&_dataBus, dp, portmask, PIN_OUTPUT);
    portmask = 0;
    portmask |= 1 << _p8;
    portmask |= 1 << _p9;
    portmask |= 1 << _p9;
    portmask |= 1 << _p10;
    portmask |= 1 << _p11;
    portmask |= 1 << _p12;
    portmask |= 1 << _p13;
    portmask |= 1 << _p14;
    port_init(&_dataBus2,dp2,portmask,PIN_OUTPUT);
    orientation = 0;
    char_x = 0;
    tft_reset();
}

int PARALLEL_TFT_ILI9341::width()
{
    if (orientation == 0 || orientation == 2) return 240;
    else return 320;
}


int PARALLEL_TFT_ILI9341::height()
{
    if (orientation == 0 || orientation == 2) return 320;
    else return 240;
}


void PARALLEL_TFT_ILI9341::set_orientation(unsigned int o)
{
    orientation = o;
    wr_cmd(0x36);                     // MEMORY_ACCESS_CONTROL
    switch (orientation) {
            // was x8h
        case 0:
            wr_dat16(0x00C8);
            break;
        case 1:
            wr_dat16(0x00A8);
            break;
        case 2:
            wr_dat16(0x0008);
            break;
        case 3:
            wr_dat16(0x0068);
            break;
    }
    WindowMax();
}


// write command to tft register

void PARALLEL_TFT_ILI9341::wr_cmd(unsigned char cmd)
{
    _CS = 0;
    _DC = 0;
    _WR = 1;
    _RD = 1;
    uint32_t co_s=0;
    co_s |= ((cmd>>7) & 0x01) << _p0;
    co_s |= ((cmd>>6) & 0x01) << _p1;
    co_s |= ((cmd>>5) & 0x01) << _p2;
    co_s |= ((cmd>>4) & 0x01) << _p3;
    co_s |= ((cmd>>3) & 0x01) << _p4;
    co_s |= ((cmd>>2) & 0x01) << _p5;
    co_s |= ((cmd>>1) & 0x01) << _p6;
    co_s |= ((cmd>>0) & 0x01) << _p7;
    port_write(&_dataBus,co_s);
    _WR = 0;
    _WR = 1;
}



void PARALLEL_TFT_ILI9341::wr_dat(unsigned char dat)
{
    _CS = 0;
    _DC = 1;
    _WR = 0;
    _RD = 1;
    uint32_t co_s=0;
    co_s |= ((dat>>7) & 0x01) << _p0;
    co_s |= ((dat>>6) & 0x01) << _p1;
    co_s |= ((dat>>5) & 0x01) << _p2;
    co_s |= ((dat>>4) & 0x01) << _p3;
    co_s |= ((dat>>3) & 0x01) << _p4;
    co_s |= ((dat>>2) & 0x01) << _p5;
    co_s |= ((dat>>1) & 0x01) << _p6;
    co_s |= ((dat>>0) & 0x01) << _p7;
    port_write(&_dataBus,co_s);
    //_WR = 0;
    _WR = 1;
    _CS = 1;
}


void PARALLEL_TFT_ILI9341::wr_dat16(uint16_t dat)
{
    _CS = 0;
    _DC = 1;
    _WR = 0;
    _RD = 1;
    uint32_t co_s=0;
    co_s |= ((dat>>7) & 0x01) << _p0;
    co_s |= ((dat>>6) & 0x01) << _p1;
    co_s |= ((dat>>5) & 0x01) << _p2;
    co_s |= ((dat>>4) & 0x01) << _p3;
    co_s |= ((dat>>3) & 0x01) << _p4;
    co_s |= ((dat>>2) & 0x01) << _p5;
    co_s |= ((dat>>1) & 0x01) << _p6;
    co_s |= ((dat>>0) & 0x01) << _p7;
    port_write(&_dataBus,co_s);
    co_s=0;
    co_s |= ((dat>>15) & 0x01) << _p8;
    co_s |= ((dat>>14) & 0x01) << _p9;
    co_s |= ((dat>>13) & 0x01) << _p10;
    co_s |= ((dat>>12) & 0x01) << _p11;
    co_s |= ((dat>>11) & 0x01) << _p12;
    co_s |= ((dat>>10) & 0x01) << _p13;
    co_s |= ((dat>>9) & 0x01) << _p14;
    co_s |= ((dat>>8) & 0x01) << _p15;
    port_write(&_dataBus2,co_s);
    //_WR = 0;
    _WR = 1;
    _CS = 1;
}


// the ILI9341 can read

char PARALLEL_TFT_ILI9341::rd_byte(unsigned char cmd)
{

    char r=0;
    /*
    _dc = 0;
    _cs = 0;
    wr_dat(cmd);      // mbed lib
    _cs = 1;
    r = wr_dat(0xff);
    _cs = 1;
    */
    return(r);
}

// read 32 bit
int PARALLEL_TFT_ILI9341::rd_32(unsigned char cmd)
{
    int d=0;
    /*
    _dc = 0;
    _cs = 0;
    d = cmd;
    d = d << 1;
    _spi.format(9,3);    // we have to add a dummy clock cycle
    wr_dat(d);
    _spi.format(8,3);
    _dc = 1;
    r = wr_dat(0xff);
    d = r;
    r = wr_dat(0xff);
    d = (d << 8) | r;
    r = wr_dat(0xff);
    d = (d << 8) | r;
    r = wr_dat(0xff);
    d = (d << 8) | r;
    _cs = 1;
    */
    return(d);
}

int  PARALLEL_TFT_ILI9341::Read_ID(void)
{
    int r;
    r = rd_byte(0x0A);
    r = rd_byte(0x0A);
    r = rd_byte(0x0A);
    r = rd_byte(0x0A);
    return(r);
}


// Init code based on MI0283QT datasheet

void PARALLEL_TFT_ILI9341::tft_reset()
{


    _IM0 = 0; // 0 16-bit 1 8-bit
    _CS = 0;
    _RD = 1;
    _WR = 0;
    _RESET = 0;
    wait_ms(120);
    _RESET = 1;
    wait_ms(120);

    wr_cmd(0x01);
    wait_ms(5);

    wr_cmd(0x28);//display OFF

    wr_cmd(0x11);
    wr_dat(0x00);//exit SLEEP mode


    wr_cmd(0xCB);//Power Control A
    wr_dat(0x39);//always 0x39
    wr_dat(0x2C);//always 0x2C
    wr_dat(0x00);//always 0x00
    wr_dat(0x34);//Vcore = 1.6V
    wr_dat(0x02);//DDVDH = 5.6V

    wr_cmd(0xCF);//Power Control B
    wr_dat(0x00);//always 0x00
    wr_dat(0x81);//81 PCEQ off
    wr_dat(0x30);//ESD protection


    wr_cmd(0xE8);//Driver timing control A
    wr_dat(0x85);//85 non-overlap
    wr_dat(0x01);//01 EQ timing
    wr_dat(0x79);//79 Pre-charge timing

    wr_cmd(0xEA);//Driver timing control B
    wr_dat(0x00);//Gate driver timing
    wr_dat(0x00);//always 0x00
    /**/


    wr_cmd(0xED);//Power-On sequence control
    wr_dat(0x64);//soft start
    wr_dat(0x03);//power on sequence
    wr_dat(0x12);//power on sequence
    wr_dat(0x81);//DDVDH enhance on

    wr_cmd(0xF7);//Pump ratio control
    wr_dat(0x20);//DDVDH=2xVCI

    wr_cmd(0xC0);//power control 1
    wr_dat(0x26);

    wr_cmd(0xC1);//power control 2
    wr_dat(0x11);

    wr_cmd(0xC5);//VCOM control 1
    wr_dat(0x35);
    wr_dat(0x3E);

    wr_cmd(0xC7);//VCOM control 2
    wr_dat(0xBE);


    wr_cmd(0x36);//memory access control = BGR
    wr_dat(0x88);



    wr_cmd(0xB1);//frame rate control
    wr_dat(0x00);
    wr_dat(0x10);
    //wr_dat(0x33);


    wr_cmd(0xB6);//display function control
    wr_dat(0x0A);
    wr_dat(0xA2);


    wr_cmd(0x3A);//pixel format = 16 bit per pixel
    wr_dat(0x55);

    wr_cmd(0xF2);//3G Gamma control
    wr_dat(0x02);//off


    wr_cmd(0x26);//Gamma curve 3
    wr_dat(0x01);

wr_cmd(0x00E0);wr_dat16(0x001F);//positive gamma correction
                              wr_dat16(0x001B);
                              wr_dat16(0x0018);
                              wr_dat16(0x000B);
                              wr_dat16(0x000F);
                              wr_dat16(0x0009);
                              wr_dat16(0x0046);
                              wr_dat16(0x00B5);
                              wr_dat16(0x0037);
                              wr_dat16(0x000A);
                              wr_dat16(0x000C);
                              wr_dat16(0x0007);
                              wr_dat16(0x0007);
                              wr_dat16(0x0005);
                              wr_dat16(0x0000);
wr_cmd(0x00E1);wr_dat16(0x0000);//negative gamma correction
                              wr_dat16(0x0024);
                              wr_dat16(0x0027);
                              wr_dat16(0x0004);
                              wr_dat16(0x0010);
                              wr_dat16(0x0006);
                              wr_dat16(0x0039);
                              wr_dat16(0x0074);
                              wr_dat16(0x0048);
                              wr_dat16(0x0005);
                              wr_dat16(0x0013);
                              wr_dat16(0x0038);
                              wr_dat16(0x0038);
                              wr_dat16(0x003A);
                              wr_dat16(0x001F);

    wr_cmd(0x2A);
    wr_dat(0x00);//column address set
    wr_dat(0x00);//start 0x0000
    wr_dat(0x00);
    wr_dat(0xEF);//end 0xEF

    wr_cmd(0x2B);
    wr_dat(0x00);//page address set
    wr_dat(0x00);//start 0x00
    wr_dat(0x01);
    wr_dat(0x3F);//end 0x013F


    
    wr_cmd(0x11);
    wait_ms(200);
    wr_cmd(0x29);
    wait_ms(200);

    wr_cmd(0x2c);


}


void PARALLEL_TFT_ILI9341::pixel(int x, int y, int color)
{
    wr_cmd(0x2A);
    wr_dat(x >> 8);
    wr_dat(x);
    wr_cmd(0x2B);
    wr_dat(y >> 8);
    wr_dat(y);
    wr_cmd(0x2C);  // send pixel
    //wr_dat(color >> 8);
    //wr_dat(color & 0xff);
    wr_dat16(color);
}


void PARALLEL_TFT_ILI9341::window (unsigned int x, unsigned int y, unsigned int w, unsigned int h)
{

    wr_cmd(0x2A);
    wr_dat(x >> 8);
    wr_dat(x);
    wr_dat((x+w-1) >> 8);
    wr_dat((x+w-1));
    wr_cmd(0x2B);
    wr_dat(y >> 8);
    wr_dat(y);
    wr_dat((y+h-1) >> 8);
    wr_dat((y+h-1));
    wr_dat16(y+h-1);
    wr_cmd(0x2C);

}


void PARALLEL_TFT_ILI9341::WindowMax (void)
{
    window (0, 0, width(),  height());
}



void PARALLEL_TFT_ILI9341::cls (void)
{
    //int pixel = ( width() * height());
    WindowMax();
    wr_cmd(0x2C);  // send pixel
    unsigned int i;
    for (i = 0; i < ( width() * height()); i++) {
        //wr_dat(_background >> 8);
        //wr_dat(_background & 0xff);
        wr_dat16(_background);
    }

}


void PARALLEL_TFT_ILI9341::circle(int x0, int y0, int r, int color)
{

    int x = -r, y = 0, err = 2-2*r, e2;
    do {
        pixel(x0-x, y0+y,color);
        pixel(x0+x, y0+y,color);
        pixel(x0+x, y0-y,color);
        pixel(x0-x, y0-y,color);
        e2 = err;
        if (e2 <= y) {
            err += ++y*2+1;
            if (-x == y && e2 <= x) e2 = 0;
        }
        if (e2 > x) err += ++x*2+1;
    } while (x <= 0);

}

void PARALLEL_TFT_ILI9341::fillcircle(int x0, int y0, int r, int color)
{
    int x = -r, y = 0, err = 2-2*r, e2;
    do {
        vline(x0-x, y0-y, y0+y, color);
        vline(x0+x, y0-y, y0+y, color);
        e2 = err;
        if (e2 <= y) {
            err += ++y*2+1;
            if (-x == y && e2 <= x) e2 = 0;
        }
        if (e2 > x) err += ++x*2+1;
    } while (x <= 0);
}


void PARALLEL_TFT_ILI9341::hline(int x0, int x1, int y, int color)
{
    int w;
    w = x1 - x0 + 1;
    window(x0,y,w,1);
    wr_cmd(0x2C);  // send pixel
    int j;
    for (j=0; j<w; j++) {
        //wr_dat(color >> 8);
        //wr_dat(color & 0xff);
        wr_dat16(color);
    }
    WindowMax();
    return;
}

void PARALLEL_TFT_ILI9341::vline(int x, int y0, int y1, int color)
{
    int h;
    h = y1 - y0 + 1;
    window(x,y0,1,h);
    wr_cmd(0x2C);  // send pixel
    for (int y=0; y<h; y++) {
        //wr_dat(color >> 8);
        //wr_dat(color & 0xff);
        wr_dat16(color);
    }
    WindowMax();
    return;
}



void PARALLEL_TFT_ILI9341::line(int x0, int y0, int x1, int y1, int color)
{
    //WindowMax();
    int   dx = 0, dy = 0;
    int   dx_sym = 0, dy_sym = 0;
    int   dx_x2 = 0, dy_x2 = 0;
    int   di = 0;

    dx = x1-x0;
    dy = y1-y0;

    if (dx == 0) {        /* vertical line */
        if (y1 > y0) vline(x0,y0,y1,color);
        else vline(x0,y1,y0,color);
        return;
    }

    if (dx > 0) {
        dx_sym = 1;
    } else {
        dx_sym = -1;
    }
    if (dy == 0) {        /* horizontal line */
        if (x1 > x0) hline(x0,x1,y0,color);
        else  hline(x1,x0,y0,color);
        return;
    }

    if (dy > 0) {
        dy_sym = 1;
    } else {
        dy_sym = -1;
    }

    dx = dx_sym*dx;
    dy = dy_sym*dy;

    dx_x2 = dx*2;
    dy_x2 = dy*2;

    if (dx >= dy) {
        di = dy_x2 - dx;
        while (x0 != x1) {

            pixel(x0, y0, color);
            x0 += dx_sym;
            if (di<0) {
                di += dy_x2;
            } else {
                di += dy_x2 - dx_x2;
                y0 += dy_sym;
            }
        }
        pixel(x0, y0, color);
    } else {
        di = dx_x2 - dy;
        while (y0 != y1) {
            pixel(x0, y0, color);
            y0 += dy_sym;
            if (di < 0) {
                di += dx_x2;
            } else {
                di += dx_x2 - dy_x2;
                x0 += dx_sym;
            }
        }
        pixel(x0, y0, color);
    }
    return;
}


void PARALLEL_TFT_ILI9341::rect(int x0, int y0, int x1, int y1, int color)
{

    if (x1 > x0) hline(x0,x1,y0,color);
    else  hline(x1,x0,y0,color);

    if (y1 > y0) vline(x0,y0,y1,color);
    else vline(x0,y1,y0,color);

    if (x1 > x0) hline(x0,x1,y1,color);
    else  hline(x1,x0,y1,color);

    if (y1 > y0) vline(x1,y0,y1,color);
    else vline(x1,y1,y0,color);

    return;
}



void PARALLEL_TFT_ILI9341::fillrect(int x0, int y0, int x1, int y1, int color)
{

    int h = y1 - y0 + 1;
    int w = x1 - x0 + 1;
    int pixel = h * w;
    window(x0,y0,w,h);
    wr_cmd(0x2C);  // send pixel
    for (int p=0; p<pixel; p++) {
        //wr_dat(color >> 8);
        //wr_dat(color & 0xff);
        wr_dat16(color);
    }
    WindowMax();
    return;
}


void PARALLEL_TFT_ILI9341::locate(int x, int y)
{
    char_x = x;
    char_y = y;
}



int PARALLEL_TFT_ILI9341::columns()
{
    return width() / font[1];
}



int PARALLEL_TFT_ILI9341::rows()
{
    return height() / font[2];
}



int PARALLEL_TFT_ILI9341::_putc(int value)
{
    if (value == '\n') {    // new line
        char_x = 0;
        char_y = char_y + font[2];
        if (char_y >= height() - font[2]) {
            char_y = 0;
        }
    } else {
        character(char_x, char_y, value);
    }
    return value;
}


void PARALLEL_TFT_ILI9341::character(int x, int y, int c)
{
    unsigned int hor,vert,offset,bpl,j,i,b;
    unsigned char* zeichen;
    unsigned char z,w;

    if ((c < 31) || (c > 127)) return;   // test char range

    // read font parameter from start of array
    offset = font[0];                    // bytes / char
    hor = font[1];                       // get hor size of font
    vert = font[2];                      // get vert size of font
    bpl = font[3];                       // bytes per line

    if (char_x + hor > width()) {
        char_x = 0;
        char_y = char_y + vert;
        if (char_y >= height() - font[2]) {
            char_y = 0;
        }
    }

    window(char_x, char_y,hor,vert); // char box

    wr_cmd(0x2C);  // send pixel
    zeichen = &font[((c -32) * offset) + 4]; // start of char bitmap
    w = zeichen[0];                          // width of actual char
    for (j=0; j<vert; j++) {  //  vert line
        for (i=0; i<hor; i++) {   //  horz line
            z =  zeichen[bpl * i + ((j & 0xF8) >> 3)+1];
            b = 1 << (j & 0x07);
            if (( z & b ) == 0x00) {
                //wr_dat(_background >> 8);
                //wr_dat(_background & 0xff);
                wr_dat16(_background);
            } else {
                //wr_dat(_foreground >> 8);
                //wr_dat(_foreground & 0xff);
                wr_dat16(_foreground);
            }
        }
    }

    WindowMax();
    if ((w + 2) < hor) {                   // x offset to next char
        char_x += w + 2;
    } else char_x += hor;
}


void PARALLEL_TFT_ILI9341::set_font(unsigned char* f)
{
    font = f;
}



void PARALLEL_TFT_ILI9341::Bitmap(unsigned int x, unsigned int y, unsigned int w, unsigned int h,unsigned char *bitmap)
{
    unsigned int  j;
    int padd;
    unsigned short *bitmap_ptr = (unsigned short *)bitmap;
    unsigned short pix_temp;

    unsigned int i;

    // the lines are padded to multiple of 4 bytes in a bitmap
    padd = -1;
    do {
        padd ++;
    } while (2*(w + padd)%4 != 0);
    window(x, y, w, h);
    bitmap_ptr += ((h - 1)* (w + padd));
    wr_cmd(0x2C);  // send pixel                      // switch to 16 bit Mode 3
    for (j = 0; j < h; j++) {         //Lines
        for (i = 0; i < w; i++) {     // one line
            pix_temp = *bitmap_ptr;
            //wr_dat(pix_temp >> 8);
            //wr_dat(pix_temp);
            wr_dat16(pix_temp);
            bitmap_ptr++;
        }
        bitmap_ptr -= 2*w;
        bitmap_ptr -= padd;
    }
    WindowMax();
}


// local filesystem is not implemented in kinetis board , but you can add a SD card

int PARALLEL_TFT_ILI9341::BMP_16(unsigned int x, unsigned int y, const char *Name_BMP)
{

#define OffsetPixelWidth    18
#define OffsetPixelHeigh    22
#define OffsetFileSize      34
#define OffsetPixData       10
#define OffsetBPP           28

    char filename[50];
    unsigned char BMP_Header[54];
    unsigned short BPP_t;
    unsigned int PixelWidth,PixelHeigh,start_data;
    unsigned int    i,off;
    int padd,j;
    unsigned short *line;

    // get the filename
    i=0;
    while (*Name_BMP!='\0') {
        filename[i++]=*Name_BMP++;
    }
    filename[i] = 0;

    FILE *Image = fopen((const char *)&filename[0], "rb");  // open the bmp file
    if (!Image) {
        return(0);      // error file not found !
    }

    fread(&BMP_Header[0],1,54,Image);      // get the BMP Header

    if (BMP_Header[0] != 0x42 || BMP_Header[1] != 0x4D) {  // check magic byte
        fclose(Image);
        return(-1);     // error no BMP file
    }

    BPP_t = BMP_Header[OffsetBPP] + (BMP_Header[OffsetBPP + 1] << 8);
    if (BPP_t != 0x0010) {
        fclose(Image);
        return(-2);     // error no 16 bit BMP
    }

    PixelHeigh = BMP_Header[OffsetPixelHeigh] + (BMP_Header[OffsetPixelHeigh + 1] << 8) + (BMP_Header[OffsetPixelHeigh + 2] << 16) + (BMP_Header[OffsetPixelHeigh + 3] << 24);
    PixelWidth = BMP_Header[OffsetPixelWidth] + (BMP_Header[OffsetPixelWidth + 1] << 8) + (BMP_Header[OffsetPixelWidth + 2] << 16) + (BMP_Header[OffsetPixelWidth + 3] << 24);
    if (PixelHeigh > height() + y || PixelWidth > width() + x) {
        fclose(Image);
        return(-3);      // to big
    }

    start_data = BMP_Header[OffsetPixData] + (BMP_Header[OffsetPixData + 1] << 8) + (BMP_Header[OffsetPixData + 2] << 16) + (BMP_Header[OffsetPixData + 3] << 24);

    line = (unsigned short *) malloc (2 * PixelWidth); // we need a buffer for a line
    if (line == NULL) {
        return(-4);         // error no memory
    }

    // the bmp lines are padded to multiple of 4 bytes
    padd = -1;
    do {
        padd ++;
    } while ((PixelWidth * 2 + padd)%4 != 0);

    window(x, y,PixelWidth ,PixelHeigh);
    wr_cmd(0x2C);  // send pixel                       // switch to 16 bit Mode 3
    for (j = PixelHeigh - 1; j >= 0; j--) {               //Lines bottom up
        off = j * (PixelWidth  * 2 + padd) + start_data;   // start of line
        fseek(Image, off ,SEEK_SET);
        fread(line,1,PixelWidth * 2,Image);       // read a line - slow
        for (i = 0; i < PixelWidth; i++) {        // copy pixel data to TFT
            wr_dat(line[i] >> 8);
            wr_dat(line[i]);
        }
    }
    free (line);
    fclose(Image);
    WindowMax();
    return(1);
}
