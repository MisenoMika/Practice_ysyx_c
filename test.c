#include <stdio.h>
typedef struct Rational {
	int numerator;
	int denominator;
} Rational;

Rational make_rational(int numerator, int denominator)
{
	Rational r;
	r.numerator = numerator;
	r.denominator = denominator;
	return r;
}

int gcd(int x, int y)
{
	int r = x % y;
	int temp = y;
	while (r != 0) {
		temp = r;
		r = x % r;
	}
	return temp;
}

Rational reduction(Rational * r1)
{
	int a1 = r1->numerator;
	int a2 = r1->denominator;
	if (a1 == 0) {
		r1->denominator = 1;
		return *r1;
	}
	if (a1 < 0 && a2 < 0) {
		a1 = -a1;
		a2 = -a2;
	} else if (a2 < 0) {
		a1 = -a1;
		a2 = -a2;
	}
	int d = gcd((a1 > 0) ? a1 : -a1, (a2 > 0) ? a2 : -a2);
	r1->numerator = a1 / d;
	r1->denominator = a2 / d;

	return *r1;
}

void print_rational(Rational rational)
{
	rational = reduction(&rational);
	if (rational.numerator == 0)
		printf("0\n");
	else
		printf("%d/%d\n", rational.numerator,
		       rational.denominator);
}


Rational add_rational(Rational r1, Rational r2)
{
	Rational r;
	r.numerator =
	    r1.numerator * r2.denominator + r2.numerator * r1.denominator;
	r.denominator = r1.denominator * r2.denominator;
	return r;
}

Rational sub_rational(Rational r1, Rational r2)
{
	Rational r;
	r.numerator =
	    r1.numerator * r2.denominator - r2.numerator * r1.denominator;
	r.denominator = r1.denominator * r2.denominator;
	return r;
}

Rational mul_rational(Rational r1, Rational r2)
{
	Rational r;
	r.numerator = r1.numerator * r2.numerator;
	r.denominator = r1.denominator * r2.denominator;
	return r;
}

Rational div_rational(Rational r1, Rational r2)
{
	Rational r;
	r.numerator = r1.numerator * r2.denominator;
	r.denominator = r1.denominator * r2.numerator;
	return r;
}

int main()
{
	struct Rational a = make_rational(1, 8);	/* a=1/8 */
	struct Rational b = make_rational(-1, 8);	/* b=-1/8 */
	print_rational(add_rational(a, b));	//0
	print_rational(sub_rational(a, b));	//1/4
	print_rational(mul_rational(a, b));	//-1/64
	print_rational(div_rational(a, b));	//-1

	return 0;
}
