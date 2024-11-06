#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <unordered_map>
#include <stdexcept>

class UserHashTable {
private:
    struct UserProfile {
        std::string username;
        std::unordered_map<std::string, std::string> profile_data;

        UserProfile(const std::string& user, const std::unordered_map<std::string, std::string>& data)
            : username(user), profile_data(data) {}
    };

    std::vector<std::list<UserProfile>> table; // Hash table using separate chaining
    size_t capacity; // Size of the hash table
    size_t hash(const std::string& username) const;

public:
    UserHashTable(size_t size = 10) : capacity(size) {
        table.resize(capacity);
    }

    void addUser(const std::string& username, const std::unordered_map<std::string, std::string>& profile_data);
    std::unordered_map<std::string, std::string> getUser(const std::string& username) const;
};

size_t UserHashTable::hash(const std::string& username) const {
    std::hash<std::string> hasher;
    return hasher(username) % capacity; // Hash function to compute index
}

void UserHashTable::addUser(const std::string& username, const std::unordered_map<std::string, std::string>& profile_data) {
    size_t index = hash(username);
    for (const auto& userProfile : table[index]) {
        if (userProfile.username == username) {
            throw std::invalid_argument("Username '" + username + "' already exists.");
        }
    }
    table[index].emplace_back(username, profile_data); // Add new user profile
}

std::unordered_map<std::string, std::string> UserHashTable::getUser(const std::string& username) const {
    size_t index = hash(username);
    for (const auto& userProfile : table[index]) {
        if (userProfile.username == username) {
            return userProfile.profile_data; // Return profile data
        }
    }
    throw std::out_of_range("Username '" + username + "' not found.");
}

// Example usage
int main() {
    UserHashTable userHashTable;

    // Adding users
    try {
        userHashTable.addUser("john_doe", {{"age", "30"}, {"email", "john@example.com"}});
        userHashTable.addUser("jane_smith", {{"age", "25"}, {"email", "jane@example.com"}});

        // Retrieving user profiles
        auto johnProfile = userHashTable.getUser("john_doe");
        std::cout << "John's Profile:\n";
        for (const auto& pair : johnProfile) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }

        auto janeProfile = userHashTable.getUser("jane_smith");
        std::cout << "Jane's Profile:\n";
        for (const auto& pair : janeProfile) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }

        // Attempting to retrieve a non-existent user
        userHashTable.getUser("non_existent_user"); // This will raise an exception
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
