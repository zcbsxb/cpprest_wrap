#pragma once

#include "HttpMessageDef.h"

#include <cpprest/http_client.h>
#include <cpprest/http_msg.h>

class HttpMessageRequest
{
public:
    HttpMessageRequest();
    virtual ~HttpMessageRequest();

public:
    void Begin();

    void End();

private:
    void RequestPost();
    void RequestGet();

    void ProcessResponse(pplx::task<web::http::http_response> httpResponseTask);

    web::http::client::http_client CreateClient(const std::wstring &serverAddress);

    virtual pplx::task<web::http::http_response> ClientHandler(
        web::http::http_request request,
        std::shared_ptr<web::http::http_pipeline_stage> nextStage);

    std::wstring GetUserAgent();

private:
    HttpMessageSharedPtr mHttpMessage;

    pplx::task<void> mResponseTask;
};