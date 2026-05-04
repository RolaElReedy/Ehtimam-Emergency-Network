#include "LoginWindow.h"
#include <QVBoxLayout>
#include <QFormLayout>
LoginWindow::LoginWindow(QWidget* parent) : QWidget(parent) {
    setWindowTitle("Ehtimam - Login");
    setFixedSize(400, 300);
    setStyleSheet("background-color: #2c3e50; color: white;");
    auto* layout = new QVBoxLayout(this);
    auto* title = new QLabel("Ehtimam Emergency Network");
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #e74c3c; padding: 20px;");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);
    auto* form = new QFormLayout();
    usernameEdit_ = new QLineEdit();
    usernameEdit_->setPlaceholderText("Your name");
    usernameEdit_->setStyleSheet("background: #34495e; color: white; padding: 6px; border-radius: 4px;");
    hostEdit_ = new QLineEdit("127.0.0.1");
    hostEdit_->setStyleSheet("background: #34495e; color: white; padding: 6px; border-radius: 4px;");
    portEdit_ = new QLineEdit("12345");
    portEdit_->setStyleSheet("background: #34495e; color: white; padding: 6px; border-radius: 4px;");
    form->addRow("Username:", usernameEdit_);
    form->addRow("Host:", hostEdit_);
    form->addRow("Port:", portEdit_);
    layout->addLayout(form);
    loginBtn_ = new QPushButton("Connect");
    loginBtn_->setStyleSheet("background-color: #e74c3c; color: white; font-size: 14px; padding: 10px; border-radius: 4px;");
    layout->addWidget(loginBtn_);
    statusLabel_ = new QLabel("");
    statusLabel_->setAlignment(Qt::AlignCenter);
    statusLabel_->setStyleSheet("color: #e74c3c;");
    layout->addWidget(statusLabel_);
    connect(loginBtn_, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
}
void LoginWindow::onLoginClicked() {
    QString username = usernameEdit_->text().trimmed();
    QString host = hostEdit_->text().trimmed();
    int port = portEdit_->text().toInt();
    if (username.isEmpty()) { statusLabel_->setText("Please enter a username."); return; }
    if (host.isEmpty()) { statusLabel_->setText("Please enter a host."); return; }
    if (port <= 0) { statusLabel_->setText("Invalid port."); return; }
    loginBtn_->setEnabled(false);
    statusLabel_->setText("Connecting...");
    emit loginRequested(username, host, port);
}
