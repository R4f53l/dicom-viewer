#pragma once 
#include <QImage>
#include <QString>

struct DicomLoadResult{
    bool success = false; 
    QImage image; 
    QString errorMessage;     
    QString metaDataText;
}; 

class DicomLoader{
public:
    static DicomLoadResult loadImageFromFile(const QString &filepath);

private: 
    static QString extractMetaData(const QByteArray &encodedpath, int widht, int height);
}; 
