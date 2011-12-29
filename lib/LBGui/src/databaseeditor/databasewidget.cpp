#include "databasewidget.h"

#include <widgets/groupbox.h>

#include <LBDatabase/LBDatabase.h>

#include <QFileInfo>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>

namespace LBGui {

DatabaseWidget::DatabaseWidget(QWidget *parent) :
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
    m_tablesListWidget = new QListWidget(tablesGroupBox);
    m_tablesListWidget->setAlternatingRowColors(true);
    m_tablesListWidget->setAttribute(Qt::WA_MacShowFocusRect, false);
    QFile stylesheet;
    stylesheet.setFileName(QLatin1String(":/listwidget/itunes_white/stylesheet"));
    stylesheet.open(QFile::ReadOnly);
    m_tablesListWidget->setStyleSheet(stylesheet.readAll());
    stylesheet.close();
    tablesLayout->addWidget(m_tablesListWidget);
    overviewLayout->addWidget(tablesGroupBox);

    GroupBox *sourceGroupBox = new GroupBox(overviewWidget);
    sourceGroupBox->setCheckable(true);
    sourceGroupBox->setChecked(false);
    sourceGroupBox->setFixedWidth(792);
    sourceGroupBox->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Maximum);
    sourceGroupBox->setStyle(GroupBox::ItunesWhite);
    sourceGroupBox->setTitle(tr("Keep sources in sync (not supported yet)"));
    QHBoxLayout *sourceLayout = new QHBoxLayout();
    sourceGroupBox->setLayout(sourceLayout);
    sourceLayout->addWidget(new QLabel(tr("Source directory")));
    sourceLayout->addWidget(new QLineEdit());
    QPushButton *chooseSourceButton = new QPushButton(tr("Choose..."),sourceGroupBox);
    sourceLayout->addWidget(chooseSourceButton);

    overviewLayout->addWidget(sourceGroupBox);

    QScrollArea *overviewScrollArea = new QScrollArea();
    overviewScrollArea->setWidget(overviewWidget);
    overviewScrollArea->setWidgetResizable(true);

    addTab(overviewScrollArea,tr("Overview"));
}

void DatabaseWidget::setDatabase(LBDatabase::Database *database)
{
    setWindowTitle(QFileInfo(database->fileName()).fileName());

    m_tablesListWidget->clear();
    foreach(LBDatabase::Table *table, database->tables()) {
        m_tablesListWidget->addItem(table->name());
    }
}

} // namespace LBGui
