/*=========================================================================
Copyright 2009 Rensselaer Polytechnic Institute
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. 
=========================================================================*/

//***********************************************************************************
// TableWindow provides a classic table view into a model
//***********************************************************************************
#include "TableWindow.h"

//Constructor
TableWindow::TableWindow(QItemSelectionModel *selectionModel, QWidget *parent)
: QMainWindow(parent)
{
	this->table = new QTableView();
	this->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->setCentralWidget(this->table);
	this->setWindowTitle(tr("Table"));
	// The following causes the program to get crashed if we close
	// the table first and the main window afterwards
	//this->setAttribute ( Qt::WA_DeleteOnClose );

	this->table->setModel( (QAbstractItemModel*)selectionModel->model() );
	this->table->setSelectionModel(selectionModel);
	this->table->setSelectionBehavior( QAbstractItemView::SelectRows );
	connect(selectionModel->model(), SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(modelChange(const QModelIndex &, const QModelIndex &)));

	this->createMenus();
}

void TableWindow::createMenus()
{
	viewMenu = menuBar()->addMenu(tr("View"));
	sortByAction = new QAction(tr("Sort by..."),this);
	connect(sortByAction, SIGNAL(triggered()), this, SLOT(sortBy()));
	viewMenu->addAction(sortByAction);
}

void TableWindow::sortBy()
{
	//Get the Currently Selected Features
	QStringList features;
	for( int i=0; i < this->table->model()->columnCount(); ++i)
	{	
		if( !this->table->isColumnHidden(i) )
		{
			features << this->table->model()->headerData(i,Qt::Horizontal).toString();
		}
	}
	
	//Let user choose one using popup:
	ChooseItemDialog *dialog = new ChooseItemDialog(features, this);
	if(!dialog->exec())
	{
		delete dialog;
		return;
	}
	QString feat = dialog->getSelectedItem();
	delete dialog;
	//Which column is this feature?
	for( int i=0; i < this->table->model()->columnCount(); ++i)
	{	
		if( this->table->model()->headerData(i,Qt::Horizontal).toString() == feat )
		{
			this->table->sortByColumn(i,Qt::AscendingOrder);
			emit sorted();
			break;
		}
	}
}

void TableWindow::modelChange(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
	//this->update();	//This is too big of an update, make it more specific
	int l_column = topLeft.column();
	int t_row = topLeft.row();
	int r_column = bottomRight.column();
	int b_row = bottomRight.row();

	for(int r=t_row; r<=b_row; r++)
	{
		table->resizeRowToContents(r);
		table->verticalHeader()->resizeSection(r,18);
	}
	for(int c=l_column; c<=r_column; c++)
	{
		table->resizeColumnToContents(c);
	}
}

void TableWindow::update()
{
	QWidget::update();
	table->resizeRowsToContents();
	table->resizeColumnsToContents();
	//Resize Rows to be as small as possible
	for (int i=0; i<table->model()->rowCount(); i++)
	{
		table->verticalHeader()->resizeSection(i,18);
	}
	//for(int i = visibleRows; i < table->model()->rowCount(); ++i)
	//{
	//	table->setColumnHidden(i,true);
	//}
}

void TableWindow::closeEvent(QCloseEvent *event)
{
	emit closing(this);
	event->accept();
} 

/*
void TableWindow::SetModels(QItemSelectionModel *selectionModel)
{
	table->setModel( (QAbstractItemModel*)selectionModel->model() );
	table->setSelectionModel(selectionModel);
}
*/

//***********************************************************************************
//This function calculates the optimal size of the window so that all columns can be
//displayed.  It also figures the a good height depending on the number of rows in the
//model.
//***********************************************************************************
void TableWindow::ResizeToOptimalSize(void)
{
	int screenWidth = qApp->desktop()->width();
	//Resize rows to minimum height
	table->resizeRowsToContents();
	table->resizeColumnsToContents();

	//Resize Rows to be as small as possible
	for (int i=0; i<table->model()->rowCount(); i++)
	{
		table->verticalHeader()->resizeSection(i,18);
	}

	//assumes all rows have the same height
	int rowHeight = table->rowHeight(0);
	int numRows = table->model()->rowCount();
	if (numRows > 5) numRows = 5;
	int bestHeight =( numRows + 1 ) * rowHeight;

	int bestWidth = 0;
	for (int i=0; i<table->model()->columnCount(); i++)
	{
		bestWidth = bestWidth + table->columnWidth(i);
	}
	bestWidth = bestWidth + 100;

	resize(bestWidth,bestHeight+5);

	if (this->frameGeometry().width() > screenWidth)
		resize(screenWidth-10,bestHeight+5);
}

ChooseItemDialog::ChooseItemDialog(QStringList items, QWidget *parent)
: QDialog(parent)
{
	itemCombo = new QComboBox();
	for (int i = 0; i < items.size(); ++i)
	{
		itemCombo->addItem( items.at(i) );
	}

	okButton = new QPushButton(tr("OK"),this);
	connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
	QHBoxLayout *bLayout = new QHBoxLayout;
	bLayout->addStretch(20);
	bLayout->addWidget(okButton);

	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(itemCombo);
	layout->addLayout(bLayout);
	this->setLayout(layout);
	this->setWindowTitle(tr("Choose Item"));

	Qt::WindowFlags flags = this->windowFlags();
	flags &= ~Qt::WindowContextHelpButtonHint;
	this->setWindowFlags(flags);
}