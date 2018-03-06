#include "RBTree.hpp"

template<class K, class V>
class Map
{
public:
	typedef pair<const K, V> ValueType;
	struct KeyOfValue
	{
		const K& operator()(const ValueType& v)
		{
			return v.first;
		}
	};

	typedef typename RBTree<K, ValueType, KeyOfValue>::Iterator Iterator;

	pair<bool, Iterator> Insert(const ValueType& v)
	{
		return t.Insert(v);
	}

	Iterator Begin()
	{
		return t.Begin();
	}

	Iterator End()
	{
		return t.End();
	}

	void InOrder()
	{
		t.InOrder();
	}
	//首先根据类型推演产生一个临时对象ValueType(k, V())，在将其插入到map中，插入返回一个pair第二
	//个元素是迭代器，指向新插入的元素，
	//或插入失败的地方，最后取出迭代器中的第二个元素
	V operator[](const K& k)
	{
		pair<bool, Iterator> tmp = t.Insert(ValueType(k, V()));
		return (*(tmp.second)).second;
	}
private:
	RBTree<K, ValueType, KeyOfValue> t;
};
