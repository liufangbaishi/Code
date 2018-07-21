#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
using namespace std;

template <class T>
class Stack
{
public:
	Stack()
		: _data(new T[3])
		, _size(0)
		, _capacity(3)
	{}
	void Push(const T& data)
	{
		_CheckCapacity();
		_data[_size++] = data;
	}
	void Pop()
	{
		assert(_size);
		_size--;
	}
	T& Top()
	{
		return _data[_size - 1];
	}
	T& Top()const
	{
		return _data[size - 1];
	}
	size_t Size()const
	{
		return _size;
	}
	bool Empty()const
	{
		return 0 == _size;
	}
	~Stack()
	{
		if (_data)
		{
			delete[] _data;
			_data = NULL;
			_size = 0;
			_capacity = 0;
		}
	}
private:
	void _CheckCapacity()
	{
		if (_size == _capacity)
		{
			T* tmp = new T[_capacity * 2];
			for (size_t i = 0; i < _capacity; i++)
				tmp[i] = _data[i];
			delete[] _data;
			_data = tmp;
			_capacity = _capacity * 2;
		}
	}
	T* _data;
	size_t _size;//”––ß‘™Àÿ∏ˆ ˝
	size_t _capacity;
};

int main()
{
	Stack<int> s;
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	cout << s.Size() << endl;
	cout << s.Top() << endl;

	s.Pop();
	s.Pop();
	cout << s.Empty() << endl;
	cout << s.Size() << endl;
	cout << s.Top() << endl;

	s.Pop();
	s.Pop();
	cout << s.Empty() << endl;
	cout << s.Size() << endl;
	cout << s.Top() << endl;
	return 0;
}
#if 0
#include <stack>
bool IsBrackets(char p)
{
	if (p == '(' || p == ')'
		|| p == '[' || p == ']'
		|| p == '{' || p == '}')
		return true;
	return false;
}
bool MatchBrackets(char* pStr)
{
	const char* p = pStr;
	stack<char> s;
	for (int i = 0; p[i] != '\0'; ++i)
	{
		if (!IsBrackets(p[i]))
			continue;
		else
		{
			if (p[i] == '(' || p[i] == '{' || p[i] == '[')
			{
				s.push(p[i]);
				continue;
			}
			if (p[i] == ')' || p[i] == '}' || p[i] == ']')//”“¿®∫≈
			{
				if (s.empty())
				{
					cout << "”“¿®∫≈∂‡”⁄◊Û¿®∫≈" << endl;//abc)))))
					return false;
				}
				else if (s.top()=='('&&p[i]==')' || s.top()=='{'&&p[i]=='}' || s.top()=='['&&p[i]==']')
					s.pop();
				else
				{
					cout << "◊Û”“¿®∫≈¥Œ–Ú≤ª∆•≈‰" << endl;
					return false;
				}//else
			}//if”“¿®∫≈
		}
	}//for
	if (s.empty())
	{
		cout << "∆•≈‰≥…π¶" << endl;
		return true;
	}
	else
	{
		cout << "◊Û¿®∫≈∂‡”⁄”“¿®∫≈" << endl;
		return false;
	}
}
int main()
{
	char a[] = "(())abc{[(])}"; // ◊Û”“¿®∫≈¥Œ–Ú∆•≈‰≤ª’˝»∑
	MatchBrackets(a);
	char b[] = "(()))abc{[]}"; // ”“¿®∫≈∂‡”⁄◊Û¿®∫≈
	MatchBrackets(b);
	char c[] = "(()()abc{[]}"; // ◊Û¿®∫≈∂‡”⁄”“¿®∫≈
	MatchBrackets(c);
	char d[] = "(())abc{[]()}"; // ◊Û”“¿®∫≈∆•≈‰’˝»∑
	MatchBrackets(d);
	return 0;
}
#endif

#if 0
#include <stack>
enum OPERATOR
{ADD, SUB, MUL, DIV, DATA};
struct Cell
{
	OPERATOR _op;
	int _data;
};
int CalcRPN(Cell* RPN, int size)
{
	stack<int> s;
	for (int i = 0; i < size; i++)
	{
		if (RPN[i]._op == DATA)
			s.push(RPN[i]._data);
		else
		{
			int right = s.top();
			s.pop();
			int left = s.top();
			s.pop();
			switch (RPN[i]._op)
			{
			case ADD:
				s.push(left + right);
				break;
			case SUB:
				s.push(left - right);
				break;
			case MUL:
				s.push(left * right);
				break;
			case DIV:
				if (right != 0)
					s.push(left / right);
				break;
			}//switch
		}
	}//for
	return s.top();
}
void FunTest()
{
	Cell RPN[] = { { DATA, 12 }, { DATA, 3 }, { DATA, 4 }, { ADD, 0 }, { MUL, 0 }, { DATA, 6 }, { SUB, 0 }, { DATA, 8 }
	, { DATA, 2 }, { DIV, 0 }, { ADD, 0 } };
	int tmp = CalcRPN(RPN, sizeof(RPN) / sizeof(RPN[0]));
	cout << tmp << endl;
}
#endif

/*
bool Isoperator(const char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%'||ch =='('||ch ==')')
		return true;
	return false;
}
//’ªƒ⁄≤Ÿ◊˜∑˚
int isp(char ch)
{
	switch (ch)
	{
	case '#':
		return 0;
	case '(':
		return 1;
	case '*':
	case '/':
	case '%':
		return 5;
	case '+':
	case '-':
		return 3;
	case ')':
		return 6;
	default:
		assert(0);
		cout << "‘ÀÀ„∑˚≤ª∫œ∑®" << endl; 
	}
	return 0;
}
//’ªÕ‚≤Ÿ◊˜∑˚
int icp(char ch)
{
	switch (ch)
	{
	case '#':
		return 0;
	case '(':
		return 6;
	case '*':
	case '/':
	case '%':
		return 4;
	case '+':
	case '-':
		return 2;
	case ')':
		return 1;
	default:
		assert(0);
		cout << "‘ÀÀ„∑˚≤ª∫œ∑®" << endl;
	}
	return 0;
}
void Postfixnotation(char*Expre)
{
	//stack<char>Data;
	string str;
	char ch;
	stack<char>Op;
	Op.push('#');
	int i = 0;
	while (Expre[i])
	{
		if (!Isoperator(Expre[i]))
		{
			str.push_back( Expre[i]);
			cout << Expre[i];
		}
		else
		{
			str.push_back(' ');
			cout << ' ';
			ch = Op.top();
			if (icp(Expre[i]) > isp(ch))
				Op.push(Expre[i]);
			else if (icp(Expre[i]) < isp(ch))
			{
				str.push_back(ch);
				Op.pop();
				cout << ch;
				continue;
			}
			else
			{
				if (Op.top() == '(')
				{
					Op.pop();
				}
			}
		}
		++i;
	}
	while (Op.top() != '#')
	{
		ch = Op.top();
		str.push_back(ch);
		cout << ch;
		Op.pop();
	}
	cout << endl;
	str.push_back(0);
}
*/