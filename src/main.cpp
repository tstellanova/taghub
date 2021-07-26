/*
 * Copyright (c) 2021 Particle Industries, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <Particle.h>

#include "BeaconScanner.h"

SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(SEMI_AUTOMATIC);

// max number of BLE scan results supported
const size_t SCAN_RESULT_MAX = 30;
// our custom adv data length
const size_t CUSTOM_ADV_DATA_LEN = 7;

// SerialLogHandler logHandler(LOG_LEVEL_INFO);
SerialLogHandler logHandler(115200, LOG_LEVEL_INFO, {    
    { "app", LOG_LEVEL_INFO },
});



/// Perform a device reset on demand from the network
static int do_reset(String ignore) {
  Log.info("Reset on network command");
  System.reset();
  return 0;
}

// setup() runs once, when the device is first turned on.
void setup() {
  Serial.begin();
  delay(3000); //wait for serial usb to init, if connected
  Log.info("=== begin ===");

    // enable BLE radio so we can use it for scanning
  if ( SYSTEM_ERROR_NONE != BLE.on()) {
      Log.error("BLE on failed");
  }

  Particle.function("reset", do_reset);

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  static uint32_t reconnect_count = 0;

  if (!Particle.connected()) {
    if (reconnect_count > 20) {
      Log.warn("Reset on poor network");
      System.reset();
    }
    Particle.connect();
    delay(3000);
    reconnect_count += 1;
  }
  else {
    reconnect_count = 0;
    Scanner.scanAndPublish(5, SCAN_IBEACON | SCAN_EDDYSTONE, "bcnz", PRIVATE);
    delay(5000);
  }
}

