#ifndef OGG_GRAPHIC_COMPONENT__GRID_CANVAS__HEADER_FILE____
# define OGG_GRAPHIC_COMPONENT__GRID_CANVAS__HEADER_FILE____
# include "ogg_components.h"

    typedef enum {
        ogg_rect_unit = 0,
        ogg_bitmap_unit
    } ogg_paint_unit_type;

    typedef struct {
        ogg_color color;
    } ogg_paint_unit_rect;

    typedef struct {
        ogg_paint_unit_type type;
        union {
            ogg_paint_unit_rect rect;
            //ogg_paint_unit_bitmap bitmap;
        };
    } ogg_paint_unit;

    def_startup(ogg_grid_canvas)(
        ogg_coord size;
    );

    def_component(ogg_grid_canvas)(
        ogg_coord size;
        ogg_paint_unit* sub;
    );

    void paint_grid_canvas_elem(ogg_com_ptr canvas, ogg_coord pos);

    void resize_canvas(ogg_com_ptr canvas, ogg_coord size);

    void set_canvas_color(ogg_com_ptr canvas, ogg_coord pos, ogg_color color);

    //void set_canvas_bitmap

#endif //OGG_GRAPHIC_COMPONENT__GRID_CANVAS__HEADER_FILE____
