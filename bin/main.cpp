#include <iostream>
#include "lib/terminal_controller.cpp"

using namespace terminal;

int main(int argc, char* argv[]) {
    controller::my_header = argv[1];
    terminal::DrawAndFollowTerminal();
    return 0;
}