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

#endif //OGG_GRAPHIC_UTILS__HEADER_FILE______