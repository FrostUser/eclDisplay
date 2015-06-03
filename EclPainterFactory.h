#ifndef ECLPAINTERFACTORY_H
#define ECLPAINTERFACTORY_H

#include "painters/EclPainter.h"
#include "painters/EclPainter1D.h"
#include "painters/EclPainter2D.h"
#include "painters/EclPainter3D.h"
#include "painters/EclPainterPolar.h"

// Also see const char* titles definition in EclPainterFactory.cc
enum EclPainterType {
  PAINTER_PHI,
//  PAINTER_THETA,
  PAINTER_CHANNEL,
  PAINTER_SHAPER,
  PAINTER_COLLECTOR,
  PAINTER_CHANNEL_2D,
  PAINTER_SHAPER_2D,
  PAINTER_3D
};

class EclPainterFactory
{
private:
  static const int types_count = PAINTER_3D+1;
  static const char* titles[types_count];

  EclPainterFactory();

public:

  static EclPainter* CreatePainter(EclPainterType type, EclData* data);
  static const char** GetTypeTitles();
  static const int GetTypeTitlesCount();
};

#endif // ECLPAINTERFACTORY_H
