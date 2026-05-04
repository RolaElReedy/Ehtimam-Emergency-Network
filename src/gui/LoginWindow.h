#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
class LoginWindow : public QWidget {
    Q_OBJECT
public:
    explicit LoginWindow(QWidget* parent = nullptr);
signals:
    void loginRequested(const QString& username, const QString& host, int port);
private slots:
    void onLoginClicked();
private:
    QLineEdit* usernameEdit_;
    QLineEdit* hostEdit_;
    QLineEdit* portEdit_;
    QPushButton* loginBtn_;
    QLabel* statusLabel_;
};
