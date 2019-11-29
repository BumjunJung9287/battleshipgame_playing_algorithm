/* file = xutil.h */
#define FONT_HEIGHT 10     /* probably should query X for this */
#define FONT_WIDTH 8     /* probably should query X for this */

#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

Display	*display;
Window	win;

/* shared colors */
GC gc_red, gc_pink, gc_grey;
/* primary colors */
GC gc_wash, gc_deep, gc_green, gc_orange, gc_yellow,
   gc_purple, gc_brown, gc_red1, gc_red2, gc_red3, gc_red4, gc_grey;

void sg_create(int width, int height, int flushflag, char *name);	
void sg_shared_gcs(void);
void sg_primary_gcs(void);
void sg_pastel_gcs(void);
void sg_add_color(GC *new_gc, char *color_name);
void sg_wait_for_mapping(void);
void sg_clear(void);
void sg_flush(void);
void sg_close(void);

void sg_line(int x0,int y0,int x1,int y1);
void sg_line_red(int x0,int y0,int x1,int y1);
void sg_clear_line(int x0, int y0, int x1, int y1);

void vertical_dots(int x, int y1, int y2); 
void horizontal_dots(int x1, int x2, int y); 

void sg_string(int x, int y, char *s);	
void sg_imagestring(int x, int y, char *s);	
void sg_string_red(int x, int y, char *s);	
void sg_clear_string(int x, int y, char *s);

void sg_pset(int x, int y);
void sg_pset_red(int x, int y);
void sg_pset_green(int x, int y);
void sg_preset(int x, int y);
void sg_big_preset(int x, int y);

void sg_draw_rect(int x, int y, int width, int height);
void sg_ellipse(int x, int y, int width, int height);
void sg_rect_color(int x, int y, int width, int height, GC color_gc);
void sg_draw_wash_rect(int x, int y, int width, int height);
void sg_draw_deep_rect(int x, int y, int width, int height);
void sg_erase_rect(int x, int y, int width, int height);
void sg_outline_rect(int x, int y, int width, int height);
void sg_clear_outline_rect(int x, int y, int width, int height);

void sg_bell(void);

void sg_big_pset_deep(int x, int y);
void sg_big_pset_red(int x, int y);

void sg_line_color(int x0, int y0, int x1, int y1, GC color_gc);
void sg_pset_color(int x, int y, GC color_gc);
void sg_big_pset_color(int x, int y, GC color_gc);
void sg_disc(int x, int y, int diameter, GC gc);
