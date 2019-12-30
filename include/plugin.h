#pragma once

#include <vector>
#include <webutils.h>

class Plugin {
public:
    // Constructor for parsing data
	explicit Plugin(std::string name);
	// Constructor for imported data from json
	Plugin (std::string name, int stars, int open, int closed, std::string category);
	Plugin();

	void setName(std::string& name);
	// Getting plugin info
	int getStarsCount();
	int getOpenedIssues();
	int getClosedIssues();
	std::string getPluginName();
    std::string getFormattedPluginName();
	std::string getVimAwesomePluginClassification();
	double getAmountOfOpenedIssuesToClosed();

	// Parse functions
	void parseStarsCount();
	void parseOpenedIssues();
	void parseClosedIssues();
	void parseVimAwesomePluginClassification();
private:
	int         _starsCount = 0;
	int         _openIssues = 0;
	int         _closedIssues = 0;
    double      _openToCloseIssues = 0;
    std::string _pluginName;
	std::string _category;

	std::string _username = "none";
	std::string _password = "none";
};

