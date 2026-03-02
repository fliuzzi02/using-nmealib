#include <iostream>
#include <nmealib/nmea0183/rmc.h>
#include <nmealib/nmea0183/gga.h>

int main() {
    try {
        nmealib::nmea0183::RMC rmc_msg(
            "GP", 
            123519, 
            'A', 
            4807.038, 
            'N', 
            1131.000, 
            'E', 
            22.4, 
            84.4, 
            230394, 
            3.1, 
            'W', 
            'A', 
            'V'
        );
        std::cout << "Packed RMC: " << rmc_msg.serialize() << "\n";

        nmealib::nmea0183::GGA gga_msg("GP", 123519, 4807.038, 'N', 1131.000, 'E', 1,8, 0.9, 200.0, 'M', 46.9, 'M', 0.0, "");
        std::cout << "Packed GGA: " << gga_msg.serialize() << "\n";
    } catch (const nmealib::NmeaException& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
