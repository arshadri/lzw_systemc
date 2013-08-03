#include "ram_dp_ar_aw.h"

void  ram_dp_ar_aw::READ_0 () {
  if (cs_0.read() && oe_0.read() && !we_0.read()) {
    data_0 = mem[address_0.read()];
  }
}

void  ram_dp_ar_aw::READ_1 () {
  if (cs_1.read() && oe_1.read() && !we_1.read()) {
    data_1 = mem[address_1.read()];
  }
}

void  ram_dp_ar_aw::WRITE_0 () {
  if (cs_0.read() && we_0.read()) {
    mem[address_0.read()] = data_0.read();
  } 
}

void  ram_dp_ar_aw::WRITE_1 () {
  if (cs_1.read() && we_1.read()) {
    mem[address_1.read()] = data_1.read();
  } 
}