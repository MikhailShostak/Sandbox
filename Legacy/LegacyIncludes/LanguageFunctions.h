#pragma once

#include <Foundation.pch.hpp>
#include <Data>
#include <System.pch.hpp>
#include <BuildSystem.pch.hpp>

#if !NDEBUG
#define BOOST_STACKTRACE_USE_WINDBG 1
//Ole32.lib
//dbgeng.lib
#endif

//namespace std
//{
//
//template< class F, class... ArgTypes >
//using result_of = invoke_result<F, ArgTypes...>;
//
//}

//#include <Async.h>

/*template<typename ReturnType, typename ContainerType>
ReturnType Read(std::vector<ContainerType> &&Containers, ReturnType &&DefaultValue)
{
	T r;
	for(auto c : Containers)
	{

	}
}*/

template<typename ValueType>
inline void deserialize(const AJSONValue &data, ValueType &value)
{
	fromJSONValue(data, value);
}

template<typename ValueType>
inline void deserialize(const AJSONObject &data, ValueType &value)
{
	deserialize(AJSONValue(data), value);
}

template<typename ReturnType>
inline ReturnType deserialize(const AJSONValue &value)
{
	ReturnType result;
	deserialize(value, result);
	return result;
}

template<typename ReturnType>
inline ReturnType deserialize(const AJSONObject &object)
{
	return deserialize<ReturnType>(AJSONValue(object));
}

namespace BuildSystem
{

struct Toolchain
{
	BuildingSettings settings;
};

}


//inline void print_stack() {
//    Log::Print(boost::stacktrace::stacktrace());
//}

//inline void print_thread_id(std::string tag) {
//	Log::Print("[{}] Current Thread: {}", tag, std::this_thread::get_id());
//}

/*template<typename Awaitable>
class AwaitableTask
{
public:
	Awaitable awaitable;
};*/

struct TaskDescription
{
	std::string name;
	std::string description;
};

/*
class Action
{
public:
	String category;
	String title;
	String description;
	String logs;
	AError error;
	ActionStatus status = ActionStatus::Scheduled;

	virtual AError onRun()
	{

	}

	virtual ActionStatus syncRun()
	{
		status = ActionStatus::Scheduled;
		error = onRun();
		status = error ? Failed : Succeeded;
		return status;
	}

	async<ActionStatus> asyncRun()
	{
		co_await tm.AsyncWorkers.service.schedule();
		co_return syncRun();
	}
};

class ParallelActionGroup
{
public:
	std::vector<Action> actions;
	virtual AError onRun()
	{
		for()
		{
			
		}
	}
};

class SequentialActionGroup
{
public:
	virtual AError onRun()
	{

	}
	std::vector<Action> actions;
};*/

template<typename T1, typename T2>
inline auto merge_data_nodes_recursively(T1 &data_set1, const T2 &data_set2) -> decltype(data_set1)
{
	for (auto[k, v] : data_set2)
	{
		AJSONValue existed_value;
		if(data_set1.read(k, existed_value))
		{
			if(v.isObject() && existed_value.isObject())
			{
				data_set1.insert(k, merge_data_nodes_recursively(v.asObject(), existed_value.asObject()));
			}
			else if (v.isString() && existed_value.isString())
			{
				data_set1.insert(k, String(Str::Format(v.asString(), Str::Args(Map<String, String>({ { "Inherit", existed_value.asString() } })))));
			}
			else
			{
				data_set1.insert(k, v);
			}
		}
		else
		{
			data_set1.insert(k, v);
		}
	}
	return data_set1;
}

template<typename T>
inline auto merge_data_nodes_recursively(const T &data_sets)
{
	AJSONObject result;// = data_sets[0];
	for (const auto &data_set : data_sets/* | rngv::drop(1)*/)
	{
		merge_data_nodes_recursively(result, data_set);
	}
	return result;
}

class Application
{
public:

	inline void run()
	{

	}
};

inline void Print()
{
	
}

inline void HelloWorld()
{
	//const std::source_location& location = std::source_location::current();
	//ALogMessage("", "Hello World from %s at %s:%d:%d!", location.function_name(), location.file_name(), location.line(), location.column());
}

inline int SuccessCode()
{
	return 0;
}

inline int ErrorCode()
{
	return 1;
}
