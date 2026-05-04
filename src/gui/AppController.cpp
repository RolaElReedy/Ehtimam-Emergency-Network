#include "AppController.h"
#include <QMessageBox>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
AppController::AppController(QObject* parent) : QObject(parent) {}
void AppController::start() {
    loginWindow_ = std::make_unique<LoginWindow>();
    connect(loginWindow_.get(), &LoginWindow::loginRequested, this, &AppController::onLoginRequested);
    loginWindow_->show();
}
void AppController::onLoginRequested(const QString& username, const QString& host, int port) {
    username_ = username;
    client_ = std::make_unique<NetworkClient>();
    client_->onMessageReceived = [this](const std::string& msg) {
        QMetaObject::invokeMethod(this, [this, msg]() { onMessageReceived(msg); });
    };
    client_->onDisconnected = [this]() {
        QMetaObject::invokeMethod(this, [this]() { onDisconnected(); });
    };
    if (!client_->connectToServer(host.toStdString(), port)) {
        QMessageBox::critical(loginWindow_.get(), "Error", "Could not connect to server.");
        loginWindow_->findChild<QPushButton*>()->setEnabled(true);
        return;
    }
    mainWindow_ = std::make_unique<MainWindow>(username_);
    connect(mainWindow_.get(), &MainWindow::alertTriggered, this, &AppController::onAlertTriggered);
    connect(mainWindow_.get(), &MainWindow::messageSent, this, &AppController::onMessageSent);
    connect(mainWindow_.get(), &MainWindow::openCircleManager, this, &AppController::onOpenCircleManager);
    loginWindow_->hide();
    mainWindow_->show();
    json j;
    j["type"] = "join";
    j["user"] = username_.toStdString();
    j["message"] = "joined the network";
    client_->sendMessage(j.dump());
}
void AppController::onAlertTriggered() {
    json j;
    j["type"] = "alert";
    j["user"] = username_.toStdString();
    j["message"] = "EMERGENCY - HELP NEEDED";
    client_->sendMessage(j.dump());
    mainWindow_->appendMessage("YOU sent an EMERGENCY ALERT");
}
void AppController::onMessageSent(const QString& msg) {
    json j;
    if (msg.startsWith("suggest ")) {
        j["type"] = "suggest";
        j["user"] = username_.toStdString();
        j["message"] = msg.mid(8).toStdString();
    } else {
        j["type"] = "status";
        j["user"] = username_.toStdString();
        j["message"] = msg.toStdString();
    }
    client_->sendMessage(j.dump());
    mainWindow_->appendMessage("You: " + msg);
}
void AppController::onOpenCircleManager() {
    if (!circleWindow_) circleWindow_ = std::make_unique<CircleWindow>(mainWindow_.get());
    circleWindow_->show();
}
void AppController::onMessageReceived(const std::string& raw) {
    try {
        auto j = json::parse(raw);
        std::string type = j.value("type", "");
        std::string user = j.value("user", "");
        std::string msg  = j.value("message", "");
        QString display;
        if (type == "alert")
            display = "ALERT from " + QString::fromStdString(user) + ": " + QString::fromStdString(msg);
        else if (type == "suggest" || raw.find("[AI Advice") != std::string::npos)
            display = QString::fromStdString(raw);
        else
            display = QString::fromStdString(user) + ": " + QString::fromStdString(msg);
        if (mainWindow_) mainWindow_->appendMessage(display);
    } catch (...) {
        if (mainWindow_) mainWindow_->appendMessage(QString::fromStdString(raw));
    }
}
void AppController::onDisconnected() {
    if (mainWindow_) mainWindow_->setStatus("Disconnected", false);
}
