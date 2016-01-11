#pragma once

#include "HttpMessageDef.h"

#include <cpprest/json.h>

class HttpMessageResult : public IHttpMessageResult
{
public:
    HttpMessageResult();
    virtual ~HttpMessageResult();

public:
    /*******************************************************************
    *  描述：解析内容
    *  参数：content 文本内容那个
    *  返回：无
    *******************************************************************/
    virtual void Parse(const std::wstring &content) override;

    /*******************************************************************
    *  描述：是否所有OK
    *  参数：isOk 是否OK
    *  返回：无
    *******************************************************************/
    virtual void SetIsOk(bool isOk) override
    {
        mIsOk = isOk;
    }

    /*******************************************************************
    *  描述：是否所有OK
    *  参数：isOk 是否OK
    *  返回：无
    *******************************************************************/
    virtual bool IsOk() const override
    {
        return mIsOk;
    }


    /*******************************************************************
    *  描述：设置错误码
    *  参数：iErrorCode 错误码，可能为http错误码，可能为内部错误码；
    *  返回：无
    *******************************************************************/
    virtual void SetErrorCode(int iErrorCode) override
    {
        mErrorCode = iErrorCode;
    }

    /*******************************************************************
    *  描述：获取错误码
    *  参数：无
    *  返回：错误码
    *******************************************************************/
    virtual int GetErrorCode() const override
    {
        return mErrorCode;
    }


    /*******************************************************************
    *  描述：设置错误信息
    *  参数：strErrorInfo 错误信息
    *  返回：无
    *******************************************************************/
    virtual void SetErrorInfo(std::wstring strErrorInfo) override
    {
        mErrorInfo = strErrorInfo;
    }

    /*******************************************************************
    *  描述：获取错误信息
    *  参数：无
    *  返回：错误信息
    *******************************************************************/
    virtual std::wstring GetErrorInfo() const override
    {
        return mErrorInfo;
    }

public:
    /*******************************************************************
    *  描述：解析JSON内容
    *  参数：val json内容
    *  返回：无
    *******************************************************************/
    virtual void Parse(const web::json::value &val);

private:
    bool mIsOk;
    int mErrorCode;
    std::wstring mErrorInfo;
};
