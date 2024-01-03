#ifndef ROOTHELPER_HPP
#define ROOTHELPER_HPP
#ifdef MY_ROOT

#include <TCanvas.h>
#include <TFile.h>
#include <TGraph.h>
#include <TH1F.h>

#include <iostream>
#include <string>
#include <unordered_map>

class RootHelper {
 private:
  std::unordered_map<std::string, TGraph> R_data;
  TCanvas R_canvas;
  int countDrawn, countDivide;

 public:
  RootHelper(std::string name, std::string title, int wide, int height);
  ~RootHelper();

  template <typename T>
  void AddGraph(std::string name, std::vector<T> data) {
    const int size = data.size() - 1;
    int x_array[size];
    T y_array[size];
    for (int i = 0; i < size; i++) {
      x_array[i] = i;
      y_array[i] = data[i];
    }

    R_data[name] = TGraph(size, x_array, y_array);
  }

  void DivideCanvas(int lineNumber, int columnNumber);
  void Draw(int canvasPosition, std::string padName, std::string xAxisName,
            std::string yAxisName, std::string name, EColor color);
  void PrintToFile(std::string& fileName, std::string pathToSave);
};

#endif  // MY_ROOT
#endif  // ROOTHELPER_HPP