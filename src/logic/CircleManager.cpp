#include "CircleManager.h"
#include <algorithm>
void CircleManager::addMember(const std::string& username) {
    if (!isMember(username)) {
        members_.push_back(username);
        statuses_[username] = false;
    }
}
void CircleManager::removeMember(const std::string& username) {
    members_.erase(std::remove(members_.begin(), members_.end(), username), members_.end());
    statuses_.erase(username);
}
void CircleManager::setOnline(const std::string& username, bool online) {
    statuses_[username] = online;
}
bool CircleManager::isMember(const std::string& username) const {
    return std::find(members_.begin(), members_.end(), username) != members_.end();
}
std::vector<std::string> CircleManager::getMembers() const { return members_; }
