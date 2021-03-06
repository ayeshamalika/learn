#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct node{
	int ballX;
	int ballY;
	vector<vector<int>> used;
	int dist;
	string path;
};

class Solution {
public:
    string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {
        vector<node> queue;
		vector<vector<int>> directions = {{0, 1}, {-1, 0}, {1, 0}, {0, -1}}; // d,l,r,u
		vector<string> dirName = {"d", "l", "r", "u"};
		node x;
		int height = maze.size(), width = maze[0].size();
		for (int i = 0; i < maze.size(); i++){
			maze[i].insert(maze[i].begin(), 1);
			maze[i].push_back(1);
		}
		vector<int> border(width + 2, 1);
		maze.push_back(border);
		maze.insert(maze.begin(), border);
		int front = 0, minDist = -1;
		string perfectPath = "";
		width += 2;
		height += 2;
		int holeX = hole[0] + 1, holeY = hole[1] + 1;
		x.ballX = ball[1] + 1; x.ballY = ball[0] + 1; x.dist = 0; x.path = "";
		x.used = vector<vector<int>>(height, vector<int>(width, 0));
		for (int i =0; i < height; i ++)
			for (int j = 0; j < width; j++)
				x.used[i][j] = maze[i][j];
		queue.push_back(x);
		while (!queue.empty()){
			node curPos = queue[0];
			queue.erase(queue.begin());
			for (int i = 0; i < 4; i++){
				int dirX = directions[i][0];
				int dirY = directions[i][1];
				int tmpX = curPos.ballX, tmpY = curPos.ballY, dist = curPos.dist;
				string path = curPos.path + dirName[i];
				vector<vector<int>> used(height, vector<int>(width, 0));
				for (int j =0; j < height; j++)
					for (int k = 0; k < width; k++)
						used[j][k] = curPos.used[j][k];
				while (tmpX >= 0 && tmpX < width && tmpY >= 0 && tmpY < height){
					if (tmpX == holeY && tmpY == holeX){
						if (minDist == -1){
							minDist = dist;
							perfectPath = path;
							return perfectPath;
						} else if (minDist > dist) {
							minDist = dist;
							perfectPath = path;
						}
					}
				    if (maze[tmpY][tmpX] == 1){// meet the wall
						node y;
						y.ballX = tmpX - dirX;
						y.ballY = tmpY - dirY;
						y.dist = dist;
						y.path = path;
						y.used = used;
						queue.push_back(y);
						break;
					} else {
						tmpX += dirX;
						tmpY += dirY;
						if (used[tmpY][tmpX] == 1 && maze[tmpY][tmpX] != 1){
							break;
						}
						used[tmpY][tmpX] = 1;
						dist++;
					}
				}
			}
		}
		if (minDist == -1){
			return "impossible";
		} else {
			return perfectPath;
		}
    }
};

int main(){
	vector<vector<int>> maze1 = {{0, 0, 0, 0, 0},
								{1, 1, 0, 0, 1},
								{0, 0, 0, 0, 0},
								{0, 1, 0, 0, 1},
								{0, 1, 0, 0, 0}};
	vector<int> ball1 = {4, 3};
	vector<int> hole1 = {3, 0};
	vector<vector<int>> maze2 = {{0, 0, 0, 0, 0},
								 {1, 1, 0, 0, 1},
								 {0, 0, 0, 0, 0},
								 {0, 1, 0, 0, 1},
								 {0, 1, 0, 0, 0}};
	vector<int> ball2 = {4, 3};
	vector<int> hole2 = {0, 1};
	Solution sol;
	cout << sol.findShortestWay(maze2, ball2, hole2) << endl;
	cout << sol.findShortestWay(maze1, ball1, hole1) << endl;
	return 0;
}
