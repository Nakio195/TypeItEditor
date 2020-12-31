#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelection>
#include <QDataWidgetMapper>
#include "../TypeIt/TypeIt/Book.h"
#include "SceneModel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public slots:
        bool openBook();
        void onSceneSelect(const QItemSelection &i, const QItemSelection &j);

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:
        Ui::MainWindow *ui;
        Book mBook;
        SceneModel *mScenes;

        QDataWidgetMapper *mSceneMapper;

};
#endif // MAINWINDOW_H
