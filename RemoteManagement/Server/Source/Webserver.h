#pragma once

#pragma warning(push)
#pragma warning(disable: 4324)
#pragma warning(disable: 4127)
#pragma warning(disable: 4456)
#include <restinio/all.hpp>
#pragma warning(pop)

class WebServer
{
public:
    void Init();
    void Destroy();

private:
    typedef restinio::http_server_t<restinio::default_traits_t> ServerType;
    ServerType* Server = nullptr;
    std::thread* ServerThread = nullptr;
};
