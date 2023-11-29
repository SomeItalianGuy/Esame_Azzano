#include <iostream>
#include <limits>
#include <random>
#include <sstream>

#include "individual.hpp"
#include "population.hpp"
#include "rnghelper.hpp"

int main() {
  try {
    // Primi messggi con le spiegazioni base per questo programma
    std::cout << '\n'
              << "-------------------------------------------------------------"
                 "-------------------------------------------------------------"
                 "---------------------------------\n";

    std::cout
        << "Welcome to behavioral evolution,\n"
        << "in this simulation we recognize three types of behaviors:\n"
        << '\n'

        << "-Passive :    tries to divide food equally with its bretheren;\n"
        << '\n'

        << "-Aggressive : will try to steal most of the food it finds "
           "but gets exhasted when it has to compete;\n"
        << '\n'

        << "-Adaptable :  it will give most of the food if it encounters "
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
      std::cout
          << "Please input the number of Passive individuals you would like: ";
      bool is_failing = !(std::cin >> userIntInput);
      if (userIntInput < 0) {
        std::cout << '\n';
        std::cout
            << "The number of Passive individuals must be higher than 0!\n";
      }
      else if (is_failing) {
        std::cout << '\n';
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "The number of Passive individuals must be a number "
                     "higher than 0!\n";
      }
      else {
        passiveNumber = userIntInput;
      }
    }
    std::cout << '\n';
    while (aggressiveNumber < 0) {
      std::cout << "Please input the number of Aggressive individuals "
                   "you would like: ";
      bool is_failing = !(std::cin >> userIntInput);
      if (userIntInput < 0) {
        std::cout << '\n';
        std::cout << "The number of Aggressive individuals must "
                     "be higher than 0!\n";
      }
      else if (is_failing) {
        std::cout << '\n';
        std::cout << "The number of Aggressive individuals must "
                     "be a number "
                     "higher than 0!\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      else {
        aggressiveNumber = userIntInput;
      }
    }
    std::cout << '\n';
    while (adaptableNumber < 0) {
      std::cout << "Please input the number of Adaptable individuals "
                   "indviduals you would like: ";
      bool is_failing = !(std::cin >> userIntInput);
      if (userIntInput < 0) {
        std::cout << '\n';
        std::cout << "The number of Adaptable individuals must "
                     "be higher than 0!\n";
      }
      else if (is_failing) {
        std::cout << '\n';
        std::cout << "The number of Adaptable individuals must "
                     "be a number "
                     "higher than 0!\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      else {
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
    std::vector<GenerationData> simulatioData;

    // Salvo la prima generazione sul vettore di GenerationData
    simulatioData.push_back(population->WriteTo_GenerationData());

    std::cout << "Population: " << population->Size() << '\n';
    std::cout << "Reproduction rate: " << population->Get_reproductionRate() << '\n';


    // Messaggi per spiegare i due comandi disponibili durante la simulazione
    std::cout << '\n';
    std::cout << "Now we are set to go, here is a list of all the possible "
                 "commands:\n"
              << "-run [value]          : lets you run a number equal to value "
                 "of generations, for each generation prints"
                 "the number of individuals for each behavior;\n"
              << "-quit                 : lets you quit the simulation.\n"
              << '\n';


    // Inizio della fase centrale della simulazione
    std::cout << "What would you like to do now? ";
    std::cout << '\n';
    while (std::cin >> userStringInput) {
      // Inizializzo la veriabile userIntInput
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
          std::cout << "Max population: " << population->Get_genMaxPopulation() << '\n';
          // Mi assicuro che la popolazione non superi il valore massimo
          while (population->Size() > population->Get_genMaxPopulation()) {
            int randomId = RNG->GetRandomInt(0, idList.size() - 1);
            auto id = idList.begin() + randomId;
            population->Kill_individual(idList[randomId]);
            idList.erase(id);
          }
          // Creo un numero di luoghi pari al massimo teorico di popolazione per
          // la generazione corrente diviso due
          for (int i = 0; i < population->Get_genMaxPopulation() / 2; i++) {
            Place place;
            availablePlaces.push_back(place);
            availablePlacesIndex.push_back(i);
          }
          // Assegno i luoghi casualmente a ciascun individuo
          for (auto& id : idList) {
            int randomPosition =
                RNG->GetRandomInt(0, availablePlacesIndex.size() - 1);
            Place randomPlace =
                availablePlaces[availablePlacesIndex[randomPosition]];
            randomPlace.Add_Index(id);
            if (randomPlace.isFull()) {
              std::vector<int>::iterator placeId =
                  availablePlacesIndex.begin() + randomPosition;
              availablePlacesIndex.erase(placeId);
            }
          }
          // Interazione
          for (auto& place : availablePlaces) {
            population->Interaction(place);
          }
          // Calcolo della sopravvivenza ed eventuale riproduzione degli individui

          for (std::vector<int>::size_type i = 0; i < idList.size(); i++) {
            if(!RNG->probability(population->Get_IndividualFood(idList[i]))) {
              auto it = idList.begin() + i;
              population->Kill_individual(idList[i]);
              idList.erase(it);
            } else if (RNG->probability(population->Get_IndividualFood(idList[i]) - 1)){
              population->Generate_individual(idList[i]);
            }
          }
          
          // Mettere i cambiamenti di questa generazione in cout
          GenerationData genData = population->WriteTo_GenerationData();
          double populationSize = population->Size();
          std::cout << "-------------------------------------------------------------"
                 "-------------------------------------------------------------"
                 "---------------------------------\n";
          std::cout << "At generation number " << simulatioData.size() << " , here is how the population is split up:" << '\n';
          std::cout << '\n';
          std::cout << "Passive Individuals: " <<  genData.GetPassivePercentage() << "%  " << genData.passiveNumber << "  " << "(" << genData.passiveNumber - simulatioData[simulatioData.size() - 1].passiveNumber << ")" << '\n';
          std::cout << '\n';
          std::cout << "Aggressive Individuals: " << genData.GetAggressivePercentage() << "%  " << genData.aggressiveNumber << "  " << "(" << genData.aggressiveNumber - simulatioData[simulatioData.size() - 1].aggressiveNumber << ")" << '\n';
          std::cout << '\n';
          std::cout << "Adaptable Individuals: " << genData.GetAdaptablePercentage() << "%  " <<  genData.adaptableNumber << "  " << "(" << genData.adaptableNumber - simulatioData[simulatioData.size() - 1].adaptableNumber << ")" << '\n';
          std::cout << '\n';
          std::cout << "-------------------------------------------------------------"
                 "-------------------------------------------------------------"
                 "---------------------------------\n";
          // Carica i dati su data
          simulatioData.push_back(genData);
          // Pulisci tutti i vettori che devono variare da generazione a generazione
          availablePlaces.clear();
          availablePlacesIndex.clear();
          idList.clear();
          std::cout << "What would you like to do now? ";

        }
      }
      // Comando "quit"
      else if (userStringInput == "quit") {
        break;
      }
      // Comando non valido
      else {
        std::cout << "Invalid command, try one of the two valid commands\n";
      }
    }
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