#ifndef OGG_GRAPHIC_COMPONENTS__HEADER_FILE_____
#define OGG_GRAPHIC_COMPONENTS__HEADER_FILE_____
//#include "geometry.h"
#include "utils/ogg_utils.h"
#include "events/ogg_events.h"

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
/*
 * enum ogg_anchor_type
 * deternines the alignment type of a particular component.
 * ----------------------------------------------------------------
 * value:
 *   $ ogg_anchor_pec:     align by percentage of parent component, 
 *                         automatically resize when parent component
 *                         resizes and keep the percentage.
 *   $ ogg_anchor_coord:   align by pixel and will keep size.
 */

    typedef enum {
        ogg_anchor_pec,
        ogg_anchor_coord
    } ogg_anchor_type;

/*
 * struct ogg_anchor
 * self struct determines how and where the owner component is aligned.
 * ----------------------------------------------------------------
 * member:
 *   @ type:   ogg_anchor_type { ln 32 }
 *                         component alignment type, valued among { ogg_anchor_pec, ogg_anchor_coord }
 *   @ pec:    ogg_pec_anchor { ln 17 }
 *                         determine the percentage of owner component (relative to parent component), 
 *                         only valid when (type == ogg_anchor_pec).
 *   @ coord:  ogg_coord_anchor { ln 18 }
 *                         determine the pixel location of owner component (relative to parent component),
 *                         only valid when (type == ogg_coord_pec).
 */

    typedef struct {
        ogg_anchor_type type;
        union {
            ogg_pec_anchor pec;
            ogg_coord_anchor coord;
        };
    } ogg_anchor;

/*
 * const ogg_full_anchor
 * make owner component fill parent component(by pec) { ln 46 }.
 */

    //static const ogg_anchor ogg_full_anchor = {
    //    .type = ogg_anchor_pec,
    //    .pec = {
    //        .top = 0,
    //        .bottom = 100,
    //        .left = 0,
    //        .right = 100
    //    }
    //};

/*
 * typename ogg_com_ptr = void *
 * use self type to create a generic pointer to ogg_component
 */
    typedef void *ogg_com_ptr;

    struct ogg_component_ty;

    struct ogg_subcomponent_ty;
    typedef struct ogg_subcomponent_ty {
        struct ogg_component_ty* object;
        struct ogg_subcomponent_ty* next;
    } ogg_subcomponent;
    
    typedef void (*ogg_event_handler)();
    
/*
 * struct ogg_component
 * base of all ogg components.
 * ----------------------------------------------------------------
 * member:
 *   @ vptr          ogg_event_handler { ln 87 }
 *   @ parent        ogg_component*
 *   sub_component_list {  hold the list of all the sub component of self component
 *     @ sub           ogg_subcomponent*
 *     @ subrear       ogg_subcomponent*
 *   }
 *   anchor {              deternmine the anchor of self component
 *     @ anchor_type   ogg_anchor_type
 *     @ pec           ogg_pec_anchor
 *     @ coord         ogg_coord_anchor
 *   }
 */
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

/*
 * struct ogg_component_info
 * basic startup for every ogg component(inherited).
 * every component have to fill in self component info when it is created.
 * ----------------------------------------------------------------
 * member:
 *   @ parent          ogg_component* { ln 106 }
 *   @ anchor          ogg_anchor { ln 50 }
 */
    typedef struct {
        ogg_component* parent;
        ogg_anchor anchor;
    } ogg_component_info;

/*
 * typename ogg_handle_flag = unsigned
 * self type is related with the ogg event handle module.
 * value:
 *   $ OGG_HANDLED     self event has been handled.
 *   $ OGG_UNHANDLED   self event hasn't been handled yet.
 */
    typedef unsigned ogg_handle_flag;
#  define OGG_HANDLED     (1)
#  define OGG_UNHANDLED   (0)

    typedef coordf ogg_pec;
    /* coord utils */
    /* create percentage by two float params x, y */
    ogg_pec ogg_make_pec(float x, float y);
	
    /* convert absolute coord position to pec position */
    ogg_pec coord2pec(ogg_coord p);
    /* convert absolute pec position to coord position */
    ogg_coord pec2coord(ogg_pec p);

    /* pec + pec */
    ogg_pec pec_add_pec(ogg_pec a, ogg_pec b);
    /* pec - pec */
    ogg_pec pec_sub_pec(ogg_pec a, ogg_pec b);
    /* pec + coord => pec */
    ogg_pec pec_add_coord(ogg_pec a, ogg_coord b);
    /* pec - coord => pec */
    ogg_pec pec_sub_coord(ogg_pec a, ogg_coord b);

    /* get the absolute coord of a pec coord in canvas */
    ogg_pec get_real_pec(ogg_com_ptr com_ptr, ogg_pec pix);

    /* get the real coord anchor of component */
    void get_component_real_coord_anchor(ogg_com_ptr com_ptr, ogg_anchor* anchor);

    /* get the absolute anchor of a component in canvas */
    void get_component_real_anchor(ogg_com_ptr com_ptr, ogg_anchor* anchor);

    /* get the absolute pec anchor of a component in canvas */
    void get_component_real_pec_anchor(ogg_com_ptr com_ptr, ogg_anchor* anchor);

    /* set the anchor of a component */
    void set_component_anchor(ogg_com_ptr com_ptr, const ogg_anchor* anchor);

    /* event handler */
    /* send event to a component with given args ... */
    void ogg_send_event(ogg_com_ptr com_ptr, event event_name, ...);

    /* destroy any component */
    void ogg_destroy(ogg_com_ptr com_ptr);

    /* create full anchor startup in a parent component */
    //ogg_component_info ogg_default_info_ogg_component___(ogg_com_ptr parent);

    /* make a int-int coord */
    ogg_coord coord(int x, int y);

#  ifdef DESIGN_TIME
    /* draw the border anchor of component */
    void draw_design_anchor(ogg_com_ptr self);
#  endif

#  define OGG_EXPAND_ARGS_DBL_BRAK(...)                                 \
        __VA_ARGS__                                                     \
    })

#  define OGG_EXPAND_ARGS_WITH_BRAK(...)                                \
        __VA_ARGS__                                                     \
    }
/*
 * macro def_startup_inh(T, super_class)
 * define a component startup information type of class T, inherited from super_class.
 * ----------------------------------------------------------------
 * usage:
 *    def_startup_inh(ogg_button, ogg_rect) (
 *      ogg_color focused_color;
 *      ogg_color down_color;
 *      ogg_text text;
 *      button_callback callback;
 *    );
 *    // get the startup info of type ogg_button.
 */
#  define def_startup_inh(T, super_class)                               \
    struct OGG_COMPONENT_STARTUP_##T##_info;                            \
    typedef struct OGG_COMPONENT_STARTUP_##T##_info T##_info;           \
                                                                        \
    /*T##_info ogg_default_info_##T##___(ogg_com_ptr);*/                    \
    /*extern super_class##_info ogg_default_info_##super_class##___(*/      \
        /*ogg_com_ptr);*/                                                   \
                                                                        \
    /*static super_class##_info (*const parent_default_info_##T##__)(*/     \
            /*ogg_com_ptr) = ogg_default_info_##super_class##___;*/         \
                                                                        \
    struct OGG_COMPONENT_STARTUP_##T##_info {                           \
        super_class##_info super_class;                                 \
        OGG_EXPAND_ARGS_WITH_BRAK

#  define OGG_DEFAULT_ARGS_EXPAND_ARGS(...)                             \
            __VA_ARGS__                                                 \
        };                                                              \
        return info;                                                    \
    }

/*
 * macro default_startup_inh(T, super_class)
 * define the default startup information of class T, inherited from super_class.
 * make sure it appears in source code, not header file.
 * ----------------------------------------------------------------
 * usage:
 *   default_startup_inh(ogg_button, ogg_rect)(
 *     .focused_color = OGG_GREEN,
 *     .down_color = OGG_RED,
 *     .text = {
 *       .content = "Button",
 *       .color = OGG_RED
 *     },
 *     .callback = 0
 *   )
 *   // get the default startup info of type ogg_button.
 */
//#  define default_startup_inh(T, super_class)                           \
//    T##_info ogg_default_info_##T##___(ogg_com_ptr parent)              \
//    {                                                                   \
//        T##_info info = {                                               \
//            .super_class = parent_default_info_##T##__(parent),         \
//            OGG_DEFAULT_ARGS_EXPAND_ARGS

/*
 * macro def_startup(T, super_class)
 * define a component startup information type of class T, inherited from super_class. { ln 209 }
 */
#  define def_startup(component_type)                                   \
    def_startup_inh(component_type, ogg_component)

/*
 * macro default_startup(T)
 * define a component startup information type of class T, inherited from ogg_component. { ln 231 }
 */
//#  define default_startup(component_type)                               \
//    default_startup_inh(component_type, ogg_component)
    
/* default info generate function */
//#  define ogg_default(T)                                                \
//    ogg_default_info_##T##___

/*
 * macro def_component_inh(T, super_class)
 * define a component type T, inherited from super_class.
 * ----------------------------------------------------------------
 * usage:
 *   def_component_inh(ogg_button, ogg_rect)(
 *     ogg_color default_color;
 *     ogg_color focused_color;
 *     ogg_color down_color;
 *     ogg_text text;
 *     button_callback callback;
 *   );
 *   // created component type ogg_button, inherited from ogg_rect.
 */
#  define def_component_inh(T, super_class)                             \
    struct OGG_COMPONENT_HELPER_##T;                                    \
    typedef struct OGG_COMPONENT_HELPER_##T T;                          \
                                                                        \
    T* ogg_constructor_##T##___(const T##_info* args);                  \
                                                                        \
    void ogg_static_constructor_##T##___(T*, const void*);              \
                                                                        \
    extern void ogg_static_constructor_##super_class##___(              \
        super_class*, const void*);                                     \
                                                                        \
    static void (*const parent_static_constructor_##T##__)(             \
            super_class*, const void*) =                                \
        ogg_static_constructor_##super_class##___;                      \
                                                                        \
    void ogg_destructor_##T##___(T* self);                              \
                                                                        \
    extern void ogg_destructor_##super_class##___(super_class* self);   \
                                                                        \
    static void (*const parent_destructor_##T##__)(super_class*) =      \
        ogg_destructor_##super_class##___;                              \
                                                                        \
    extern ogg_event_handler super_class##_vtable[];                    \
    static ogg_event_handler const* const T##_parent_vtable =           \
        super_class##_vtable;                                           \
                                                                        \
    struct OGG_COMPONENT_HELPER_##T {                                   \
        super_class super;                                              \
        OGG_EXPAND_ARGS_WITH_BRAK

/*
 * macro def_component(T)
 * define a component type T, inherited from ogg_component. { ln 286 }
 */
#  define def_component(component_type)                                 \
    def_component_inh(component_type, ogg_component)

/*
 * macro def_vtable(T)
 * define the vtable of component T, indicating handler of each event.
 * ----------------------------------------------------------------
 * usage:
 *   def_vtable(ogg_button) (
 *     [OGG_PAINT_EVENT] = ogg_handler(ogg_button, OGG_PAINT_EVENT),
 *     [OGG_MOUSE_EVENT] = ogg_handler(ogg_button, OGG_MOUSE_EVENT),
 *     [OGG_MOUSE_ENTER_EVENT] = ogg_handler(ogg_button, OGG_MOUSE_ENTER_EVENT),
 *     [OGG_MOUSE_LEAVE_EVENT] = ogg_handler(ogg_button, OGG_MOUSE_LEAVE_EVENT),
 *     [OGG_MOUSE_DOWN_EVENT] = ogg_handler(ogg_button, OGG_MOUSE_DOWN_EVENT),
 *     [OGG_MOUSE_UP_EVENT] = ogg_handler(ogg_button, OGG_MOUSE_UP_EVENT)
 *   );
 *   // now button can handle events as the table says.
 */
# ifdef DESIGN_TIME
#  define def_vtable(component_type)                                    \
    /*static */ogg_event_handler component_type##_vtable[OGG_EVENT_COUNT];  \
    static void ogg_design_time_painter_##component_type##_(            \
        component_type* self, va_list args, ogg_handle_flag* handled)   \
    {                                                                   \
        if (component_type##_vtable[OGG_PAINT_EVENT] != 0) {            \
            component_type##_vtable[OGG_PAINT_EVENT](                   \
                    self, args, handled);                               \
        }                                                               \
        ogg_com_ptr get_current_component();                            \
        if (self == get_current_component())                            \
            draw_design_anchor(self);                                   \
        *handled = ogg_false;                                           \
    }                                                                   \
    /*static */ogg_event_handler ogg_design_time_##component_type##_vtable  \
            [OGG_EVENT_COUNT] = {                                       \
        [OGG_DESTROY_EVENT] = ogg_destructor(component_type),           \
        [OGG_PAINT_EVENT] = ogg_design_time_painter_##component_type##_,\
    };                                                                  \
    /*static */ogg_event_handler component_type##_vtable[OGG_EVENT_COUNT]= {\
        [OGG_DESTROY_EVENT] = ogg_destructor(component_type),           \
        OGG_EXPAND_ARGS_WITH_BRAK
# else
#  define def_vtable(component_type)                                    \
    /*static */ogg_event_handler component_type##_vtable[OGG_EVENT_COUNT]= {\
        [OGG_DESTROY_EVENT] = ogg_destructor(component_type),           \
        OGG_EXPAND_ARGS_WITH_BRAK
# endif

#  define using_handler(T, event_name)                                  \
    [event_name] = T##_##event_name##___handler__

#  define ogg_startup(T)                                                \
    T##_info

#  define OGG_CREATOR_RAW__HELPER_DEF(st)                               \
        object__constructor__(&st);                                     \
    } while (0)

#  define ogg_create_def_raw(T)                                         \
	do {                                                                \
        static T* (*object__constructor__)(const T##_info*) =           \
            ogg_constructor_##T##___;                                   \
        OGG_CREATOR_RAW__HELPER_DEF

#  define OGG_CREATOR_RAW__FINISH(object)                               \
        object = object__constructor__(object__startup_info__);         \
    } while (0)

#  define OGG_CREATOR_RAW__HELPER(st)                                   \
        const ogg_startup(T)* object__startup_info__ = &st;             \
        OGG_CREATOR_RAW__FINISH

#  define ogg_create_raw(T)                                             \
	do {                                                                \
        static T* (*object__constructor__)(const T##_info*) =           \
            ogg_constructor_##T##___;                                   \
        OGG_CREATOR_RAW__HELPER


#  define OGG_CREATOR__HELPER_DEF(...)                                  \
            __VA_ARGS__                                                 \
        };                                                              \
        object__constructor__(&object__startup_info__);                 \
    } while (0)

/*
 * macro_function ogg_create_def(T)(startup_args)
 * create a T type component using startup args and discard the component ptr.
 */
#  define ogg_create_def(T)                                             \
	do {                                                                \
        static T* (*object__constructor__)(const T##_info*) =           \
            ogg_constructor_##T##___;                                   \
        const ogg_startup(T) object__startup_info__ = {                 \
            OGG_CREATOR__HELPER_DEF

#  define OGG_CREATOR__FINISH(object)                                   \
        object = object__constructor__(&object__startup_info__);        \
    } while (0)

#  define OGG_CREATOR__HELPER(...)                                      \
            __VA_ARGS__                                                 \
        };                                                              \
        OGG_CREATOR__FINISH

/*
 * macro_function ogg_create(T)(startup_args)(component_ptr)
 * create a T type component using startup args and assign it to component_ptr.
 */
#  define ogg_create(T)                                                 \
	do {                                                                \
        static T* (*object__constructor__)(const T##_info*) =           \
            ogg_constructor_##T##___;                                   \
        const ogg_startup(T) object__startup_info__ = {                 \
            OGG_CREATOR__HELPER

/*
 * macro_function def_constructor(T, args_name)
 * define the constructor of component type T. args_name indicates the name of 
 * the input T type startup ptr.
 * ----------------------------------------------------------------
 * usage:
 *   def_constructor(ogg_button, args)
 *   {
 *     self->down_color = args->down_color;
 *     self->focused_color = args->focused_color;
 *     self->default_color = ((ogg_shape*)self)->color;
 *     self->text = args->text;
 *     self->callback = args->callback;
 *   }
 *   // define the constructor of ogg_button type. self macro function will
 *   // automatically call the constructor of super_class before it is called.
 *   // and will automatically alloc memory for the created component.
 */
#  ifdef DEBUG
#    ifndef DESIGN_TIME
#      define def_constructor(T, ...)                                   \
    ogg_bool allow_create_sub_##T(ogg_com_ptr parent)                   \
    {                                                                   \
        return (__VA_ARGS__);                                           \
    }                                                                   \
    T* ogg_constructor_##T##___(const T##_info* args)                   \
    {                                                                   \
        if (allow_create_sub_##T(parent)) {                             \
            ogg_bool accept = ogg_true;                                 \
            if (parent != 0 && parent->vptr[OGG_CAN_ADD_CHILD]) {       \
                ogg_send_event(parent, OGG_CAN_ADD_CHILD,               \
                    T##_vtable, &accept);                               \
            }                                                           \
            if (accept) {                                               \
                T* object = (T*)malloc(sizeof(T));                              \
                alloc_memory++;                                                 \
                void ogg_static_constructor_##T##___(T*, const void*);          \
                ogg_static_constructor_##T##___(object, args);                  \
                ((ogg_component*)object)->vptr = T##_vtable;                    \
                if (((ogg_component_info*)args)->parent) {                      \
                    ogg_send_event(((ogg_component_info*)args)->parent,         \
                        OGG_CREATE_SUB_COMPONENT_EVENT, object);                \
                }                                                               \
                return object;                                                  \
            }                                                           \
        }                                                               \
        return 0;                                                       \
    }                                                                   \
    void ogg_static_constructor_##T##___(T* object, const void* args)   \
    {                                                                   \
        void create_##T(T* self, const T##_info* args);                 \
        parent_static_constructor_##T##__((void*)object, args);         \
        create_##T(object, (const T##_info*)args);                      \
    }                                                                   \
    void create_##T(T* self, const T##_info* args)
#    else
#      define def_constructor(T, ...)                                   \
    ogg_bool allow_create_sub_##T(ogg_com_ptr parent)                   \
    {                                                                   \
        return (__VA_ARGS__);                                           \
    }                                                                   \
    T* ogg_constructor_##T##___(const T##_info* args)                   \
    {                                                                   \
        ogg_component* parent = ((ogg_component_info*)args)->parent;    \
        if (allow_create_sub_##T(parent)) {                             \
            ogg_bool accept = ogg_true;                                 \
            if (parent != 0 && parent->vptr[OGG_CAN_ADD_CHILD]) {       \
                ogg_send_event(parent, OGG_CAN_ADD_CHILD,               \
                    T##_vtable, &accept);                               \
            }                                                           \
            if (accept) {                                               \
                T* object = (T*)malloc(sizeof(T));                              \
                alloc_memory++;                                                 \
                void ogg_static_constructor_##T##___(T*, const void*);          \
                ogg_static_constructor_##T##___(object, args);                  \
                ((ogg_component*)object)->vptr = ogg_design_time_##T##_vtable;  \
                if (((ogg_component_info*)args)->parent) {                      \
                    ogg_send_event(((ogg_component_info*)args)->parent,         \
                        OGG_CREATE_SUB_COMPONENT_EVENT, object);                \
                }                                                               \
                return object;                                                  \
            }                                                           \
        }                                                               \
        return 0;                                                       \
    }                                                                   \
    void ogg_static_constructor_##T##___(T* object, const void* args)   \
    {                                                                   \
        void create_##T(T* self, const T##_info* args);                 \
        parent_static_constructor_##T##__((void*)object, args);         \
        create_##T(object, (const T##_info*)args);                      \
    }                                                                   \
    void create_##T(T* self, const T##_info* args)
#    endif
#  else
#    ifndef DESIGN_TIME
#      define def_constructor(T, ...)                                   \
    ogg_bool allow_create_sub_##T(ogg_com_ptr parent)                   \
    {                                                                   \
        return (__VA_ARGS__);                                           \
    }                                                                   \
    T* ogg_constructor_##T##___(const T##_info* args)                   \
    {                                                                   \
        ogg_component* parent = ((ogg_component_info*)args)->parent;    \
        if (allow_create_sub_##T(parent)) {                             \
            ogg_bool accept = ogg_true;                                 \
            if (parent != 0 && parent->vptr[OGG_CAN_ADD_CHILD]) {       \
                ogg_send_event(parent, OGG_CAN_ADD_CHILD,               \
                    T##_vtable, &accept);                               \
            }                                                           \
            if (accept) {                                               \
                T* object = (T*)malloc(sizeof(T));                          \
                void ogg_static_constructor_##T##___(T*, const void*);      \
                ogg_static_constructor_##T##___(object, args);              \
                ((ogg_component*)object)->vptr = T##_vtable;                \
                if (parent) {                                               \
                    ogg_send_event(parent,                                  \
                        OGG_CREATE_SUB_COMPONENT_EVENT, object);            \
                }                                                           \
                return object;                                              \
            }                                                           \
        }                                                               \
        return 0;                                                       \
    }                                                                   \
    void ogg_static_constructor_##T##___(T* object, const void* args)   \
    {                                                                   \
        void create_##T(T* self, const T##_info* args);                 \
        parent_static_constructor_##T##__((void*)object, args);         \
        create_##T(object, (const T##_info*)args);                      \
    }                                                                   \
    void create_##T(T* self, const T##_info* args)
#    else
#      define def_constructor(T, ...)                                   \
    ogg_bool allow_create_sub_##T(ogg_com_ptr parent)                   \
    {                                                                   \
        return (__VA_ARGS__);                                           \
    }                                                                   \
    T* ogg_constructor_##T##___(const T##_info* args)                   \
    {                                                                   \
        ogg_component* parent = ((ogg_component_info*)args)->parent;    \
        if (allow_create_sub_##T(parent)) {                             \
            ogg_bool accept = ogg_true;                                 \
            if (parent != 0 && parent->vptr[OGG_CAN_ADD_CHILD]) {       \
                ogg_send_event(parent, OGG_CAN_ADD_CHILD,               \
                    T##_vtable, &accept);                               \
            }                                                           \
            if (accept) {                                               \
                T* object = (T*)malloc(sizeof(T));                              \
                void ogg_static_constructor_##T##___(T*, const void*);          \
                ogg_static_constructor_##T##___(object, args);                  \
                ((ogg_component*)object)->vptr = ogg_design_time_##T##_vtable;  \
                if (((ogg_component_info*)args)->parent) {                      \
                    ogg_send_event(((ogg_component_info*)args)->parent,         \
                        OGG_CREATE_SUB_COMPONENT_EVENT, object);                \
                }                                                               \
                return object;                                                  \
            }                                                           \
        }                                                               \
        return 0;                                                       \
    }                                                                   \
    void ogg_static_constructor_##T##___(T* object, const void* args)   \
    {                                                                   \
        void create_##T(T* self, const T##_info* args);                 \
        parent_static_constructor_##T##__((void*)object, args);         \
        create_##T(object, (const T##_info*)args);                      \
    }                                                                   \
    void create_##T(T* self, const T##_info* args)
#    endif
#  endif

#  define ogg_destructor(T)                                             \
    ogg_destructor_##T##___

/*
 * macro_function def_destructor(T)
 * define the destructor of component type T.
 * ----------------------------------------------------------------
 * usage:
 *   def_destructor(ogg_button)
 *   {   // do nothing
 *   }
 *   // self macro function will automatically call the destructor after it is called.
 *   // deallocate of those memories are automatic.
 */
#  define def_destructor(T)                                             \
    void ogg_destructor_##T##___(T* self)                               \
    {                                                                   \
        void ogg_destructor_##T##_helper__(T*);                         \
        ogg_destructor_##T##_helper__(self);                            \
        parent_destructor_##T##__((ogg_com_ptr)self);                   \
    }                                                                   \
    void ogg_destructor_##T##_helper__(T* self)


#endif //OGG_GRAPHIC_COMPONENTS__HEADER_FILE_____
