#ifndef TP2_STRUCTURES_HEADER
#define TP2_STRUCTURES_HEADER

#include <iostream>
#include <map>
#include <vector>


/* Common Structures */
class Point {
public:
	long x,y;
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
	void pr() const {printf("(%ld, %ld)\n", this->x, this->y);}
};

int distance(Point const p1, Point const p2);

/* Dynamic Programming structures */
/* A set is an integer whose bits of weight i
 * denote the appartenance of the i-th element
 * to the set*/
using Set  = uint32_t;
/* A path is the pair of a et and a point
 * The lower half of the integer is the set
 * The higher is the point */
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
using edge = std::pair<uint, uint>;

struct Node {
	uint index;
	std::vector<Node*> children;
	Node(uint idx, std::vector<Node*> children);
};


void build_tree(std::vector<edge> const& edges, Node& tree);

using id_node = std::pair<uint, Node*>;

#endif /* TP2_STRUCTURES_HEADER */
