# Visualizador DICOM com Qt e C++

Aplicação desktop desenvolvida em C++17 utilizando Qt 6 Widgets e DCMTK para leitura, descompressão e visualização de imagens médicas no formato DICOM (`.dcm`).

## Descrição da Solução

A arquitetura foi dividida em duas camadas principais, separando o processamento dos dados médicos da interface gráfica.

- **`DicomLoader` (`src/DicomLoader.h`, `src/DicomLoader.cpp`):** Encapsula a biblioteca DCMTK. Realiza o registro dos codecs de descompressão JPEG e RLE, valida a integridade do arquivo, aplica a normalização automática de brilho e contraste (`setMinMaxWindow`), converte os pixels para 8 bits em escala de cinza (`Format_Grayscale8`) ou RGB (`Format_RGB888`) e realiza a cópia dos dados para a memória gerenciada pelo Qt (`QImage`).

- **`MainWindow` (`src/MainWindow.h`, `src/MainWindow.cpp`):** Gerencia a interface gráfica utilizando Qt Widgets. Permite a seleção de arquivos por meio de `QFileDialog`, a exibição responsiva da imagem (`QLabel` + `QPixmap`), com preservação da proporção durante o redimensionamento da janela (`resizeEvent`), e o tratamento visual de erros para arquivos inválidos ou corrompidos (`QMessageBox`).

## Bibliotecas Utilizadas

- **Qt 6 (Widgets e Gui):** Desenvolvimento da interface gráfica,
  gerenciamento de janelas, layouts, diálogos, eventos e manipulação
  e exibição de imagens (`QImage`, `QPixmap`, `QLabel`, `QFileDialog`, `QMessageBox`, etc).
- **DCMTK (`libdcmtk-dev`):** Leitura de arquivos DICOM, decodificação JPEG/RLE (`dcmjpeg`, `dcrledrg`) e processamento de janela e contraste (`DicomImage`).

### Ferramentas e Padrões

- **C++17:** Linguagem utilizada no desenvolvimento.
- **CMake:** Sistema de configuração e compilação do projeto.

## Versão do Qt Utilizada

- **Qt 6.4.2**

## Instruções de Configuração, Compilação e Execução

### 1. Instalar dependências (Ubuntu / Debian)

```bash
sudo apt update
sudo apt install -y build-essential cmake qt6-base-dev libdcmtk-dev libnsl-dev
```

### 2. Clonar e compilar o projeto

```bash
git clone https://github.com/R4f53l/dicom-viewer.git
cd dicom-viewer

cmake -S . -B build
cmake --build build -j$(nproc)
```

### 3. Executar a aplicação

Para executar:

```bash
./build/dicom-viewer
```