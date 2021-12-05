#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceBegin
//CLASSGEN END REGION
#include <Foundation>
enum class OSFileSystemItemFlags
{
    Openable = 1 << 0,
    Renameable = 1 << 1,
    Removeable = 1 << 2,
    Closable = 1 << 3,
};

inline OSFileSystemItemFlags operator |(OSFileSystemItemFlags l, OSFileSystemItemFlags r)
{
    return OSFileSystemItemFlags(uint32_t(l) | uint32_t(r));
}

inline OSFileSystemItemFlags operator &(OSFileSystemItemFlags l, OSFileSystemItemFlags r)
{
    return OSFileSystemItemFlags(uint32_t(l) & uint32_t(r));
}

class OSFileSystemItem;

class OSFileSystemItemObserver
{
public:
    void onItemSelect(OSFileSystemItem *item);
};

class OSFileSystemItem
{
    String text;
    APath path;

    OSFileSystemItemFlags flags;

    OSFileSystemItem *parent = nullptr;
    Array<SharedReference<OSFileSystemItem>> items;

    Array<OSFileSystemItemObserver *> observers;

public:

    bool isExpanded = false;

    void removeObserver(OSFileSystemItemObserver *observer)
    {
        ArrayUtils::Remove(observers, observer);
    }

    void addObserver(OSFileSystemItemObserver *observer)
    {
        observers.push_back(observer);
    }

    const String &getText() const
    {
        return this->text;
    }

    void setText(const String &text)
    {
        this->text = text;
    }

    void setText(String &&text)
    {
        this->text = std::move(text);
    }

    const APath &getPath() const
    {
        return this->path;
    }

    void setPath(const APath &path)
    {
        this->path = path;
    }

    void setPath(APath &&path)
    {
        this->path = std::move(path);
    }

    OSFileSystemItemFlags getFlags()
    {
        return this->flags;
    }

    void setFlags(OSFileSystemItemFlags flags)
    {
        this->flags = flags;
    }

    OSFileSystemItem *getParent() const
    {
        return this->parent;
    }

    const Array<SharedReference<OSFileSystemItem>> &getItems() const
    {
        return this->items;
    }

    void setItems(const Array<SharedReference<OSFileSystemItem>> &items)
    {
        for(auto &item : items)
        {
            item->parent = nullptr;
        }
        this->items = items;
        for(auto &item : items)
        {
            item->parent = this;
        }
    }

    void addItem(const SharedReference<OSFileSystemItem> &item)
    {
        if(item->parent)
        {
            ArrayUtils::Remove(parent->items, item);
        }
        this->items.push_back(item);
        item->parent = this;
    }

    void addItems(const Array<SharedReference<OSFileSystemItem>> &items)
    {
        for(auto &item : items)
        {
            addItem(item);
        }
    }

    void removeItem(const SharedReference<OSFileSystemItem> &item)
    {
        if(ArrayUtils::Contains(this->items, item))
        {
            item->parent = nullptr;
        }
        ArrayUtils::Remove(parent->items, item);
    }

    void removeItems(const Array<SharedReference<OSFileSystemItem>> &items)
    {
        for(auto &item : items)
        {
            removeItem(item);
        }
    }

    void removeFromParent()
    {
        if(parent)
        {
            for(auto it = parent->items.begin(); it != parent->items.end(); ++it)
            {
                if(it->get() == this)
                {
                    parent->items.erase(it);
                    break;
                }
            }
            parent = nullptr;
        }
    }
};
//CLASSGEN GENERATED REGION: NamespaceEnd
//CLASSGEN END REGION
