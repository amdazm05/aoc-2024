#ifndef _UTILS
#define _UTILS
#include <vector>
#include <string_view>

namespace utils{
    std::vector<std::string_view> get_inputs_from_file(std::string_view filepath);
}

#endif /*_UTILS*/