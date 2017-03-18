#ifndef OGG_GRAPHIC_UTILS__HEADER_FILE______
#define OGG_GRAPHIC_UTILS__HEADER_FILE______
#include "gl/glut.h"
#include "geometry.h"

# ifdef WIN32
#  ifndef OGG_SHOW_CONSOLE
#   pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#  endif
# endif

# ifdef __cplusplus
extern "C" {
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
    } ogg_window;

    typedef struct {
        int argc;
        char **argv;
        ogg_display_mode display_mode;
        ogg_window window;
    } ogg_startup_info;

    void ogg_startup(ogg_startup_info*);
    void ogg_delegate(void);
    int ogg_exit_status(void);
    int main(int argc, char *argv[]);

    void ogg_clear_screen(void);

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
# endif

# ifdef __cplusplus
}
# endif

#endif //OGG_GRAPHIC_UTILS__HEADER_FILE______