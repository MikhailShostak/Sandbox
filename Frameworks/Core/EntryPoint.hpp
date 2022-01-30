
namespace Core::Details
{
UniqueReference<Core::Application> CreateMainApplication();
}

#define DEFINE_MAIN_APPLICATION(name)\
namespace Core::Details\
{\
UniqueReference<Core::Application> CreateMainApplication()\
{\
    return std::make_unique<name>();\
}\
}\
