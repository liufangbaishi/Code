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
	//���ȸ����������ݲ���һ����ʱ����ValueType(k, V())���ڽ�����뵽map�У����뷵��һ��pair�ڶ�
	//��Ԫ���ǵ�������ָ���²����Ԫ�أ�
	//�����ʧ�ܵĵط������ȡ���������еĵڶ���Ԫ��
	V operator[](const K& k)
	{
		pair<bool, Iterator> tmp = t.Insert(ValueType(k, V()));
		return (*(tmp.second)).second;
	}
private:
	RBTree<K, ValueType, KeyOfValue> t;
};
