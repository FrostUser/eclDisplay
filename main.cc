#include <TROOT.h>
// Contains TApplication
#include <TRint.h>

#include "viewer.h"
#include "EclData.h"
#include "EclFrame.h"

#include "painters/EclPainterPolar.h"

//#include "CERNfunctions.h"
#include <iostream>

int main(int argc, char **argv) {
  TApplication app("tapp", &argc, argv);
  // Hide statistics box. This might also require to add gROOT->ForceStyle(); after this line.
  gStyle->SetOptStat(0);

  // TODO: Add message for the available options.

  EclData* ecl_data = new EclData();

  ecl_data->AddFile("histofile.root");
  std::cout << ecl_data->GetTimeMax() << std::endl;

  if (argc > 1)
    setMode(0);

  EclFrame* frame = new EclFrame(0, ecl_data);
  // Make application terminate when this window is closed.
  frame->Connect("CloseWindow()", "TApplication", &app, "Terminate()");

  app.Run();

  delete frame;
  delete ecl_data;

  return 0;
}
