#pragma once 
#include <QImage>
#include <QString>

struct DicomLoadResult{
    bool success = false; 
    QImage image; 
    QString errorMessage;    
}; 

class DicomLoader{
public:
    static DicomLoadResult loadImageFromFile(const QString &filepath);   
}; 
