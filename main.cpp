#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <sstream>

#include "simulation.hpp"

int main() {
  try {
    // Primi messggi con le spiegazioni base per questo programma
    Graphic::PrintSeparationLines();

    std::cout << "Welcome to behavioral evolution,\n"
              << "in this simulation we recognize three types of behaviors:\n"
              << '\n'

              << "-" << Graphic::ColorText(std::string("Passive"), BLUE_TEXT)
              << " :    tries to divide food equally with its bretheren;\n"
              << '\n'

              << "-"
              << Graphic::ColorText(std::string("Aggressive"), YELLOW_TEXT)
              << " : will try to steal most of the food it finds "
                 "but gets exhasted when it has to compete;\n"
              << '\n'

              << "-"
              << Graphic::ColorText(std::string("Adaptable"), MAGENTA_TEXT)
              << " :  it will give most of the food if it encounters "
                 "a Passive individual,\n"
              << "              but will not tolerate Aggressive individuals.\n"
              << '\n';

    Graphic::PrintSeparationLines();

    std::cout << "Now, to get started, we will ask you to insert some "
                 "parameters for your personal simulation.\n";

    std::shared_ptr<Simulation> simulation =
        Simulation::GetSimulationFromInput();

    // Messaggi per spiegare i due comandi disponibili durante la simulazione
    std::cout << '\n';
    std::cout << "Now we are set to go, here is a list of all the possible "
                 "commands:\n"
              << "-run [value]          : lets you run a number equal to value "
                 "of generations, for each generation prints"
                 "the number of individuals for each behavior;\n"
              << "-quit                 : lets you quit the simulation.\n"
              << '\n';

    int userIntInput;
    std::string userStringInput;

    // Fase centrale della simulazione
    while (!simulation->PopulationIsExtinct()) {
      std::cout << "What would you like to do now? ";
      std::cin >> userStringInput;
      if (std::cin.peek() == '\n') {
        userIntInput = 0;
      } else {
        std::cin >> userIntInput;
      }
      // Comando "run"
      if (userStringInput == "run") {
        simulation->RunGenerations(userIntInput);
      }
      // Comando "quit"
      else if (userStringInput == "quit") {
        break;
      }
      // Comando non valido
      else {
        std::cout << "Invalid command, try one of the two valid commands\n";
        std::cout << "What would you like to do now? ";
      }
    }
    std::cout << "Successfully exited the simulation" << '\n';
  }
  // Catch per i possibili errori
  catch (std::domain_error& error) {
    std::cout << "Caught a domain error: ";
    std::cout << error.what() << '\n';
  } catch (std::overflow_error& error) {
    std::cout << "Caught an overflow error: ";
    std::cout << error.what() << '\n';
  } catch (...) {
    std::cout << "Unkown error has occured" << '\n';
  }

  // Implementare la scrittura su file e la stampa dei grafici
}