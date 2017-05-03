#ifndef OGG_GEOMETRY__HEADER_FILE___
#define OGG_GEOMETRY__HEADER_FILE___
#include <math.h>
# ifdef __cplusplus
#define max(a, b) ((a)>(b)?(a):(b))
#define min(a, b) ((a)<(b)?(a):(b))
# endif
#define register_geometry_system(T, id) /* register a geometry system by given type */\
typedef struct {\
    T x, y;\
} point##id;\
\
typedef point##id coord##id;\
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
point##id add_point##id(point##id lhs, point##id rhs) {\
    lhs.x += rhs.x; lhs.y += rhs.y;\
    return lhs;\
}\
point##id sub_point##id(point##id lhs, point##id rhs) {\
    lhs.x -= rhs.x; lhs.y -= rhs.y;\
    return lhs;\
}\
point##id mul_point##id(point##id lhs, T rhs) {\
    lhs.x *= rhs; lhs.y *= rhs;\
    return lhs;\
}\
point##id div_point##id(point##id lhs, T rhs) {\
    lhs.x /= rhs; lhs.y /= rhs;\
    return lhs;\
}\
double norm##id(point##id v) {\
    return sqrt(v.x * v.x + v.y * v.y);\
}\
T inner_product##id(point##id lhs, point##id rhs) {\
    return lhs.x * rhs.x + lhs.y * rhs.y;\
}\
T outer_product##id(point##id lhs, point##id rhs) {\
    return lhs.x * rhs.y - rhs.x * lhs.y;\
}\
double angle##id(point##id lhs, point##id rhs) {\
    return acos((double)inner_product##id(lhs, rhs)/(norm##id(lhs)*norm##id(rhs)));\
}

#endif //OGG_GEOMETRY__HEADER_FILE___
