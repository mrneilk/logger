#include <iostream>
#include <string>
#include <ctime>

// Define log levels for better organization
enum LogLevel {
    INFO,
    WARNING,
    ERROR
};

class Logger {
public:
    // Function to log a message
    static void Log(LogLevel level, const std::string& message) {
        // Get current system time
        std::time_t now = std::time(0);
        char* dt = std::ctime(&now);
        std::string timeStr(dt);
        timeStr.erase(timeStr.length() - 1); // Remove trailing newline

        // Output the log based on the level
        switch (level) {
            case INFO:
                std::cout << "[INFO]  [" << timeStr << "] " << message << std::endl;
                break;
            case WARNING:
                std::cout << "[WARN]  [" << timeStr << "] " << message << std::endl;
                break;
            case ERROR:
                std::cerr << "[ERROR] [" << timeStr << "] " << message << std::endl;
                break;
        }
    }
};

int main() {
    // Simulating program execution
    Logger::Log(INFO, "Application started successfully.");
    
    int diskSpace = 15; // percent
    if (diskSpace < 20) {
        Logger::Log(WARNING, "Low disk space detected: 15%.");
    }

    try {
        throw std::runtime_error("Database connection failed.");
    } catch (const std::exception& e) {
        Logger::Log(ERROR, e.what());
    }

    return 0;
}
