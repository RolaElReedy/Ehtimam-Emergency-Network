#include "ResourcesWindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
ResourcesWindow::ResourcesWindow(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Emergency Resources");
    setFixedSize(400, 500);
    setStyleSheet("background-color: #2c3e50; color: white;");
    auto* layout = new QVBoxLayout(this);
    auto* title = new QLabel("Emergency Hotlines - Egypt");
    title->setStyleSheet("font-size: 16px; font-weight: bold; color: #e74c3c; padding: 10px;");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);
    struct Hotline { QString name; QString number; };
    QList<Hotline> hotlines = {
        {"Ambulance", "123"},
        {"Police", "122"},
        {"Fire Department", "180"},
        {"Traffic Police", "128"},
        {"Child Helpline", "16000"},
        {"Women Hotline (NCW)", "15115"},
        {"Electricity Emergency", "121"},
        {"Gas Emergency", "129"}
    };
    for (auto& h : hotlines) {
        auto* row = new QWidget();
        row->setStyleSheet("background: #34495e; border-radius: 6px; margin: 3px;");
        auto* rowLayout = new QHBoxLayout(row);
        auto* nameLabel = new QLabel(h.name);
        nameLabel->setStyleSheet("color: white; font-size: 13px; padding: 8px;");
        auto* numLabel = new QLabel(h.number);
        numLabel->setStyleSheet("color: #e74c3c; font-size: 16px; font-weight: bold; padding: 8px;");
        numLabel->setAlignment(Qt::AlignRight);
        rowLayout->addWidget(nameLabel);
        rowLayout->addWidget(numLabel);
        layout->addWidget(row);
    }
    auto* closeBtn = new QPushButton("Close");
    closeBtn->setStyleSheet("background-color: #7f8c8d; color: white; padding: 8px; border-radius: 4px; margin-top: 10px;");
    layout->addWidget(closeBtn);
    connect(closeBtn, &QPushButton::clicked, this, &QDialog::accept);
}
