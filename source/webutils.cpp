#include <webutils.h>

namespace {
std::size_t callback(
	const char* in,
	std::size_t size,
	std::size_t num,
	std::string* out
	) {
	const std::size_t totalBytes(size * num);
	out->append(in, totalBytes);
	return totalBytes;						    
}
}

std::string httpQuery(const std::string& url, bool onlyHeader) {
	CURL* curl = curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

	curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.64.1");

	curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    if(std::getenv("GITHUB_USERNAME") != nullptr and std::getenv("GITHUB_PASSWORD") != nullptr) {
        curl_easy_setopt(curl, CURLOPT_USERNAME, std::getenv("GITHUB_USERNAME"));

        curl_easy_setopt(curl, CURLOPT_PASSWORD, std::getenv("GITHUB_PASSWORD"));
    }

    long httpCode(0);
    auto* httpData = new std::string();
    if (onlyHeader) {
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, callback);

        curl_easy_setopt(curl, CURLOPT_HEADERDATA, httpData);
    } else {
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData);
    }
	curl_easy_perform(curl);
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
	curl_easy_cleanup(curl);
	
	if (httpCode == 200) {
		std::string out = *httpData;
        delete httpData;
		return out;
	} else if(httpCode == 0) {
	    std::cout << "Error: no internet connection!";

	} else {
		std::cout << "Could not parse HTTP data as JSON from url:"<<url << std::endl;
		std::cout << "HTTP data was:\n" << *httpData << std::endl;
		std::cout << "HTTP code: " << httpCode << std::endl;
        delete httpData;
	}
    return "empty";
}
