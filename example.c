#define BTPRNT_IMPL
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "btprnt.h"
#include "font.xbm"

#define MESSAGE \
    "There is\n" \
    "one art,\n" \
    "no more,\n" \
    "no less,\n" \
    "to do\n" \
    "all things\n" \
    "with art-\n" \
    "lessness." \

static btprnt_buf * setup_font(void)
{
    return btprnt_buf_extmem(font_width,
                             font_height,
                             font_bits);
}

static void draw_triangle(btprnt_region *r)
{
    int v1x, v1y;
    int v2x, v2y;
    int v3x, v3y;

    v1x = 3;
    v1y = 3;

    v2x = 40;
    v2y = 21;

    v3x = 10;
    v3y = 80;

    btprnt_draw_triangle(r,
                         v1x, v1y,
                         v2x, v2y,
                         v3x, v3y,
                         1);

}

static void draw_arrow(btprnt_region *r)
{
    int startx;
    int starty;
    int endx;
    int endy;


    startx = 40;
    starty = 40;

    endx = 80;
    endy = 60;

    btprnt_draw_rect(r, startx, starty, 50, 50, 1);
    startx += 50;
    starty += 30;
    endx += 50;
    endy += 50;

    btprnt_draw_arrow(r, startx, starty, endx, endy, 1, 1, 1);
    endx -= 10;
    btprnt_draw_rect(r, endx, endy, 20, 20, 1);


    startx = 100;
    starty = 0;

    endx = 100;
    endy = 40;

    btprnt_draw_rect(r, startx, starty, 20, 20, 1);
    startx += 10;
    starty += 20;

    btprnt_draw_arrow(r, startx, starty, endx, endy, 1, 1, 1);
}

int main(int argc, char *argv[])
{
    btprnt *bp;
    btprnt_region r;
    btprnt_buf *font;
    int off;

    off = 6;
    bp = btprnt_new(400, 200);

    if (bp == NULL) {
        printf("There was an issue starting btprnt\n");
        return 1;
    }

    font = setup_font();

    btprnt_region_init(btprnt_canvas_get(bp),
                       &r, 10, 10,
                       180, 180);

    btprnt_fill(&r, 1);

    btprnt_draw_textbox(&r, font,
                        off, off,
                        8, 8,
                        "Ars Brevis", 2, 0);

    btprnt_draw_rect(&r, off/2, off/2, 180 - off, 180 - off, 0);

    btprnt_draw_textbox(&r, font,
                        off, 16 + off,
                        8, 8, "\nby Piet Hein", 1, 0);

    btprnt_draw_textbox(&r, font,
                        off, 8*5 + off,
                        8, 8, MESSAGE, 1, 0);

    btprnt_draw_circ(&r,
                     180 - 32 - 16,
                     180 - 32 - 16,
                     32, 0);

    btprnt_draw_rect_filled(&r,
                            32,
                            180 - 32 - 16,
                            32, 32, 0);


    btprnt_region_init(btprnt_canvas_get(bp),
                       &r, 210, 10,
                       180, 180);

    draw_triangle(&r);

    draw_arrow(&r);

    btprnt_buf_pbm(btprnt_buf_get(bp), "out.pbm");

    btprnt_del(&bp);
    btprnt_buf_free(&font);
    return 0;
}
