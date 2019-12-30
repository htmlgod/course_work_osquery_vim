#pragma once

#include <iostream>
#include <string>

#include <curl/curl.h>


namespace API {
	static std::string GITHUB_API_ENTRY = "https://api.github.com/";
	static std::string VIMAWESOME_SEARCH_API_ENTRY = "https://vimawesome.com/api/plugins?query=";
}

std::string httpQuery(const std::string& url,
                      const std::string& username,
                      const std::string& password);

std::string httpHeader(const std::string& url);