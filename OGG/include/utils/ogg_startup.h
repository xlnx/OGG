#ifndef OGG_GRAPHIC_STARUP__HEADER_FILE____
#define OGG_GRAPHIC_STARUP__HEADER_FILE____
#include "components/ogg_components.h"
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
    } ogg_startup_window_position;

    typedef struct {
        int width, height;
    } ogg_startup_window_size;

    typedef struct {
        ogg_startup_window_position position;
        ogg_startup_window_size size;
        const char *title;
    } ogg_startup_window_info;

    typedef struct {
        int argc;
        char **argv;
        ogg_display_mode display_mode;
        ogg_startup_window_info window;
    } ogg_startup_info;

    typedef void(*glut_callback)();
    typedef void(_stdcall *glut_register)(glut_callback);

    void ogg_register_event(event event_name, glut_callback callback);
    ogg_component_info make_global_startup(void);

    void ogg_main(ogg_startup_info*);
# ifdef OGG_GRAPHIC_STARTUP__INST____
    extern void ogg_delegate(void);
    extern int ogg_exit_status(void);
# else
    void ogg_delegate(void)
#  ifdef OGG_DELEGATE
    ;
#  else
    {}
#  endif
    int ogg_exit_status(void)
#  ifdef OGG_EXIT_STATUS
    ;
#  else
    { return 0; }
#  endif
# endif

    int main(int argc, char *argv[]);
# endif

#endif //OGG_GRAPHIC_STARUP__HEADER_FILE____