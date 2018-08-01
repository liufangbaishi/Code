#include "bb.h"
#include "aa.h"
extern "C"
{
	struct Test
	{
		A a;
	};
	struct Test *GetInstance()
	{
		return new struct Test;
	}
	void test(struct Test* p)
	{
		p->a.fun();
	}
};