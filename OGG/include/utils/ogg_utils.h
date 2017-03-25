#ifndef OGG_GRAPHIC_UTILS__HEADER_FILE______
#define OGG_GRAPHIC_UTILS__HEADER_FILE______
#include "geometry.h"
//# define DEBUG
# ifdef DEBUG
    int alloc_memory;
# endif

#  ifndef REG__GEOMETRY_SYSTEM__FLOAT__F___
#   define REG__GEOMETRY_SYSTEM__FLOAT__F___
    register_geometry_system(float, f);
#  endif
#  ifndef REG__GEOMETRY_SYSTEM__INT__I___
#   define REG__GEOMETRY_SYSTEM__INT__I___
    register_geometry_system(int, i)
#  endif

    typedef coordi ogg_coord;
    typedef rectf ogg_pec_anchor;
    typedef recti ogg_coord_anchor;
    typedef unsigned char ogg_bool;
    static const ogg_bool ogg_false = 0;
    static const ogg_bool ogg_true = 1;

    void ogg_clear_screen(void);
    void ogg_flush_screen(void);

    typedef struct {
        float R, G, B;
    } ogg_color;

    static const ogg_color OGG_BLACK = {
        0.0, 0.0, 0.0
    };
    static const ogg_color OGG_RED = {
        255.0/255.0, 0.0, 0.0
    };
    static const ogg_color OGG_GREEN = {
        0.0, 255.0/255.0, 0.0
    };
    static const ogg_color OGG_BLUE = {
        0.0, 0.0, 255.0/255.0
    };
    static const ogg_color OGG_YELLOW = {
        255.0/255.0, 255.0/255.0, 0.0
    };
    static const ogg_color OGG_FUCHSIN = {
        255.0/255.0, 0.0, 255.0/255.0
    };
    static const ogg_color OGG_CYAN = {
        0.0, 255.0/255.0, 255.0/255.0
    };
    static const ogg_color OGG_WHITE = {
        255.0/255.0, 255.0/255.0, 255.0/255.0
    };

    void ogg_paint_char(char chr, ogg_color color, coordf pix);

    void ogg_paint_string(const char* str, ogg_color color, coordf pix);

    ogg_color ogg_make_color(int R, int G, int B);

    typedef struct {
        coordf* point;
        unsigned size;
    } ogg_vertex;

    ogg_vertex* vertex_list(unsigned n, ...);

    coordf vertex(float x, float y);

#endif //OGG_GRAPHIC_UTILS__HEADER_FILE______