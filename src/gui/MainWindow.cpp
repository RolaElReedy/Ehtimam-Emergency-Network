#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDateTime>
MainWindow::MainWindow(const QString& username, QWidget* parent)
    : QMainWindow(parent), username_(username) {
    setWindowTitle("Ehtimam - " + username);
    resize(650, 550);
    setStyleSheet("background-color: #2c3e50; color: white;");
    auto* central = new QWidget();
    setCentralWidget(central);
    auto* layout = new QVBoxLayout(central);
    statusLabel_ = new QLabel("Connected as " + username);
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
    auto* btnRow1 = new QHBoxLayout();
    alertBtn_ = new QPushButton("SEND ALERT");
    alertBtn_->setStyleSheet("background-color: #e74c3c; color: white; font-size: 14px; padding: 10px; border-radius: 4px;");
    safeBtn_ = new QPushButton("I AM SAFE");
    safeBtn_->setStyleSheet("background-color: #27ae60; color: white; font-size: 14px; padding: 10px; border-radius: 4px;");
    btnRow1->addWidget(alertBtn_);
    btnRow1->addWidget(safeBtn_);
    layout->addLayout(btnRow1);
    auto* btnRow2 = new QHBoxLayout();
    circleBtn_ = new QPushButton("Manage Circle");
    circleBtn_->setStyleSheet("background-color: #8e44ad; color: white; padding: 8px; border-radius: 4px;");
    resourcesBtn_ = new QPushButton("Emergency Hotlines");
    resourcesBtn_->setStyleSheet("background-color: #d35400; color: white; padding: 8px; border-radius: 4px;");
    btnRow2->addWidget(circleBtn_);
    btnRow2->addWidget(resourcesBtn_);
    layout->addLayout(btnRow2);
    connect(alertBtn_, &QPushButton::clicked, this, &MainWindow::onAlertClicked);
    connect(sendBtn_, &QPushButton::clicked, this, &MainWindow::onSendClicked);
    connect(messageInput_, &QLineEdit::returnPressed, this, &MainWindow::onSendClicked);
    connect(circleBtn_, &QPushButton::clicked, this, &MainWindow::openCircleManager);
    connect(resourcesBtn_, &QPushButton::clicked, this, &MainWindow::openResources);
    connect(safeBtn_, &QPushButton::clicked, this, &MainWindow::onSafeClicked);
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
void MainWindow::onSafeClicked() {
    auto reply = QMessageBox::information(this, "Mark as Safe",
        "Mark yourself as safe? This will notify your circle.",
        QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) emit markSafe();
}
