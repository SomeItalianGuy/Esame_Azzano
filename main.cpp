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
                 "but gets exhausted when it has to compete;\n"
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
    std::cout << "Now we are set to go, here is a list of all the possible "
                 "commands:\n";

    int userIntInput;
    std::string userStringInput;

    // Fase centrale della simulazione
    while (!simulation->PopulationIsExtinct()) {
      std::cout << '\n';
      std::cout
          << "-run [value]          : lets you run a number equal to value "
          << "of generations, for each generation prints "
          << "the number of individuals for each behavior;\n"
          << "-quit                 : lets you quit the simulation.\n"
          << '\n';
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
        std::cout << "Invalid command, try one of the two valid commands\n\n";
      }
    }
    std::cout << "\nSuccessfully exited the simulation"
              << "\n\n";

    std::string userInput = Logic::GetValidatedInput<std::string>(
        "Now that we are done with the simulation, would you like to save the "
        "data you have collected in a file?(yes/no) ",
        {{[](std::string str) { return str == "yes" || str == "no"; },
          "The only accepted inputs are yes or no"}});

    if (userInput == "yes") {
      simulation->SaveSimulationToFile();
#ifdef MY_ROOT
      simulation->PrintGraphs();
#else
      std::cout
          << "Could not find the root package, therfore the graphs could "
             "not be printed. In order to solve this problem i recommend "
             "visiting "
             "https://root.cern/manual/integrate_root_into_my_cmake_project/"
          << '\n';
#endif
    }
    std::cout << "Quitting the program" << '\n';
    return EXIT_SUCCESS;
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
}