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
        ogg_anchor anchor;
    } ogg_component_info;

    static const void (*parent_static_constructor_ogg_component__)() = 0;

    typedef unsigned ogg_handle_flag;
#  define OGG_HANDLED     (1)
#  define OGG_UNHANDLED   (0)

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
    ogg_component_info make_startup(ogg_com_ptr parent);

    /* make a int-int coord */
    ogg_coord coord(int x, int y);

#  define OGG_COMPONENT_STARTUP_HELPER(...)                             \
        __VA_ARGS__                                                     \
    }

#  define def_startup_inh(component_type, super_class)                  \
    struct OGG_COMPONENT_STARTUP_##component_type##_info;               \
    typedef struct OGG_COMPONENT_STARTUP_##component_type##_info        \
        component_type##_info;                                          \
    struct OGG_COMPONENT_STARTUP_##component_type##_info {              \
        super_class##_info super;                                       \
        OGG_COMPONENT_STARTUP_HELPER

#  define def_startup(component_type)                                   \
    def_startup_inh(component_type, ogg_component)

#  define OGG_COMPONENT_INH_INST(...)                                   \
        __VA_ARGS__                                                     \
    }

#  define def_component_inh(T, super_class)                             \
    struct OGG_COMPONENT_HELPER_##T;                                    \
    typedef struct OGG_COMPONENT_HELPER_##T T;                          \
    void ogg_static_constructor_##T##___(T*, const void*);              \
    extern void ogg_static_constructor_##super_class##___(              \
        super_class*, const void*);                                     \
    static const void (*parent_static_constructor_##T##__)(             \
            super_class*, const super_class##_info*) =                  \
        ogg_static_constructor_##super_class##___;                      \
    struct OGG_COMPONENT_HELPER_##T {                                   \
        super_class super;                                              \
        OGG_COMPONENT_INH_INST

#  define def_component(component_type)                                 \
    def_component_inh(component_type, ogg_component)

#  define OGG_COMPONENT_VTABLE_INST(...)                                \
        __VA_ARGS__                                                     \
    }

#  define def_vtable(component_type)                                    \
    static ogg_event_handler component_type##_vtable[OGG_EVENT_COUNT]= {\
        OGG_COMPONENT_VTABLE_INST

#  define ogg_create(T)                                                 \
	ogg_constructor_##T##___

#  define ogg_startup(T)                                                \
    T##_info

#  define constructor(T)                                                \
    T* ogg_constructor_##T##___(const T##_info* args)

#  ifdef DEBUG
#    define def_constructor(T, args_name)                               \
    T* ogg_constructor_##T##___(const T##_info* args_name)              \
    {                                                                   \
        T* object = (T*)malloc(sizeof(T));                              \
        alloc_memory++;                                                 \
        void ogg_static_constructor_##T##___(T*, const void*);          \
        ogg_static_constructor_##T##___(object, args_name);             \
        ((ogg_component*)object)->vptr = T##_vtable;                    \
        return object;                                                  \
    }                                                                   \
    void ogg_static_constructor_##T##___(T* object, const void* args)   \
    {                                                                   \
        void create_##T(T* this, const T##_info* args_name);            \
        if (parent_static_constructor_##T##__ != 0)                     \
            parent_static_constructor_##T##__((void*)object, args);     \
        create_##T(object, (const T##_info*)args);                      \
    }                                                                   \
    void create_##T(T* this, const T##_info* args_name)
#  else
#    define def_constructor(T, args_name)                               \
    T* ogg_constructor_##T##___(const T##_info* args_name)              \
    {                                                                   \
        T* object = (T*)malloc(sizeof(T));                              \
        void ogg_static_constructor_##T##___(T*, const void*);          \
        ogg_static_constructor_##T##___(object, args_name);             \
        ((ogg_component*)object)->vptr = T##_vtable;                    \
        return object;                                                  \
    }                                                                   \
    void ogg_static_constructor_##T##___(T* object, const void* args)   \
    {                                                                   \
        void create_##T(T* this, const T##_info* args_name);            \
        if (parent_static_constructor_##T##__ != 0)                     \
            parent_static_constructor_##T##__((void*)object, args);     \
        create_##T(object, (const T##_info*)args);                      \
    }                                                                   \
    void create_##T(T* this, const T##_info* args_name)
#  endif

#endif //OGG_GRAPHIC_COMPONENTS__HEADER_FILE_____