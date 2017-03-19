#include "graphic_utils.h"
#include <GL/freeglut.h>

#ifdef __cplusplus
extern "C"{
#endif

void ogg_clear_screen()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

# ifndef OGG_CUSTOM_STARTUP

# ifndef INST__GEOMETRY_SYSTEM__FLOAT__F___
#  define INST__GEOMETRY_SYSTEM__FLOAT__F___
    inst_geometry_system(float, f);
# endif
# ifndef INST__GEOMETRY_SYSTEM__INT__I___
#  define INST__GEOMETRY_SYSTEM__INT__I___
    inst_geometry_system(int, i)
# endif

int main(int argc, char *argv[])
{
    ogg_startup_info st = {
        .argc = argc,
        .argv = argv,
        .display_mode = GLUT_RGB | GLUT_SINGLE,
        .window.position = { 100, 100 },
        .window.size = { 400, 400 },
        .window.title = "OGG Form"
    };
    ogg_startup(&st);
    glutInit(&st.argc, st.argv);
    glutInitDisplayMode(st.display_mode);
    glutInitWindowPosition(st.window.position.x, st.window.position.y);
    glutInitWindowSize(st.window.size.width, st.window.size.height);
    glutCreateWindow(st.window.title);
    ogg_delegate();
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    glutMainLoop();
    return ogg_exit_status();
}

# endif

#ifdef __cplusplus
}
#endif
