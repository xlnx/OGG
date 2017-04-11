#ifndef OGG__OPENGL_GRAPHIC_LIBRARY__HEADER_FILE____
#define OGG__OPENGL_GRAPHIC_LIBRARY__HEADER_FILE____

# ifdef __cplusplus
extern "C" {
# endif

# include "components/ogg_components.h"

# include "components/ogg_forms.h"
# include "components/ogg_grid.h"
# include "components/ogg_shape.h"
# include "components/ogg_button.h"
# include "components/ogg_edit.h"
# include "components/ogg_grid_canvas.h"

# include <../dependency/freeglut/freeglut/include/GL/freeglut.h>

# ifndef LIB_OGG__BUILDING

#  ifdef WIN32
#    ifndef OGG_SHOW_CONSOLE
#      pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#    endif
#  endif

    extern ogg_application* application;

    void ogg_init_application_forms();

    void ogg_init_application(ogg_application* this);

    void ogg_terminate_application(ogg_application* this);

    void ogg_run_application(ogg_application* this);

    void ogg_terminate();

    int main(int argc, char *argv[]);

# endif

# ifdef __cplusplus
}
#endif

#endif //OGG__OPENGL_GRAPHIC_LIBRARY__HEADER_FILE____