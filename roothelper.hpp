#ifndef ROOTHELPER_HPP
#define ROOTHELPER_HPP
#ifdef MY_ROOT

#include <TCanvas.h>
#include <TFile.h>
#include <TGraph.h>
#include <TMultiGraph.h>

#include <string>
#include <unordered_map>

class RootHelper {
 private:
  std::unordered_map<std::string, TGraph> R_data;
  TCanvas R_canvas;
  int countDrawn;

 public:
  RootHelper(std::string name, std::string title, int wide, int height);
  ~RootHelper();
  void AddGraph(std::string name, std::vector<int> data);
  void DivideCanvas(int lineNumber, int columnNumber);
  void Draw(int canvasPosition, std::vector<std::string> names,
            std::vector<EColor> colors);
  void PrintToFile(std::string& fileName);
};

#endif  // MY_ROOT
#endif  // ROOTHELPER_HPP