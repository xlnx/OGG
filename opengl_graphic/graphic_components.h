#ifndef OGG_GRAPHIC_COMPONENTS__HEADER_FILE_____
#define OGG_GRAPHIC_COMPONENTS__HEADER_FILE_____
//#include "geometry.h"
#include "graphic_utils.h"

# ifdef __cplusplus
extern "C"{
# endif

# ifndef REG__GEOMETRY_SYSTEM__FLOAT__F___
#  define REG__GEOMETRY_SYSTEM__FLOAT__F___
    register_geometry_system(float, f);
# endif
# ifndef REG__GEOMETRY_SYSTEM__INT__I___
#  define REG__GEOMETRY_SYSTEM__INT__I___
    register_geometry_system(int, i)
# endif

    typedef coordi ogg_coord;
    typedef rectf ogg_pec_anchor;
    typedef recti ogg_coord_anchor;

    typedef enum {
        ogg_anchor_pec,
        ogg_anchor_coord
    } ogg_anchor_type;

    typedef struct {
        ogg_anchor_type type;
        union {
            ogg_pec_anchor pec;
            ogg_coord_anchor coord;
        };
    } ogg_anchor;

    typedef void *ogg_com_ptr;
    typedef void (*ogg_dtor)(ogg_com_ptr);
    typedef void(*ogg_paint)(ogg_com_ptr);

    struct ogg_component_ty;

    typedef struct {
        ogg_anchor anchor;
        struct ogg_component_ty* parent;
    } ogg_com_startup;

    typedef void (*ogg_event_handler)();
    typedef struct ogg_component_ty {
        ogg_event_handler* vptr;
        struct ogg_component_ty* parent;
        ogg_anchor_type anchor_type;
        union {
            ogg_pec_anchor pec;
            ogg_coord_anchor coord;
        };
    } ogg_component;

    typedef struct {
        ogg_component* parent;
        const ogg_anchor* anchor;
        ogg_event_handler* vptr;
    } ogg_component_info;

#define OGG_DESTROY_EVENT  (0)
#define OGG_PAINT_EVENT    (1)
    
    void create_component(ogg_com_ptr com_ptr, const ogg_component_info* cominfo);

    coordf get_real_coord(ogg_com_ptr com_ptr, coordf pix);

    void get_component_real_anchor(ogg_com_ptr com_ptr, ogg_anchor* anchor);

    void set_component_anchor(ogg_com_ptr com_ptr, const ogg_anchor* anchor);

    void ogg_send_event(ogg_com_ptr com_ptr, unsigned event_name);

    void destroy_component(ogg_com_ptr* com_ptr);

    ogg_coord coord(int x, int y);

    static const ogg_anchor ogg_full_anchor = {
        .type = ogg_anchor_pec,
        .pec = {
            .top = 0,
            .bottom = 100,
            .left = 0,
            .right = 100
        }
    };
    static const ogg_com_startup ogg_global_startup = {
        .anchor = {
            .type = ogg_anchor_pec,
            .pec = {
                .top = 0,
                .bottom = 100,
                .left = 0,
                .right = 100
            }
        },
        .parent = 0
    };

    ogg_com_startup ogg_make_startup(ogg_com_ptr parent);

# ifdef __cplusplus
}
# endif

#endif //OGG_GRAPHIC_COMPONENTS__HEADER_FILE_____