#include "tablewidget.h"

#include "tableview.h"

#include <LBGui/LBGui.h>
#include <LBDatabase/LBDatabase.h>

#include <QScrollArea>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QFileInfo>
#include <QStandardItemModel>

namespace LBGui {

TableWidget::TableWidget(QWidget *parent) :
    TabWidget(parent),
    m_table(0)
{
#ifdef Q_WS_MAC
    setStyle(TabWidget::ItunesWhite);
#endif

    QWidget *overviewWidget = new QWidget();
    overviewWidget->setBackgroundRole(QPalette::Base);
    QVBoxLayout *overviewLayout = new QVBoxLayout();
    overviewLayout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    overviewLayout->setContentsMargins(0,0,0,40);
    overviewWidget->setLayout(overviewLayout);

    GroupBox *typesGroupBox = new GroupBox(overviewWidget);
    typesGroupBox->setFixedWidth(792);
    typesGroupBox->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::MinimumExpanding);
    typesGroupBox->setStyle(GroupBox::ItunesWhite);
    typesGroupBox->setTitle(tr("Types"));
    QVBoxLayout *typesLayout = new QVBoxLayout(typesGroupBox);
    typesGroupBox->setLayout(typesLayout);
    TreeView *typesListWidget = new TreeView(typesGroupBox);
    typesListWidget->setStyle(TreeView::ItunesWhite);
    typesLayout->addWidget(typesListWidget);
    overviewLayout->addWidget(typesGroupBox);

//    GroupBox *attributesGroupBox = new GroupBox(overviewWidget);
//    attributesGroupBox->setFixedWidth(792);
//    attributesGroupBox->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::MinimumExpanding);
//    attributesGroupBox->setStyle(GroupBox::ItunesWhite);
//    attributesGroupBox->setTitle(tr("Attributes"));
//    QVBoxLayout *attributesLayout = new QVBoxLayout(attributesGroupBox);
//    attributesGroupBox->setLayout(attributesLayout);
//    m_attributesTable = new AttributesTable(attributesGroupBox);
//    m_attributesTable->setStyle(TreeView::ItunesWhite);
//    attributesLayout->addWidget(m_attributesTable);
//    ListEditButtonsWidget *attributesListEditButtonsWidget = new ListEditButtonsWidget(attributesGroupBox);
//    connect(attributesListEditButtonsWidget, SIGNAL(editClicked()), this, SLOT(editSelectedAttribute()));
//    connect(attributesListEditButtonsWidget, SIGNAL(addClicked()), this, SLOT(addAttribute()));
//    connect(attributesListEditButtonsWidget, SIGNAL(removeClicked()), this, SLOT(removeAttribute()));
//    attributesLayout->addWidget(attributesListEditButtonsWidget);
//    overviewLayout->addWidget(attributesGroupBox);

    QScrollArea *overviewScrollArea = new QScrollArea();
    overviewScrollArea->setWidget(overviewWidget);
    overviewScrollArea->setWidgetResizable(true);

//    addTab(overviewScrollArea,tr("Overview"));

    QWidget *plainContentsWidget = new QWidget();
    QVBoxLayout *plainContentsLayout = new QVBoxLayout();
    plainContentsLayout->setContentsMargins(0,0,0,0);
    plainContentsWidget->setLayout(plainContentsLayout);
    m_plainContentsTableView = new TableView(plainContentsWidget);
    plainContentsLayout->addWidget(m_plainContentsTableView);
    addTab(plainContentsWidget,tr("Plain view"));
}

void TableWidget::setTable(LBDatabase::Table *table)
{
    m_table = table;
    setWindowTitle(table->name()+ QString::fromUtf8(" \u2013 ")+QFileInfo(table->database()->fileName()).fileName());
    m_plainContentsTableView->setTable(table);
}

TableView *TableWidget::tableView() const
{
    return m_plainContentsTableView;
}

} // namespace LBGui
