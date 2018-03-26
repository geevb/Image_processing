#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

void menuInicial() {
    std::cout <<"    ____  _       _ __        __   ____                         "      << std::endl;
    std::cout <<"   / __ \\(_)___ _(_) /_____ _/ /  /  _/___ ___  ____ _____ ____ "     << std::endl;
    std::cout <<"  / / / / / __ `/ / __/ __ `/ /   / // __ `__ \\/ __ `/ __ `/ _ \\"    << std::endl;
    std::cout <<" / /_/ / / /_/ / / /_/ /_/ / /  _/ // / / / / / /_/ / /_/ /  __/"      << std::endl;
    std::cout <<"/_____/_/\\__, /_/\\__/\\__,_/_/  /___/_/ /_/ /_/\\__,_/\\__, /\\___/ "<< std::endl;
    std::cout <<"        /____/                                     /____/       "      << std::endl;
    std::cout <<"                           .---."                                      << std::endl;
    std::cout <<"                           |[X]|"                                      << std::endl;
    std::cout <<"                    _.==._.\"\"\"\"\".___n__"                          << std::endl;
    std::cout <<"                   d __ ___.-\'\'-. _____b "                           << std::endl;
    std::cout <<"                   |[__]  /.\"\"\"\".\\     |"                         << std::endl;
    std::cout <<"                   |     // /\"\"\\ \\\\    |"                         << std::endl;
    std::cout <<"                   |     \\\\ \\__/ //    |"                           << std::endl;
    std::cout <<"                   |pentax\\`.__.\'/     |"                            << std::endl;
    std::cout <<"                   \\=======`-..-\'======/"                            << std::endl;
    std::cout <<"                    `-----------------\' "                             << std::endl;
    std::cout <<"       ____                                 _            "             << std::endl;
    std::cout <<"       / __ \\_________  ________  __________(_)___  ____ _"            << std::endl;
    std::cout <<"      / /_/ / ___/ __ \\/ ___/ _ \\/ ___/ ___/ / __ \\/ __ `/"          << std::endl;
    std::cout <<"     / ____/ /  / /_/ / /__/  __(__  |__  ) / / / / /_/ / "             << std::endl;
    std::cout <<"    /_/   /_/   \\____/\\___/\\___/____/____/_/_/ /_/\\__, /  "         << std::endl;
    std::cout <<"                                                /____/   "             << std::endl;
}

std::string perguntarTipoExibicao() {
    std::string resp;
    std::cout << "\nDeseja aplicar um dos filtros na Webcam ou em uma imagem?" << std::endl;
    std::cout << "1) Webcam \n2) Imagem:\nR: ";   

    while(true) {
        std::cin >> resp;
        if(resp.compare("1") == 0 || resp.compare("2") == 0) {
            break;
        }

        std::cout << "\nOpcao inválida, por favor reinserir \nR: ";
    }

    return resp;
}

std::string perguntarQualImagem() {
    std::string resp;
    std::cout <<  "\nPor favor, escolha uma das seguintes imagens: " << std::endl;
    system ("ls images/");
    std::cout << "\nR:";
    std::cin >> resp;

    return resp;
}

int perguntarQualFiltro() {
    int resp;
    std::cout << "\nPor favor, escolha um dos filtros disponíveis: " << std::endl;
    std::cout << "1) Cinza Média \n2) Cinza Ponderado \n3) Cor Invertida \n4) Limiarizacao \n5) Canal de cor isolado \n6) Incrementar Canal de cor \n7) Zoom In \n8) Somar imagem \n9) Subtrair imagem";
    std::cout << "\nR: ";
    std::cin >> resp;
    
    while(true) {
        if(resp >= 1 && resp <= 9) {
            break;
        }
        
        std::cout << "\nResposta inválida, por favor reeinserir! \nR: ";
        std::cin >> resp;
    }
    
    return resp;
}

std::string perguntarQualCor() {
    std::string resp;
    std::cout << "\n Por favor, insira a cor que deseja: 'R', 'G' ou 'B' \nR: ";
    std::cin >> resp;
    while(true) {
        if(resp.compare("R") == 0 || resp.compare("G") == 0 || resp.compare("B") == 0 ) {
            break;
        }
        std::cout << "Valor inválido inserido, por favor reeinserir! \nR: ";
        std::cin >> resp;
    }

    return resp;
}

int perguntarValorZoom() {
    int valor;
    std::cout << "Por favor, insira o valor do Zoom In que deseja utilizar \nR: ";
    std::cin >> valor;

    while(true) {
        if(isdigit(valor) && valor > 0) {
            break;
        }
        std::cout << "Valor inválido inserido, por favor reinserir! \nR: ";
        std::cin >> valor;
    }

    return valor;
}

std::string perguntarSegundaImagem() {
    std::string resp;
    std::cout <<  "\nPor favor, para a segunda imagem, escolha uma das seguintes: " << std::endl;
    system ("ls images/");
    std::cout << "\nR:";
    std::cin >> resp;

    return resp;
}

int perguntarQualValorLimiar() {
    int resp;
    std::cout << "\nPor favor, insira o valor mínimo de limiar \nR: ";
    std::cin >> resp;

    return resp;
}

void apresentarImagem(cv::Mat image) {

    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE );
    cv::imshow("Display Image", image);
    // cvSetMouseCallback("Display Image", cv::mouseHandler,cv::&mouseParam);
    cv::waitKey(0);
}

void apresentarVideo(cv::Mat frame) {
    cv::imshow("Webcam image", frame);
}
