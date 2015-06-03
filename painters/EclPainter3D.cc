#include "EclPainter3D.h"
#include <TMath.h>
#include <TColor.h>
#include "../geometry.h"
#include "../viewer.h"

#include <iostream>

#define SEG_COUNT_Z 12
#define SEG_COUNT_PHI 36

EclPainter3D::EclPainter3D(EclData *data, EclPainter3D::Type type) :
  EclPainter(data)
{
  m_type = type;
  InitScene();
}

EclPainter3D::~EclPainter3D()
{
}

void EclPainter3D::CreateThetaSegment(int count, TGeoMedium *med, TGeoVolume **segs)
{
  double dphi = 360.0 / count;
  double phi = 0;

  for (int i = 0; i < count; i++) {
    segs[i] = gGeoManager->MakeTubs("Seg", med, 120, 150, 11,
                                    phi-dphi, phi-1);
    phi -= dphi;
  }
}

TGeoVolume* EclPainter3D::CreateSegmentedTube(int theta_count, int phi_count,
                                      TGeoMedium* med, TGeoVolume*** segs)
{
  TGeoVolume* tube_box = gGeoManager->MakeBox("Box", med, 200, 200, 24*12);

  for (int i = 0; i < theta_count; i++) {
    TGeoTranslation* transl = new TGeoTranslation(0, 0, 24*i);
    CreateThetaSegment(phi_count, med, segs[i]);

    for (int j = 0; j < phi_count; j++) {
      tube_box->AddNode(segs[i][j], 1, transl);
      segs[i][j]->SetNumber(j * theta_count + i);
    }
  }

  return tube_box;
}

void EclPainter3D::InitScene()
{
  m_geo_manager = new TGeoManager("world", "ECL");
  TGeoMaterial* mat = new TGeoMaterial("Vacuum", 0, 0, 0);
  TGeoMedium* med = new TGeoMedium("Vacuum", 1, mat);
  m_topbox = gGeoManager->MakeBox("Top", med, 200, 24*SEG_COUNT_Z, 200);
  m_segs = new TGeoVolume**[SEG_COUNT_Z];

  for (int i = 0; i < SEG_COUNT_Z; i++)
    m_segs[i] = new TGeoVolume*[SEG_COUNT_PHI];

  m_box = CreateSegmentedTube(SEG_COUNT_Z, SEG_COUNT_PHI, med, m_segs);

  TGeoRotation* rot = new TGeoRotation("rot1", 90, 90, 180);
  m_topbox->AddNode(m_box, 1, rot);

  gGeoManager->SetTopVolume(m_topbox);
  gGeoManager->CloseGeometry();

  m_topbox->SetVisibility(false);
  gGeoManager->SetTopVisible();
}

void EclPainter3D::GetInformation(int seg_id, int py, MultilineWidget* panel)
{
  EclPainter::GetInformation(0, 0, panel);

  char info[255];

  sprintf(info, "crate_id = %d", seg_id/12);
  panel->SetLine(1, info);
  sprintf(info, "shaper_id = %d", seg_id);
  panel->SetLine(2, info);
}

EclPainter3D::Type EclPainter3D::GetType()
{
  return m_type;
}

void EclPainter3D::Draw()
{
  EclData* data = GetData();
  const int* ev_counts = data->GetEventCounts();
  const float* energy_sums = data->GetEnergySums();

  Double_t r[5]    = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t g[5]    = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t b[5]    = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  Double_t stop[5] = { 0.00, 0.34, 0.61, 0.84, 1.00 };

  int palette = TColor::CreateGradientColorTable(5, stop, r, g, b, 256);

  float vals[SEG_COUNT_PHI*SEG_COUNT_Z];
  float max = 0;

  for (int i = 0; i < SEG_COUNT_PHI*SEG_COUNT_Z; i++) {
    vals[i] = 0;
  }

  int id;

  for (int i = 0; i < 6912; i++) {
    id = GetCrateId(i) * SEG_COUNT_Z + GetShaperId(i);
    if (GetMode())
      vals[id] += energy_sums[i];
    else
      vals[id] += ev_counts[i];

    if (max < vals[id]) max = vals[id];
  }

  for (int i = 0; i < SEG_COUNT_Z; i++) {
    for (int j = 0; j < SEG_COUNT_PHI; j++) {
      int color = kGray;
      if (vals[j*SEG_COUNT_Z + i] > 0) {
        vals[j*SEG_COUNT_Z + i] = TMath::Log(1 + vals[j*SEG_COUNT_Z + i]) /
            TMath::Log(1 + max);
        color = palette + vals[j*12 + i] * 255;
      }

      m_segs[i][j]->SetLineColor(color);
    }
  }

  m_topbox->Draw("gl");
}
