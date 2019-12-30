#include <shell.h>

#define VERSION "Version 1.0"

#define PLUGINSLIST 1
#define SETTINGSLIST 2
#define RUNTIME 3
#define PLUGINSTARS 4
#define PLUGINCLASS 5
#define PLUGINSISSUES 6
#define GROUPSTARS 7
#define FINDFROMSTARS 8
#define EXPORTJSON 9
#define MENU 10
#define EXIT 0

namespace po = boost::program_options;

void Shell::start(int argc, const char *argv[]){
    // boost::program_options flags set up
    po::options_description desc("vim-info options");
    desc.add_options()
            ("help,h", "Help screen")
            ("start_extension,e", "Start osquery extension without GUI")
            ("json_export,j", "Parse and export information into json files without GUI")
            ("version,v", "print version")
            ("clear,c", "Clear all data");
    po::variables_map vm;
    po::store(po::parse_command_line(argc,argv,desc), vm);
    po::notify(vm);

    // initialization
    VimConfig::Instance().init();
    // parsing commandline options
    if (vm.count("clear")) {
        std::cout << "Deletening data..." << std::endl;
        VimConfig::Instance().clear();
    }
    if (vm.count("help"))
        std::cout << desc << std::endl;
    else if (vm.count("version"))
        Shell::printVersion();

    else if (vm.count("start_extension")) {
        std::cout << "Extension started" << std::endl;
        VimConfig::Instance().parseFromJSON();
        VimConfig::Instance().startExtension();
    }
    else if (vm.count("json_export")) {
        std::cout << "Json export" << std::endl;
        VimConfig::Instance().start();
        VimConfig::Instance().exportJSONData();
    }
    else {
        Shell::prompt();
    }
}

void Shell::printVersion() {
    std::cout << R"(
__      _______ __  __      _____ _   _ ______ ____
\ \    / /_   _|  \/  |    |_   _| \ | |  ____/ __ \
 \ \  / /  | | | \  / |______| | |  \| | |__ | |  | |
  \ \/ /   | | | |\/| |______| | | . ` |  __|| |  | |
   \  /   _| |_| |  | |     _| |_| |\  | |   | |__| |
    \/   |_____|_|  |_|    |_____|_| \_|_|    \____/

	)"
	<< std::endl << VERSION << std::endl;
}

void Shell::printMenu() {
	std::cout << R"(
1. Get list of plugins
2. Get setting list
3. Get VIM Startup Time
4. Get amount of stars of plugin on Github
5. Get VimAwesome classification of plugin
6. Get amount of open issues to closed issues on Github for plugin
7. Count amount for group of plugins stars to amount of plugins
8. Find Vim Plugins in Github User Star's
9. Export data to JSON files
10. Print menu
0. Exit from vim-info
--------------------------------------------------------------------
)";
}

void Shell::prompt() {
    int command = 10;
    VimConfig::Instance().start();
	while (true) {
		switch (command) {
			case PLUGINSLIST: {
                Shell::Command::pluginsList();
				break;
			}
			case SETTINGSLIST: {
                Shell::Command::settingsList();
                break;
			}
			case RUNTIME: {
                Shell::Command::vimRuntime();
			    break;
			}
			case PLUGINSTARS: {
                Shell::Command::pluginStars();
				break;
			}
			case PLUGINCLASS: {
				Shell::Command::pluginClass();
				break;
			}
			case PLUGINSISSUES: {
                Shell::Command::pluginIssues();
				break;
			}
			case GROUPSTARS: {
				Shell::Command::groupStars();
				break;
			}
            case FINDFROMSTARS: {
                Shell::Command::findStarredPlugins();
                break;
            }
			case EXPORTJSON: {
                Shell::Command::exportToJSON();
			    break;
			}
			case MENU: {
                Shell::printMenu();
                break;
			}
			case EXIT: {
			    break;
			}
			default: {
                std::cerr<< "Wrong Input" << std::endl;
                break;
			}
		}
		if (command == EXIT)
			break;
        std::cout << "vim-info> ";
        std::cin >> command;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767,'\n');
            command = 11;
        }
	}
}

// vim-info functions
void Shell::Command::pluginsList() {
    std::cout << "Found " << VimConfig::Instance().getPluginsAmount() << " plugins" << std::endl;
    VimConfig::Instance().getPluginList();
}

void Shell::Command::settingsList() {
    VimConfig::Instance().getSettingList();
}

void Shell::Command::vimRuntime() {
    std::cout << "Vim Current StartupTime in Milliseconds: " << VimConfig::Instance().getStartupTimeMS() << std::endl;
    std::cout << "Vim Current StartupTime in Seconds: " <<	VimConfig::Instance().getStartupTimeS() << std::endl;
}

void Shell::Command::pluginStars() {
    std::string name;
    std::cout << "Your plugins:" << std::endl;
    VimConfig::Instance().getPluginList();
    std::cout << "Enter plugin name: ";
    std::cin.ignore();
    getline(std::cin,name);
    if (!VimConfig::Instance().isForeignPlugin(name)) {
        std::cout << name << " has "
        << VimConfig::Instance().getPluginByName(name).getStarsCount()
        << " stars on Github" << std::endl;
    } else {
        Plugin plug = VimConfig::Instance().getPluginByName(name);
        plug.setName(name);
        plug.parseStarsCount();
        std::cout << name << " has " << plug.getStarsCount()<< " stars on Github" << std::endl;
    }
}

void Shell::Command::pluginClass() {
    std::string name;
    std::cout << "Your plugins:" << std::endl;
    VimConfig::Instance().getPluginList();
    std::cout << "Enter plugin name: ";
    std::cin.ignore();
    getline(std::cin,name);
    if (!VimConfig::Instance().isForeignPlugin(name)) {
        std::cout << name << " has "
                  << VimConfig::Instance().getPluginByName(name).getVimAwesomePluginClassification()
                  << " category on VimAwesome" << std::endl;
    } else {
        Plugin plug = VimConfig::Instance().getPluginByName(name);
        plug.setName(name);
        plug.parseVimAwesomePluginClassification();
        std::cout << name << " category on vim-awesome: "<<plug.getVimAwesomePluginClassification() << std::endl;
    }

}

void Shell::Command::pluginIssues() {
    std::string name;
    std::cout << "Enter plugin name: ";
    std::cin.ignore();
    getline(std::cin, name);
    if (!VimConfig::Instance().isForeignPlugin(name)) {
        std::cout << name << " has " << VimConfig::Instance().getPluginByName(name).getOpenedIssues()
                  << " amount of opened issues," << std::endl
                  << VimConfig::Instance().getPluginByName(name).getClosedIssues()
                  << " amount of closed issues, "
                  << std:: endl << VimConfig::Instance().getPluginByName(name).getAmountOfOpenedIssuesToClosed()
                  << " amount of opened/closed issues" << std::endl;
    } else {
        Plugin plug = VimConfig::Instance().getPluginByName(name);
        plug.setName(name);
        plug.parseOpenedIssues();
        plug.parseClosedIssues();
        std::cout << name << " has " << plug.getOpenedIssues()
                  << " amount of opened issues," << std::endl <<
                  plug.getClosedIssues() << " amount of closed issues, "
                  << std:: endl << plug.getAmountOfOpenedIssuesToClosed()
                  << " amount of opened/closed issues" << std::endl;
    }

}

void Shell::Command::groupStars() {
    std::vector<Plugin> group;
    int groupSize;
    std::cout << "Enter size of group: "; std::cin >> groupSize;
    group.reserve(groupSize);
    std::cout << "Enter group of plugins" << std::endl;
    std::cin.ignore();
    std::string name;
    for (int i = 0; i < groupSize; i++) {
        getline(std::cin, name);
        if (!VimConfig::Instance().isForeignPlugin(name)) {
            group.push_back(VimConfig::Instance().getPluginByName(name));
        } else {
            Plugin plug;
            plug.setName(name);
            plug.parseStarsCount();
            group.push_back(plug);
        }
    }
    double starsToAmountOfPlugins = 0;
    std::cout << "Group:" << std::endl;
    for (auto& x : group) {
        std::cout << x.getPluginName() << std::endl;
        starsToAmountOfPlugins += double(x.getStarsCount());
    }
    starsToAmountOfPlugins /= double(groupSize);
    std::cout << "amount of stars/number is "<< starsToAmountOfPlugins << std::endl;
}

void Shell::Command::exportToJSON() {
    VimConfig::Instance().exportJSONData();
}

void Shell::Command::findStarredPlugins() {
    VimConfig::Instance().findGitHubStarsPlugins();
}
