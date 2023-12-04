#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRsend.h>

const uint8_t PIN_IR_RX = 2; //D4 ик приёмник
const uint8_t PIN_IR_TX = 4; //D2 ик передатчик  в данном случае не используется

const uint16_t CAPTURE_BUFFER_SIZE = 256;
const uint8_t TIMEOUT = 45; // 15

const uint32_t BLINK_TIMEOUT = 5000; // 5 sec.

IRrecv irRX(PIN_IR_RX, CAPTURE_BUFFER_SIZE, TIMEOUT, true);
IRsend irTX(PIN_IR_TX);
decode_results results;
uint16_t rawBuf[CAPTURE_BUFFER_SIZE];
uint16_t rawBufLen = 0;
uint32_t nextBlink;

void setup() {
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
  Serial.println();

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  irRX.enableIRIn();
  irTX.begin();
}

bool cloneBuffer(decode_results *results) {
  static const char irTypes[][14] PROGMEM = { "UNKNOWN", "UNUSED", "RC5", "RC6", "NEC", "SONY", "PANASONIC", "JVC", "SAMSUNG", "WHYNTER",
    "AIWA_RC_T501", "LG", "SANYO", "MITSUBISHI", "DISH", "SHARP", "COOLIX", "DAIKIN", "DENON", "KELVINATOR", "SHERWOOD", "MITSUBISHI_AC",
    "RCMM", "SANYO_LC7461", "RC5X", "GREE", "PRONTO", "NEC_LIKE", "ARGO", "TROTEC" };

  if (results->repeat) {
    Serial.println(F("IR sequence is repeat code, ignored!"));
    return false;
  }
  if (results->overflow) {
    Serial.println(F("IR sequence too big!"));
    return false;
  }

  Serial.print(F("IR type: "));
  Serial.print(FPSTR(irTypes[results->decode_type - UNKNOWN]));
  Serial.print(F(", code: 0x"));
  Serial.print((uint32_t)results->value, HEX);
  Serial.print(F(" ("));
  Serial.print(results->bits);
  Serial.println(F(" bits)"));

  rawBufLen = 0;
  for (uint16_t i = 1; i < results->rawlen; ++i) {
    uint32_t usecs;

    for (usecs = results->rawbuf[i] * RAWTICK; usecs > UINT16_MAX; usecs -= UINT16_MAX) {
      rawBuf[rawBufLen++] = UINT16_MAX;
      rawBuf[rawBufLen++] = 0;
    }
    rawBuf[rawBufLen++] = usecs;
  }
  Serial.print(F("Raw code buffer length: "));
  Serial.println(rawBufLen);

  nextBlink = millis() + BLINK_TIMEOUT;

  return true;
}

void ledPulse(uint32_t onDuration = 500, uint32_t offDuration = 0, uint8_t count = 1) {
  while (count--) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(onDuration);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(offDuration);
  }
}

void loop() {
  if (irRX.decode(&results)) {
    if (cloneBuffer(&results)) {
      ledPulse(250, 100, 3);
    }
    irRX.resume();
  }
  if (rawBufLen && ((int32_t)millis() >= (int32_t)nextBlink)) {
    irRX.disableIRIn();
    irTX.sendRaw(rawBuf, rawBufLen, 38);
    irRX.enableIRIn();
    ledPulse(250);
    nextBlink = millis() + BLINK_TIMEOUT;
  }
  yield();
}
