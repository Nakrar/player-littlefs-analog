/**
 * @file player-littlefs-i2s.ino
 * @brief example using the LittleFS library
 * 
 * @author Phil Schatzmann
 * @copyright GPLv3
 */

#include "AudioTools.h"
#include "AudioLibs/AudioSourceLittleFS.h"
#include "AudioCodecs/CodecMP3Helix.h"

// SOURCE
const char *startFilePath="/";
const char* ext="mp3";
AudioSourceLittleFS source(startFilePath, ext);

// OUT
AnalogAudioStream out; 

// DECODE
MP3DecoderHelix decoder;

AudioPlayer player(source, out, decoder);

void printMetaData(MetaDataType type, const char* str, int len){
  Serial.print("==> ");
  Serial.print(toStr(type));
  Serial.print(": ");
  Serial.println(str);
}

void setup() {
  Serial.begin(115200);
  AudioLogger::instance().begin(Serial, AudioLogger::Info);

  // start the analog output
  auto config = out.defaultConfig(TX_MODE);
//  config.copyFrom(info); 
  out.begin(config);

  // setup player
  //source.setFileFilter("*Bob Dylan*");
  player.setMetadataCallback(printMetaData);
  player.begin();
}

void loop() {
  player.copy();
}
