#ifndef PC_SPEAKER_SOUNDS_H
#define PC_SPEAKER_SOUNDS_H

#include "../../pc_speaker.h"

void happy_birthday_sound()
{
    PLAY(C4, 300);
    PLAY(C4, 150);
    
    PLAY(D4, 400);
    PLAY(C4, 400);
    PLAY(F4, 400);
    PLAY(E4, 800);
    PAUSE(200);
    
    PLAY(C4, 300);
    PLAY(C4, 150);
    PLAY(D4, 400);
    PLAY(C4, 400);
    PLAY(G4, 400);
    PLAY(F4, 800);
    PAUSE(200);
    
    PLAY(C4, 300);
    PLAY(C4, 150);
    PLAY(C5, 400);
    PLAY(A4, 400);
    PLAY(F4, 400);
    PLAY(E4, 400);
    PLAY(D4, 800);
    PAUSE(200);
    
    PLAY(Bb4, 300);
    PLAY(Bb4, 150);
    PLAY(A4, 400);
    PLAY(F4, 400);
    PLAY(G4, 400);
    PLAY(F4, 800);
    PAUSE(400);
}
void clap_sound()
{
    for (int i = 0; i < 20; i++) {
        beep_sound(500 + (i * 50), 5);
    }
}

void dnb_beat()
{
    beep_sound(100, 30);
    sleep_ms(20);
    beep_sound(2000, 10);
    sleep_ms(30);
    beep_sound(100, 20);
    sleep_ms(20);
    beep_sound(3000, 5);
}

void hardcore_glitch_hop_music()
{
    for (int i = 0; i < 8; i++) {
        PLAY(50, 100);
        PLAY(50, 100);
        PLAY(500, 100);
        PLAY(50, 100);
        PLAY(500, 100);
    }
    for (int i = 0; i < 8; i++) {
        PLAY(50, 100);
        PLAY(50, 100);
        PLAY(500, 100);
        PLAY(50, 100);
        PLAY(500, 100);
        clap_sound();
    }
    for (int i = 0; i < 16; i++) {
        PLAY(50, 50);
        PLAY(50, 50);
        PLAY(500, 50);
        PLAY(50, 50);
        PLAY(500, 50);
        clap_sound();
    }
    for (int i = 0; i < 8; i++) {
        PLAY(10, 60);
        PLAY(10, 50);
    }
    PAUSE(2000);
    PLAY(1000, 100);
    for (int i = 0; i < 16 * 4; i++) {
        PLAY(1000, 100);
        dnb_beat();
    }
    PLAY(7000, 2500);
}

#endif