# ifndef DESIGN_TIME
    
# include "ogg.h"

    extern ogg_application* application;

    void ogg_init_application_forms();

    void ogg_init_application(ogg_application* this)
    {
        glutInit(this->argc, this->argv);
        glutInitDisplayMode(this->display_mode);
    }

    void ogg_terminate_application(ogg_application* this)
    {
        ogg_destroy(this);
        exit(0);
    }

    void ogg_run_application(ogg_application* this)
    {
        //current_component = ogg_active_form();
        glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
        glutMainLoop();
    }

    void ogg_terminate()
    {
        ogg_terminate_application(application);
    }

    int main(int argc, char *argv[])
    {
        ogg_create(ogg_application)(
            .ogg_component = {
                .parent = 0,
                .anchor = {
                    .type = ogg_anchor_pec,
                    .pec = {
                        .top_left = { 0, 0 },
                        .bottom_right = { 100, 100 }
                    }
                }
            },
            .argc = &argc,
            .argv = argv,
            .display_mode = GLUT_RGB | GLUT_SINGLE,
        )(application);
        ogg_init_application(application);
        ogg_init_application_forms();
        ogg_run_application(application);
    }
# endif