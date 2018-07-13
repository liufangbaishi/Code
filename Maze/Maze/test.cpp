#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stack>
using namespace std;
struct Seat
{
	Seat(int x, int y)
	: _x(x)
	, _y(y)
	{}
	int _x;
	int _y;
};
#if 0
#define ROW 10
#define COL 10
class Maze
{
public:
	Maze(int map[ROW][COL])
	{
		for (int i = 0; i < ROW; ++i)
		{
			for (int j = 0; j < COL; ++j)
				_map[i][j] = map[i][j];
		}
	}
	void PrintMap()
	{
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
				cout << _map[i][j] << " ";
			cout << endl;
		}
	}
	bool IsPass(const Seat& s)
	{
		if (IsExit(s))
			return true;
		if (1 == _map[s._x][s._y])
			return true;
		return false;
	}
	bool IsExit(const Seat& s)
	{
		if (s._x<0 || s._x>=ROW
			|| s._y<0 || s._y>=COL)
			return true;
		return false;
	}
	bool PassMaze(Seat& enter)
	{
		//检测入口
		if (!IsPass(enter))
		{
			cout << "入口非法" << endl;
			return false;
		}
		
		stack<Seat> s;
		s.push(enter);
		Seat curPos = s.top();

		while (!s.empty())
		{
			curPos = s.top();

			if (IsExit(curPos))
				return true;

			_map[curPos._x][curPos._y] = 2;//真正的走
			Seat up = curPos;
			up._x -= 1;
			if (IsPass(up))
			{
				s.push(up);
				continue;
			}

			Seat down = curPos;
			down._x += 1;
			if (IsPass(down))
			{
				s.push(down);
				continue;
			}

			Seat left = curPos;
			left._y -= 1;
			if (IsPass(left))
			{
				s.push(left);
				continue;
			}

			Seat right = curPos;
			right._y += 1;
			if (IsPass(right))
			{
				s.push(right);
				continue;
			}
			
			//走错了
			s.pop();
			_map[curPos._x][curPos._y] = 3;
		}
		cout << "走出失败" << endl;
		return false;
	}
private:
	int _map[ROW][COL];
};
int main()
{
	int mapArr[ROW][COL] = {
		{ 0, 0, 0, 1, 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 0, 1, 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 1, 1, 0, 0, 1, 0, 0, 1 },
		{ 0, 0, 1, 0, 1, 0, 1, 0, 0, 1 },
		{ 0, 0, 1, 0, 1, 0, 1, 0, 0, 1 },
		{ 0, 0, 1, 1, 1, 0, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 0, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 0, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 0, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 }
	};
	Maze m(mapArr);
	m.PrintMap();
	m.PassMaze(Seat(9,6));
	cout << endl;
	m.PrintMap();
	return 0;
}
#endif
#if 1
#include <vector>
class Maze
{
public:
	Maze(int* map, int row, int col)
		: _row(row)
		, _col(col)
	{
		_map.resize(row);
		for (int i = 0; i < row; ++i)
		{
			_map[i].resize(col);
			for (int j = 0; j < col; ++j)
				_map[i][j] = map[i*col + j];
		}
	}
	void PrintMap()
	{
		for (int i = 0; i < _row; i++)
		{
			for (int j = 0; j < _col; j++)
				cout << _map[i][j] << " ";
			cout << endl;
		}
	}
	bool IsPass(const Seat& s)
	{
		if (IsExit(s))
			return true;
		if (1 == _map[s._x][s._y])
			return true;
		return false;
	}
	bool IsExit(const Seat& s)
	{
		if (s._x<0 || s._x >= _row
			|| s._y<0 || s._y >= _col)
			return true;
		return false;
	}
	bool PassMaze(Seat& enter)
	{
		//检测入口
		if (!IsPass(enter))
		{
			cout << "入口非法" << endl;
			return false;
		}

		stack<Seat> s;
		s.push(enter);
		Seat curPos = s.top();

		while (!s.empty())
		{
			curPos = s.top();
			if (IsExit(curPos))
				return true;
			_map[curPos._x][curPos._y] = 2;//真正的走
			Seat up = curPos;
			up._x -= 1;
			if (IsPass(up))
			{
				s.push(up);
				continue;
			}

			Seat down = curPos;
			down._x += 1;
			if (IsPass(down))
			{
				s.push(down);
				continue;
			}

			Seat left = curPos;
			left._y -= 1;
			if (IsPass(left))
			{
				s.push(left);
				continue;
			}

			Seat right = curPos;
			right._y += 1;
			if (IsPass(right))
			{
				s.push(right);
				continue;
			}

			//走错了
			s.pop();
			_map[curPos._x][curPos._y] = 3;
		}
		cout << "走出失败" << endl;
		return false;
	}
private:
	vector<vector<int>> _map;
	int _row;
	int _col;
};
int main()
{
	int mapArr[][10] = {
		{ 0, 0, 0, 1, 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 0, 1, 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 1, 1, 0, 0, 1, 0, 0, 1 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 1 },
		{ 0, 0, 1, 0, 0, 0, 1, 0, 0, 1 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 }
	};
	int row = sizeof(mapArr) / sizeof(mapArr[0]);
	int col = sizeof(mapArr[0])/sizeof(mapArr[0][0]);
	Maze m((int*)mapArr,row, col);
	m.PrintMap();
	m.PassMaze(Seat(9, 6));
	cout << endl;
	m.PrintMap();
	return 0;
}
#endif
