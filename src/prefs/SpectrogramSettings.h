/**********************************************************************

Audacity: A Digital Audio Editor

SpectrogramSettings.h

Paul Licameli

**********************************************************************/

#ifndef __AUDACITY_SPECTROGRAM_SETTINGS__
#define __AUDACITY_SPECTROGRAM_SETTINGS__

#include "../Experimental.h"

struct FFTParam;
class SpectrumPrefs;

class SpectrogramSettings
{
   friend class SpectrumPrefs;
public:

   enum {
      LogMinWindowSize = 3,
      LogMaxWindowSize = 15,

      NumWindowSizes = LogMaxWindowSize - LogMinWindowSize + 1,
   };

   static SpectrogramSettings &defaults();
   SpectrogramSettings();
   SpectrogramSettings(const SpectrogramSettings &other);
   SpectrogramSettings& operator= (const SpectrogramSettings &other);
   ~SpectrogramSettings();

   bool IsDefault() const
   {
      return this == &defaults();
   }

   bool Validate(bool quiet);
   void LoadPrefs();
   void SavePrefs();
   void InvalidateCaches();
   void DestroyWindows();
   void CacheWindows() const;
   void ConvertToEnumeratedWindowSizes();
   void ConvertToActualWindowSizes();

private:
   int minFreq;
   int maxFreq;
   int logMinFreq;
   int logMaxFreq;
public:
   int GetMinFreq(double rate) const;
   int GetMaxFreq(double rate) const;
   int GetLogMinFreq(double rate) const;
   int GetLogMaxFreq(double rate) const;

   void SetMinFreq(int freq);
   void SetMaxFreq(int freq);
   void SetLogMinFreq(int freq);
   void SetLogMaxFreq(int freq);

public:
   int range;
   int gain;
   int frequencyGain;

   int windowType;
   int windowSize;
#ifdef EXPERIMENTAL_ZERO_PADDED_SPECTROGRAMS
   int zeroPaddingFactor;
#endif

   int GetFFTLength(bool autocorrelation) const; // window size (times zero padding, if STFT)

   bool isGrayscale;

#ifdef EXPERIMENTAL_FFT_Y_GRID
   bool fftYGrid;
#endif //EXPERIMENTAL_FFT_Y_GRID

#ifdef EXPERIMENTAL_FIND_NOTES
   bool fftFindNotes;
   bool findNotesMinA;
   bool numberOfMaxima;
   bool findNotesQuantize;
#endif //EXPERIMENTAL_FIND_NOTES

   // Following fields are derived from preferences.

#ifdef EXPERIMENTAL_USE_REALFFTF
   // Variables used for computing the spectrum
   mutable FFTParam      *hFFT;
   mutable float         *window;
#endif
};

#endif
