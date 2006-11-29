#include "dlgfilters.h"
#include "filterwidget.h"
 
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
 
DlgFilters::DlgFilters(const QList<QPair<bool,QString> >& filters,
            QWidget *parent)
        : QDialog(parent, Qt::Dialog) {
    setWindowTitle(tr("strigiclient - Edit filters"));
    QLabel* explanation = new QLabel(tr("Define filters that determine which files will be included and which will be excluded from the index, e.g. '*.html' or '.svn/' (do not index directories called '.svn')."));
    explanation->setWordWrap(true);
    filterwidget = new FilterWidget();
    filterwidget->setFilters(filters);
    QPushButton* ok = new QPushButton(tr("&Ok"));
    ok->setDefault(true);
    QPushButton* cancel = new QPushButton(tr("&Cancel"));
 
    QVBoxLayout* layout = new QVBoxLayout();
    setLayout(layout);
    layout->addWidget(explanation);
    layout->addWidget(filterwidget);
    QHBoxLayout* hl = new QHBoxLayout();
    layout->addLayout(hl);
    hl->addStretch();
    hl->addWidget(ok);
    hl->addWidget(cancel);
    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
}
const QList<QPair<bool,QString> >&
DlgFilters::getFilters() const {
    return filterwidget->getFilters();
}