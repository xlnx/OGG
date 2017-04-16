#ifndef OGG_PAGE_CONTROL__HAEDER_FILE___
#define OGG_PAGE_CONTROL__HAEDER_FILE___

# include "ogg_shape.h"
    
    def_startup_inh(ogg_page_control, ogg_rect)(
        
    );

    def_component_inh(ogg_page_control, ogg_rect)(
        int page_count;
        int est_page_size;
        int active_page;
        ogg_com_ptr* sub_pages;
    );

    def_startup_inh(ogg_tab_page, ogg_rect)(
        const char* title;
    );

    def_component_inh(ogg_tab_page, ogg_rect)(
        const char* title;
    );

#endif
