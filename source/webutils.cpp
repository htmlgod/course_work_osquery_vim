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

std::string httpQuery(const std::string& url) {
	CURL* curl = curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

	curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.64.1");

	curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

	long httpCode(0);

	auto* httpData = new std::string();

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

	curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData);

	curl_easy_perform(curl);
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
	curl_easy_cleanup(curl);
	
	if (httpCode != 300) {
		std::string out = *httpData;
		delete httpData;
		return out;
	}
	else {
		std::cout << "Could not parse HTTP data as JSON" << std::endl;
		//std::cout << "HTTP data was:\n" << *httpData << std::endl;
		std::cout << "HTTP code: " << httpCode << std::endl;
		return "empty";
	}
}