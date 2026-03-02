#include <iostream>
#include <nmealib/nmealib.hpp>

int main() {
    // Example NMEA 0183 sentences to parse
    const std::string gga = "$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47";
    const std::string rmc = "$GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W,A,V*7D";

    try {
        auto gga_msg = nmealib::nmea0183::Nmea0183Factory::create(gga);
        std::cout << "GGA: " << gga_msg->getStringContent(false) << "\n";

        auto rmc_msg = nmealib::nmea0183::Nmea0183Factory::create(rmc);
        std::cout << "RMC: " << rmc_msg->getStringContent(false) << "\n";
    } catch (const nmealib::NmeaException& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
