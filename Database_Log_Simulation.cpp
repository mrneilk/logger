// Database Log Simulation in C++
// This program simulates a database logging system with failover capabilities.
// It demonstrates successful logging, performance monitoring, and failover handling when the database is offline.

//Header files
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include <fstream>

//enum for log levels
enum class LogLevel { DEBUG, INFO, WARN, ERROR };

// Struct to represent a log entry
struct LogEntry {
    std::string timestamp;
    LogLevel level;
    std::string source;
    std::string message;
};

// Class to simulate database logging with failover capabilities
class DatabaseSimulator {
private:
    std::vector<LogEntry> primaryStorage;
    bool isDatabaseOnline = true;

    std::string levelToString(LogLevel level) {
        switch (level) {
            case LogLevel::DEBUG: return "DEBUG";
            case LogLevel::INFO:  return "INFO";
            case LogLevel::WARN:  return "WARN";
            case LogLevel::ERROR: return "ERROR";
            default: return "UNKNOWN";
        }
    }

//Function to set the database status (online/offline)
public:
    void setDatabaseStatus(bool online) { isDatabaseOnline = online; }

    void insertLog(const LogEntry& entry) {
        if (isDatabaseOnline) {
            primaryStorage.push_back(entry);
            std::cout << "[DB PRIMARY] Saved: " << entry.message << std::endl;
        } else {
            // Failover Simulation
            std::ofstream backupFile("failover_logs.txt", std::ios::app);
            backupFile << "[" << entry.timestamp << "] " << levelToString(entry.level) 
                       << " - " << entry.message << std::endl;
            std::cout << "[FAILOVER] Database Offline. Logged to local file." << std::endl;
        }
    }
};


std::string getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
}

// Main function to demonstrate the database log simulation
int main() {
    DatabaseSimulator db;

    // 1. Successful Logging Simulation
    LogEntry e1 = {getCurrentTimestamp(), LogLevel::INFO, "System", "Service started successfully."};
    db.insertLog(e1);

    // 2. Performance Monitoring Simulation
    LogEntry e2 = {getCurrentTimestamp(), LogLevel::DEBUG, "Network", "Latency detected at 45ms."};
    db.insertLog(e2);

    // 3. Failover Simulation (Simulating a DB crash)
    std::cout << "\n--- Simulating Database Connection Loss ---" << std::endl;
    db.setDatabaseStatus(false);

    LogEntry e3 = {getCurrentTimestamp(), LogLevel::ERROR, "Security", "Unauthorized access attempt blocked."};
    db.insertLog(e3);

    return 0;
}
