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
    *  ��������������
    *  ������content �ı������Ǹ�
    *  ���أ���
    *******************************************************************/
    virtual void Parse(const std::wstring &content) override;

    /*******************************************************************
    *  �������Ƿ�����OK
    *  ������isOk �Ƿ�OK
    *  ���أ���
    *******************************************************************/
    virtual void SetIsOk(bool isOk) override
    {
        mIsOk = isOk;
    }

    /*******************************************************************
    *  �������Ƿ�����OK
    *  ������isOk �Ƿ�OK
    *  ���أ���
    *******************************************************************/
    virtual bool IsOk() const override
    {
        return mIsOk;
    }


    /*******************************************************************
    *  ���������ô�����
    *  ������iErrorCode �����룬����Ϊhttp�����룬����Ϊ�ڲ������룻
    *  ���أ���
    *******************************************************************/
    virtual void SetErrorCode(int iErrorCode) override
    {
        mErrorCode = iErrorCode;
    }

    /*******************************************************************
    *  ��������ȡ������
    *  ��������
    *  ���أ�������
    *******************************************************************/
    virtual int GetErrorCode() const override
    {
        return mErrorCode;
    }


    /*******************************************************************
    *  ���������ô�����Ϣ
    *  ������strErrorInfo ������Ϣ
    *  ���أ���
    *******************************************************************/
    virtual void SetErrorInfo(std::wstring strErrorInfo) override
    {
        mErrorInfo = strErrorInfo;
    }

    /*******************************************************************
    *  ��������ȡ������Ϣ
    *  ��������
    *  ���أ�������Ϣ
    *******************************************************************/
    virtual std::wstring GetErrorInfo() const override
    {
        return mErrorInfo;
    }

public:
    /*******************************************************************
    *  ����������JSON����
    *  ������val json����
    *  ���أ���
    *******************************************************************/
    virtual void Parse(const web::json::value &val);

private:
    bool mIsOk;
    int mErrorCode;
    std::wstring mErrorInfo;
};
