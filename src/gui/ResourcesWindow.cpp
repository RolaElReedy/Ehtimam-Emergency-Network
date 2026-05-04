#include "ResourcesWindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

ResourcesWindow::ResourcesWindow(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Emergency Hotlines - Egypt");
    setMinimumSize(420, 520);
    setStyleSheet("background-color: #2c3e50;");
    auto* layout = new QVBoxLayout(this);
    layout->setSpacing(8);
    layout->setContentsMargins(20, 20, 20, 20);
    auto* title = new QLabel("Emergency Hotlines - Egypt");
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #e74c3c;");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);
    auto* subtitle = new QLabel("In case of emergency, call:");
    subtitle->setStyleSheet("font-size: 12px; color: #bdc3c7; margin-bottom: 8px;");
    subtitle->setAlignment(Qt::AlignCenter);
    layout->addWidget(subtitle);
    auto addRow = [&](const QString& name, const QString& number) {
        auto* row = new QWidget();
        row->setStyleSheet("background-color: #34495e; border-radius: 6px; padding: 4px;");
        auto* rowLayout = new QHBoxLayout(row);
        rowLayout->setContentsMargins(12, 8, 12, 8);
        auto* nameLabel = new QLabel(name);
        nameLabel->setStyleSheet("color: #ecf0f1; font-size: 13px;");
        auto* numLabel = new QLabel(number);
        numLabel->setStyleSheet("color: #e74c3c; font-size: 16px; font-weight: bold;");
        numLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        rowLayout->addWidget(nameLabel);
        rowLayout->addStretch();
        rowLayout->addWidget(numLabel);
        layout->addWidget(row);
    };
    addRow("Ambulance", "123");
    addRow("Police", "122");
    addRow("Fire Department", "180");
    addRow("Traffic Police", "128");
    addRow("Child Helpline", "16000");
    addRow("National Council for Women", "15115");
    addRow("Electricity Emergency", "121");
    addRow("Gas Emergency", "129");
    layout->addStretch();
    auto* closeBtn = new QPushButton("Close");
    closeBtn->setStyleSheet("background-color: #7f8c8d; color: white; padding: 10px; border-radius: 4px; font-size: 13px;");
    layout->addWidget(closeBtn);
    connect(closeBtn, &QPushButton::clicked, this, &QDialog::accept);
}
