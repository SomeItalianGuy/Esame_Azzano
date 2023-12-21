#include "roothelper.hpp"

RootHelper::RootHelper(const char* name, const char* title, int wide,
                       int height)
    : R_canvas(name, title, wide, height) {}

void RootHelper::AddGraph(std::vector<int> data) {
  int xArray[data.size()];
  int yArray[data.size()];
  for (long unsigned int i = 0; i < data.size() - 1; i++) {
    xArray[i] = data[i];
    yArray[i] = i;
  }
  R_data.push_back(TGraph(data.size(), xArray, yArray));
  //   R_data[name] = TGraph(data.size(), xArray, yArray);
}

void RootHelper::DivideCanvas(int lineNumber, int columnNumber) {
  R_canvas.Divide(columnNumber, lineNumber);
}

void RootHelper::Draw(int canvasPosition, std::vector<int> names) {
  if (names.size() == 0) {
    throw std::invalid_argument("Cannot draw 0 graphs");
  }
  R_canvas.cd(canvasPosition);
  for (auto name : names) {
    R_data[name].Draw("AL");
  }
}

// template void RootHelper::AddGraph<int>(int name,
//                                         std::vector<int> data);
// template void RootHelper::AddGraph<float>(std::string name,
//                                           std::vector<float> data);
// template void RootHelper::AddGraph<double>(std::string name,
//                                            std::vector<double> data);