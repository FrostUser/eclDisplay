#ifndef ECLCHANNELMAPPER_H
#define ECLCHANNELMAPPER_H
// #include <framework/logging/Logger.h>
namespace Belle2 {

#define DETECTOR_MASK 0xFF000000 // tentative
#define COPPERID_MASK 0x00FFFFFF // tentative
#define SVD_ID  0x01000000 // tentative
#define CDC_ID  0x02000000 // tentative
#define TOP_ID 0x03000000 // tentative
#define ARICH_ID 0x04000000 // tentative
#define BECL_ID  0x05000000 // tentative
#define EECL_ID  0x06000000 // tentative
#define BKLM_ID  0x07000000 // tentative
#define EKLM_ID  0x08000000 // tentative
#define TRGDATA_ID  0x10000000 // tentative
#define CDCTRGDATA_ID  0x11000000 // tentative
#define ECLTRGDATA_ID  0x12000000 // tentative
#define TOPTRGDATA_ID  0x13000000 // tentative
#define KLMTRGDATA_ID  0x14000000 // tentative
#define GDLTRGDATA_ID  0x15000000 // tentative

  enum {
    ECL_BARREL_SHAPERS_IN_CRATE = 12,
    ECL_FWD_SHAPERS_IN_CRATE    = 10,
    ECL_BKW_SHAPERS_IN_CRATE    = 8,
    ECL_TOTAL_SHAPERS      = 576,
    ECL_FINESSES_IN_COPPER = 2,
    ECL_CHANNELS_IN_SHAPER = 16,
    ECL_CRATES             = 52,
    ECL_BARREL_CRATES      = 36,
    ECL_FWD_CRATES         = 8,
    ECL_BKW_CRATES         = 8,
    ECL_COPPERS            = 26,
    ECL_BARREL_COPPERS     = 18,
    ECL_ENCAP_COPPERS      = 8,
    ECL_TOTAL_CHANNELS     = 8736,
    ECL_BARREL_CHANNELS    = 6624,
    ECL_FWD_CHANNELS       = 1152,
    ECL_BKW_CHANNELS       = 960
  };

  class ECLChannelMapper {

    bool isInitialized;

    /// convert (iCrate, iShaper, iChannel) to CellId for Barrel ECL
    int convertArrayBarrel[ECL_BARREL_CRATES * ECL_BARREL_SHAPERS_IN_CRATE * ECL_CHANNELS_IN_SHAPER];
    /// convert (iCrate, iShaper, iChannel) to CellId for Forward endcap
    int convertArrayFWD[ECL_FWD_CRATES * ECL_FWD_SHAPERS_IN_CRATE * ECL_CHANNELS_IN_SHAPER];
    /// convert (iCrate, iShaper, iChannel) to CellId Backward endcap
    int convertArrayBKW[ECL_BKW_CRATES * ECL_BKW_SHAPERS_IN_CRATE * ECL_CHANNELS_IN_SHAPER];
    /// convert CellId to (iCrate, iShaper, iChannel)
    int convertArrayInv[ECL_TOTAL_CHANNELS][3]; // 0 -- icrate, 1 -- iboard, 2 -- ichannel

  public:
    ECLChannelMapper();
    ~ECLChannelMapper() {};
    /// Initialize channel mapper using data stored in the ASCII file
    bool initFromFile(const char* eclMapFile);
    /// Initialize from DataBase TODO
    bool initFromDB();

    /// get crate number by given COPPER node number and FINESSE number
    int getCrateID(int iCOPPERNode, int iFINESSE); // iFINNES = 0 (FINESSE A) or 1 (FINESSE B)
    /// get CellId by given crate number, shaper position in the crate and DSP channel number in the shaper
    int getCellId(int iCrate, int iShaper, int iChannel);
    /// get number of COPPER node by given crate number
    int getCOPPERNode(int iCrate);
    /// get number of FINESSE (0/1) in COPPER by given crate number
    int getFINESSE(int iCrate);
    /// get ECL subsystem ID by given crate number: 0 -- barrel, 1 -- forward. 2 -- backward endcap
    int getSubSystem(int iCrate);

    /// get crate number by given CellId
    int getCrateID(int cellID);
    /// get position of the shaper in the crate by given CellId
    int getShaperPosition(int cellID);
    /// get number of DSP channel in the shaper by given number of  CellId
    int getShaperChannel(int cellID);

    inline int getNShapersInCrate(int iCrate)
    {
      if (iCrate <= ECL_BARREL_CRATES) return ECL_BARREL_SHAPERS_IN_CRATE;
      if (ECL_BARREL_CRATES < iCrate && iCrate <= ECL_BARREL_CRATES + ECL_FWD_CRATES) return ECL_FWD_SHAPERS_IN_CRATE;
      if (ECL_BARREL_CRATES + ECL_FWD_CRATES < iCrate && iCrate <= ECL_CRATES) return ECL_BKW_SHAPERS_IN_CRATE;
      return 0;
    }




  };


}
#endif
