#ifndef AUDIO_H
#define AUDIO_H

#include <stdint.h>

void audio_init(void);
void audio_beep(uint32_t frequency, uint32_t duration_ms);
void audio_play_melody(void);

#endif
