#ifndef TP2_STRUCTURES_H
#define TP2_STRUCTURES_H

#include <iostream>
#include <map>
#include <vector>


/* Common Structures */
class Point {
public:
	int x,y;
	Point() {this->x = 0; this->y = 0;}
	Point(int x, int y) { this->x = x; this->y = y;}
	Point copy() {return Point(this->x, this->y);}

	Point operator+(Point const p2) const {return Point(this->x + p2.x, this->y + p2.y);}
	Point operator-(Point const p2) const {return Point(this->x - p2.x, this->y - p2.y);}
	Point operator*(int          k) const {return Point(this->x * k   , this->y * k   );}
	Point operator/(int          k) const {return Point(this->x / k   , this->y / k   );}
	Point operator-() const {return Point(-this->x, -this->y);}

	Point& operator+=(Point const p2) {this->x += p2.x; this->y += p2.y; return *this;}
	Point& operator-=(Point const p2) {this->x -= p2.x; this->y -= p2.y; return *this;}
	Point& operator*=(int 		   k) {this->x *= 	 k; this->y *=    k; return *this;}
	Point& operator/=(int 		   k) {this->x /= 	 k; this->y /=    k; return *this;}
	void pr() const {printf("(%d, %d)\n", this->x, this->y);}
};

int distance(Point const p1, Point const p2);

/* Dynamic Programming structures */
using Set  = uint32_t;
using Path = uint64_t;

bool contains(Set s, int i);
Set add(Set s, int i);
Set remove(Set s, int i);
int size(Set s);
Set initSet(int i);

Set get_set(Path p);
uint8_t get_point(Path p);
Path path_from_point(uint8_t pt);
Path constr(uint8_t pt, uint32_t set);

using PathTable = std::map<Path, int>;
using TableIndex = std::pair<Path, int>;


/* Prim Structures */



#endif /* TP2_STRUCTURES_H */
