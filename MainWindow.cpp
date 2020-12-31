#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QAction>
#include <QJsonDocument>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(QString("TypeIt Creator"));

    mScenes = nullptr;

    mSceneMapper = new QDataWidgetMapper(this);

    connect(ui->actionOuvrir, &QAction::triggered, this, &MainWindow::openBook);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSceneSelect(const QItemSelection &i , const QItemSelection &j)
{
    mSceneMapper->setCurrentModelIndex(i.indexes().first());
    Scene* scene = static_cast<Scene*>(i.indexes().first().internalPointer());

    qDebug() << "Selection changed : " << scene->mName << ", " << i.indexes().first().column();
}

bool MainWindow::openBook()
{
    QString bookPath = QFileDialog::getOpenFileName(this, tr("Ouvrir un livre"));

    if(!mBook.load(bookPath))
    {
        QMessageBox::warning(this, tr("Erreur.."), QString("Impossible de charger le livre ") + bookPath);
        return false;
    }

    if(mScenes != nullptr)
        delete mScenes;

    mScenes = new SceneModel(mBook.startScene(), this);

    ui->sceneView->setModel(mScenes);

    mSceneMapper->setModel(mScenes);
    mSceneMapper->addMapping(ui->lbl_id, 0);
    mSceneMapper->addMapping(ui->ln_Name, 1);
    mSceneMapper->addMapping(ui->txt_Text, 2);

    connect(ui->sceneView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::onSceneSelect);

    return true;
}
