#include <shell.h>

#define PLUGINSLIST 1
#define PLUGINSETTINGS 2
#define SETTINGSLIST 3
#define MODELIST 4
#define RUNTIME 5
#define PLUGINSTARS 6
#define PLUGINCLASS 7
#define PLUGINSISSUES 8
#define GROUPSTARS 9
#define EXIT 0

void start(){

	std::cout << R"(
__      _______ __  __      _____ _   _ ______ ____  
\ \    / /_   _|  \/  |    |_   _| \ | |  ____/ __ \ 
 \ \  / /  | | | \  / |______| | |  \| | |__ | |  | |
  \ \/ /   | | | |\/| |______| | | . ` |  __|| |  | |
   \  /   _| |_| |  | |     _| |_| |\  | |   | |__| |
    \/   |_____|_|  |_|    |_____|_| \_|_|    \____/ 
		                                                      
	)" 
	<< std::endl;
}

void printMenu() {
	std::cout << R"(
**************************************************************************
1. Get list of plugins
2. Get list of plugins settings
3. Get list of setting
4. Get list of ????????
5. Get VIM runtime
6. Get amount of stars of plugin on Github
7. Get plugin's category on vim-awesome
8. Get amount of open issues to closed issues on Github for plugin
9. Count amount for group of plugins stars to amount of plugins
0. Exit from vim-info
**************************************************************************
	)"
	<< std::endl;
}

int prompt() {
	while (true) {
		int command = 0;
		std::cout << "> ";
		std::cin >> command;
		switch (command) {
			case PLUGINSLIST:
				break;
			case PLUGINSETTINGS:
				break;
			case SETTINGSLIST:
				break;
			case MODELIST:
				break;
			case RUNTIME:
				break;
			case PLUGINSTARS: {
				std::string name;
				std::cout << "Enter plugin name: ";
				std::cin.ignore();
				getline(std::cin,name);
				Plugin plug(name);
				std::cout << name << " has " << plug.getPluginStarCount()
				<< " stars on Github" << std::endl;
				break;
			}
			case PLUGINCLASS: {
				std::string name;
				std::cout << "Enter plugin name: ";
				std::cin.ignore();
				getline(std::cin,name);
				std::cout << name << " has "
				<< " category on vim-awesome" << std::endl;
				break;
			}
			case PLUGINSISSUES: {
				std::string name;
				std::cout << "Enter plugin name: ";
				std::cin.ignore();
				getline(std::cin, name);
				std::cout << name << " has "
				<< " amount of opened/closed issues on Github" << std::endl;
				break;
			}
			case GROUPSTARS:
				break;
			case EXIT:
				break;
			default:
				std::cout<< "Wrong Input" << std::endl;
				break;
		}
		if (command == EXIT)
			break;
	}
	return EXIT;
}
