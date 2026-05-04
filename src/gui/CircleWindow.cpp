#include "CircleWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
CircleWindow::CircleWindow(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Manage Your Circle");
    setFixedSize(350, 400);
    setStyleSheet("background-color: #2c3e50; color: white;");
    auto* layout = new QVBoxLayout(this);
    auto* title = new QLabel("Your Emergency Circle");
    title->setStyleSheet("font-size: 16px; font-weight: bold; padding: 10px;");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);
    memberList_ = new QListWidget();
    memberList_->setStyleSheet("background: #34495e; color: white; border-radius: 4px;");
    layout->addWidget(memberList_);
    auto* inputRow = new QHBoxLayout();
    nameInput_ = new QLineEdit();
    nameInput_->setPlaceholderText("Enter username...");
    nameInput_->setStyleSheet("background: #34495e; color: white; padding: 6px; border-radius: 4px;");
    addBtn_ = new QPushButton("Add");
    addBtn_->setStyleSheet("background-color: #2ecc71; color: white; padding: 6px; border-radius: 4px;");
    inputRow->addWidget(nameInput_);
    inputRow->addWidget(addBtn_);
    layout->addLayout(inputRow);
    removeBtn_ = new QPushButton("Remove Selected");
    removeBtn_->setStyleSheet("background-color: #e74c3c; color: white; padding: 6px; border-radius: 4px;");
    layout->addWidget(removeBtn_);
    connect(addBtn_, &QPushButton::clicked, this, &CircleWindow::onAddClicked);
    connect(removeBtn_, &QPushButton::clicked, this, &CircleWindow::onRemoveClicked);
}
void CircleWindow::onAddClicked() {
    QString name = nameInput_->text().trimmed();
    if (!name.isEmpty()) { memberList_->addItem(name); nameInput_->clear(); }
}
void CircleWindow::onRemoveClicked() {
    auto* item = memberList_->currentItem();
    if (item) delete item;
}
void CircleWindow::addMember(const QString& name) { memberList_->addItem(name); }
void CircleWindow::removeMember(const QString& name) {
    for (int i = 0; i < memberList_->count(); i++)
        if (memberList_->item(i)->text() == name) { delete memberList_->item(i); break; }
}
QStringList CircleWindow::getMembers() const {
    QStringList members;
    for (int i = 0; i < memberList_->count(); i++) members << memberList_->item(i)->text();
    return members;
}
