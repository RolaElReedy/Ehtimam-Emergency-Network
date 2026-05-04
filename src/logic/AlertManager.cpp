#include "AlertManager.h"
AlertManager::AlertManager() {}
void AlertManager::triggerAlert(const std::string& user) {
    state_ = AlertState::Active;
    acknowledgments_.clear();
    if (onStateChanged) onStateChanged(state_);
}
void AlertManager::resolveAlert(const std::string& user) {
    state_ = AlertState::Resolved;
    if (onStateChanged) onStateChanged(state_);
    state_ = AlertState::Normal;
}
void AlertManager::addAcknowledgment(const std::string& from) {
    acknowledgments_.push_back(from);
}
