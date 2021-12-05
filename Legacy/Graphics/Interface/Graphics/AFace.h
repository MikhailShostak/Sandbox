#pragma once
#include <cstddef>

using std::size_t;

struct AFace final
{
public:

	short first;
	short second;
	short third;

	AFace(short first = 0, short second = 0, short third = 0):first(first), second(second), third(third) {}

	void set(short first, short second, short third)
	{
		this->first = first;
		this->second = second;
		this->third = third;
	}

	short *data() { return &first; }
	const short *data() const { return &first; }
	short &operator[](size_t index) { return (&first)[index]; }
	const short &operator[](size_t index) const { return (&first)[index]; }
};
