#include <SoftwareSerial.h>

/*
 * See:
 *   http://wiki.seeed.cc/125Khz_RFID_module-UART/
 *   http://www.instructables.com/id/Arduino-and-RFID-from-seeedstudio/
 */

#define TX_PIN 2
#define RX_PIN 3

SoftwareSerial rfid = SoftwareSerial(TX_PIN, RX_PIN);
String msg = "";

void setup() {
  Serial.begin(9600);
  rfid.begin(9600);
}

void loop() {
  // Get message from RFID reader when there are bytes available
  while (rfid.available()) {
    msg += rfid.read();
  }

  // Delay for read to complete, otherwise (msg.length() >= 26)
  // will never evaluate to true
  delay(500);

  // Check if we have read a full message and drop everything after
  // the 26th character as sometimes the tag is read twice into the
  // same message
  if (msg.length() >= 26) {
    Serial.println(msg.substring(0, 26));
  }
  
  // Reset message
  msg = "";
}
