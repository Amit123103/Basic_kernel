#include "kernel.h"
#include "audio/audio.h"

void audio_init(void)
{
    kprintf("Audio subsystem initialized\n");
}

void audio_beep(uint32_t frequency, uint32_t duration_ms)
{
    (void)frequency;
    (void)duration_ms;
    kprintf("Audio beep requested\n");
}

void audio_play_melody(void)
{
    kprintf("Audio melody placeholder\n");
}
