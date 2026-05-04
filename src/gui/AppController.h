#pragma once
#include <QObject>
#include <memory>
#include "LoginWindow.h"
#include "MainWindow.h"
#include "CircleWindow.h"
#include "ResourcesWindow.h"
#include "../network/NetworkClient.h"
class AppController : public QObject {
    Q_OBJECT
public:
    explicit AppController(QObject* parent = nullptr);
    void start();
private slots:
    void onLoginRequested(const QString& username, const QString& host, int port);
    void onAlertTriggered();
    void onMessageSent(const QString& msg);
    void onOpenCircleManager();
    void onOpenResources();
    void onMarkSafe();
private:
    void onMessageReceived(const std::string& msg);
    void onDisconnected();
    QString username_;
    std::unique_ptr<LoginWindow> loginWindow_;
    std::unique_ptr<MainWindow> mainWindow_;
    std::unique_ptr<CircleWindow> circleWindow_;
    std::unique_ptr<ResourcesWindow> resourcesWindow_;
    std::unique_ptr<NetworkClient> client_;
};
