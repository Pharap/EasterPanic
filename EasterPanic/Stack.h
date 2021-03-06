#pragma once

#include <stdint.h>

//
// Declaration
//

template< typename Type, uint8_t Capacity >
class Stack
{
public:
	static_assert(Capacity > 0, "Attempt to create a Stack with Capacity less than 1");
	static_assert(Capacity < 128, "Attempt to create a Stack with Capacity greater than 127");

	using ItemType = Type;
	using IndexType = uint8_t;
	using IndexOfType = int8_t;

	constexpr static const IndexType FirstIndex = 0;
	constexpr static const IndexType LastIndex = Capacity - 1;

private:
	ItemType items[Capacity];
	IndexType next;

public:
	Stack(void);

	bool isEmpty(void) const; // O(1)
	bool isFull(void) const; // O(1)

	IndexType GetCount(void) const; // O(1)
	constexpr IndexType GetCapacity(void) const; // O(1)

	ItemType & peek(void); // O(1)
	const ItemType & peek(void) const; // O(1)
	bool push(const ItemType & item); // O(1)
	bool push(ItemType && item); // O(1)
	void drop(void); // O(1)

	void clear(void); // O(n)
	bool contains(const ItemType & item) const; // O(n)

	// Returns -1 if item not found
	IndexOfType indexOf(const ItemType & item) const; // O(n)

	ItemType & operator [] (const IndexType index); // O(1)
	const ItemType & operator [] (const IndexType index) const; // O(1)
};


//
// Definition
//

template< typename Type, uint8_t Capacity >
Stack< Type, Capacity >::Stack(void)
	: items(), next(0)
{
}

template< typename Type, uint8_t Capacity >
bool Stack< Type, Capacity >::isEmpty(void) const // O(1)
{
	return (this->next == FirstIndex);
}

template< typename Type, uint8_t Capacity >
bool Stack< Type, Capacity >::isFull(void) const // O(1)
{
	return (this->next == this->GetCapacity());
}

template< typename Type, uint8_t Capacity >
typename Stack< Type, Capacity >::IndexType Stack< Type, Capacity >::GetCount(void) const // O(1)
{
	return this->next;
}

template< typename Type, uint8_t Capacity >
constexpr typename Stack< Type, Capacity >::IndexType Stack< Type, Capacity >::GetCapacity(void) const // O(1)
{
	return static_cast<IndexType>(Capacity);
}

template< typename Type, uint8_t Capacity >
typename Stack< Type, Capacity >::ItemType & Stack< Type, Capacity >::peek(void) // O(1)
{
	//DEBUG_ASSERT(this->next > 0);

	return this->items[this->next - 1];
}

template< typename Type, uint8_t Capacity >
const typename Stack< Type, Capacity >::ItemType & Stack< Type, Capacity >::peek(void) const // O(1)
{
	//DEBUG_ASSERT(this->next > 0);

	return this->items[this->next - 1];
}

template< typename Type, uint8_t Capacity >
bool Stack< Type, Capacity >::push(const typename Stack< Type, Capacity >::ItemType & item) // O(1)
{
	if (this->isFull())
		return false;

	this->items[this->next] = item;
	++this->next;
	return true;
}

template< typename Type, uint8_t Capacity >
bool Stack< Type, Capacity >::push(typename Stack< Type, Capacity >::ItemType && item) // O(1)
{
	if (this->isFull())
		return false;

	this->items[this->next] = item; // ought to be std::move
	++this->next;
	return true;
}

template< typename Type, uint8_t Capacity >
void Stack< Type, Capacity >::drop(void) // O(1)
{
	//DEBUG_ASSERT(this->next > 0);

	--this->next;
	this->items[this->next].~ItemType();
}

template< typename Type, uint8_t Capacity >
void Stack< Type, Capacity >::clear(void) // O(n)
{
	for (IndexType i = 0; i < this->next; ++i)
		(&this->items[i])->~ItemType();
	this->next = 0;
}

template< typename Type, uint8_t Capacity >
bool Stack< Type, Capacity >::contains(const typename Stack< Type, Capacity >::ItemType & item) const // O(n)
{
	return this->indexOf(item) != -1;
}

template< typename Type, uint8_t Capacity >
typename Stack< Type, Capacity >::IndexOfType Stack< Type, Capacity >::indexOf(const typename Stack< Type, Capacity >::ItemType & item) const // O(n)
{
	for (IndexType i = 0; i < this->next; ++i)
		if (this->items[i] == item)
			return i;
	return -1;
}

template< typename Type, uint8_t Capacity >
typename Stack< Type, Capacity >::ItemType & Stack< Type, Capacity >::operator [] (const typename Stack< Type, Capacity >::IndexType index) // O(1)
{
	//DEBUG_ASSERT(index < this->GetCapacity());
	//DEBUG_ASSERT(index < this->next);

	return this->items[index];
}

template< typename Type, uint8_t Capacity >
const typename Stack< Type, Capacity >::ItemType & Stack< Type, Capacity >::operator [] (const typename Stack< Type, Capacity >::IndexType index) const // O(1)
{
	//DEBUG_ASSERT(index < this->GetCapacity());
	//DEBUG_ASSERT(index < this->next);

	return this->items[index];
}
