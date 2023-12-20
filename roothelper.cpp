#include "roothelper.hpp"

RootHelper::RootHelper(const char* name, const char* title, int wide,
                       int height)
    : R_canvas(name, title, wide, height) {}

template <typename T>
void RootHelper::AddGraph(std::string name, std::vector<T> data) {
  T xArray[data.size()];
  int yArray[data.size()];
  for (int i = 0; i < data.size() - 1; i++) {
    xArray[i] = data[i];
    yArray[i] = i;
  }
  TGraph graph(data.size(), xArray, yArray);
  R_data.insert(std::make_pair<std::string, TGraph>(name, graph));
}

void RootHelper::DivideCanvas(int lineNumber, int columnNumber) {
  R_canvas.Divide(columnNumber, lineNumber);
}

void RootHelper::Draw(int canvasPosition, std::vector<std::string> names) {
  if (names.size() == 0) {
    throw std::invalid_argument("Cannot draw 0 graphs");
  }
  R_canvas.cd(canvasPosition);
  for (auto name : names) {
    R_data[name].Draw("AL");
  }
}

template void RootHelper::AddGraph<int>(std::string name,
                                        std::vector<int> data);
template void RootHelper::AddGraph<float>(std::string name,
                                          std::vector<float> data);
template void RootHelper::AddGraph<double>(std::string name,
                                           std::vector<double> data);