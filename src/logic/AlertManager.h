#pragma once
#include <string>
#include <vector>
#include <functional>
enum class AlertState { Normal, Active, Resolved };
class AlertManager {
public:
    AlertManager();
    void triggerAlert(const std::string& user);
    void resolveAlert(const std::string& user);
    void addAcknowledgment(const std::string& from);
    AlertState getState() const { return state_; }
    std::vector<std::string> getAcknowledgments() const { return acknowledgments_; }
    std::function<void(AlertState)> onStateChanged;
private:
    AlertState state_ = AlertState::Normal;
    std::vector<std::string> acknowledgments_;
};
