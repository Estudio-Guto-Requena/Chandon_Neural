#ifndef _CONFIG
#define _CONFIG
#include <Arduino.h>
#define ESP_A 1
#define ESP_B 2
#define ESP_C 3
#define ESP_D 4
#define ESP_E 5
#define ESP_F 6
#define ESP_G 7
#define ESP_H 8
#define ESP_I 9

#define IM ESP_I

#if IM == ESP_A
uint8_t address[6]  = {0xC4, 0x64, 0xE3, 0xE7, 0xB9, 0xE6};
#define NAME "ESP_A"

#elif IM == ESP_B
uint8_t address[6]  = {0x00, 0x81, 0xF9, 0x2A, 0x51, 0x4D};
#define NAME "ESP_B"

#elif IM == ESP_C
uint8_t address[6]  = {0xC4, 0x64, 0xE3, 0xE7, 0xB6, 0xA9};
#define NAME "ESP_C"

#elif IM == ESP_D
uint8_t address[6]  = {0x00, 0x81, 0xF9, 0x29, 0xBA, 0xEE};
#define NAME "ESP_D"

#elif IM == ESP_E
uint8_t address[6]  = {0xC4, 0x64, 0xE3, 0xE7, 0xC6, 0x49};
#define NAME "ESP_E"

#elif IM == ESP_F
uint8_t address[6]  = {0xC4, 0x64, 0xE3, 0xE8, 0xF4, 0x90};
#define NAME "ESP_F"

#elif IM == ESP_G
uint8_t address[6]  = {0xC4, 0x64, 0xE3, 0xEA, 0x75, 0x28};
#define NAME "ESP_G"

#elif IM == ESP_H
uint8_t address[6]  = {0xC4, 0x64, 0xE3, 0xEA, 0x7B, 0x1F};
#define NAME "ESP_H"

#elif IM == ESP_I
uint8_t address[6]  = {0xC4, 0x64, 0xE3, 0xEA, 0x77, 0x9C};
#define NAME "ESP_I"
#endif

#endif
