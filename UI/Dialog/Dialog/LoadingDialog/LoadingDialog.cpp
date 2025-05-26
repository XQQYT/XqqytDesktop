/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "LoadingDialog.h"
#include "ui_LoadingDialog.h"
#include <iostream>
#include <QMovie>

LoadingDialog::LoadingDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoadingDialog)
{
    ui->setupUi(this);
    ui->progressBar->hide();
    // 设置无边框 + 背景透明
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground); 
    setModal(true);

    // 设置固定大小（你也可以根据 GIF 动态获取）
    setFixedSize(100, 100);

    // 加载并缩放 GIF
    movie = new QMovie(":/images/pic/loading.gif");
    ui->label_loading->setMovie(movie);
    ui->label_loading->setAlignment(Qt::AlignCenter);
    ui->label_loading->setScaledContents(true);  // QLabel 自动缩放内容
    movie->start();
}

LoadingDialog::~LoadingDialog()
{
    delete movie;
    delete ui;
}

void LoadingDialog::setProgress(int progress)
{
    ui->progressBar->show();   
    ui->progressBar->setValue(progress);
}