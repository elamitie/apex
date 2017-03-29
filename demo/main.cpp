#include "app/application.h"

int main(int argc, char** argv) {
    Application app;
    app.Start(1280, 720, "OpenGL Demo");

    return 0;
}