#pragma once

#include "AMeta.h"
#include "AMemory.h"
#include "AAssert.h"

enum class ADelegateType
{
    Null,
    Method,
    WeakMethod,
    SharedMethod,
    Functor,
    Function
};

template<typename Type>
class ADelegate;

template<typename ReturnType, typename ...Arguments>
class ADelegate<ReturnType(Arguments...)>
{

    class Void
    {
        virtual ~Void() {}
    };

    class DelegateData
    {

    public:

        virtual ~DelegateData() {}
        virtual DelegateData *copy() const = 0;
        virtual bool isNull() const { return false; }
        virtual bool isValid() const { return true; }
        virtual ReturnType operator()(Arguments ...arguments) const = 0;

    };

    DelegateData *delegateData = nullptr;
    ADelegateType delegateType = ADelegateType::Null;

public:

    static const ADelegate<ReturnType(Arguments...)> &EmptyDelegate()
    {
        static ADelegate<ReturnType(Arguments...)> emptyDelegate;
        return emptyDelegate;
    }

    ADelegate() {}
    ADelegate(std::nullptr_t) {}

    template<typename Type, typename OtherReturnType, typename ...OtherArguments>
    ADelegate(Type *object, OtherReturnType (Type::*method)(OtherArguments...))
    {
        static_assert(std::is_convertible<OtherReturnType, ReturnType>::value, "Return types is not convertible");
        typedef typename AMeta::isCallableArguments<OtherReturnType(OtherArguments...)>:: template withArguments<ReturnType(Arguments...)> expression;
        static_assert(expression::value, "Arguments of the method is not convertible");

        assign(ADelegateType::Method, new MethodDataWithOtherArguments<Type, OtherReturnType, OtherArguments...>(object, method));
    }

    template<typename Type, typename OtherReturnType, typename ...OtherArguments>
    ADelegate(const WeakReference<Type> &object, OtherReturnType (Type::*method)(OtherArguments...))
    {
        static_assert(std::is_convertible<OtherReturnType, ReturnType>::value, "Return types is not convertible");
        typedef typename AMeta::isCallableArguments<OtherReturnType(OtherArguments...)>:: template withArguments<ReturnType(Arguments...)> expression;
        static_assert(expression::value, "Arguments of the method is not convertible");

        AAssert(object.data(), "Weak pointer is null");

        assign(ADelegateType::WeakMethod, new WeakMethodDataWithOtherArguments<Type, OtherReturnType, OtherArguments...>(object, method));
    }

    template<typename Type, typename OtherReturnType, typename ...OtherArguments>
    ADelegate(const SharedReference<Type> &object, OtherReturnType (Type::*method)(OtherArguments...))
    {
        static_assert(std::is_convertible<OtherReturnType, ReturnType>::value, "Return types is not convertible");
        typedef typename AMeta::isCallableArguments<OtherReturnType(OtherArguments...)>:: template withArguments<ReturnType(Arguments...)> expression;
        static_assert(expression::value, "Arguments of the function is not convertible");

        AAssert(object.get(), "Shared pointer is null");

        assign(ADelegateType::SharedMethod, new SharedMethodDataWithOtherArguments<Type, OtherReturnType, OtherArguments...>(object, method));
    }

    template<typename Functor>
    ADelegate(Functor &&functor)
    {
        typedef typename std::remove_reference<Functor>::type FunctorType;
        static_assert(AMeta::isCallable<FunctorType>::value, "The Function type must be a callable functor");

        assign(ADelegateType::Functor, new FunctorData<FunctorType>(std::forward<Functor>(functor)));
    }

    template<typename OtherReturnType, typename ...OtherArguments>
    ADelegate(OtherReturnType (*function)(OtherArguments...)): delegateType()
    {
        static_assert(std::is_convertible<OtherReturnType, ReturnType>::value, "Return types is not convertible");
        typedef typename AMeta::isCallableArguments<OtherReturnType(OtherArguments...)>:: template withArguments<ReturnType(Arguments...)> expression;
        static_assert(expression::value, "Arguments of the function is not convertible");

        assign(ADelegateType::Function, new FunctionDataWithOtherArguments<OtherReturnType, OtherArguments...>(function));
    }

    ADelegate(const ADelegate &delegate)
    {
        if(!delegate)
        {
            assignNull();
            return;
        }

        copy(delegate);
    }

    ADelegate(ADelegate &delegate): ADelegate(static_cast<const ADelegate &>(delegate)) {}

    ADelegate(ADelegate &&delegate)
    {
        if(!delegate)
        {
            assignNull();
            return;
        }

        move(std::move(delegate));
    }

    ~ADelegate() { free(); }

    void set(std::nullptr_t)
    {
        free();
        assignNull();
    }

    template<typename Type, typename OtherReturnType, typename ...OtherArguments>
    void set(Type *object, OtherReturnType (Type::*method)(OtherArguments...))
    {
        static_assert(std::is_convertible<OtherReturnType, ReturnType>::value, "Return types is not convertible");
        typedef typename AMeta::isCallableArguments<OtherReturnType(OtherArguments...)>:: template withArguments<ReturnType(Arguments...)> expression;
        static_assert(expression::value, "Arguments of the method is not convertible");

        free();

        if(!object)
        {
            assignNull();
            return;
        }

        assign(ADelegateType::Method, new MethodDataWithOtherArguments<Type, OtherReturnType, OtherArguments...>(object, method));
    }

    template<typename Type, typename OtherReturnType, typename ...OtherArguments>
    void set(const WeakReference<Type> &object, OtherReturnType (Type::*method)(OtherArguments...))
    {
        static_assert(std::is_convertible<OtherReturnType, ReturnType>::value, "Return types is not convertible");
        typedef typename AMeta::isCallableArguments<OtherReturnType(OtherArguments...)>:: template withArguments<ReturnType(Arguments...)> expression;
        static_assert(expression::value, "Arguments of the method is not convertible");

        free();

        AAssert(object, "Weak pointer is null");

        assign(ADelegateType::WeakMethod, new WeakMethodDataWithOtherArguments<Type, OtherReturnType, OtherArguments...>(object, method));
    }

    template<typename Type, typename OtherReturnType, typename ...OtherArguments>
    void set(const SharedReference<Type> &object, OtherReturnType (Type::*method)(OtherArguments...))
    {
        static_assert(std::is_convertible<OtherReturnType, ReturnType>::value, "Return types is not convertible");
        typedef typename AMeta::isCallableArguments<OtherReturnType(OtherArguments...)>:: template withArguments<ReturnType(Arguments...)> expression;
        static_assert(expression::value, "Arguments of the method is not convertible");

        free();

        AAssert(object, "Shared pointer is null");

        assign(ADelegateType::SharedMethod, new SharedMethodDataWithOtherArguments<Type, OtherReturnType, OtherArguments...>(object, method));
    }

    template<typename Functor>
    void set(Functor &&functor)
    {
        typedef typename std::remove_reference<Functor>::type FunctorType;
        static_assert(AMeta::isCallable<FunctorType>::value, "The Function type must be a callable functor");

        free();

        assign(ADelegateType::Functor, new FunctorData<FunctorType>(std::forward<Functor>(functor)));
    }

    template<typename OtherReturnType, typename ...OtherArguments>
    void set(OtherReturnType (*function)(OtherArguments...))
    {
        static_assert(std::is_convertible<OtherReturnType, ReturnType>::value, "Return types is not convertible");
        typedef typename AMeta::isCallableArguments<OtherReturnType(OtherArguments...)>:: template withArguments<ReturnType(Arguments...)> expression;
        static_assert(expression::value, "Arguments of the function is not convertible");

        free();

        assign(ADelegateType::Function, new FunctionDataWithOtherArguments<OtherReturnType, OtherArguments...>(function));
    }

    void clear()
    {
        free();
        assignNull();
    }

    ADelegateType type() const { return delegateType; }

    bool isNull() const { return delegateType == ADelegateType::Null || delegateData->isNull(); }
    bool isValid() const { return delegateType != ADelegateType::Null && delegateData->isValid(); }

    bool isMethod() const { return delegateType == ADelegateType::Method; }
    bool isWeakMethod() const { return delegateType == ADelegateType::WeakMethod; }
    bool isSharedMethod() const { return delegateType == ADelegateType::SharedMethod; }
    bool isFunctor() const { return delegateType == ADelegateType::Functor; }
    bool isFunction() const { return delegateType == ADelegateType::Function; }

    ADelegate &operator =(std::nullptr_t)
    {
        free();
        assignNull();

        return *this;
    }

    template<typename Functor>
    ADelegate &operator =(const Functor &functor)
    {
        static_assert(AMeta::isCallable<Functor>::value, "Type must be a functor function");

        set(functor);

        return *this;
    }

    ADelegate &operator =(ReturnType (*function)(Arguments...))
    {
        set(function);

        return *this;
    }

    template<typename OtherReturnType, typename ...OtherArguments>
    ADelegate &operator =(OtherReturnType (*function)(OtherArguments...))
    {
        static_assert(std::is_convertible<OtherReturnType, ReturnType>::value, "Return types is not convertible");
        typedef typename AMeta::isCallableArguments<OtherReturnType(OtherArguments...)>:: template withArguments<ReturnType(Arguments...)> expression;
        static_assert(expression::value, "Arguments of the function is not convertible");

        set(function);

        return *this;
    }

    ADelegate &operator =(const ADelegate &delegate)
    {
        if(!delegate)
        {
            clear();
            return *this;
        }

        free();
        copy(std::move(delegate));
        return *this;
    }

    ADelegate &operator =(ADelegate &delegate)
    {
        return *this = static_cast<const ADelegate &>(delegate);
    }

    ADelegate &operator =(ADelegate &&delegate)
    {
        if(!delegate)
        {
            clear();
            return *this;
        }

        free();
        move(std::move(delegate));
        return *this;
    }

    bool operator ==(const ADelegate &delegate) const
    {
        return delegateType == delegate.delegateType && delegateData == delegate.delegateData;
    }

    operator bool() const { return isValid(); }

    ReturnType operator()(Arguments ...arguments) const
    {
        AAssert(isValid(), "Delegate should be valid for call");
        return (*delegateData)(std::forward<Arguments>(arguments)...);
    }

    void tryExecute(Arguments ...arguments) const
    {
        if(isValid())
        {
            (*this)(arguments...);
        }
    }

    /*void tryExecute(const ADelegate<void(ReturnType &&value)> &callback, Arguments ...arguments) const
    {
        if(isValid())
        {
            AAssert(callback, "Callback should be valid, use an overloaded method if you don't need the callback");
            callback((*this)(arguments...));
        }
    }*/

private:

    void assignNull()
    {
        assign(ADelegateType::Null, nullptr);
    }

    void assign(const ADelegateType type, DelegateData *data)
    {
        delegateType = type;
        delegateData = data;
    }

    void copy(const ADelegate &delegate)
    {
        delegateType = delegate.delegateType;
        delegateData = delegate.delegateData->copy();
    }

    void move(ADelegate &&delegate)
    {
        delegateType = delegate.delegateType;
        delegateData = delegate.delegateData;
        delegate.delegateData = nullptr;
        delegate.delegateType = ADelegateType::Null;
    }

    void free() {
        if(delegateType != ADelegateType::Null)
            delete delegateData;
    }

    template <typename Functor>
    class FunctorData : public DelegateData
    {

    public:
        template<typename FunctionType>
        FunctorData(FunctionType &&functor):functor(std::forward<FunctionType>(functor)) {}
        DelegateData *copy() const { return new FunctorData(*this); }

        ReturnType operator()(Arguments ...arguments) const
        {
            return functor(std::forward<Arguments>(arguments)...);
        }

    private:

        Functor functor;

    };

    template<typename OtherReturnType, typename ...OtherArguments>
    class FunctionDataWithOtherArguments : public DelegateData
    {

    public:

        FunctionDataWithOtherArguments(OtherReturnType (*function)(OtherArguments...)):functionPointer(function) {}
        DelegateData *copy() const { return new FunctionDataWithOtherArguments<OtherReturnType, OtherArguments...>(*this); }

        ReturnType operator()(Arguments ...arguments) const
        {
            return AMeta::call<OtherReturnType(OtherArguments...)>:: template withType<ReturnType(Arguments...)>::andArguments(functionPointer, std::forward<Arguments>(arguments)...);
        }

    private:

        OtherReturnType (*functionPointer)(OtherArguments...);
    };

    template<typename Type, typename OtherReturnType, typename ...OtherArguments>
    class MethodDataWithOtherArguments : public DelegateData
    {

    public:

        MethodDataWithOtherArguments(Type *object, OtherReturnType (Type::*method)(OtherArguments...)):objectPointer(object), methodPointer(method) {}
        DelegateData *copy() const { return new MethodDataWithOtherArguments<Type, OtherReturnType, OtherArguments...>(*this); }

        ReturnType operator()(Arguments ...arguments) const
        {
            return AMeta::call<OtherReturnType(OtherArguments...)>:: template withType<ReturnType(Arguments...)>::andArguments(objectPointer, methodPointer, std::forward<Arguments>(arguments)...);
        }

    private:

        Type *objectPointer;
        OtherReturnType (Type::*methodPointer)(OtherArguments...);

    };

    template<typename Type, typename OtherReturnType, typename ...OtherArguments>
    class WeakMethodDataWithOtherArguments : public DelegateData
    {

    public:

        WeakMethodDataWithOtherArguments(const WeakReference<Type> &object, OtherReturnType (Type::*method)(OtherArguments...)):objectPointer(object), methodPointer(method) {}
        DelegateData *copy() const { return new WeakMethodDataWithOtherArguments<Type, OtherReturnType, OtherArguments...>(*this); }
        bool isNull() const { return objectPointer.lock() == nullptr; }
        bool isValid() const { return objectPointer.lock() != nullptr; }

        ReturnType operator()(Arguments ...arguments) const
        {
            return AMeta::call<OtherReturnType(OtherArguments...)>:: template withType<ReturnType(Arguments...)>::andArguments(objectPointer.data(), methodPointer, std::forward<Arguments>(arguments)...);
        }

    private:

        mutable WeakReference<Type> objectPointer;
        OtherReturnType (Type::*methodPointer)(OtherArguments...);

    };

    template<typename Type, typename OtherReturnType, typename ...OtherArguments>
    class SharedMethodDataWithOtherArguments : public DelegateData
    {

    public:

        SharedMethodDataWithOtherArguments(const SharedReference<Type> &object, OtherReturnType (Type::*method)(OtherArguments...)):objectPointer(object), methodPointer(method) {}
        DelegateData *copy() const { return new SharedMethodDataWithOtherArguments<Type, OtherReturnType, OtherArguments...>(*this); }
        bool isNull() const { return objectPointer.get() == nullptr; }
        bool isValid() const { return objectPointer.get() != nullptr; }

        ReturnType operator()(Arguments ...arguments) const
        {
            return AMeta::call<OtherReturnType(OtherArguments...)>:: template withType<ReturnType(Arguments...)>::andArguments(objectPointer.get(), methodPointer, std::forward<Arguments>(arguments)...);
        }

    private:

        mutable SharedReference<Type> objectPointer;
        OtherReturnType (Type::*methodPointer)(OtherArguments...);

    };
};
