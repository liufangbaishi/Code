#pragma once

struct Test;
#ifdef __cplusplus  //C��C++�����Ա���
extern "C" {
#endif
	struct Test* GetInstance(void);
	extern void test(struct Test* p);
#ifdef __cplusplus
};
#endif