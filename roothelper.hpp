#ifndef ROOTHELPER_HPP
#define ROOTHELPER_HPP
#ifdef MY_ROOT

#include <TCanvas.h>
#include <TGraph.h>
#include <TObject.h>
#include <TPad.h>

#include <string>
#include <unordered_map>

class RootHelper {
 private:
  std::vector<TGraph> R_data;
  TCanvas R_canvas;

 public:
  RootHelper(const char* name, const char* title, int wide, int height);
  void AddGraph(std::vector<int> data);
  void DivideCanvas(int lineNumber, int columnNumber);
  void Draw(int canvasPosition, std::vector<int> names);
};

#endif  // MY_ROOT
#endif  // ROOTHELPER_HPP