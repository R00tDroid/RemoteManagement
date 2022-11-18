#include "Webserver.h"
#include "Resources.h"
#include <filesystem>

restinio::request_handling_status_t RequestHandler(restinio::request_handle_t Request)
{
    if (restinio::http_method_get() == Request->header().method())
    {
        std::string TargetResource = Request->header().request_target();

        if (TargetResource == "/")
        {
            TargetResource += "index.html";
        }

        TargetResource = "Resources/" + TargetResource;

        if (ResourceFS().exists(TargetResource))
        {
            cmrc::file File = ResourceFS().open(TargetResource);
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
            Response.done();

            return restinio::request_accepted();
        }
    }

    return restinio::request_rejected();
}

void WebServer::Init()
{
    Server = new ServerType
    {
       restinio::own_io_context(),
       [](auto& settings)
        {
            settings.port(8080);
            settings.address("localhost");
            settings.request_handler(RequestHandler);
        }
    };

    ServerThread = new std::thread
    {
        [this]
        {
            restinio::run(restinio::on_thread_pool(4, restinio::skip_break_signal_handling(), *Server));
        }
    };
}

void WebServer::Destroy()
{
    if (Server != nullptr) 
    {
        restinio::initiate_shutdown(*Server);
        ServerThread->join();

        delete Server;
        delete ServerThread;
        Server = nullptr;
        ServerThread = nullptr;
    }
}
