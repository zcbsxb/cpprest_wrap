#include "stdafx.h"
#include "HttpMessage.h"
#include "HttpDef.h"

#include <algorithm>

HttpMessage::HttpMessage(HttpMessageType messageType)
: mMethod(METHOD_POST)
, mType(messageType)
, mServer()
, mBase()
, mAddress()
, mVecParams()
{
}

HttpMessage::~HttpMessage()
{
}

void HttpMessage::AddParam(const std::wstring &name, const std::wstring &value, bool bPost)
{
    HttpMessageParam param;
    param.mName = name;
    param.mValue = value;
    param.mNeedPost = bPost;

    mVecParams.emplace_back(std::move(param));
}

std::wstring HttpMessage::GetParam(const std::wstring &name) const
{
    auto &iter = std::find_if(mVecParams.begin(), mVecParams.end(), [&](const HttpMessageParam &param)
    {
        return param.mName == name;
    });

    if (iter == mVecParams.end())
    {
        return std::wstring();
    }

    return iter->mValue;
}

std::vector<HttpMessageParam> HttpMessage::GetParams() const
{
    return mVecParams;
}