#pragma once

template<typename Type>
using UniqueReference = std::unique_ptr<Type>;

template<typename Type>
using SharedReference = std::shared_ptr<Type>;

template<typename Type>
using WeakReference = std::weak_ptr<Type>;
