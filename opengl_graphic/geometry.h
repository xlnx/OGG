#ifndef OGG_GEOMETRY__HEADER_FILE___
#define OGG_GEOMETRY__HEADER_FILE___

#ifdef __cplusplus
extern "C" {
#endif
#include <math.h>

#define register_geometry_system(T, id) /* register a geometry system by given type */\
typedef struct {\
    T x, y;\
} point##id;\
\
typedef point##id coord##id;\
typedef point##id vector##id;\
\
typedef struct {\
    point##id u, v;\
} segment##id;\
\
typedef struct {\
    union {\
        struct {\
            point##id top_left, bottom_right;\
        };\
        struct {\
            T left, top, right, bottom;\
        };\
    };\
} rect##id;

#define inst_geometry_system(T, id) /* inst a geometry system */\
point##id* add_point##id(point##id* lhs, const point##id* rhs) {\
    lhs->x += rhs->x; lhs->y += rhs->y;\
    return lhs;\
}\
point##id* sub_point##id(point##id* lhs, const point##id* rhs) {\
    lhs->x -= rhs->x; lhs->y -= rhs->y;\
    return lhs;\
}\
double norm##id(const vector##id* v){\
    return sqrt(v->x * v->x + v->y * v->y);\
}\
T inner_product##id(const vector##id* lhs, const vector##id* rhs) {\
    return lhs->x * rhs->x + lhs->y * rhs->y;\
}\
T outer_product##id(const vector##id* lhs, const vector##id* rhs) {\
    return lhs->x * rhs->y - rhs->x * lhs->y;\
}\
double angle##id(const vector##id* lhs, const vector##id* rhs) {\
    return acos((double)inner_product##id(lhs, rhs)/(norm##id(lhs)*norm##id(rhs)));\
}

#ifdef __cplusplus
}
#endif

#endif //OGG_GEOMETRY__HEADER_FILE___