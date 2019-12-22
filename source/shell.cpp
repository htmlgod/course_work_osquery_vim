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
    VimConfig::Instance().init();

}

void printMenu() {
	std::cout << R"(
**************************************************************************
1. Get list of plugins
2. WIP
3. WIP
4. WIP
5. Get VIM Startup Time
6. Get amount of stars of plugin on Github
7. Get VimAwesome classification of plugin
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
			case PLUGINSLIST: {
				break;
			}
				
			case PLUGINSETTINGS:
				break;
			case SETTINGSLIST:
				break;
			case MODELIST:
				break;
			case RUNTIME: {
                std::cout << "Vim Current StartupTime: " << VimConfig::Instance().getStartupTime() << std::endl;
			    break;
			}

			case PLUGINSTARS: {
				std::string name;
				std::cout << "Enter plugin name: ";
				std::cin.ignore();
				getline(std::cin,name);
				Plugin plug(name);
				std::cout << name << " has " << plug.getStarsCount()
				<< " stars on Github" << std::endl;
				break;
			}
			case PLUGINCLASS: {
				std::string name;
				std::cout << "Enter plugin name: ";
				std::cin.ignore();
				getline(std::cin,name);
				Plugin plug(name);
				std::cout << name << " has "
				<< " category on vim-awesome: "<<plug.getVimAwesomePluginClassification() << std::endl;
				
				break;
			}
			case PLUGINSISSUES: {
				std::string name;
				std::cout << "Enter plugin name: ";
				std::cin.ignore();
				getline(std::cin, name);
				Plugin plug(name);
				std::cout << name << " has " << plug.getOpenedIssues() 
				<< " amount of opened issues," << std::endl <<
				plug.getClosedIssues() << " amount of closed issues, "
				<< std:: endl << plug.getAmountOfOpenedIssuesToClosed()
				<< " amount of opened/closed issues" << std::endl;
				break;
			}
			case GROUPSTARS: {
				std::vector<Plugin> group;
				int groupSize;
                std::cout << "Enter size of group: "; std::cin >> groupSize;
                group.reserve(groupSize);
				std::cout << "Enter group of plugins" << std::endl;
                std::cin.ignore();
                std::string name;
				for (int i = 0; i < groupSize; i++) {
					getline(std::cin, name);
					group.emplace_back(name);
				}
				printGroup(group);
				Plugin plug;
                std::cout << "Group amount of stars/number is "<< plug.countForGroupOfPluginAmountOfStars(group)
                << std::endl;
				break;
			}
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
