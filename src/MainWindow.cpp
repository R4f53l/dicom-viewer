#include "MainWindow.h"
#include "DicomLoader.h"

#include <QVBoxLayout> 
#include <QFileDialog>
#include <QMessageBox>
#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    setWindowTitle("Visualizador DICOM"); 
    resize(800, 600); 

    auto *centralWidget = new QWidget(this); 
    auto *layout = new QVBoxLayout(centralWidget); 

    m_button = new QPushButton("CLIQUE para abrir arquivo DICOM (.dcm)", centralWidget);
    m_imagelabel = new QLabel ("Selecione um arquivo DICOM para visualizar", centralWidget); 
    m_imagelabel -> setAlignment(Qt::AlignCenter); 
    m_imagelabel -> setMinimumSize(400, 300); 
    
    layout -> addWidget(m_button); 
    layout -> addWidget(m_imagelabel, 1); 
    setCentralWidget(centralWidget); 

    connect(m_button, &QPushButton::clicked, this, &MainWindow::onOpenFileClicked);
}

void MainWindow::resizeEvent(QResizeEvent *event){
    QMainWindow::resizeEvent(event); 
    updateImageDisplay(); 
}

void MainWindow::onOpenFileClicked(){
    QString filepath = QFileDialog::getOpenFileName(
        this, "Selecionar DICOM", "", "Arquivos DICOM (*.dcm);;Todos os Arquivos (*)"); 
    
    if(filepath.isEmpty())
        return; 
    
    DicomLoadResult result = DicomLoader::loadImageFromFile(filepath); 

    if(!result.success){
        QMessageBox::critical(this, "Erro ao abrir DCOM", result.errorMessage); 
        return; 
    }

    m_currpixmap = QPixmap::fromImage(result.image); 

    updateImageDisplay(); 
}

void MainWindow::updateImageDisplay(){
    if(m_currpixmap.isNull())
        return; 
    m_imagelabel->setPixmap(m_currpixmap.scaled(
        m_imagelabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation
    ));
}