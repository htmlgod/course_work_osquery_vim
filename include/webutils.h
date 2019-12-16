#pragma once

#include <curl/curl.h>
#include <string>
#include <iostream>

namespace API {
	static std::string GITHUB_API_ENTRY = "https://api.github.com/";
}

std::string httpQuery(const std::string& url);
