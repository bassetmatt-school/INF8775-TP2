# INF8775 - TP2
Second group project for the course INF8775.<br>
Implementation of three algorithms for the Travel Salesman Problem (TSP)
- One using the greedy nearest neighbor algorithm.
- One using a minimal spanning tree.
- One using dynamic programming for an optimal solution.

## C++ build/requirements
Standard C++20 is used.
### Requirements
- `make`
- `cmake`
- `g++`
- `SDL2`

### Build
First option: Build the project inside vscode.
Second: manually:
```bash
mkdir -p build && cd build
```
```bash
cmake ..
```
```bash
make tp2
```
```bash
cd ../bin && ./tp2
```
