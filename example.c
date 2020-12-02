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

    btprnt_draw_arrow(r, startx, starty, endx, endy, 1, 1, 1, 1);
    endx -= 10;
    btprnt_draw_rect(r, endx, endy, 20, 20, 1);


    startx = 100;
    starty = 0;

    endx = 100;
    endy = 40;

    btprnt_draw_rect(r, startx, starty, 20, 20, 1);
    startx += 10;
    starty += 20;

    btprnt_draw_arrow(r, startx, starty, endx, endy, 1, 1, 1, 1);
}

static void draw_bezier(btprnt_region *r)
{
    btprnt_draw_bezier(r,
                       0, 150,
                       50, 100,
                       100, 130,
                       1);
}

static void draw_bezier_arrow(btprnt_region *r)
{

    btprnt_draw_bezier_arrow(r,
                       20, 150,
                       90, 150,
                       65, 180,
                       1, 1,
                       1);
}

static void draw_tinytile(btprnt_region *r)
{
    int pat;
    int offx, offy;

    /* black square, white square */
    pat = 0xf0;

    offx = 160;
    offy = 88;

    /* checkerboard */
    btprnt_draw_tinytile(r, offx, offy, pat, 0xa5, 0xa5);

    /* vertical lines */
    btprnt_draw_tinytile(r, offx + 8, offy, pat, 0xaa, 0xaa);

    /* horizontal lines */
    btprnt_draw_tinytile(r, offx , offy + 8, pat, 0xf0, 0xf0);

    /* box */
    btprnt_draw_tinytile(r, offx + 8, offy + 8, pat, 0xff, 0xff);
}

static void draw_centerbox(btprnt_region *r)
{
    btprnt_region center;
    btprnt_region g;
    btprnt_region b;
    int border;

    border = 4;
    btprnt_layout_centerbox(r, 80, 100, &center);

    btprnt_layout_outline(r, 1);
    btprnt_layout_outline(&center, 1);

    btprnt_layout_grid(&center, 2, 3, 0, 0, &g);
    btprnt_layout_border(&g, border, &b);
    btprnt_layout_outline(&b, 1);
    btprnt_layout_grid(&center, 2, 3, 1, 0, &g);
    btprnt_layout_border(&g, border, &b);
    btprnt_layout_outline(&b, 1);

    btprnt_layout_grid(&center, 1, 3, 0, 1, &g);
    btprnt_layout_border(&g, border, &b);
    btprnt_layout_outline(&b, 1);

    btprnt_layout_grid(&center, 1, 3, 0, 2, &g);
    btprnt_layout_border(&g, border, &b);
    btprnt_layout_outline(&b, 1);
}

static void draw_hexagon(btprnt_region *r, int xpos, int ypos)
{
    int x, y;

    x = xpos;
    y = ypos;
    btprnt_draw_slopeline(r, x, y, 1, 2, 7, 1, &x, &y);
    btprnt_draw_slopeline(r, x, y, 1, 0, 10, 1, &x, &y);
    btprnt_draw_slopeline(r, x + 1, y - 1, 1, -2, 7, 1, &x, &y);
    btprnt_draw_slopeline(r, x - 1, y - 1, -1, -2, 7, 1, &x, &y);
    btprnt_draw_slopeline(r, x, y, -1, 0, 10, 1, &x, &y);
    btprnt_draw_slopeline(r, x - 1, y + 1, -1, 2, 7, 1, &x, &y);
}

int main(int argc, char *argv[])
{
    btprnt *bp;
    btprnt_region r;
    btprnt_buf *font;
    int off;

    off = 6;
    bp = btprnt_new(400, 400);

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


    /* second area to draw stuff */

    btprnt_region_init(btprnt_canvas_get(bp),
                       &r, 210, 10,
                       180, 180);

    draw_triangle(&r);

    draw_arrow(&r);

    draw_bezier(&r);
    draw_bezier_arrow(&r);

    draw_tinytile(&r);

    /* bottom-left quadrant */
    btprnt_region_init(btprnt_canvas_get(bp),
                       &r, 10, 210,
                       180, 180);

    draw_centerbox(&r);

    btprnt_draw_circ_filled(&r, 10, 10, 8, 1);
    btprnt_draw_circ(&r, 30, 10, 8, 1);

    draw_hexagon(&r, 4, 100);
    draw_hexagon(&r, 4 + 13, 100 + 7);
    draw_hexagon(&r, 4 + 13, 100 - 7);
    draw_hexagon(&r, 4, 100 - 14);
    draw_hexagon(&r, 4 + 13, 100 - 21);

    /* bottom-right quadrant */
    btprnt_region_init(btprnt_canvas_get(bp),
                       &r, 210, 210,
                       180, 180);

    btprnt_layout_outline(&r, 1);
    btprnt_draw_circ(&r, 32, 32, 16, 1);
    btprnt_draw_thickcirc(&r, 70, 32, 16, 2, 1);
    btprnt_draw_thickcirc(&r, 110, 32, 16, 4, 1);
    btprnt_draw_thickcirc(&r, 155, 32, 16, 8, 1);

    btprnt_draw_thickline(&r, 10, 170, 90, 100, 3, 1);
    btprnt_draw_thickline(&r, 10, 170, 40, 100, 2, 1);
    btprnt_draw_thickline(&r, 10, 170, 90, 150, 4, 1);

    btprnt_buf_pbm(btprnt_buf_get(bp), "out.pbm");

    btprnt_del(&bp);
    btprnt_buf_free(&font);
    return 0;
}
