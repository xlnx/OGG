#ifndef OGG_GRAPHIC_STARUP__HEADER_FILE____
#define OGG_GRAPHIC_STARUP__HEADER_FILE____
#include "graphic_components.h"
#include <GL/glut.h>

# ifdef WIN32
#  ifndef OGG_SHOW_CONSOLE
#   pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#  endif
# endif

# ifndef OGG_CUSTOM_STARTUP
    typedef unsigned int ogg_display_mode;

    typedef struct {
        int x, y;
    } ogg_window_position;

    typedef struct {
        int width, height;
    } ogg_window_size;

    typedef struct {
        ogg_window_position position;
        ogg_window_size size;
        const char *title;
    } ogg_window_info;

    typedef struct {
        int argc;
        char **argv;
        ogg_display_mode display_mode;
        ogg_window_info window;
    } ogg_startup_info;

    typedef struct {
        ogg_component com;
    } ogg_window;

    ogg_com_startup make_global_startup(void);

    void ogg_startup(ogg_startup_info*);
    void ogg_delegate(void);
    int ogg_exit_status(void);

    int main(int argc, char *argv[]);
# endif

#endif //OGG_GRAPHIC_STARUP__HEADER_FILE____