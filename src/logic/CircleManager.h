#pragma once
#include <string>
#include <vector>
#include <map>
class CircleManager {
public:
    void addMember(const std::string& username);
    void removeMember(const std::string& username);
    void setOnline(const std::string& username, bool online);
    bool isMember(const std::string& username) const;
    std::vector<std::string> getMembers() const;
    std::map<std::string, bool> getStatuses() const { return statuses_; }
private:
    std::vector<std::string> members_;
    std::map<std::string, bool> statuses_;
};
