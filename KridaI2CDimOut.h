#include "esphome.h"
 
using namespace esphome;
 
class KridaI2CDimOut : public Component, public FloatOutput {
 private:
  int out_register;
  
 public:
  KridaI2CDimOut(int output) {
    out_register = output;
  }
 
  void setup() override {
    Wire.begin();
  }
 
  void write_state(float state) override {
    // state is the amount this output should be on, from 0.0 to 1.0
    // we need to convert it to an integer first
    // KRIDA controller expects a value between 0 and 100
    // 0 = maximum brightness, 100 = off
	int value = 100 - (state * 100);
    // Sets the device address
    auto dev_address = 0x3f;
    // Write the value "value" to register "out_register" of device with address "dev_address"
    Wire.beginTransmission(dev_address);
    Wire.write(out_register);
    Wire.write(value);
    Wire.endTransmission();
    // Write the log
    ESP_LOGD("custom", "KRIDA brightness - device address: %u, register: %i -----------> value: %i", dev_address, out_register, value);
  }
};