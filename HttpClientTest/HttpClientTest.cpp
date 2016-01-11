// HttpClientTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

#include <thread>

using namespace utility;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;


void TestBlock()
{
    for (int i = 0; i < 10; i++)
    {
        printf_s("%i\n", i);

        const string_t searchTerm = U("cpprest");
        const string_t outputFileName = U("1.html");

        // Open a stream to the file to write the HTTP response body into.
        auto fileBuffer = std::make_shared<streambuf<uint8_t>>();
        file_buffer<uint8_t>::open(outputFileName, std::ios::out).then([=](streambuf<uint8_t> outFile) -> pplx::task < http_response >
        {
            *fileBuffer = outFile;

            // Create an HTTP request.
            // Encode the URI query since it could contain special characters like spaces.
            http_client client(U("http://www.bing.com/"));
            return client.request(methods::GET, uri_builder(U("/search")).append_query(U("q"), searchTerm).to_string());
        })

            // Write the response body into the file buffer.
            .then([=](http_response response) -> pplx::task < size_t >
        {
            printf("Response status code %u returned.\n", response.status_code());

            return response.body().read_to_end(*fileBuffer);
        })

            // Close the file buffer.
            .then([=](size_t)
        {
            return fileBuffer->close();
        })

            // Wait for the entire response body to be written into the file.
            .wait();
    }
}
int _tmain(int argc, _TCHAR* argv[])
{
    std::thread threadArry[20];
    for (int i = 0; i < 20; i++)
    {
        threadArry[i] = std::thread(TestBlock);
    }

    for (auto &thread: threadArry)
    {
        thread.join();
    }

	return 0;
}

