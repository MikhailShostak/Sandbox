#pragma once

#include "String.h"

class ATableItem
{
public:

};

class StringItem : public ATableItem
{
public:

};

template<typename Type, typename Size = size_t>
class ATableAdapter
{
public:

    using SizeType = Size;
    using ItemType = Type;

    virtual ~ATableAdapter() {}

    virtual SizeType getGroupsCount() const
    {
        return 0;
    }

    virtual String getGroupTitle(SizeType groupIndex) const
    {
        return String::EmptyString();
    }

    virtual SizeType getRowsCount(SizeType groupIndex) const
    {
        return 0;
    }

    virtual SizeType getColumnsCount(SizeType groupIndex) const
    {
        return 0;
    }

    virtual ItemType getItem(SizeType groupIndex, SizeType rowIndex, SizeType columnIndex) const
    {
        return ItemType();
    }

    virtual void onItemChange(SizeType groupIndex, SizeType rowIndex, SizeType columnIndex, const ItemType &item)
    {

    }

};
