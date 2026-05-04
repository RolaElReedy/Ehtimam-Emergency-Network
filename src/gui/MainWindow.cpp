#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDateTime>
MainWindow::MainWindow(const QString& username, QWidget* parent)
    : QMainWindow(parent), username_(username) {
    setWindowTitle("Ehtimam - " + username);
    resize(600, 500);
    setStyleSheet("background-color: #2c3e50; color: white;");
    auto* central = new QWidget();
    setCentralWidget(central);
    auto* layout = new QVBoxLayout(central);
    statusLabel_ = new QLabel("Connected");
    statusLabel_->setStyleSheet("color: #2ecc71; font-weight: bold; padding: 4px;");
    layout->addWidget(statusLabel_);
    chatLog_ = new QTextEdit();
    chatLog_->setReadOnly(true);
    chatLog_->setStyleSheet("background: #34495e; color: white; border-radius: 4px; padding: 8px;");
    layout->addWidget(chatLog_);
    auto* inputRow = new QHBoxLayout();
    messageInput_ = new QLineEdit();
    messageInput_->setPlaceholderText("Type a message or: suggest <situation>");
    messageInput_->setStyleSheet("background: #34495e; color: white; padding: 6px; border-radius: 4px;");
    sendBtn_ = new QPushButton("Send");
    sendBtn_->setStyleSheet("background-color: #3498db; color: white; padding: 6px; border-radius: 4px;");
    inputRow->addWidget(messageInput_);
    inputRow->addWidget(sendBtn_);
    layout->addLayout(inputRow);
    auto* btnRow = new QHBoxLayout();
    alertBtn_ = new QPushButton("SEND ALERT");
    alertBtn_->setStyleSheet("background-color: #e74c3c; color: white; font-size: 14px; padding: 10px; border-radius: 4px;");
    circleBtn_ = new QPushButton("Manage Circle");
    circleBtn_->setStyleSheet("background-color: #2ecc71; color: white; padding: 8px; border-radius: 4px;");
    btnRow->addWidget(alertBtn_);
    btnRow->addWidget(circleBtn_);
    layout->addLayout(btnRow);
    connect(alertBtn_, &QPushButton::clicked, this, &MainWindow::onAlertClicked);
    connect(sendBtn_, &QPushButton::clicked, this, &MainWindow::onSendClicked);
    connect(messageInput_, &QLineEdit::returnPressed, this, &MainWindow::onSendClicked);
    connect(circleBtn_, &QPushButton::clicked, this, &MainWindow::openCircleManager);
}
void MainWindow::appendMessage(const QString& msg) {
    QString time = QDateTime::currentDateTime().toString("hh:mm");
    chatLog_->append("[" + time + "] " + msg);
}
void MainWindow::setStatus(const QString& status, bool connected) {
    statusLabel_->setText(status);
    statusLabel_->setStyleSheet(connected ? "color: #2ecc71; font-weight: bold;" : "color: #e74c3c; font-weight: bold;");
}
void MainWindow::onAlertClicked() {
    auto reply = QMessageBox::warning(this, "Send Emergency Alert",
        "Are you sure you want to send an emergency alert to everyone?",
        QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) emit alertTriggered();
}
void MainWindow::onSendClicked() {
    QString text = messageInput_->text().trimmed();
    if (text.isEmpty()) return;
    emit messageSent(text);
    messageInput_->clear();
}
