#pragma once

#include "Includes/View.gen.h"

template<typename Observer>
class ObservableInterface
{
public:
    using ObserverType = Observer;
public:
    virtual void registerObserver(ObserverType *observer) = 0;
    virtual void unregisterObserver(ObserverType *observer) = 0;
};

template<typename Observer>
class Observable
{
public:
    using ObserverType = Observer;
protected:
    Array<ObserverType *> observers;
public:
    void registerObserver(ObserverType *observer) { observers.append(observer); }
    void unregisterObserver(ObserverType *observer) { observers.erase(std::find(observers.begin(), observers.end(), observer)); }
};

namespace UI
{

template<typename Adapter, typename BaseView = View>
class DataView : public BaseView
{
CLASSGEN_GENERATED_REGION_OBJECT
CLASSGEN_END_REGION
public:
    using AdapterType = Adapter;
private:
    AdapterType *adapter = nullptr;
public:

    virtual AdapterType *getAdapter() const
    {
        return adapter;
    }

    virtual void setAdapter(AdapterType *adapter)
    {
        /*if (this->adapter)
        {
        this->adapter->unregisterObserver(this);
        }*/

        this->adapter = adapter;

        /*if (this->adapter)
        {
        this->adapter->registerObserver(this);
        }*/
    }
};

}