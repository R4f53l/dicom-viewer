#include "DicomLoader.h"
#include <QFile>
#include <memory>
#include <QDate>
#include <dcmtk/dcmjpeg/djdecode.h>  
#include <dcmtk/dcmdata/dcrledrg.h>
#include <dcmtk/dcmimgle/dcmimage.h>
#include <dcmtk/dcmimage/diregist.h>
#include <dcmtk/dcmdata/dcfilefo.h>
#include <dcmtk/dcmdata/dctk.h>


DicomLoadResult DicomLoader::loadImageFromFile (const QString &filepath){
    DicomLoadResult result;


    static bool codecsRegistered = false; 
    if(!codecsRegistered){
        DJDecoderRegistration::registerCodecs();  
        DcmRLEDecoderRegistration::registerCodecs();        
        codecsRegistered = true; 
    }    
    const auto encondedpath = QFile::encodeName(filepath);     
    auto dcmImage = std::make_unique<DicomImage>(QFile::encodeName(filepath).constData());

    if(!dcmImage || dcmImage->getStatus() != EIS_Normal){
        result.errorMessage = "Nao foi possivel ler o arquivo DICOM!"; 
        return result; 
    }

    auto isMono = dcmImage->isMonochrome(); 

    if(isMono){    
        //normaliza de 0 a 255; 
        dcmImage->setMinMaxWindow();     
    }
    

    const int width = static_cast<int>(dcmImage -> getWidth()); 
    const int height = static_cast<int> (dcmImage -> getHeight()); 
    
    const auto *pixelData = static_cast<const uint8_t *>(dcmImage -> getOutputData(8));
    
    if(!pixelData){
        result.errorMessage = "Erro ao extrair os dados de pixel da imagem!"; 
        return result; 
    }

    const auto bytesperline = isMono? width: 3 * width; 
    QImage::Format format = isMono? QImage::Format_Grayscale8 : QImage::Format_RGB888; 
    QImage Image(pixelData, width, height, bytesperline, format);     
    result.image = Image.copy(); 
    result.metaDataText = extractMetaData(encondedpath, width, height); 
    result.success = true; 

    return result; 
}


QString DicomLoader::extractMetaData(const QByteArray &encondedpath, int width, int height){
    DcmFileFormat fileFormat; 
    if(fileFormat.loadFile(encondedpath.constData()).bad()){
        return "Metadados indisponiveis!"; 
    }

    //dicionario das tags
    DcmDataset *dcmdataset = fileFormat.getDataset(); 
    
    auto getTag =  [&](const DcmTagKey &key) -> QString {
        OFString val; 
        if(dcmdataset -> findAndGetOFStringArray(key, val).good() && !val.empty()){
            return QString::fromLatin1(val.c_str()).trimmed(); 
        }
        return "N/A"; 
    };

    QString rawdate = getTag(DCM_StudyDate); 
    QDate parsedDate = QDate::fromString(rawdate, "yyyyMMdd"); 
    QString formattedDate = parsedDate.isValid() ? parsedDate.toString("dd/MM/yyyy") : rawdate;  

    return QString("Paciente: %1 | ID: %2 | Data: %3 | Modalidade: %4 | Resolução: %5x%6")
        .arg(getTag(DCM_PatientName),
            getTag(DCM_PatientID),
            formattedDate,
            getTag(DCM_Modality),
            QString::number(width),
            QString::number(height));
    

}