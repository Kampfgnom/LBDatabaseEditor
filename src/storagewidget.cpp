#include "storagewidget.h"

#include <LBDatabase/LBDatabase.h>

#include <QVBoxLayout>
#include <QScrollArea>
#include <QListWidget>

namespace LBGui {

StorageWidget::StorageWidget(QWidget *parent) :
    TabWidget(parent)
{
#ifdef Q_WS_MAC
    setStyle(TabWidget::ItunesWhite);
#endif

    QWidget *overviewWidget = new QWidget();
    overviewWidget->setBackgroundRole(QPalette::Base);
    QVBoxLayout *overviewLayout = new QVBoxLayout();
    overviewLayout->setContentsMargins(0,0,0,40);
    overviewLayout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    overviewWidget->setLayout(overviewLayout);

    GroupBox *tablesGroupBox = new GroupBox(overviewWidget);
    tablesGroupBox->setFixedWidth(792);
    tablesGroupBox->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::MinimumExpanding);
    tablesGroupBox->setStyle(GroupBox::ItunesWhite);
    tablesGroupBox->setTitle(tr("Tables"));
    QVBoxLayout *tablesLayout = new QVBoxLayout(tablesGroupBox);
    tablesGroupBox->setLayout(tablesLayout);
    m_contextListWidget = new QListWidget(tablesGroupBox);
    m_contextListWidget->setAlternatingRowColors(true);
    m_contextListWidget->setAttribute(Qt::WA_MacShowFocusRect, false);
    QFile stylesheet;
    stylesheet.setFileName(QLatin1String(":/listwidget/itunes_white/stylesheet"));
    stylesheet.open(QFile::ReadOnly);
    m_contextListWidget->setStyleSheet(stylesheet.readAll());
    stylesheet.close();
    tablesLayout->addWidget(m_contextListWidget);
    overviewLayout->addWidget(tablesGroupBox);

//    GroupBox *sourceGroupBox = new GroupBox(overviewWidget);
//    sourceGroupBox->setCheckable(true);
//    sourceGroupBox->setChecked(false);
//    sourceGroupBox->setFixedWidth(792);
//    sourceGroupBox->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Maximum);
//    sourceGroupBox->setStyle(GroupBox::ItunesWhite);
//    sourceGroupBox->setTitle(tr("Keep sources in sync (not supported yet)"));
//    QHBoxLayout *sourceLayout = new QHBoxLayout();
//    sourceGroupBox->setLayout(sourceLayout);
//    sourceLayout->addWidget(new QLabel(tr("Source directory")));
//    sourceLayout->addWidget(new QLineEdit());
//    QPushButton *chooseSourceButton = new QPushButton(tr("Choose..."),sourceGroupBox);
//    sourceLayout->addWidget(chooseSourceButton);

//    overviewLayout->addWidget(sourceGroupBox);

    QScrollArea *overviewScrollArea = new QScrollArea();
    overviewScrollArea->setWidget(overviewWidget);
    overviewScrollArea->setWidgetResizable(true);

    addTab(overviewScrollArea,tr("Overview"));
}

void StorageWidget::setStorage(LBDatabase::Storage *storage)
{
    setWindowTitle(storage->name());

    m_contextListWidget->clear();
    foreach(LBDatabase::Context *context, storage->contexts()) {
        m_contextListWidget->addItem(context->name());
    }
}

} // namespace LBGui
