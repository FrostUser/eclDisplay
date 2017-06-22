#include <TApplication.h>
#include "EclFrame.h"

#include <TFile.h>

using namespace Belle2;

int main(int argc, char** argv)
{
  /**************************************************************/
  /*              OPEN TEMP FILE FOR LARGE TTREEs               */
  /**************************************************************/
  // This module generates large Root trees that sometimes can't be
  // completely kept in memory. Thus, we create a temp file to store it.
  TString temp_fname = "ecldisplay_tmp";

  if (gSystem->TempFileName(temp_fname) == 0) {
    std::cout << "Could not create temp file." << std::endl;
    return -1;
  }
  std::cout << temp_fname << std::endl;
  TFile* temp_tfile = new TFile(temp_fname, "RECREATE");

  /**************************************************************/

  ECLChannelMapper m_mapper;
  m_mapper.initFromFile("data/ecl_channels_map.txt");

  TApplication* m_app;
  EclData* m_data;
  EclFrame* m_frame;

  int m_displayMode = 7;
  int m_autoDisplay = 1;
  
  m_app   = new TApplication("ECLDisplay App", 0, 0);
  m_data  = new EclData();
  m_frame = new EclFrame(m_displayMode, m_data, m_autoDisplay, &m_mapper);

  m_frame->Connect("CloseWindow()", "TSystem", gSystem, "ExitLoop()");

  if (argc > 1) {
    m_data->loadRootFile(argv[1]);
    m_frame->loadNewData();
  }

  m_app->Run();

  temp_tfile->Close();
  gSystem->Unlink(temp_fname);

  return 0;
}

