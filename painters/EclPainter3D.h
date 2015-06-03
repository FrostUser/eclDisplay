#ifndef ECL_CANVAS_3D
#define ECL_CANVAS_3D

#include <TGeoManager.h>
#include <TGeoMaterial.h>
#include <TGeoMedium.h>
#include <TGeoVolume.h>
#include "EclPainter.h"

class EclPainter3D : public EclPainter {
public:
  enum Type{THETA_PHI};

  EclPainter3D(EclData* data, Type m_type);
  ~EclPainter3D();

private:
  Type m_type;
  /// Segments of the calorimeter barrel.
  TGeoVolume*** m_segs;
  /// Box which contains the calorimeter.
  TGeoVolume* m_box;
  /// The top box which contains the entire scene.
  TGeoVolume* m_topbox;
  TGeoManager* m_geo_manager;

  /// For testing, going to remove soon.
  TGCompositeFrame* m_frame;

  void CreateThetaSegment(int count, TGeoMedium* med, TGeoVolume** m_segs);
  TGeoVolume* CreateSegmentedTube(int theta_count, int phi_count,
                                  TGeoMedium *med, TGeoVolume ***segs);
  void InitScene();

public:
  /**
   * @brief Sets the information to be displayed in the provided
   * MultilineWidget
   * @param px X coordinate of mouse cursor.
   * @param py Y coordinate of mouse cursor.
   */
  virtual void GetInformation(int px, int py, MultilineWidget* panel);

  Type GetType();

  /**
   * @brief Redraw the canvas.
   */
  virtual void Draw();
};

#endif // ECL_CANVAS_3D
