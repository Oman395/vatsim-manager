#include <iostream>
#include <cstring>
#include <curl/curl.h>
#include <cstdio>
#include <cstdlib>
#include "utils.h"
#include "download.h"

using namespace std;

const char* version = "0.2.1";

utils ut;
download dl;

//TODO keep track of installed programs and add --refresh option

int install(const char* program) {
    //TODO simplify
    if (ut.iequals(program, "xpilot")) {
        if (ut.askForConfirmation("xPilot")) {
            dl.downloadPilotClient(0);
            system("chmod +x /tmp/vatsim-manager/xPilot.run");
            system("/tmp/vatsim-manager/xPilot.run");
        }
    } else if (ut.iequals(program, "swift")) {
        if (ut.askForConfirmation("Swift")) {
            dl.downloadPilotClient(1);
            system("chmod +x /tmp/vatsim-manager/Swift.run");
            system("/tmp/vatsim-manager/Swift.run");
        }
    } else {
        cout << "Program name not recognised." << endl << endl;
    }

    return 0;
}

int remove(const char* program) {
    if (ut.iequals(program, "xpilot")) {
        system("rm -rf \"$HOME/.cache/Justin Shannon\"");
        system("$(find $HOME -name xPilot)/uninstall");
    } else if (ut.iequals(program, "swift")) {
        //doesn't work if the qt sdk is installed
        system("$(find $HOME -name swift-*)/uninstall");
    } else {
        cout << "Program name not recognised." << endl << endl;
    }
    return 0;
}

void showLicense() {
    cout << "This project is not endorsed by any VATSIM staff member." << endl;
    cout << "The xPilot 2.0.0 beta is licensed under GPL3. Express permission to redistribute the proprietary " <<
    "installer was given by Justin Shannon." << endl;
    cout << "The Swift beta is licensed under GPL3. Express permission to redistribute the proprietary installer was" <<
    "given by Mat Sutcliffe." << endl << endl;
    cout << "vSTARS is proprietary software. Express permission to redistribute the proprietary installer was given " <<
    "by Ross Carlson." << endl;
    cout << "vERAM is proprietary software. Express permission to redistribute the proprietary installer was given " <<
    "by Ross Carlson." << endl << endl;
    cout << "libcURL 7.81.0 has a custom license. Usage is allowed under this license." << endl << endl;
}

void showCommands() {
    cout << "-h - displays this page" << endl;
    cout << "-l - displays license information" << endl;
    cout << "-i - installs a pilot/ATC client from the following list - " << endl;
    cout << "     xPilot 2.0.0 beta (X-Plane 11), Swift (X-Plane 11, FlightGear)" << endl;
    cout << "-r - uninstalls a pilot/ATC client from the above list" << endl << endl;
}

int main(int argc, char** argv) {

    cout << endl << "VATSIM Program Manager version " << version << " by Cian Ormond" << endl;
    cout << "Licensed under GPL3. For licensing of programs included, use -l." << endl << endl;

    //TODO remove this if statement bs
    //TODO add config option for xPilot's AppConfig
    if (argc > 1) {
        if (strcmp(argv[1], "-i") == 0) {
            if (argc > 2) {
                install(argv[2]);
            } else {
                //TODO only show uninstalled programs
                cout << "Please specify a program to install. Available options are xPilot and Swift." << endl << endl;
            }
        } else if (strcmp(argv[1], "-r") == 0) {
            if (argc > 2) {
                remove(argv[2]);
            } else {
                //TODO only show installed programs
                cout << "Please specify a program to uninstall. Available options are xPilot and Swift." << endl << endl;
            }
        } else if (strcmp(argv[1], "-h") == 0) {showCommands();}
        else if (strcmp(argv[1], "-l") == 0) {showLicense();}
    } else {
        cout << "No command specified. Use the -h flag for a command list." << endl << endl;
    }
    return 0;
}

