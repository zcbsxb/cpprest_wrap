#pragma once

#include "HttpMessageDef.h"

class HttpMessage : public IHttpMessage
{
public:
    HttpMessage(HttpMessageType messageType);
    virtual ~HttpMessage();

public:
    /*******************************************************************
    *  描述：设置响应结果
    *  参数：result 响应结果
    *  返回：无
    *******************************************************************/
    virtual void SetResult(HttpMessageResultSharedPtr result) override
    {
        mHttpMessageResult = result;
    }

    /*******************************************************************
    *  描述：获取结果
    *  参数：无
    *  返回：结果
    *******************************************************************/
    virtual HttpMessageResultSharedPtr GetResult() const override
    {
        return mHttpMessageResult;
    }


    /*******************************************************************
    *  描述：设置消息类型
    *  参数：type 消息类型
    *  返回：无
    *******************************************************************/
    virtual void SetType(HttpMessageType type) override
    {
        mType = type;
    }

    /*******************************************************************
    *  描述：获取消息类型
    *  参数：无
    *  返回：消息类型
    *******************************************************************/
    virtual HttpMessageType GetType() const override
    {
        return mType;
    }


    /*******************************************************************
    *  描述：设置消息投递类型；
    *  参数：method 消息投递类型：POST,GET等
    *  返回：无
    *******************************************************************/
    virtual void SetMethod(HttpMessageMethod method) override
    {
        mMethod = method;
    }

    /*******************************************************************
    *  描述：设置消息投递类型
    *  参数：无
    *  返回：消息投递类型
    *******************************************************************/
    virtual HttpMessageMethod GetMethod() const override
    {
        return mMethod;
    }


    /*******************************************************************
    *  描述：设置服务器地址
    *  参数：server 服务器地址
    *  返回：无
    *******************************************************************/
    virtual void SetServer(const std::wstring &server) override
    {
        mServer = server;
    }

    /*******************************************************************
    *  描述：获取服务器地址
    *  参数：无
    *  返回：服务器地址
    *******************************************************************/
    virtual std::wstring GetServer() const override
    {
        return mServer;
    }


    /*******************************************************************
    *  描述：设置服务器的基地址
    *  参数：base base地址
    *  返回：无
    *******************************************************************/
    virtual void SetBase(const std::wstring &base) override
    {
        mBase = base;
    }

    /*******************************************************************
    *  描述：获取服务器的基地址
    *  参数：无
    *  返回：base地址
    *******************************************************************/
    virtual std::wstring GetBase() const override
    {
        return mBase;
    }


    /*******************************************************************
    *  描述：设置服务器的实际地址
    *  参数：address 实际地址
    *  返回：无
    *******************************************************************/
    virtual void SetAddress(const std::wstring &address) override
    {
        mAddress = address;
    }

    /*******************************************************************
    *  描述：获取服务器的实际地址
    *  参数：无
    *  返回：实际地址
    *******************************************************************/
    virtual std::wstring GetAddress() const override
    {
        return mAddress;
    }


    /*******************************************************************
    *  描述：添加请求参数
    *  参数：name 参数名；value 参数的值；bPost 是否投递；
    *  返回：无
    *******************************************************************/
    virtual void AddParam(const std::wstring &name, const std::wstring &value, bool bPost) override;

    /*******************************************************************
    *  描述：获取请求参数的值
    *  参数：name 参数名；
    *  返回：参数值
    *******************************************************************/
    virtual std::wstring GetParam(const std::wstring &name) const override;

    /*******************************************************************
    *  描述：获取请求参数列表
    *  参数：无
    *  返回：请求参数列表
    *******************************************************************/
    virtual std::vector<HttpMessageParam> GetParams() const override;

private:
    HttpMessageMethod mMethod;
    HttpMessageType mType;
    std::wstring mServer;
    std::wstring mBase;
    std::wstring mAddress;
    
    std::vector<HttpMessageParam> mVecParams;

    HttpMessageResultSharedPtr mHttpMessageResult;
};