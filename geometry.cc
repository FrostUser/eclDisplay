
int GetCrateId(int ch_num) {
  return ch_num / 192;
}
// Identical to GetCrateId
int GetCollectorId(int ch_num) {
  return GetCrateId(ch_num);
}

int GetCrateChannelId(int ch_num) {
  return ch_num % 192;
}

int GetShaperId(int ch_num) {
  return GetCrateChannelId(ch_num) / 16;
}

int GetShaperChannelId(int ch_num) {
  return GetCrateChannelId(ch_num) % 16;
}

int GetChannelCount() {
  return 6912;
}
