/*
-----------------------------------------------------------------------------
Copyright (c) 26.02.2014 Tobias Peters <tobias.peters@kreativeffekt.at>

This file is part of Q-Gears

Q-Gears is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 2.0 (GPLv2) of the License.

Q-Gears is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
-----------------------------------------------------------------------------
*/

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , model(new QFileSystemModel)
{
    ui->setupUi(this);
    model->setRootPath( ":/new/prefix1" );
    ui->treeView->setModel( model );
    ui->treeView->setRootIndex( model->index( ":/new/prefix1" ) );
    QDir res_dir( ":/new/prefix1");
    qDebug() << res_dir.entryList();
}

MainWindow::~MainWindow()
{
    delete ui;
}
