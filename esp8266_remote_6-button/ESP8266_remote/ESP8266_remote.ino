#include <ESP8266WiFi.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint8_t BUTTON_PIN_1 = 0;    // Пин для первой кнопки                        (Вы можете поменять пин подключения)
const uint8_t BUTTON_PIN_2 = 2;    // Пин для второй кнопки                        (Вы можете поменять пин подключения)
const uint8_t BUTTON_PIN_3 = 12;     // Пин для третьей кнопки                     (Вы можете поменять пин подключения)
const uint8_t BUTTON_PIN_4 = 13;     // Пин для четвертой кнопки                   (Вы можете поменять пин подключения)
const uint8_t BUTTON_PIN_5 = 14;    // Пин для пятой кнопки                        (Вы можете поменять пин подключения)
const uint8_t BUTTON_PIN_6 = 16;    // Пин для шестой кнопки                       (Вы можете поменять пин подключения)
const uint8_t BUTTON_PIN_7 = 5;     // Пин для седьмой кнопки                      (Вы можете поменять пин подключения)
const uint8_t IR_TX_PIN = 4;        // НЕ ИСПОЛЬЗУЙТЕ ПИН, Пин для ИК-передатчика  (Вы можете поменять пин подключения, кроме пина 2)

const uint64_t IR_CODE_1 = 0x10C8E11E; // HEX-код для первой кнопки                (Это мои коды, их надо заменить на свои)
const uint64_t IR_CODE_2 = 0x4CB3817E; // HEX-код для второй кнопки                (Это мои коды, их надо заменить на свои)
const uint64_t IR_CODE_3 = 0x8087887;  // HEX-код для третьей кнопки               (Это мои коды, их надо заменить на свои)
const uint64_t IR_CODE_4 = 0x808E817;  // HEX-код для четвертой кнопки             (Это мои коды, их надо заменить на свои)
const uint64_t IR_CODE_5 = 0x808F807;  // HEX-код для пятой кнопки                 (Это мои коды, их надо заменить на свои)
const uint64_t IR_CODE_6 = 0x8086897;  // HEX-код для шестой кнопки                (Это мои коды, их надо заменить на свои)
const uint64_t IR_CODE_7 = 0x808C03F;  // HEX-код для седьмой кнопки               (Это мои коды, их надо заменить на свои)

IRsend irSender(IR_TX_PIN);

void setup() {
  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);
  pinMode(BUTTON_PIN_3, INPUT_PULLUP);
  pinMode(BUTTON_PIN_4, INPUT_PULLUP);
  pinMode(BUTTON_PIN_5, INPUT_PULLUP);
  pinMode(BUTTON_PIN_6, INPUT_PULLUP);
  pinMode(BUTTON_PIN_7, INPUT_PULLUP);
  irSender.begin();
}

void loop() {
  if (digitalRead(BUTTON_PIN_1) == LOW) {
    sendIRCode(IR_CODE_1);
    delay(1000);                  // Задержка для предотвращения множественных нажатий кнопки
  } else if (digitalRead(BUTTON_PIN_2) == LOW) {
    sendIRCode(IR_CODE_2);
    delay(1000);                  // Задержка для предотвращения множественных нажатий кнопки
  } else if (digitalRead(BUTTON_PIN_3) == LOW) {
    sendIRCode(IR_CODE_3);
    delay(1000);                  // Задержка для предотвращения множественных нажатий кнопки
  } else if (digitalRead(BUTTON_PIN_4) == LOW) {
    sendIRCode(IR_CODE_4);
    delay(1000);                  // Задержка для предотвращения множественных нажатий кнопки
  } else if (digitalRead(BUTTON_PIN_5) == LOW) {
    sendIRCode(IR_CODE_5);
    delay(1000);                  // Задержка для предотвращения множественных нажатий кнопки
  } else if (digitalRead(BUTTON_PIN_6) == LOW) {
    sendIRCode(IR_CODE_6);
    delay(1000);                  // Задержка для предотвращения множественных нажатий кнопки
  } else if (digitalRead(BUTTON_PIN_7) == LOW) {
    sendIRCode(IR_CODE_7);
    delay(1000);                  // Задержка для предотвращения множественных нажатий кнопки
  }
}

void sendIRCode(uint64_t code) {
  irSender.sendNEC(code, 32); // Отправка IR-кода
}
