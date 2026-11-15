#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <dcmtk/dcmimgle/dcmimage.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);    
    QLabel label("Qt + DCMTK funcionando no WSL!");
    label.resize(400, 200);
    label.setAlignment(Qt::AlignCenter);
    label.show();

    
    

    return app.exec();
}