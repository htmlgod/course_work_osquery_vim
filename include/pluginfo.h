#pragma once

#include <curl/curl.h>
#include <string>
#include <memory>
#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>
#include <webutils.h>

class Plugin {
public:
	explicit Plugin(std::string name) : _pluginName(std::move(name)) {}
	
	const int getStarsCount();

	const int getOpenedIssues();

	const int getClosedIssues();

	const double getAmountOfOpenedIssuesToClosed();

	std::string getVimAwesomePluginClassification();

	int countForGroupOfPluginAmountOfStars(std::vector<Plugin>& list);
	
	friend void printGroup(std::vector<Plugin>& group);
private:
	std::string _pluginName;
};


