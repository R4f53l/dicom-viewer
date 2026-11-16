#pragma once

#include <QMainWindow> 
#include <QPushButton>
#include <QLabel>
#include <QPixmap>

class MainWindow : public QMainWindow{
    Q_OBJECT

public: 
    explicit MainWindow(QWidget *parent = nullptr); 
    
protected:
    void resizeEvent(QResizeEvent *event) override; 

private slots:     
    void onOpenFileClicked(); 
    
private: 
    void updateImageDisplay(); 
    QPushButton *m_button = nullptr; 
    QLabel *m_imagelabel = nullptr; 
    QPixmap m_currpixmap; 
}; 

