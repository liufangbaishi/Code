#pragma once
struct InputIteratorTag   // 只读
{};

struct OutputIteratorTag   // 读写
{};

struct ForwardIteratorTag : public InputIteratorTag   // 单向
{};

struct BidirectionalIteratorTag : public ForwardIteratorTag  // 双向
{};

struct RandomAccessIteratorTag : public BidirectionalIteratorTag // 随机读取
{};

template<class T, class Distance>
struct BidirectionalIterator
{
	typedef BidirectionalIteratorTag IteratorCategory;
	typedef T ValueType;
	typedef Distance DifferenceType;
	typedef T* Pointer;
	typedef T& Reference;
};

template<class T, class Distance>
struct RandomAccessIterator
{
	typedef RandomAccessIteratorTag IteratorCategory;
	typedef T ValueType;
	typedef Distance DifferenceType;
	typedef T* Pointer;
	typedef T& Reference;
};

//自定义迭代器
template <class Iterator>
class IteratorTraits
{
public:
	typename typedef Iterator::ValueType ValueType;
	typename typedef Iterator::Reference Reference;
	typename typedef Iterator::Pointer Pointer;
	typename typedef Iterator::DifferenceType DifferenceType;
	typename typedef Iterator::IteratorCategory IteratorCategory;
};
// 原生态的指针
template <class T>
class IteratorTraits<T*>
{
public:
	typedef T ValueType;
	typedef T* Pointer;
	typedef T& Reference;
	typedef int DifferenceType;
	typedef RandomAccessIteratorTag IteratorCategory;
};

// O(N)
template <class Iterator> //不能随机访问，只能连续访问
typename IteratorTraits<Iterator>::DifferenceType Difference(Iterator first, Iterator last, BidirectionalIteratorTag)
{
	typename IteratorTraits<Iterator>::DifferenceType diff = 0;
	while (first != last)
	{
		++diff;
		++first;
	}
	return diff;
}
// O(1)
template <class Iterator>//可以随机访问的迭代器
typename IteratorTraits<Iterator>::DifferenceType Difference(Iterator first, Iterator last, RandomAccessIteratorTag)
{
	return last - first;
}
//效率
template <class Iterator>
typename IteratorTraits<Iterator>::DifferenceType Difference(Iterator first, Iterator last)
{
	return Difference(first, last, IteratorTraits<Iterator>::IteratorCategory());
}

// 看做正向迭代器的适配器
template <class Iterator>
class ReverseIterator
{
	typedef ReverseIterator<Iterator> Self;
public:
	typename typedef IteratorTraits<Iterator>::ValueType ValueType;// 迭代器有这些类型
	typename typedef IteratorTraits<Iterator>::Reference Reference;
	typename typedef IteratorTraits<Iterator>::Pointer Pointer;
	typename typedef IteratorTraits<Iterator>::DifferenceType DifferenceType;
	typename typedef IteratorTraits<Iterator>::IteratorCategory IteratorCategory;

	ReverseIterator()
	{}
	ReverseIterator(Iterator it)
		:_it(it)
	{}
	ReverseIterator(Self& s)
		:_it(s._it)
	{}
	
	Reference operator*()
	{
		Iterator tmp(_it);
		--tmp;
		return *tmp;
	}
	Pointer operator->()
	{
		return &(operator*());
	}
	Self& operator++()
	{
		--_it;
		return *this;
	}
	Self operator++(int)
	{
		Iterator tmp(_it);
		_it--;
		return tmp;
	}
	Self& operator--()
	{
		++_it;
		return *this;
	}
	Self operator--(int)
	{
		Iterator tmp(_it);
		_it++;
		return tmp;
	}
	bool operator!=(const Self& s)
	{
		return _it != s._it;
	}
	bool operator==(const Self& s)
	{
		return _it == s._it;
	}
private:
	Iterator _it;
};