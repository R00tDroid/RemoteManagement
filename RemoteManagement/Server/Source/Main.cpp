#include <cmrc/cmrc.hpp>
#include <filesystem>

#pragma warning(push)
#pragma warning(disable: 4324)
#pragma warning(disable: 4127)
#pragma warning(disable: 4456)
#include <restinio/all.hpp>
#pragma warning(pop)

CMRC_DECLARE(ServerResources);

cmrc::embedded_filesystem* ResourceFS = nullptr;

restinio::request_handling_status_t handler(restinio::request_handle_t Request)
{
    if (restinio::http_method_get() == Request->header().method())
    {
        std::string TargetResource = Request->header().request_target();

        if (TargetResource == "/")
        {
            TargetResource += "index.html";
        }

        TargetResource = "Resources/" + TargetResource;

        if (ResourceFS->exists(TargetResource))
        {
            cmrc::file File = ResourceFS->open(TargetResource);
            std::string FileData(File.begin(), File.end());

            std::string Extension = std::filesystem::path(TargetResource).extension().string();
            std::string ContentType = "";

            if (Extension == ".html")
            {
                ContentType = "text/html; charset=utf-8";
            }

            auto Response = Request->create_response();
            Response.append_header(restinio::http_field::server, "RemoteManagement WebInterface");
            Response.append_header_date_field();
            Response.append_header(restinio::http_field::content_type, ContentType);
            Response.set_body(FileData);
            Response.done();;

            return restinio::request_accepted();
        }
    }

    return restinio::request_rejected();
}

int main()
{
    cmrc::embedded_filesystem FS = cmrc::ServerResources::get_filesystem();
    ResourceFS = &FS;

    restinio::run(
        restinio::on_this_thread()
        .port(8080)
        .address("localhost")
        .request_handler(handler));

    return 0;
}
