#include <iostream>
#include <string>
#include <cstdint>
#include <memory>

#include <curl/curl.h>
#include "json/json.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "HtmlElement.h"
#include "HtmlParser.h"

namespace
{
    std::size_t callback(
            const char* in,
            std::size_t size,
            std::size_t num,
            std::string* out)
    {
        const std::size_t totalBytes(size * num);
        out->append(in, totalBytes);
        return totalBytes;
    }
}

int main(int argc, char* argv[]) {
    std::string url("https://prodota.ru/forum/index.php?showforum=15");

    CURL* curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    int httpCode(0);
    std::unique_ptr<std::string> httpData(new std::string());

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());
    curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    curl_easy_cleanup(curl);

    if (httpCode == 200)
    {
        std::cout << "\nGot successful response from " << url << std::endl;

        std::string strData = *httpData;

        HtmlParser baseParse(url, strData);

        //std::cout << baseParse.getContent() << std::endl;
        HtmlElement asd = baseParse.getNextTag();

        //HtmlElement qwe = baseParse.getRoot();

        asd.displayInfo();

    }
    else
    {
        std::cout << "Couldn't GET from " << url << " - exiting" << std::endl;
        return 1;
    }
    //testing::InitGoogleTest(&argc, argv);
    //RUN_ALL_TESTS();
    return 0;
}