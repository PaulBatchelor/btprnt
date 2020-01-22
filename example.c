#define BTPRNT_IMPL
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "btprnt.h"
#include "font.xbm"

#define MESSAGE \
    "i am of the nature to grow old.\n\n" \
    "there is no way to escape growing old."

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
                       &r,
                       (200 - 112) / 2,
                       (200 - (8 * 8))/2,
                       112, 112);

    btprnt_draw_textbox(&r, font, 0, 0, 8, 8, MESSAGE);

    btprnt_buf_xbm(btprnt_buf_get(bp), "grow_old", "out.xbm");

    btprnt_del(&bp);
    btprnt_buf_free(&font);
    return 0;
}
