//#define DEBUG

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

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

/**
 * Get charge density at (xi, eta, zeta)
 * @param xi horizontal coordinate parpendicular to the beam direction [mm]
 * @param eta vertical coordinate [mm]
 * @param zeta horizontal coordinate along the beam direction [mm]
 * @return charge density at (xi, eta, zeta) [C/mm3]
 */
double ChargeDensityAt(double xi, double eta, double zeta) {
  return electron_charge * number_of_electron
    * exp(- (xi   * xi)   / (2 * sigmax * sigmax)
	  - (eta  * eta)  / (2 * sigmay * sigmay)
	  - (zeta * zeta) / (2 * sigmaz * sigmaz))
    / (2 * pow(M_PI, 1.5) * sigmax * sigmay * sigmaz);
}

/**
 * Get electric field element at (x, y, z) from (xi, eta, zeta)
 * @param x, y, z coordinate at which you want to calculate electric field [mm]
 * @param xi, eta, zeta coordinate from which you want to calculate electric field [mm]
 * @return electric field element at (x, y, z) from (xi, eta, zeta) [V/mm/mm3]
 */
double FieldContributionFrom(double x, double y, double z,
			     double xi, double eta, double zeta) {
  return gamma_factor / (4 * M_PI * electric_constant)
    * (x - xi) * ChargeDensityAt(xi, eta, zeta)
    / pow((gamma_factor*gamma_factor*(z-zeta)*(z-zeta) + (y-eta)*(y-eta) + (x-xi)*(x-xi)), 1.5);
}

/**
 * Get Electric field at (x, y, z)
 * @param x, y, z coordinate at which you want to calculate electric field
 * @param sigma_range maximum range of gaussian which you calculate [sigma]
 * @param number_of_cells number of cells you divide sigma_range * sigma into
 * @return electric field at (x, y, z) [V/mm]
 */
double ElectricFieldAt(double x, double y, double z,
		       double sigma_range, int number_of_cells) {

  double cellx = sigma_range * sigmax / (double) number_of_cells;
  double celly = sigma_range * sigmay / (double) number_of_cells;
  double cellz = sigma_range * sigmaz / (double) number_of_cells;
  
  double electric_field = 0;
  for(int ixi = -number_of_cells; ixi < number_of_cells; ixi++) {
    for(int ieta = -number_of_cells; ieta < number_of_cells; ieta++) {
      for(int izeta = -number_of_cells; izeta < number_of_cells; izeta++) {
	
	double xi   = cellx * ((double)ixi   + 0.);
	double eta  = celly * ((double)ieta  + 0.);
	double zeta = cellz * ((double)izeta + 0.);
	electric_field += FieldContributionFrom(x, y, z, xi, eta, zeta)
	  * (cellx * celly * cellz);
#ifdef DEBUG
	cout << "xi = " << xi
	     << ", eta = " << eta
	     << ", zeta = " << zeta << endl;
	cout << "add field value: " << FieldContributionFrom(x,y,z,xi,eta,zeta) * (cellx * celly * cellz) << endl;
	cout << "to electric field and the result : " << electric_field << endl;	
#endif
      }
    }
  }

  return electric_field;
}

// main function
int main(int argc, char** argv) {
  if (argc != 4) {
    cerr << "Usage : " << argv[0]
	 << " <sigma range> <number of cells in one dimension> <z position>" << endl;
    exit(1);
  }

  string common_file_name("data/electric_field_");
  string adder("_");
  string txt_extension(".txt");
  string output_file_name  = common_file_name + argv[1]
    + adder + argv[2] + adder + argv[3] + txt_extension;
#ifdef DEBUG
  cerr << output_file_name << endl;
#endif
  ofstream ofs(output_file_name);

  double sigma_range = atof(argv[1]);
  int number_of_cells = atoi(argv[2]);

  double x = 5. * sigmax;
  double y = 0.;
  double z = atof(argv[3]);

  cout << "Loop start!" << endl;
  ofs << z << "\t" << ElectricFieldAt(x, y, z, sigma_range, number_of_cells) << endl;

  cout << "Finish!!" << endl;
  exit(0);
}
