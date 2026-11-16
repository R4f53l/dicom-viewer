#include "DicomLoader.h"
#include <dcmtk/dcmjpeg/djdecode.h>  
#include <dcmtk/dcmdata/dcrledrg.h>
#include <dcmtk/dcmimgle/dcmimage.h>
#include <QFile>
#include <memory>

DicomLoadResult DicomLoader::loadImageFromFile (const QString &filepath){

    static bool codecsRegistered = false; 
    if(!codecsRegistered){
        DJDecoderRegistration::registerCodecs();  
        DcmRLEDecoderRegistration::registerCodecs(); 
        codecsRegistered = true; 
    }
    
    DicomLoadResult result;     
    auto dcmImage = std::make_unique<DicomImage>(QFile::encodeName(filepath).constData());

    if(!dcmImage || dcmImage->getStatus() != EIS_Normal){
        result.errorMessage = "Nao foi possivel ler o arquivo DICOM!"; 
        return result; 
    }

    /*if(!dcmImage->isMonochrome()){
        result.errorMessage = "A imagem nao possui tons monocromaticos!"; 
        return result; 
    }*/

    //normaliza de 0 a 255; 
    dcmImage->setMinMaxWindow(); 

    const int width = static_cast<int>(dcmImage -> getWidth()); 
    const int height = static_cast<int> (dcmImage -> getHeight()); 
    
    const auto *pixelData = static_cast<const uint8_t *>(dcmImage -> getOutputData(8));
    
    if(!pixelData){
        result.errorMessage = "Erro ao extrair os dados de pixel da imagem!"; 
        return result; 
    }

    QImage Image(pixelData, width, height, width, QImage::Format_Grayscale8);     
    result.image = Image.copy(); 
    result.success = true; 

    return result; 

}
