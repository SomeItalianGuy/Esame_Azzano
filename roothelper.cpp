#include "roothelper.hpp"

RootHelper::RootHelper(std::string name, std::string title, int wide,
                       int height)
    : R_canvas(name.c_str(), title.c_str(), wide, height), countDrawn(0) {}

RootHelper::~RootHelper() {}

void RootHelper::AddGraph(std::string name, std::vector<int> data) {
  const int size = data.size() - 1;
  int x_array[size];
  int y_array[size];
  for (int i = 0; i < size; i++) {
    x_array[i] = i;
    y_array[i] = data[i];
  }

  R_data[name] = TGraph(size, x_array, y_array);
}

void RootHelper::DivideCanvas(int lineNumber, int columnNumber) {
  R_canvas.Divide(columnNumber, lineNumber);
}

void RootHelper::Draw(int canvasPosition, std::vector<std::string> names,
                      std::vector<EColor> colors) {
  R_canvas.cd(canvasPosition);

  R_data[names[0]].SetMarkerStyle(kOpenCircle);
  R_data[names[0]].SetMarkerColor(colors[0]);
  R_data[names[0]].SetLineColor(colors[0]);
  R_data[names[0]].Draw("APL");

  for (long unsigned int i = 1; i < names.size(); i++) {
    R_data[names[i]].SetMarkerStyle(kOpenCircle);
    R_data[names[i]].SetMarkerColor(colors[i]);
    R_data[names[i]].SetLineColor(colors[i]);
    R_data[names[i]].Draw("PL same");
  }

  countDrawn += names.size();
}

void RootHelper::PrintToFile(std::string& fileName, std::string pathToSave) {
  if (countDrawn == 0) {
    throw std::runtime_error("Cannot print without having drawn anything");
  }

  fileName.append(".root");
  TFile saveFile((pathToSave + fileName).c_str(), "UPDATE");
  saveFile.Save();

  R_canvas.Write();

  saveFile.Close();
  //   delete saveFile;
}