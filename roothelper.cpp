#include "roothelper.hpp"

RootHelper::RootHelper(std::string name, std::string title, int wide,
                       int height)
    : R_canvas(name.c_str(), title.c_str(), wide, height),
      countDrawn(0),
      countDivide(1) {}

RootHelper::~RootHelper() {}

void RootHelper::AddGraph(std::string name, std::vector<int> data) {
  const int size = data.size() - 1;
  int x_array[size];
  int y_array[size];
  for (int i = 0; i < size; i++) {
    x_array[i] = i;
    y_array[i] = data[i];
  }

  TGraph graph(size, x_array, y_array);

  R_data[name] = graph;
}

void RootHelper::DivideCanvas(int lineNumber, int columnNumber) {
  R_canvas.Divide(columnNumber, lineNumber);
  countDivide = columnNumber * lineNumber;
}

void RootHelper::Draw(int canvasPosition, std::string padName,
                      std::string xAxisName, std::string yAxisName,
                      std::string name, EColor color) {
  R_canvas.cd(canvasPosition);

  R_data[name].SetTitle(padName.c_str());

  R_data[name].GetXaxis()->SetTitle(xAxisName.c_str());
  R_data[name].GetYaxis()->SetTitle(yAxisName.c_str());

  R_data[name].SetMarkerStyle(kFullCircle);
  R_data[name].SetMarkerColor(color);
  R_data[name].SetLineColor(color);
  R_data[name].SetEditable(kFALSE);
  R_data[name].Draw("APL");

  countDrawn++;
}

void RootHelper::PrintToFile(std::string& fileName, std::string pathToSave) {
  if (!(countDivide == countDrawn)) {
    throw std::runtime_error("Some of the TPads were left undrawn");
  }

  fileName.append(".root");
  TFile saveFile((pathToSave + fileName).c_str(), "UPDATE");
  saveFile.Save();

  R_canvas.Write();

  R_canvas.BuildLegend();

  saveFile.Close();

  std::cout << "The graphs hav been saved to: '" << pathToSave + fileName
            << "' as: '" << R_canvas.GetName() << "'\n\n";
}