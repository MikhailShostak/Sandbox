#pragma once

#include <vector>
#include <typeinfo>

template<typename View, typename Model>
class ViewFactory
{

  struct Allocator
  {
    std::size_t model;
    View *(*alloc)(Model *model);
  };

  template<typename ExtendedView, typename ExtendedModel>
  static View *allocate(Model *model)
  {
        return new ExtendedView(static_cast<ExtendedModel *>(model));
  }

  std::vector<Allocator> allocators;

public:

  template<typename ExtendedView, typename ExtendedModel>
  void append()
  {
      allocators.push_back({typeid(ExtendedModel *).hash_code(), &allocate<ExtendedView, ExtendedModel>});
  }

  View *alloc(Model *model) const
  {
    for(auto &allocator : allocators)
    {
        if(typeid(model).hash_code() == allocator.model)
        {
          return allocator.alloc(model);
        }
    }
    return nullptr;
  }

};
