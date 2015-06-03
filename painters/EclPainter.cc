#include "EclPainter.h"

int EclPainter::m_obj_counter = 0;

EclPainter::EclPainter(EclData* data)
{
  SetData(data);
}

EclPainter::~EclPainter()
{

}

void EclPainter::SetData(EclData* data)
{
  m_ecl_data = data;
}

EclData* EclPainter::GetData()
{
  return m_ecl_data;
}

void EclPainter::GetInformation(int px, int py, MultilineWidget* panel)
{
  char info[255];
  sprintf(info, "energy emission = %.2f MeV", m_ecl_data->GetEnergyEmission());
  panel->SetLine(0, info);
}

EclPainter* EclPainter::HandleClick(int px, int py)
{
  return NULL;
}

void EclPainter::SetXRange(int x1, int x2)
{
}

void EclPainter::GetNewRootObjectName(char *buf, int n)
{
  snprintf(buf, n, "ECL DATA_%d", m_obj_counter++);
}
