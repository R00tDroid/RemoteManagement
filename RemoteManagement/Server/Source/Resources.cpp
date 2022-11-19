#include "Resources.h"

CMRC_DECLARE(ServerResources);

cmrc::embedded_filesystem ResourceFS()
{
    return cmrc::ServerResources::get_filesystem();
}
