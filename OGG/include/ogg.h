#ifndef OGG__OPENGL_GRAPHIC_LIBRARY__HEADER_FILE____
#define OGG__OPENGL_GRAPHIC_LIBRARY__HEADER_FILE____

# ifdef __cplusplus
extern "C" {
# endif

#  include "components/ogg_components.h"
#  include "components/ogg_forms.h"
#  include "components/ogg_grid.h"
#  include "components/ogg_shape.h"
#  include "components/ogg_button.h"
#  include "components/ogg_edit.h"
#  include "components/ogg_grid_canvas.h"

#  include <../dependency/freeglut/freeglut/include/GL/freeglut.h>

#  ifndef LIB_OGG__BUILDING
#  ifndef DESIGN_TIME

#    ifdef WIN32
#      ifndef OGG_SHOW_CONSOLE
#        pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#      endif
#    endif

    void ogg_init_application_forms();

    int main(int argc, char *argv[]);

#  endif
#  endif

# ifdef __cplusplus
}
#endif

#endif //OGG__OPENGL_GRAPHIC_LIBRARY__HEADER_FILE____