#include <spdlog/spdlog.h>
#include <scope_exit.h>

import scope_exit;

int main()
{
    spdlog::set_pattern("[%C-%m-%d %T.%e] [%^%L%$] [t:%6t] [%-8!!:%4#] %v");

    return 0;
}
