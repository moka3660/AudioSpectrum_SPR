#include <Audio.h>
#include "arduinoFFT.h"

#define SAMPLES 256
#define SAMPLINGFREQ 48000

arduinoFFT FFT = arduinoFFT();

double vReal[SAMPLES];
double vImag[SAMPLES];
int counte=0;

double mic_a;

AudioClass *theAudio;

static const int32_t recoding_frames = 400;
static const int32_t buffer_size = 1024;/* 1ch */ /*768sample,4ch,16bit -> 6144*/
static char          s_buffer[buffer_size];
static int16_t buff[buffer_size]; //^-^

bool ErrEnd = false;

/**
 * @brief Audio attention callback
 *
 * When audio internal error occurc, this function will be called back.
 */

void audio_attention_cb(const ErrorAttentionParam *atprm)
{
  puts("Attention!");
  
  if (atprm->error_code >= AS_ATTENTION_CODE_WARNING)
    {
      ErrEnd = true;
   }
}

/**
 *  @brief Setup audio device to capture PCM stream
 *
 *  Select input device as microphone <br>
 *  Set PCM capture sapling rate parameters to 48 kb/s <br>
 *  Set channel number 4 to capture audio from 4 microphones simultaneously <br>
 *  System directory "/mnt/sd0/BIN" will be searched for PCM codec
 */
void setup()
{
  theAudio = AudioClass::getInstance();

  theAudio->begin(audio_attention_cb);

  puts("initialization Audio Library");

  /* Select input device as microphone */
  theAudio->setRecorderMode(AS_SETRECDR_STS_INPUTDEVICE_MIC);

  /*
   * Set PCM capture sapling rate parameters to 48 kb/s. Set channel number 4
   * Search for PCM codec in "/mnt/sd0/BIN" directory
   */
  theAudio->initRecorder(AS_CODECTYPE_PCM, "/mnt/sd0/BIN", AS_SAMPLINGRATE_48000, AS_CHANNEL_MONO);
  puts("Init Recorder!");

  puts("Rec!");
  theAudio->startRecorder();

  Serial.begin(115200);
}

/**
 * @brief Audio signal process for your application
 */

void signal_process(uint32_t size)
{
  /* The actual signal processing will be coding here.
     For example, prints capture data. */

  //printf("started!");

  //構造体を定義してバッファの内容をキャスト
  // https://ja.stackoverflow.com/questions/55107/spresense-arduino-%E3%81%AE%E3%82%B9%E3%82%B1%E3%83%83%E3%83%81%E4%BE%8B-pcm-capture%E3%81%AE%E9%9F%B3%E5%A3%B0%E3%83%87%E3%83%BC%E3%82%BF%E6%A7%8B%E9%80%A0%E3%81%AB%E3%81%A4%E3%81%84%E3%81%A6
  struct channel_bit16
  {    
    uint16_t micA; //   uint16_t micB;  uint16_t micC;   uint16_t micD;
  };

  struct channel_bit16 *mic_data = (struct channel_bit16 *) s_buffer; // 0番目のデータにアクセス
  mic_a = mic_data[0].micA; //uint16_t mic_b = mic_data[0].micB;//uint16_t mic_c = mic_data[0].micC;//uint16_t mic_d = mic_data[0].micD;
    
}

/**
 * @brief Execute frames for FIFO empty
 */

void execute_frames()
{
  uint32_t read_size = 0;
  do
    {
      err_t err = execute_aframe(&read_size);
      if ((err != AUDIOLIB_ECODE_OK)
       && (err != AUDIOLIB_ECODE_INSUFFICIENT_BUFFER_AREA))
        {
          break;
        }
    }
  while (read_size > 0);
}

/**
 * @brief Execute one frame
 */

err_t execute_aframe(uint32_t* size)
{
  err_t err = theAudio->readFrames(s_buffer, buffer_size, size);

  if(((err == AUDIOLIB_ECODE_OK) || (err == AUDIOLIB_ECODE_INSUFFICIENT_BUFFER_AREA)) && (*size > 0)) 
    {
      signal_process(*size);
    }

  return err;
}

/*FFT
void fft()
{

}


/**
 * @brief Capture frames of PCM data into buffer
 */
void loop() {

  static int32_t total_size = 0;
  uint32_t read_size =0;

  /* Execute audio data */
  err_t err = execute_aframe(&read_size);
  if (err != AUDIOLIB_ECODE_OK && err != AUDIOLIB_ECODE_INSUFFICIENT_BUFFER_AREA)
    {
      theAudio->stopRecorder();
      goto exitRecording;
    }
  else if (read_size>0)
    {
      total_size += read_size;
    }
  /* ここやで */
  vReal[counte] = mic_a;
  counte++;
/*
  Serial.print(mic_a);
  Serial.print("  ");
  Serial.print(counte);
  Serial.print("  ");
  Serial.println(vReal[counte]);
*/
 // if(counte>=SAMPLES)
 // {
  //  Serial.println("Yes!");
  
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
  double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLINGFREQ);
  Serial.println(peak);
  delay(10);
 // }

  /* This sleep is adjusted by the time to write the audio stream file.
     Please adjust in according with the processing contents
     being processed at the same time by Application.
  */
//  usleep(10000);

  /* Stop Recording */
  if (total_size > (recoding_frames*buffer_size))
    {
      theAudio->stopRecorder();

      /* Get ramaining data(flushing) */
      sleep(1); /* For data pipline stop */
      execute_frames();
      
      goto exitRecording;
    }

  if (ErrEnd)
    {
      printf("Error End\n");
      theAudio->stopRecorder();
      goto exitRecording;
    }

  return;

exitRecording:

  theAudio->setReadyMode();
  theAudio->end();
  
  puts("End Recording");
  exit(1);

}
