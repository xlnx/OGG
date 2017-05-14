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
#  include "components/ogg_page_control.h"

#  include "utils/ogg_exception.h"

#  include <../dependency/freeglut/freeglut/include/GL/freeglut.h>

#ifndef LIB_OGG__BUILDING

#    ifdef WIN32
#      ifndef OGG_SHOW_CONSOLE
#        pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#      endif
#    endif

    ogg_application* application = 0;

    void ogg_init_application_forms();

    int main(int argc, char *argv[])
    {
        ogg_create(ogg_application)(
            {
                0,
                {
                    ogg_anchor_pec,
                    {
                        { 0, 0, 100, 100 }
                    }
                }
            },
            &argc,
            argv,
            GLUT_RGB | GLUT_SINGLE
        )(application);
        set_application(application);
        ogg_init_application(application);
        ogg_init_application_forms();
        ogg_run_application(application);
    }

#endif

#  ifdef __cplusplus
}
#  endif

#endif //OGG__OPENGL_GRAPHIC_LIBRARY__HEADER_FILE____