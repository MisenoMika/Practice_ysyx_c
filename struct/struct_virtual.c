#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
/*注意： 某些编译器（如 MSVC）需要 _USE_MATH_DEFINES；Linux/GCC 通常需要编译时加 -lm 链接数学库。*/
typedef enum {
    RECTANGULAR,
    POLAR
} complex_type;

struct complex_struct; // 前置声明

typedef struct {
    double (*real_part)(struct complex_struct *);
    double (*img_part)(struct complex_struct *);
    double (*magnitude)(struct complex_struct *);
    double (*angle)(struct complex_struct *);
} complex_ops;

typedef struct complex_struct {
    complex_type t;
    double a;  // 对于 RECTANGULAR: 实部
    double b;  // 对于 RECTANGULAR: 虚部
    const complex_ops *ops;  // 指向对应实现的 vtable
} complex_struct;

double rect_real_part(complex_struct *z) { return z->a; }
double rect_img_part(complex_struct *z)  { return z->b; }
double rect_magnitude(complex_struct *z) { return sqrt(z->a*z->a + z->b*z->b); }
double rect_angle(complex_struct *z)     { return atan2(z->b, z->a); }

const complex_ops rect_ops = {
    rect_real_part,
    rect_img_part,
    rect_magnitude,
    rect_angle
};

double pol_real_part(complex_struct *z) { return z->a * cos(z->b); }
double pol_img_part(complex_struct *z)  { return z->a * sin(z->b); }
double pol_magnitude(complex_struct *z) { return z->a; }
double pol_angle(complex_struct *z)     { return z->b; }

const complex_ops pol_ops = {
    pol_real_part,
    pol_img_part,
    pol_magnitude,
    pol_angle
};

int main() {
    complex_struct z1 = {RECTANGULAR, 3, 4, &rect_ops};
    complex_struct z2 = {POLAR, 5, M_PI/6, &pol_ops};

    printf("z1: real=%.2f, imag=%.2f, mag=%.2f, angle=%.2f\n",
           z1.ops->real_part(&z1),
           z1.ops->img_part(&z1),
           z1.ops->magnitude(&z1),
           z1.ops->angle(&z1));

    printf("z2: real=%.2f, imag=%.2f, mag=%.2f, angle=%.2f\n",
           z2.ops->real_part(&z2),
           z2.ops->img_part(&z2),
           z2.ops->magnitude(&z2),
           z2.ops->angle(&z2));

    return 0;
}