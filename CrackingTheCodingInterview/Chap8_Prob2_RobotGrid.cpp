#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <algorithm>
const int ROWS=5;
const int COLS = 4;

class Point{
	public:
		Point(int r, int c):r(r),c(c){
		}
		int getX(){
			return r;
		}
		int getY(){
			return c;
		}
	private:
		int r;
		int c;
};


namespace std{
	template<>
	class hash<Point>{
		size_t operator()(const Point& p){
				int temp;
				temp = 0x1f1f1f1f * p.getX();

				return (temp^p.getY());
		}

	};
}

using namespace std;

bool RobotMove(bool maze[ROWS][COLS],int r,int c,vector<Point>& v){
	if(r<0 || c<0 || !maze[r][c] ){
		return false;
	}
	if(r==0 && c==0)
		return true;
	v.push_back(Point(r,c));
	RobotMove(maze,r-1,c,v);
	RobotMove(maze,r,c-1,v);
}
		


int main(){
	int r,c;
	vector<Point> v;
	unordered_map<Point,bool> h;
	bool maze[ROWS][COLS];
	RobotMove(maze,ROWS-1,COLS-1,v);

}