
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <fstream>
#include "filters.cpp"
#include "view.cpp"

struct valores {
    std::string cor;
    cv::Mat segundaImagem;
    int zoom;
    int limiar;
    int tipo;
    int valor;
    int valor2;
};

std::string verificarTipoExibicao();
int executarComWebcam();
void executarComImagem();
cv::Mat verificarImagemEscolhida(std::string nomeImagem);
void executarTipo(std::string tipo);
void fluxo();
cv::Mat aplicarFiltroNaImagem(int filtro, cv::Mat imagem, valores vals);
valores pegarValoresDoFiltro(int filtro);

std::string verificarTipoExibicao() {
    return perguntarTipoExibicao();
}

int executarComWebcam() {
    int filtro = perguntarQualFiltro();
    valores vals = pegarValoresDoFiltro(filtro);

    cv::VideoCapture cap;
        if(!cap.open(0)) return 0;
        for(;;) {
            Mat frame;
            cap >> frame;
            frame = aplicarFiltroNaImagem(filtro, frame, vals);
            if( frame.empty() ) break;
            
            if( apresentarVideo(frame) >= 0) break;
        }
    return 0;
}

void executarComImagem() {
    std::string imagem = perguntarQualImagem();
    cv::Mat image = verificarImagemEscolhida(imagem);

    int filtro = perguntarQualFiltro();
    valores vals = pegarValoresDoFiltro(filtro);

    Mat filteredImage = aplicarFiltroNaImagem(filtro, image, vals);
    apresentarImagem(filteredImage);
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
        executarComWebcam();
    } else {
        executarComImagem();
    }
}

valores pegarValoresDoFiltro(int filtro) {

    valores vals;

    switch(filtro) {
        case 4: {
            vals.limiar = perguntarQualValorLimiar();
            break;
        }
        case 5: {
            std::string cor = perguntarQualCor();
            vals.cor = cor;
            break;
        }
        case 6:{
            vals.cor = perguntarQualCor();
            vals.tipo = perguntarTipoAcrescimo();
            vals.valor = perguntarValorAcrescimo();
            break;
        }
        case 7: {
            vals.zoom = perguntarValorZoom();
            break;
        }
        case 8: {
            vals.zoom = perguntarValorZoom();
            break;
        }
        case 9: {
            std::string nomeImagem = perguntarSegundaImagem();
            Mat secondImage = verificarImagemEscolhida(nomeImagem);
            vals.segundaImagem = secondImage;
            break;
        }
        case 10: {
            std::string nomeImagem = perguntarSegundaImagem();
            Mat secondImage = verificarImagemEscolhida(nomeImagem);
            vals.valor = perguntarValoresSomaPonderadaPrimeiraImagem();
            vals.valor2 = perguntarValoresSomaPonderadaSegundaImagem();
            vals.segundaImagem = secondImage;
            break;
        }
        case 11: {
            std::string nomeImagem = perguntarSegundaImagem();
            Mat secondImage = verificarImagemEscolhida(nomeImagem);
            vals.segundaImagem = secondImage;
            break;
        }
        default:
            break;
    }

    return vals;
}

cv::Mat aplicarFiltroNaImagem(int filtro, cv::Mat imagem, valores vals) {
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
            filteredImage = limiarizar(imagem, vals.limiar);
            break;
        }
        case 5: {
            filteredImage = isolarCanalDeCor(vals.cor, imagem);
            break;
        }
        case 6:{
            filteredImage = incrementarCanaisDeDor(vals.cor, vals.tipo, vals.valor, imagem);
            break;
        }
        case 7: {
            filteredImage = zoomIn(vals.zoom, imagem);
            break;
        }
        case 8: {
            filteredImage = zoomOut(vals.zoom, imagem);
            break;
        }
        case 9: {
            filteredImage = somarImagem(imagem, vals.segundaImagem);
            break;
        }
        case 10: {
            filteredImage = somarImagemPonderada(imagem, vals.segundaImagem, vals.valor, vals.valor2);
            break;
        }
        case 11: {
            filteredImage = subtrairImagem(imagem, vals.segundaImagem);
            break;
        }
        case 12: {
            filteredImage = imagem;
            showHistogram(imagem);
            break;
        }
        default:
            std::cout << "default\n";
            break;
    }

    return filteredImage;
}

void fluxo() {
    std::string tipo = verificarTipoExibicao();
    executarTipo(tipo);
}