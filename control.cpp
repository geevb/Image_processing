
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <fstream>
#include "filters.cpp"
#include "view.cpp"

std::string verificarTipoExibicao();
void executarComWebcam();
void executarComImagem();
cv::Mat verificarImagemEscolhida(std::string nomeImagem);
void executarTipo(std::string tipo);
void fluxo();
void aplicarFiltroNaImagem(int filtro, cv::Mat imagem);

std::string verificarTipoExibicao() {
    return perguntarTipoExibicao();
}

void executarComWebcam() {

}

void executarComImagem() {
    std::string imagem = perguntarQualImagem();
    cv::Mat image = verificarImagemEscolhida(imagem);

    int filtro = perguntarQualFiltro();
    aplicarFiltroNaImagem(filtro, image);

}

cv::Mat verificarImagemEscolhida(std::string nomeImagem) {
    Mat image;
    image = imread( "images/" + nomeImagem, 1 );
    while(true) {
        if(image.data) {
            break;
        }
        
        std::string novoNome = perguntarQualImagem();
        image = imread( "images/" + novoNome, 1 );
    }

    return image;
}

void executarTipo(std::string tipo) {
    if(tipo.compare("1") == 0) {
        // executarComWebcam();
    } else {
        executarComImagem();
    }
}

void aplicarFiltroNaImagem(int filtro, cv::Mat imagem) {
    cv::Mat filteredImage;
    switch(filtro) {
        case 1:{
            filteredImage = converterParaCinzaMedia(imagem);
            break;
        }
        case 2:{
            filteredImage = converterParaCinzaPonderado(imagem);
            break;
        }
        case 3:{
            filteredImage = converterParaCorInvertida(imagem);
            break;
        }
        case 4: {
            int limiar = perguntarQualValorLimiar();
            filteredImage = limiarizar(imagem, limiar);
            break;
        }
        case 5: {
            std::string cor = perguntarQualCor();
            filteredImage = isolarCanalDeCor(cor, imagem);
            break;
        }
        case 6:{
            // TODO PEGAR COR, TIPO, VALOR
            std::string cor = perguntarQualCor();
            filteredImage = incrementarCanaisDeDor(cor, 0, 0, imagem);
            break;
        }
        case 7: {
            int valorZoom = perguntarValorZoom();
            filteredImage = zoomIn(0, imagem);
            break;
        }
        case 8:
            // TODO PEGAR SEGUNDA IMAGEM
            {
            filteredImage = somarImagem(imagem, filteredImage);
            break;
        }
        case 9: {
            filteredImage = subtrairImagem(imagem, filteredImage);
            break;
        }
        default:
            std::cout << "default\n";
            break;
    }

    apresentarImagem(filteredImage);
}

void fluxo() {
    std::string tipo = verificarTipoExibicao();
    executarTipo(tipo);
}