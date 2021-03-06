#include "Graph.h"

Dot::Dot(double a, double b) {
	first = a;
	second = b;
}

inline double Dot::getX() {
	return first;
}

inline double Dot::getY() {
	return second;
}

bool Dot::equals(Dot b) {
	/*
	bool x = -EPS <= (this->getX() - b.getX()) && (this->getX() - b.getX()) <= EPS;
	bool y = -EPS <= (this->getY() - b.getY()) && (this->getY() - b.getY()) <= EPS;
	return x && y;
	*/
	return first == b.first && second == b.second;
}

Line::Line(Dot d1, Dot d2) {
	a = d1.getY() - d2.getY();
	b = d2.getX() - d1.getX();
	c = -a * d1.getX() - b * d1.getY();
}

Line::Line(double varX, double varY, double varC) {
	a = varX;
	b = varY;
	c = varC;
}

inline double Line::getA() {
	return a;
}

inline double Line::getB() {
	return b;
}

inline double Line::getC() {
	return c;
}

Circle::Circle(double varM, double varN, double varR) {
	m = varM;
	n = varN;
	r = varR;
}

inline double Circle::getA() {
	return m;
}

inline double Circle::getB() {
	return n;
}

inline double Circle::getC() {
	return r;
}

void solve(Container *con, Graph* g1, Graph* g2){
	bool aIsLine = typeid(*g1).name() == typeid(Line).name();
	bool bIsLine = typeid(*g2).name() == typeid(Line).name();

	if (aIsLine && bIsLine) {
		//if both is line
		double a1 = g1->getA(), b1 = g1->getB(), c1 = g1->getC();
		double a2 = g2->getA(), b2 = g2->getB(), c2 = g2->getC();
		if ((a1 * b2 - a2 * b1) != 0) {
			//if not parrallel
			double x = (b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1);
			double y = (a2 * c1 - a1 * c2) / (a1 * b2 - a2 * b1);
			con->add(Dot(x, y));
		}
	} else if (aIsLine && !bIsLine) {
		//if g1 is line and g2 is circle
		double _a = g1->getA(), _b = g1->getB(), _c = g1->getC();
		double _m = g2->getA(), _n = g2->getB(), _r = g2->getC();
		if (_b == 0) {
			//g1 is vertical line
			double x1 = -_c / _a, x2 = -_c / _a;
			double dis = pow(_r, 2) - pow(x1 - _m, 2);
			if (dis >= 0) {
				double y1 = _n + sqrt(dis);
				double y2 = _n + -sqrt(dis);
				con->add(Dot(x1, y1));
				con->add(Dot(x2, y2));
			}
		} else {
			double a = pow(_b, 2) + pow(_a, 2);
			double b = (_a * _c - _m * pow(_b, 2) + _n * _a * _b) * 2;
			double c = (pow(_m, 2) + pow(_n, 2) - pow(_r, 2)) * pow(_b, 2) + pow(_c, 2) + 2 * _n * _c * _b;
			double delta = pow(b, 2) - 4 * a * c;
			if (delta >= 0) {
				double x1 = (-b + sqrt(delta)) / (2 * a), x2 = (-b - sqrt(delta)) / (2 * a);
				double y1 = (_a * x1 + _c) / (-_b), y2 = (_a * x2 + _c) / (-_b);
				con->add(Dot(x1, y1));
				con->add(Dot(x2, y2));
			}
		}
	} else if (!aIsLine && bIsLine) {
		//if g1 is circle and g2 is line
		return solve(con, g2, g1);
	} else {
		//if both are circle
		double x1 = g1->getA(), y1 = g1->getB(), r1 = g1->getC();
		double x2 = g2->getA(), y2 = g2->getB(), r2 = g2->getC();
		double _a = 2 * (x1 - x2);
		double _b = 2 * (y1 - y2);
		double _c = pow(x2, 2) - pow(x1, 2) + pow(y2, 2) - pow(y1, 2) - pow(r2, 2) + pow(r1, 2);
		Line* l = new Line(_a, _b, _c);
		return solve(con, l, g2);
	}
}
