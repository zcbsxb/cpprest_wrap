#include "stdafx.h"
#include "HttpMessageRequest.h"

#include <functional>
#include <cpprest/version.h>

using namespace std;
using namespace std::placeholders;

using namespace pplx;
using namespace pplx::streams;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace utility;
using namespace utility::conversions;

#define STRINGIFY(x) _XPLATSTR(#x)
#define TOSTRING(x) STRINGIFY(x)
#define USERAGENT _XPLATSTR("cpprestsdk/") TOSTRING(CPPREST_VERSION_MAJOR) _XPLATSTR(".") TOSTRING(CPPREST_VERSION_MINOR) _XPLATSTR(".") TOSTRING(CPPREST_VERSION_REVISION)

HttpMessageRequest::HttpMessageRequest()
{
}

HttpMessageRequest::~HttpMessageRequest()
{
}

void HttpMessageRequest::Begin()
{
    switch (mHttpMessage->GetMethod())
    {
    case METHOD_POST:
        RequestPost();
        break;
    case METHOD_GET:
        RequestGet();
        break;
    default:
        break;
    }
}

void HttpMessageRequest::RequestPost()
{
    auto httpClient = CreateClient(mHttpMessage->GetAddress());

    // 构造请求地址
    auto queryUri = mHttpMessage->GetBase() + mHttpMessage->GetAddress();
    uri_builder builder(string_t(queryUri.c_str()));

    // 构造请求内容
    std::wstring body;
    auto params = mHttpMessage->GetParams();
    for (auto param : params)
    {
        if (param.mNeedPost)
        {
            body.append(param.mName);
            body.append(U("="));
            body.append(uri::encode_data_string(string_t{ param.mValue }));
            body.append(U("&"));
        }
    }

    auto httpResponse = httpClient.request(methods::POST, builder.to_string(), body, U("application/x-www-form-urlencoded"));
}

void HttpMessageRequest::RequestGet()
{
    auto httpClient = CreateClient(mHttpMessage->GetAddress());

    // 构造请求URI
    auto queryUri = mHttpMessage->GetBase() + mHttpMessage->GetAddress();
    uri_builder builder(string_t(queryUri.c_str()));

    // 构造请求内容
    auto params = mHttpMessage->GetParams();
    for (auto param : params)
    {
        if (param.mNeedPost)
        {
            builder.append_query(string_t(param.mName.c_str()), uri::encode_data_string(string_t{ param.mValue }));
        }
    }

    auto httpResponse = httpClient.request(methods::GET, builder.to_string());
}

void HttpMessageRequest::ProcessResponse(task<http_response> httpResponseTask)
{
    mResponseTask = httpResponseTask
        .then([this](http_response &response) mutable
    {
        auto httpResult = mHttpMessage->GetResult();

        httpResult->SetErrorCode(response.status_code());
        httpResult->SetErrorInfo(response.reason_phrase());

        return response.extract_string();
    })
        .then([this](string_t &str)
    {
        auto httpResult = mHttpMessage->GetResult();
        httpResult->Parse(str);
    });
}

void HttpMessageRequest::End()
{
    try
    {
        // 等待请求结束
        if (mResponseTask.wait() == task_group_status::canceled)
        {
            // 用户取消任务
            throw exception("User cancelled.");
        }
    }
    catch (const http_exception &ex)
    {
        auto &errorCode = ex.error_code();

        auto httpResult = mHttpMessage->GetResult();

        httpResult->SetErrorCode(errorCode.value());
        httpResult->SetErrorInfo(to_string_t(errorCode.message()));
    }
    catch (const exception &ex)
    {
        auto httpResult = mHttpMessage->GetResult();

        httpResult->SetErrorInfo(to_string_t(ex.what()));
    }
    catch (...)
    {
        auto httpResult = mHttpMessage->GetResult();

        httpResult->SetErrorInfo(U("exception with no reason"));
    }
}

web::http::client::http_client HttpMessageRequest::CreateClient(const std::wstring &serverAddress)
{
    utility::seconds timeout{ 10 };

    http_client_config config;
    
    http_client client{ string_t(serverAddress.c_str()), config };
    client.add_handler(bind(&HttpMessageRequest::ClientHandler, this, _1, _2));

    return client;
}

pplx::task<web::http::http_response> HttpMessageRequest::ClientHandler(
    web::http::http_request request,
    std::shared_ptr<web::http::http_pipeline_stage> nextStage)
{
    auto iter = request.headers().find(header_names::user_agent);
    if (iter == cend(request.headers()))
    {
        request.headers().add(header_names::user_agent, GetUserAgent());
    }
    else
    {
        iter->second = GetUserAgent();
    }

    return nextStage->propagate(request);
}

std::wstring HttpMessageRequest::GetUserAgent()
{
    static string_t userAgent;

    if (userAgent.empty())
    {
        wostringstream oss;
        oss << USERAGENT;
        oss << U(", ");
        oss << "HttpClientTest";
        oss << U(" (");
        oss << U(" OS ");
        oss << U(")");

        userAgent = oss.str();
    }

    return userAgent;
}