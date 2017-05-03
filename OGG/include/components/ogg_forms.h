#ifndef OGG_GRAPHIC_STARUP__HEADER_FILE____
#define OGG_GRAPHIC_STARUP__HEADER_FILE____
#include "components/ogg_components.h"

    typedef unsigned int ogg_display_mode;

    typedef void(*glut_callback)();
    typedef void(__stdcall *glut_register)(glut_callback);

    typedef struct {
        int left, top;
        int width, height;
    } ogg_form_position;

    typedef struct {
        ogg_form_position position;
        const char *title;
        ogg_color color;
    } form_info;

    def_startup(ogg_form)(
        form_info info;
    );

    typedef unsigned short ogg_form_id;
    def_component(ogg_form)(
        ogg_form_id form_id;
        ogg_form_position position;
        const char *title;
        ogg_color color;
    );

    def_startup(ogg_application)(
        int *argc;
        char **argv;
        ogg_display_mode display_mode;
    );

    def_component(ogg_application)(
        int *argc;
        char **argv;
        ogg_display_mode display_mode;
        ogg_form **forms_lookup;
        ogg_bool is_top_level;
        ogg_com_ptr current_component;
        ogg_com_ptr focused_component;
        int mouse_state;
        ogg_bool is_dragging;
    );

    //void ogg_init_application(ogg_application* self);

    //void ogg_terminate_application(ogg_application* self);

    //void ogg_run_application(ogg_application* self);

    //void ogg_terminate();

    ogg_form* ogg_create_form(form_info info);

    ogg_form* ogg_get_active_form();

    ogg_com_ptr get_current_component();

    void set_application(ogg_com_ptr app);

    void ogg_init_application(ogg_application* self);

    void ogg_terminate_application(ogg_application* self);

    void ogg_run_application(ogg_application* self);

    void ogg_terminate();

#endif //OGG_GRAPHIC_STARUP__HEADER_FILE____
