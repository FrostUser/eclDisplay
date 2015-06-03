#ifndef ECL_CANVAS_2D
#define ECL_CANVAS_2D

#include "EclPainter.h"
#include <TH2F.h>

class EclPainter2D : public EclPainter {
public:
  enum Type{CHANNEL_2D, SHAPER_2D, NONE};

  EclPainter2D(EclData* data, Type type);
  ~EclPainter2D();

private:
  Type m_type;
  TH2F* m_hist;

  void SetTitle();
  int GetMaxX();
  int GetMaxY();
  int ChannelToSegIdX(int channel);
  int ChannelToSegIdY(int channel);

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

#endif // ECL_CANVAS_2D
