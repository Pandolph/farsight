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

#ifndef TABLEWINDOW_H
#define TABLEWINDOW_H

#include <QtGui/QAction>
#include <QtGui/QMainWindow>
#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>
#include <QtGui/QWidget>
#include <QtGui/QStatusBar>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QComboBox>
#include <QtGui/QItemSelection>
#include <QtGui/QItemSelectionModel>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QCloseEvent>
#include <QtGui/QDialog>

#include <iostream>

//#include "SegmentationModel.h"

class ChooseItemDialog;

class TableWindow : public QMainWindow
{
    Q_OBJECT;

public:
	TableWindow(QItemSelectionModel *mod, QWidget *parent = 0);

	//void SetModels(QItemSelectionModel *selectionModel);
	void ResizeToOptimalSize(void);

signals:
	void closing(QWidget *widget);
	void sorted();

protected:
	void closeEvent(QCloseEvent *event);

public slots:
	void update();
	void modelChange(const QModelIndex &topLeft, const QModelIndex &bottomRight);

private slots:
	void createMenus();
	void sortBy();
    
private:
	QTableView *table;

	QMenu *viewMenu;
	QAction *sortByAction;

	int visibleRows;
};

class ChooseItemDialog : public QDialog
{
	Q_OBJECT
public:
	ChooseItemDialog(QStringList items, QWidget *parent = 0);
	QString getSelectedItem(void){return itemCombo->currentText();};

private:
	QComboBox *itemCombo;
	QPushButton *okButton;
};

#endif
