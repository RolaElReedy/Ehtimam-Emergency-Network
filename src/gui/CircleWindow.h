#pragma once
#include <QDialog>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
class CircleWindow : public QDialog {
    Q_OBJECT
public:
    explicit CircleWindow(QWidget* parent = nullptr);
    void addMember(const QString& name);
    void removeMember(const QString& name);
    QStringList getMembers() const;
private slots:
    void onAddClicked();
    void onRemoveClicked();
private:
    QListWidget* memberList_;
    QLineEdit* nameInput_;
    QPushButton* addBtn_;
    QPushButton* removeBtn_;
};
