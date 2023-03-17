#ifndef TP2_POINT_H
#define TP2_POINT_H

#include <iostream>

class Point {
public:
	int x,y;
	Point() {this->x = 0; this->y = 0;}
	Point(int x, int y) { this->x = x; this->y = y;}
	Point copy() {return Point(this->x, this->y);}
	Point operator+(Point const p2) const {return Point(this->x + p2.x, this->y + p2.y);}
	Point operator-(Point const p2) const {return Point(this->x - p2.x, this->y - p2.y);}
	Point operator-() const {return Point(-this->x, -this->y);}
	Point operator*(int const k) const {return Point(this->x * k, this->y * k);}
	Point operator/(int const k) const {return Point(this->x / k, this->y / k);}
	Point& operator+=(Point const p2) {this->x += p2.x; this->y += p2.y; return *this;}
	Point& operator*=(int const k) {this->x *= k; this->y *= k; return *this;}
	Point& operator/=(int const k) {this->x /= k; this->y /= k; return *this;}
	void pr() {printf("(%d, %d)\n", this->x, this->y);}
};

// Point operator*(int const k, Point const p2) {return Point(k * p2.x, k * p2.y);}
using Vec2 = Point;

int distance(Point const p1, Point const p2);


class OptimalSet {
public:
	uint32_t elements;

	bool isInSet(int i) const;
	void toggleFromSet(int i);
	int countElements() const;
};

class PartialPath {
public:
	uint8_t start_point;
	OptimalSet point_set;
	uint8_t point_count;
};

using DistTable = std::vector<PartialPath>;

#endif /* TP2_POINT_H */
