#include "EclData.h"

#include <iostream>

EclData::EclData() {
  m_tree = new TChain("tree");
  InitVariables();
}

EclData::EclData(const char* filename, bool update) {
  m_tree = new TChain("tree");
  InitVariables();
  AddFile(filename);
}

EclData::EclData(TChain *tree, bool update) {
  m_tree = tree;
  InitVariables();
  InitEventRanges();
}

EclData::~EclData() {
  delete m_event_counts;
  delete m_energy_sums;
  delete m_tree;
}

void EclData::InitVariables() {
  m_event_counts = new int[6912];
  m_energy_sums = new float[6912];

  m_last_event_id = -1;
  m_en_range_max = -1;

  m_excluded_ch.clear();
}

void EclData::InitEventRanges()
{
  m_event_entry.clear();

  int count = m_tree->GetEntries();
  int time, evtn;

  m_tree->SetBranchAddress("time", &time);
  m_tree->SetBranchAddress("evtn", &evtn);

  for (int i = 0; i < count; i++) {
    m_tree->GetEntry(i);

    if (m_time_max < time) m_time_max = time;

    // This is used to avoid the cases of empty events.
    while (evtn > m_last_event_id) {
      m_last_event_id++;
      m_event_entry.push_back(i);
    }
  }

  m_time_range_min = 0;
  m_time_range_max = m_time_max;

  m_ev_range_min = 0;
  m_ev_range_max = m_last_event_id;
}

void EclData::AddFile(const char* filename, bool update) {
  m_tree->Add(filename);
  InitEventRanges();
}

TChain* EclData::GetTree() {
  return m_tree;
}

int* EclData::GetEventCounts() {
  return m_event_counts;
}
// Alias for GetEventCounts()
int* EclData::GetEventCountsPerCrystal() {
  return GetEventCounts();
}

int EclData::GetEventCountsMax() {
  return m_event_count_max;
}

float* EclData::GetEnergySums() {
  return m_energy_sums;
}
// Alias for GetAmplitudeSums()
float* EclData::GetEnergySumPerCrystal() {
  return GetEnergySums();
}

float EclData::GetEnergySumsMax() {
  return m_energy_sums_max;
}

float EclData::GetEnergyEmission() {
  return m_energy_emission;
}

// TODO: is there some fancy Root classes for this occurence?
int EclData::GetTimeRangeMin() {
  return m_time_range_min;
}
int EclData::GetTimeRangeMax() {
  return m_time_range_max;
}

void EclData::SetTimeRange(int time_min, int time_max, bool update) {
  if (m_time_range_min == time_min && m_time_range_max == time_max)
    return;

  m_time_range_min = time_min;
  m_time_range_max = time_max;
  if (update)
    Update();
}

int EclData::GetEventRangeMin() {
  return m_ev_range_min;
}
int EclData::GetEventRangeMax() {
  return m_ev_range_max;
}
void EclData::SetEventRange(int ev_min, int ev_max, bool update) {
  if (ev_min == m_ev_range_min && ev_max == m_ev_range_max)
    return;

  m_ev_range_min = ev_min;
  m_ev_range_max = ev_max;
  if (update)
    Update();
}

void EclData::SetEnergyThreshold(int en_min, int en_max, bool update)
{
  if (en_min == m_en_range_min && en_max == m_en_range_max)
    return;

  m_en_range_min = en_min;
  m_en_range_max = en_max;
  if (update)
  Update();
}

int EclData::GetTimeMin() {
  return 0;
}
int EclData::GetTimeMax() {
  return m_time_max;
}

int EclData::GetLastEventId() {
  return m_last_event_id;
}

void EclData::ExcludeChannel(int ch, bool update) {
  m_excluded_ch.insert(ch);
  if (update)
    Update();
}

void EclData::IncludeChannel(int ch, bool update) {
  m_excluded_ch.erase(ch);
  if (update)
    Update();
}

void EclData::Update() {
  int start, end;

  if (m_ev_range_min > m_last_event_id || m_ev_range_min > m_ev_range_max)
    return;

  start = m_event_entry[m_ev_range_min];
  if (m_ev_range_max < m_last_event_id)
    end = m_event_entry[m_ev_range_max+1];
  else
    end = m_tree->GetEntries();

  int ch, amp, time, evtn;

  for (int i = 0; i < 6912; i++) {
    m_event_counts[i] = 0;
    m_energy_sums[i] = 0;
  }
  m_event_count_max = 0;
  m_energy_sums_max = 0;
  m_time_max = 0;
  m_energy_emission = 0;

  m_tree->SetBranchAddress("ch", &ch);
  m_tree->SetBranchAddress("amp", &amp);
  m_tree->SetBranchAddress("time", &time);
  m_tree->SetBranchAddress("evtn", &evtn);

  for (int i = start; i < end; i++) {
    m_tree->GetEntry(i);

    if (m_excluded_ch.count(ch) > 0) continue;

    if (ch >= 0 && ch < 6912) {
      // Check if current time belongs to time_range, set by user.
      if (m_time_range_max >= 0)
        if (time < m_time_range_min || time > m_time_range_max)
          continue;

      float energy = (float)amp / 20;

      if (m_en_range_max >= 0)
        if (energy < m_en_range_min || energy > m_en_range_max)
        continue;

      m_event_counts[ch]++;
      if (m_event_count_max < m_event_counts[ch])
        m_event_count_max = m_event_counts[ch];

      m_energy_sums[ch] += energy;
      m_energy_emission += energy;

      if (m_energy_sums_max < m_energy_sums[ch])
        m_energy_sums_max = m_energy_sums[ch];
    }
  }

  if (m_time_range_max < 0)
    m_time_range_max = m_time_max;
  if (m_ev_range_max < 0)
    m_ev_range_max = m_last_event_id;

  std::cout << end - start << " events handled." << std::endl;
}
