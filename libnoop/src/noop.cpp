#include "noop/noop.h"
#include <fmt/format.h>
namespace noop
{
    bool cpp_hello()
    {
        fmt::print("Hello from CPP!\n");
        return true;
    }
}