#include <cmrc/cmrc.hpp>
#include <restinio/all.hpp>

CMRC_DECLARE(ServerResources);

int main()
{
    auto ResourceFS = cmrc::ServerResources::get_filesystem();

    restinio::run(
    restinio::on_this_thread()
    .port(8080)
    .address("localhost")
    .request_handler([ResourceFS](auto Request) 
    {
        auto File = ResourceFS.open("Resources/index.html");
        std::string FileData(File.begin(), File.end());
        return Request->create_response().set_body(FileData).done();
    }));

    return 0;
}
