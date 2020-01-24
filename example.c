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

int main(int argc, char *argv[])
{
    btprnt *bp;
    btprnt_region r;
    btprnt_buf *font;

    bp = btprnt_new(200, 200);

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
                        0, 0,
                        8, 8,
                        "Ars Brevis", 2, 0);

    btprnt_draw_textbox(&r, font,
                        0, 16,
                        8, 8, "\nby Piet Hein", 1, 0);

    btprnt_draw_textbox(&r, font,
                        0, 8*5,
                        8, 8, MESSAGE, 1, 0);

    btprnt_buf_pbm(btprnt_buf_get(bp), "out.pbm");

    btprnt_del(&bp);
    btprnt_buf_free(&font);
    return 0;
}
