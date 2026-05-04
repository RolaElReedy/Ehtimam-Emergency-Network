#pragma once
#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(const QString& username, QWidget* parent = nullptr);
    void appendMessage(const QString& msg);
    void setStatus(const QString& status, bool connected);
signals:
    void alertTriggered();
    void messageSent(const QString& msg);
    void openCircleManager();
private slots:
    void onAlertClicked();
    void onSendClicked();
private:
    QString username_;
    QTextEdit* chatLog_;
    QLineEdit* messageInput_;
    QPushButton* sendBtn_;
    QPushButton* alertBtn_;
    QPushButton* circleBtn_;
    QLabel* statusLabel_;
};
