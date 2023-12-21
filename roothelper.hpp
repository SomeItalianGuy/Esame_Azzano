#ifndef ROOTHELPER_HPP
#define ROOTHELPER_HPP
#ifdef MY_ROOT

#include <TCanvas.h>
#include <TGraph.h>

#include <string>
#include <unordered_map>

class RootHelper {
 private:
  std::unordered_map<const char*, TGraph> R_data;
  TCanvas R_canvas;

 public:
  RootHelper(const char* name, const char* title, int wide, int height);
  void AddGraph(const char* name, std::vector<int> data);
  void DivideCanvas(int lineNumber, int columnNumber);
  void Draw(int canvasPosition, std::vector<const char*> names);
};

#endif  // MY_ROOT
#endif  // ROOTHELPER_HPP