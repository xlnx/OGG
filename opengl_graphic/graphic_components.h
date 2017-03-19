#ifndef OGG_GRAPHIC_COMPONENTS__HEADER_FILE_____
#define OGG_GRAPHIC_COMPONENTS__HEADER_FILE_____
//#include "geometry.h"
#include "graphic_utils.h"
#include "graphic_events.h"

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

    static const ogg_anchor ogg_full_anchor = {
        .type = ogg_anchor_pec,
        .pec = {
            .top = 0,
            .bottom = 100,
            .left = 0,
            .right = 100
        }
    };

    typedef void *ogg_com_ptr;

    struct ogg_component_ty;
    typedef struct {
        ogg_anchor anchor;
        struct ogg_component_ty* parent;
    } ogg_com_startup;

    struct ogg_subcomponent_ty;
    typedef struct ogg_subcomponent_ty {
        struct ogg_component_ty* object;
        struct ogg_subcomponent_ty* next;
    } ogg_subcomponent;

    typedef void (*ogg_event_handler)();
    typedef struct ogg_component_ty {
        ogg_event_handler* vptr;
        struct ogg_component_ty* parent;
        ogg_subcomponent* sub, * subrear;
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

    typedef unsigned ogg_handle_flag;
#  define OGG_HANDLED     (1)
#  define OGG_UNHANDLED   (0)
    
    /* create a component, every component must call this function when created */
    void create_component(ogg_com_ptr com_ptr, const ogg_component_info* cominfo);

    /* get the absolute coord of a coord in canvas */
    coordf get_real_coord(ogg_com_ptr com_ptr, coordf pix);

    /* get the absolute anchor of a component in canvas */
    void get_component_real_anchor(ogg_com_ptr com_ptr, ogg_anchor* anchor);

    /* set the anchor of a component */
    void set_component_anchor(ogg_com_ptr com_ptr, const ogg_anchor* anchor);

    /* event handler */
    /* send event to a component with given args ... */
    void ogg_send_event(ogg_com_ptr com_ptr, event event_name, ...);

    /* destroy any component */
    void ogg_destroy(ogg_com_ptr com_ptr);

    /* create full anchor startup in a parent component */
    ogg_com_startup make_startup(ogg_com_ptr parent);

    /* make a int-int coord */
    ogg_coord coord(int x, int y);

#endif //OGG_GRAPHIC_COMPONENTS__HEADER_FILE_____