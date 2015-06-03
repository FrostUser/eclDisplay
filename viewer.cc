#include "viewer.h"
#include "geometry.h"
#include <iostream>
#include "EclData.h"

/// Number of cells (crystals) per each fixed phi.
#define THETA_CELLS_COUNT 48
/// Number of cells (crystals) per each fixed theta.
#define PHI_CELLS_COUNT 144

/// Id of palette being used.
#define PALETTE_ID 1

int do_energy_count = 1;

int GetPhiId(int ch_num) {
  int crate_id = GetCrateId(ch_num); // Crate id (0..35)

  int shaper_id = GetShaperId(ch_num); // Shaper id in crate (0..11)
  int shaper_ch = GetShaperChannelId(ch_num); // Channel id in shaper (0..15)

  if (shaper_id < 11)
    return crate_id * 4 + shaper_ch / 4;
  else if (shaper_ch < 8)
    return crate_id * 4 + shaper_ch / 2;

  return -1;
}

int GetThetaId(int ch_num) {
  int shaper_id = GetShaperId(ch_num); // Shaper id in crate (0..11)
  int shaper_ch = GetShaperChannelId(ch_num); // Channel id in shaper (0..15)

  if (shaper_id < 11)
    return shaper_id * 4 + shaper_ch % 4;
  else if (shaper_ch < 8)
    return shaper_id * 4 + shaper_ch % 2;

  return -1;
}

int GetChannel(int theta_id, int phi_id)
{
  for (int i = 0; i < 6912; i++) {
    if (GetThetaId(i) == theta_id && GetPhiId(i) == phi_id)
      return i;
  }

  return -1;
}

void setMode(int i) {
  do_energy_count = i;
}
int GetMode() {
  return do_energy_count;
}
