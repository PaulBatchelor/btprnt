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


    btprnt_buf_pbm(btprnt_buf_get(bp), "out.pbm");


    btprnt_del(&bp);
    btprnt_buf_free(&font);
    return 0;
}
