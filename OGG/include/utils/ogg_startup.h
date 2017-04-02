#ifndef OGG_GRAPHIC_STARUP__HEADER_FILE____
#define OGG_GRAPHIC_STARUP__HEADER_FILE____
#include "components/ogg_components.h"

# ifdef WIN32
#  ifndef OGG_SHOW_CONSOLE
#   pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#  endif
# endif

# ifndef OGG_CUSTOM_STARTUP
    typedef unsigned int ogg_display_mode;

    typedef void(*glut_callback)();
    typedef void(_stdcall *glut_register)(glut_callback);

    typedef struct {
        int left, top;
        int width, height;
    } ogg_form_position;

    typedef struct {
        ogg_form_position position;
        const char *title;
    } form_info;

    def_startup(ogg_form)(
        form_info info;
    );

    typedef unsigned short ogg_form_id;
    def_component(ogg_form)(
        ogg_form_id form_id;
        ogg_form_position position;
        const char *title;
    );

    ogg_form* ogg_create_form(form_info info);

    //void ogg_destroy_form(ogg_form* this);
    
    ogg_form* ogg_get_active_form();

    void ogg_terminate();

    ogg_com_ptr get_current_component();

    extern void ogg_init_application_forms();

# ifdef OGG_GRAPHIC_STARTUP__INST____
    extern int ogg_exit_status(void);
# else
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