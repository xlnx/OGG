#include "ogg_utils.h"

# ifndef INST__GEOMETRY_SYSTEM__FLOAT__F___
#  define INST__GEOMETRY_SYSTEM__FLOAT__F___
inst_geometry_system(float, f);
# endif

# ifndef INST__GEOMETRY_SYSTEM__INT__I___
#  define INST__GEOMETRY_SYSTEM__INT__I___
inst_geometry_system(int, i)
# endif

void ogg_clear_screen(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
}
