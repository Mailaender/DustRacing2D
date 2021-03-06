// This file is part of Dust Racing 2D.
// Copyright (C) 2012 Jussi Lind <jussi.lind@iki.fi>
//
// Dust Racing 2D is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// Dust Racing 2D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Dust Racing 2D. If not, see <http://www.gnu.org/licenses/>.

#include "trackpropertiesdialog.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QIntValidator>

TrackPropertiesDialog::TrackPropertiesDialog(unsigned int index, QWidget * parent)
: QDialog(parent)
, m_layout(new QGridLayout(this))
, m_okButton(new QPushButton(tr("Ok")))
, m_cancelButton(new QPushButton(tr("Cancel")))
, m_indexEdit(new QLineEdit)
, m_indexLabel(new QLabel(tr("Index:")))
{
    setWindowTitle(tr("Set track properties"));

    QIntValidator * indexValidator = new QIntValidator(this);
    indexValidator->setRange(0, 999);
    m_indexEdit->setValidator(indexValidator);
    m_indexEdit->setText(QString("%1").arg(index));

    m_layout->addWidget(m_indexLabel,    0, 0);
    m_layout->addWidget(m_indexEdit,     0, 1);
    m_layout->addWidget(m_okButton,      3, 0);
    m_layout->addWidget(m_cancelButton,  3, 1);

    connect(m_okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

unsigned int TrackPropertiesDialog::index() const
{
    return m_indexEdit->text().toInt();
}
