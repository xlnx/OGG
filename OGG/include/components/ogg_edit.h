#ifndef OGG_GRAPHIC_COMPONENT__EDIT__HEADER_FILE____
#define OGG_GRAPHIC_COMPONENT__EDIT__HEADER_FILE____
#include "ogg_shape.h"
    
#  define OGG_BUFFER_SIZE (512)
    typedef struct {
        char content[OGG_BUFFER_SIZE];
        ogg_color color;
    } ogg_buffered_text;
    
    def_startup_inh(ogg_edit, ogg_rect)(
        ogg_color color;
    );

    def_component_inh(ogg_edit, ogg_rect)(
        ogg_buffered_text text;
    );

    char* ogg_edit_get_text(ogg_edit* edit);

#endif //OGG_GRAPHIC_COMPONENT__EDIT__HEADER_FILE____
