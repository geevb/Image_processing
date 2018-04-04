#include "control.cpp"

int main() {

    apresentacao();
    do {
        fluxo();
        destroyAllWindows();
    } 
    while(perguntarDesejaIniciarNovamente());
    return 0;
}

