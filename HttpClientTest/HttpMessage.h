#pragma once

#include "HttpMessageDef.h"

class HttpMessage : public IHttpMessage
{
public:
    HttpMessage(HttpMessageType messageType);
    virtual ~HttpMessage();

public:
    /*******************************************************************
    *  ������������Ӧ���
    *  ������result ��Ӧ���
    *  ���أ���
    *******************************************************************/
    virtual void SetResult(HttpMessageResultSharedPtr result) override
    {
        mHttpMessageResult = result;
    }

    /*******************************************************************
    *  ��������ȡ���
    *  ��������
    *  ���أ����
    *******************************************************************/
    virtual HttpMessageResultSharedPtr GetResult() const override
    {
        return mHttpMessageResult;
    }


    /*******************************************************************
    *  ������������Ϣ����
    *  ������type ��Ϣ����
    *  ���أ���
    *******************************************************************/
    virtual void SetType(HttpMessageType type) override
    {
        mType = type;
    }

    /*******************************************************************
    *  ��������ȡ��Ϣ����
    *  ��������
    *  ���أ���Ϣ����
    *******************************************************************/
    virtual HttpMessageType GetType() const override
    {
        return mType;
    }


    /*******************************************************************
    *  ������������ϢͶ�����ͣ�
    *  ������method ��ϢͶ�����ͣ�POST,GET��
    *  ���أ���
    *******************************************************************/
    virtual void SetMethod(HttpMessageMethod method) override
    {
        mMethod = method;
    }

    /*******************************************************************
    *  ������������ϢͶ������
    *  ��������
    *  ���أ���ϢͶ������
    *******************************************************************/
    virtual HttpMessageMethod GetMethod() const override
    {
        return mMethod;
    }


    /*******************************************************************
    *  ���������÷�������ַ
    *  ������server ��������ַ
    *  ���أ���
    *******************************************************************/
    virtual void SetServer(const std::wstring &server) override
    {
        mServer = server;
    }

    /*******************************************************************
    *  ��������ȡ��������ַ
    *  ��������
    *  ���أ���������ַ
    *******************************************************************/
    virtual std::wstring GetServer() const override
    {
        return mServer;
    }


    /*******************************************************************
    *  ���������÷������Ļ���ַ
    *  ������base base��ַ
    *  ���أ���
    *******************************************************************/
    virtual void SetBase(const std::wstring &base) override
    {
        mBase = base;
    }

    /*******************************************************************
    *  ��������ȡ�������Ļ���ַ
    *  ��������
    *  ���أ�base��ַ
    *******************************************************************/
    virtual std::wstring GetBase() const override
    {
        return mBase;
    }


    /*******************************************************************
    *  ���������÷�������ʵ�ʵ�ַ
    *  ������address ʵ�ʵ�ַ
    *  ���أ���
    *******************************************************************/
    virtual void SetAddress(const std::wstring &address) override
    {
        mAddress = address;
    }

    /*******************************************************************
    *  ��������ȡ��������ʵ�ʵ�ַ
    *  ��������
    *  ���أ�ʵ�ʵ�ַ
    *******************************************************************/
    virtual std::wstring GetAddress() const override
    {
        return mAddress;
    }


    /*******************************************************************
    *  ����������������
    *  ������name ��������value ������ֵ��bPost �Ƿ�Ͷ�ݣ�
    *  ���أ���
    *******************************************************************/
    virtual void AddParam(const std::wstring &name, const std::wstring &value, bool bPost) override;

    /*******************************************************************
    *  ��������ȡ���������ֵ
    *  ������name ��������
    *  ���أ�����ֵ
    *******************************************************************/
    virtual std::wstring GetParam(const std::wstring &name) const override;

    /*******************************************************************
    *  ��������ȡ��������б�
    *  ��������
    *  ���أ���������б�
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