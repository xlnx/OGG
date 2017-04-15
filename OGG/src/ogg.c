#ifndef DESIGN_TIME
# include "ogg.h"

    extern ogg_application* application;

    extern void ogg_init_application_forms();

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
#endif