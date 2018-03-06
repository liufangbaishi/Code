#include "RBTree.hpp"

template<class K>
class Set
{
public:
	struct KeyOfValue
	{
		const K& operator()(const K& k)
		{
			return k;
		}
	};

	typedef typename RBTree<K, K, KeyOfValue>::Iterator Iterator;

	pair<bool, Iterator> Insert(const K& key)
	{
		return t.Insert(key);
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

private:
	RBTree<K, K, KeyOfValue> t;
};
