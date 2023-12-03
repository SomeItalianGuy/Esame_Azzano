#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <sstream>

#include "individual.hpp"
#include "population.hpp"
#include "rnghelper.hpp"

#define PASSIVE "\033[1;34mPassive\033[0m"
#define AGGRESSIVE "\033[1;33mAggressive\033[0m"
#define ADAPTABLE "\033[1;35mAdaptable\033[0m"

int main() {
  try {
    // Primi messggi con le spiegazioni base per questo programma
    std::cout << '\n'
              << "-------------------------------------------------------------"
                 "-------------------------------------------------------------"
                 "---------------------------------\n";

    std::cout << "Welcome to behavioral evolution,\n"
              << "in this simulation we recognize three types of behaviors:\n"
              << '\n'

              << "-" << PASSIVE
              << " :    tries to divide food equally with its bretheren;\n"
              << '\n'

              << "-" << AGGRESSIVE
              << " : will try to steal most of the food it finds "
                 "but gets exhasted when it has to compete;\n"
              << '\n'

              << "-" << ADAPTABLE
              << " :  it will give most of the food if it encounters "
                 "a Passive individual,\n"
              << "              but will not tolerate Aggressive individuals.\n"
              << '\n'

              << "-------------------------------------------------------------"
                 "-------------------------------------------------------------"
                 "---------------------------------\n"
              << '\n'

              << "Now, to get started, we will ask you to insert some "
                 "parameters for your personal simulation.\n"

              << "Please input a seed, it can be a character, a word, a "
                 "sentence or a number: ";

    // Inizializzo alcune variabili per gli input
    int passiveNumber = -1;
    int aggressiveNumber = -1;
    int adaptableNumber = -1;
    int userIntInput;
    std::string userStringInput;

    // Prendo gli input  necessari per istanziare Population e RNGHelper
    std::cin >> userStringInput;
    std::cout << '\n';

    while (passiveNumber < 0) {
      std::cout << "Please input the number of " << PASSIVE
                << " individuals you would like: ";
      bool is_failing = !(std::cin >> userIntInput);
      if (userIntInput < 0) {
        std::cout << '\n';
        std::cout << "The number of " << PASSIVE
                  << " individuals must be higher than 0!\n";
      } else if (is_failing) {
        std::cout << '\n';
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "The number of " << PASSIVE
                  << " individuals must be a number "
                     "higher than 0!\n";
      } else {
        passiveNumber = userIntInput;
      }
    }
    std::cout << '\n';
    while (aggressiveNumber < 0) {
      std::cout << "Please input the number of " << AGGRESSIVE
                << " individuals "
                   "you would like: ";
      bool is_failing = !(std::cin >> userIntInput);
      if (userIntInput < 0) {
        std::cout << '\n';
        std::cout << "The number of " << AGGRESSIVE
                  << " individuals must "
                     "be higher than 0!\n";
      } else if (is_failing) {
        std::cout << '\n';
        std::cout << "The number of " << AGGRESSIVE
                  << " individuals must "
                     "be a number "
                     "higher than 0!\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      } else {
        aggressiveNumber = userIntInput;
      }
    }
    std::cout << '\n';
    while (adaptableNumber < 0) {
      std::cout << "Please input the number of " << ADAPTABLE
                << " individuals "
                   "indviduals you would like: ";
      bool is_failing = !(std::cin >> userIntInput);
      if (userIntInput < 0) {
        std::cout << '\n';
        std::cout << "The number of " << ADAPTABLE
                  << " individuals must "
                     "be higher than 0!\n";
      } else if (is_failing) {
        std::cout << '\n';
        std::cout << "The number of " << ADAPTABLE
                  << " individuals must "
                     "be a number "
                     "higher than 0!\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      } else {
        adaptableNumber = userIntInput;
      }
    }

    // Istanzio i puntatori a Population e RNGHelper
    std::shared_ptr<RNGHelper> RNG = RNGHelper::instance(userStringInput);
    std::shared_ptr<Population> population = Population::Population_instance(
        RNG->GetRandomDouble(3.5, 4.),
        passiveNumber + aggressiveNumber + adaptableNumber,
        RNG->GetRandomDouble(0.01, 0.99));

    // Creo la generazione iniziale
    for (int i = 0; i < passiveNumber; ++i) {
      population->Generate_individual(Behavior::Passive);
    }
    for (int i = 0; i < aggressiveNumber; ++i) {
      population->Generate_individual(Behavior::Aggressive);
    }
    for (int i = 0; i < adaptableNumber; ++i) {
      population->Generate_individual(Behavior::Adaptable);
    }

    // Istanzio vari vettori che mi serviranno durante la simulazione
    std::vector<Place> availablePlaces;
    std::vector<int> availablePlacesIndex;
    std::vector<int> idList;
    std::vector<GenerationData> simulationData;

    // Creo una variabile booleana che mi servirà più avanti
    bool isExtinct = population->Size() == 0 ? true : false;

    // Salvo la prima generazione sul vettore di GenerationData
    simulationData.push_back(population->WriteTo_GenerationData());

    std::cout << "Population: " << population->Size() << '\n';
    std::cout << "Reproduction rate: " << population->Get_reproductionRate()
              << '\n';

    // Messaggi per spiegare i due comandi disponibili durante la simulazione
    std::cout << '\n';
    std::cout << "Now we are set to go, here is a list of all the possible "
                 "commands:\n"
              << "-run [value]          : lets you run a number equal to value "
                 "of generations, for each generation prints"
                 "the number of individuals for each behavior;\n"
              << "-quit                 : lets you quit the simulation.\n"
              << '\n';

    // int debugInt0 = 0;
    // int debugInt1 = 0;

    // Inizio della fase centrale della simulazione
    std::cout << "What would you like to do now? ";
    while (!isExtinct && std::cin >> userStringInput) {
      if (std::cin.peek() == '\n') {
        userIntInput = 0;
      } else {
        std::cin >> userIntInput;
      }
      // Comando "run"
      if (userStringInput == "run") {
        for (int i = 0; i < userIntInput; i++) {
          // Set-up per la generazione
          population->Get_IdList(idList);
          population->Calculate_currentPercentage();
          // Mi assicuro che la popolazione non superi il valore massimo
          while (population->Size() > population->Get_genMaxPopulation()) {
            int randomId = RNG->GetRandomInt(0, idList.size() - 1);
            auto id = idList.begin() + randomId;
            population->Kill_individual(idList[randomId]);
            idList.erase(id);
            // std::cout << "Ucciso individuo random" << '\n';
            // debugInt0++;
          }

          // std::cout << "Max population: " <<
          // population->Get_genMaxPopulation()
          //           << '\n';
          // std::cout << "Population real size: " << population->Size() <<
          // '\n';

          // std::cout << "Numero di individui uccisi a random: " << debugInt0
          //           << '\n';
          // debugInt0 = 0;

          // Creo un numero di luoghi pari al massimo teorico di popolazione per
          // la generazione corrente diviso due
          for (int i = 0; i < round(population->Get_genMaxPopulation() / 2.);
               i++) {
            availablePlaces.push_back(Place());
            availablePlacesIndex.push_back(i);
          }

          // std::cout << "Numero di luoghi: " << availablePlaces.size()
          //           << " Numero dei rispettivi indici: "
          //           << availablePlacesIndex.size() << '\n';

          // Assegno i luoghi casualmente a ciascun individuo
          for (auto& id : idList) {
            int randomPosition =
                RNG->GetRandomInt(0, availablePlacesIndex.size() - 1);
            // std::cout << "Available places size: " << availablePlaces.size()
            //           << '\n';
            // std::cout << "Available places index size: "
            //           << availablePlacesIndex.size() << '\n';
            // std::cout << "Indexes: " << availablePlacesIndex[randomPosition]
            //           << '\n';
            Place& randomPlace =
                availablePlaces[availablePlacesIndex[randomPosition]];
            randomPlace.Add_Index(id);
            // std::cout << "Individuo aggiunto con successo a un luogo" <<
            // '\n';
            // debugInt0++;
            if (randomPlace.isFull()) {
              availablePlacesIndex.erase(availablePlacesIndex.begin() +
                                         randomPosition);
              // std::cout << "Luogo pieno, sta venendo rimosso" << '\n';
              // debugInt1++;
            }
          }
          // std::cout << "Numero di aggiunte ai luoghi: " << debugInt0 << '\n';
          // std::cout << "Numero di luoghi pieni: " << debugInt1 << '\n';
          // debugInt0 = 0;
          // debugInt1 = 0;

          // Interazione
          for (auto& place : availablePlaces) {
            // std::cout << "Ecco gli indici: " << place.firstIndex_ << "     "
            //           << place.secondIndex_ << '\n';
            population->Interaction(place);
            // std::cout << "C'è stata un'interazione" << '\n';
            // std::cout << "Quantità di cibo degli individui: "
            //           << population->Get_IndividualFood(place.firstIndex_)
            //           << " e "
            //           << population->Get_IndividualFood(place.secondIndex_)
            //           << '\n';
            // debugInt0++;
          }
          // std::cout << "Numero di interazioni: " << debugInt0 << '\n';
          // debugInt0 = 0;

          // Calcolo della sopravvivenza ed eventuale riproduzione degli
          // individui

          for (std::vector<int>::size_type i = 0; i < idList.size(); i++) {
            // std::cout << "Quantità di cibo dell'individuo numero " << i + 1
            //           << ": " << population->Get_IndividualFood(idList[i])
            //           << '\n';
            if (!RNG->probability(population->Get_IndividualFood(idList[i]))) {
              auto it = idList.begin() + i;
              population->Kill_individual(idList[i]);
              idList.erase(it);
              // std::cout << "Un individuo non è sopravvissuto" << '\n';
              // debugInt0++;
            } else if (RNG->probability(
                           population->Get_IndividualFood(idList[i]) - 1)) {
              population->Generate_individual(idList[i]);
              // std::cout << "Un individuo si è riprodotto" << '\n';
              // debugInt1++;
            }
          }
          // std::cout << "Numero di individui morti dalle interazioni: "
          //           << debugInt0 << '\n';
          // std::cout << "Numero di nuove nascite: " << debugInt1 << '\n';
          // debugInt0 = 0;
          // debugInt1 = 0;

          if (population->Size() == 0) {
            std::cout << "The population was led to extinction!" << '\n';
            isExtinct = true;
            break;
          } else {
            // Mettere i cambiamenti di questa generazione in cout
            GenerationData genData = population->WriteTo_GenerationData();
            std::string passiveNumberOutput =
                (genData.passiveNumber -
                 simulationData[simulationData.size() - 1].passiveNumber) < 0
                    ? std::string("(\033[1;31m") +
                          std::to_string(
                              (genData.passiveNumber -
                               simulationData[simulationData.size() - 1]
                                   .passiveNumber)) +
                          std::string("\033[0m)")
                    : std::string("(\033[1;32m+") +
                          std::to_string(
                              (genData.passiveNumber -
                               simulationData[simulationData.size() - 1]
                                   .passiveNumber)) +
                          std::string("\033[0m)");
            std::string aggerssiveNumberOutput =
                (genData.aggressiveNumber -
                 simulationData[simulationData.size() - 1].aggressiveNumber) < 0
                    ? std::string("(\033[1;31m") +
                          std::to_string(
                              (genData.aggressiveNumber -
                               simulationData[simulationData.size() - 1]
                                   .aggressiveNumber)) +
                          std::string("\033[0m)")
                    : std::string("(\033[1;32m+") +
                          std::to_string(
                              (genData.aggressiveNumber -
                               simulationData[simulationData.size() - 1]
                                   .aggressiveNumber)) +
                          std::string("\033[0m)");
            std::string adaptableNumberOutput =
                (genData.adaptableNumber -
                 simulationData[simulationData.size() - 1].adaptableNumber) < 0
                    ? std::string("(\033[1;31m") +
                          std::to_string(
                              (genData.adaptableNumber -
                               simulationData[simulationData.size() - 1]
                                   .adaptableNumber)) +
                          std::string("\033[0m)")
                    : std::string("(\033[1;32m+") +
                          std::to_string(
                              (genData.adaptableNumber -
                               simulationData[simulationData.size() - 1]
                                   .adaptableNumber)) +
                          std::string("\033[0m)");
            std::cout << "-----------------------------------------------------"
                         "--------"
                         "-----------------------------------------------------"
                         "--------"
                         "---------------------------------\n";
            std::cout << "At generation number " << simulationData.size()
                      << " , here is how the population is split up:" << '\n';
            std::cout << '\n';
            std::cout << PASSIVE << " Individuals: " << std::fixed
                      << std::setprecision(2) << genData.GetPassivePercentage()
                      << "%  " << genData.passiveNumber << "  "
                      << passiveNumberOutput << '\n';
            std::cout << '\n';
            std::cout << AGGRESSIVE << " Individuals: " << std::fixed
                      << std::setprecision(2)
                      << genData.GetAggressivePercentage() << "%  "
                      << genData.aggressiveNumber << "  "
                      << aggerssiveNumberOutput << '\n';
            std::cout << '\n';
            std::cout << ADAPTABLE << " Individuals: " << std::fixed
                      << std::setprecision(2)
                      << genData.GetAdaptablePercentage() << "%  "
                      << genData.adaptableNumber << "  "
                      << adaptableNumberOutput << '\n';
            std::cout << '\n';
            std::cout << "-----------------------------------------------------"
                         "--------"
                         "-----------------------------------------------------"
                         "--------"
                         "---------------------------------\n";
            // Carica i dati su data
            simulationData.push_back(genData);
            // Pulisci tutti i vettori che devono variare da generazione a
            // generazione
            availablePlaces.clear();
            availablePlacesIndex.clear();
            idList.clear();
            if (i == userIntInput - 1) {
              std::cout << "What would you like to do now? ";
            }
          }
        }
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