#ifndef _CONFIG
#define _CONFIG
#include <Arduino.h>
#define ESP_A 1
#define ESP_B 2
#define ESP_C 3

#define IM ESP_C

#if IM == ESP_A
uint8_t address[6]  = {0xC4, 0x64, 0xE3, 0xE7, 0xB9, 0xE6};
#define NAME "ESP_A"

#elif IM == ESP_B
uint8_t address[6]  = {0xC4, 0x64, 0xE3, 0xE7, 0xA3, 0x33};
#define NAME "ESP_B"

#elif IM == ESP_C
uint8_t address[6]  = {0xC4, 0x64, 0xE3, 0xE7, 0xB6, 0xA9};
#define NAME "ESP_C"
#endif

#endif
