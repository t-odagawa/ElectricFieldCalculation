const double sigmax = 2.60; // mm
const double sigmay = 0.16; // mm
const double sigmaz = 20.0; // mm

const double kinetic_energy = 6.5e6; // keV
const double electron_mass = 511.; // keV
const double gamma_factor = kinetic_energy / electron_mass;
const double beta = sqrt(1. - 1. / gamma_factor / gamma_factor);

const double electron_charge = 1.602e-19; // Coulomb
const double current = 60.e-3; // A
const double perimeter = 377e3; // mm
const double speed_of_light = 2.998e11; // mm s-1
const double number_of_electron = current * perimeter / speed_of_light / electron_charge;

const double electric_constant = 8.854e-15; // Falad mm-1
