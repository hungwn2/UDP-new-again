#include <iostream>
#include <sstream>
#include <string>
#include <vector>


#include "command_code.h"
#include "app.h"
#include "app_terminal.h"

Terminal::Terminal(Server *server){
    m_server=server;
}
std::string Terminal::toLower(const std::string &input){
    std::string lowered=input;
    std::transform(lowered.begin(), lowered.end(), lowered.begin(), [](unsigned char c) { return std::tolower(c); });
    return lowered;
}

void Terminal::handleGpioCommands(cons std::string &action, std::vector <std::string> &tokens ){
    std::string message;
    if (action == "get_pin_state" && tokens.size() >= 3) {
      message = serverGpioManager.createGpioCommand(CommandCode::GPIO_GET_PIN_STATE, tokens[2], "");
    } else if (action == "get_all_states" && tokens.size() >= 2) {
      message = serverGpioManager.createGpioCommand(CommandCode::GPIO_GET_ALL_STATES, tokens[0], "");
    } else if (action == "get_pin_mode" && tokens.size() >= 3) {
      message = serverGpioManager.createGpioCommand(CommandCode::GPIO_GET_PIN_MODE, tokens[2], "");
    } else if (action == "get_all_modes" && tokens.size() >= 2) {
      message = serverGpioManager.createGpioCommand(CommandCode::GPIO_GET_ALL_MODES, tokens[0], "");
    } else if (action == "get_pin_alt_function" && tokens.size() >= 3) {
      message = serverGpioManager.createGpioCommand(CommandCode::GPIO_GET_PIN_ALT_FUNCTION, tokens[2], "");
    } else if (action == "get_all_alt_functions" && tokens.size() >= 2) {
      message = serverGpioManager.createGpioCommand(CommandCode::GPIO_GET_ALL_ALT_FUNCTIONS, tokens[0], "");
    } else if (action == "set_pin_state" && tokens.size() >= 4) {
      message = serverGpioManager.createGpioCommand(CommandCode::GPIO_SET_PIN_STATE, tokens[2], tokens[3]);
    } else if (action == "set_all_states" && tokens.size() >= 3) {
      message = serverGpioManager.createGpioCommand(CommandCode::GPIO_SET_ALL_STATES, tokens[0], tokens[2]);
    } else {
      std::cerr << "Unsupported action: " << action << std::endl;
    }
  
    if (!message.empty()) {
      m_Server->sendMessage(m_targetClient, message);
    } else {
      std::cout << "Invalid command. Refer to sim_command.md" << std::endl;
    }
    m_targetClient = nullptr;
}