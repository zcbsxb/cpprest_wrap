#include "stdafx.h"
#include "HttpMessageResult.h"

using namespace web;
using namespace web::json;

HttpMessageResult::HttpMessageResult()
: mIsOk(false)
, mErrorCode(-1)
, mErrorInfo()
{
}

HttpMessageResult::~HttpMessageResult()
{
}

void HttpMessageResult::Parse(const std::wstring &content)
{
    try
    {
        auto jsonValue = value::parse(content);

        Parse(jsonValue);

        mIsOk = true;
    }
    catch (...)
    {
        mErrorInfo = L"Parse Json Error.";
    }
}

void HttpMessageResult::Parse(const web::json::value &val)
{

}
