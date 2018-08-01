#pragma once

struct Test;
#ifdef __cplusplus  //C和C++都可以编译
extern "C" {
#endif
	struct Test* GetInstance(void);
	extern void test(struct Test* p);
#ifdef __cplusplus
};
#endif