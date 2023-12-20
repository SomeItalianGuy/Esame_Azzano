#ifndef ROOTHELPER_HPP
#define ROOTHELPER_HPP
#ifdef MY_ROOT

#include <TCanvas.h>
#include <TGraph.h>

#include <string>
#include <unordered_map>
class RootHelper {
 private:
  std::unordered_map<std::string, TGraph> R_data;
  TCanvas R_canvas;

 public:
  RootHelper(const char* name, const char* title, int wide, int height);
  template <typename T>
  void AddGraph(std::string name, std::vector<T> data);
  void DivideCanvas(int lineNumber, int columnNumber);
  void Draw(int canvasPosition = 1, std::vector<std::string> names);
};

#endif  // MY_ROOT
#endif  // ROOTHELPER_HPP