#include <cmrc/cmrc.hpp>

CMRC_DECLARE(ServerResources);

int main()
{
    auto ResourceFS = cmrc::ServerResources::get_filesystem();
    return 0;
}
