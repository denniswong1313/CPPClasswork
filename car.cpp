#include <iostream>
#include <string>
#include <vector>
using namespace std;

/**
 * CarSpec: Manufacturer-specified information about the car.
 *
 */
struct CarSpec {
  // Minimal pressure for a tyre, below which the tyre is
  // considered punctured.
  double minTyrePressure;
  // Maximal pressure for a tyre.
  double maxTyrePressure;
  // Diameter, in inches, of a wheel.
  unsigned int wheelDiameter;
  // Maximal acceptable engine temperature.
  unsigned int maxEngineTemperature;
};

/**
 * Messages: Programmer-defined constants for the messages printed on
 * the on-board computer display.
 *
 */
class Messages {
public:
  static const std::string OK;// set to "OK";
  static const std::string TEMP_HOT; // set to "TOO HOT";
  static const std::string TANK_RESERVE; // set to "RESERVE";
  static const std::string TANK_EMPTY; // set to "EMPTY";
  static const std::string TYRE_PUNCTURE; // set to "PUNCTURE";
  static const std::string SENSOR_ERROR; // set to "SENSOR ERROR";
};
const std::string Messages::OK = "OK";
const std::string Messages::TEMP_HOT = "TOO HOT";
const std::string Messages::TANK_RESERVE = "RESERVE";
const std::string Messages::TANK_EMPTY = "EMPTY";
const std::string Messages::TYRE_PUNCTURE = "PUNCTURE";
const std::string Messages::SENSOR_ERROR = "SENSOR ERROR";

/**
 * WarningCodes: Programmer-defined constants for the alert management system
 * of the car. Each possible warning has its own code, NO_WARNING is
 * the system code when the car is functionning normally.
 *
 */
class WarningCodes {
public:
  static const unsigned int NO_WARNING = 0;
  static const unsigned int TYRE_WARNING = 1;
  static const unsigned int ENGINE_WARNING = 2;
  static const unsigned int GAS_WARNING = 3;
  static const unsigned int CAR_WARNING = 4;
};

class carEngine {
	public:
		int engineRev;
		int engineTemp;
		CarSpec spec;
		Messages message;
		WarningCodes warning;
		int maxEngineTemp;
		string output;

		string printRev() {
			if (engineRev < 0) {
				return message.SENSOR_ERROR;
			}

			if (engineRev >= 0) {
				int ival = engineRev;
				char buffer[512];
				sprintf (buffer, "%d", ival);
				std::string ret(buffer);
				output = ret;
				return output;
			}
			return output;
		}

		string printStatus() {
			maxEngineTemp = spec.maxEngineTemperature;
			if (engineTemp < 0) {
				return message.SENSOR_ERROR;
			}

			if (engineTemp > maxEngineTemp) {
				return message.TEMP_HOT;
			}

			if ((engineTemp >= 0) && (engineTemp <= maxEngineTemp)) {
				return message.OK;
			}

			return message.OK;
		}

		int engineWarningStatus() {

			if (printStatus() != message.OK) {
				return warning.ENGINE_WARNING;
			}

			if (printRev() == message.SENSOR_ERROR) {
				return warning.ENGINE_WARNING;
			}

			if (engineRev < 0) {
				return warning.ENGINE_WARNING;
			}

			if (engineTemp < 0) {
				return warning.ENGINE_WARNING;
			}

			return warning.NO_WARNING;
		}
};

class carTyres {
	public:
		double pressure[4];
		double speedWheel[4];
		CarSpec spec;
		Messages message;
		WarningCodes warning;

		string printStatus(){
			for (int i = 0; i < 4; i++) {
				if (pressure[i] < 0) {
					return message.SENSOR_ERROR;
				}

				if ((pressure[i] < spec.minTyrePressure) || (pressure[i] > spec.maxTyrePressure)) {
					return message.TYRE_PUNCTURE;
				}

				if ((pressure[i] >= spec.minTyrePressure) && (pressure[i] <= spec.maxTyrePressure)) {
					return message.OK;
				}
			}
			return message.OK;
		}

		int tyreWarningStatus() {
			if (printStatus() != message.OK) {
				return warning.TYRE_WARNING;
			}

			if ((pressure[0] < 0) || (pressure[1] < 0) || (pressure[2] < 0) || (pressure[3] < 0)) {
				return warning.TYRE_WARNING;
			}

			if ((speedWheel[0] < 0) || (speedWheel[1] < 0) || (speedWheel[2] < 0) || (speedWheel[3] < 0)) {
				return warning.TYRE_WARNING;
			}

			return warning.NO_WARNING;
		}
};

class carTank {
	public:
		double gasInTank;
		CarSpec spec;
		Messages message;
		WarningCodes warning;

		string printStatus() {
			if (gasInTank < 0) {
				return message.SENSOR_ERROR;
			}

			if (gasInTank >= 1) {
				return message.OK;
			}

			if ((gasInTank < 1) && (gasInTank > 0)) {
				return message.TANK_RESERVE;
			}

			if (gasInTank == 0) {
				return message.TANK_EMPTY;
			}

			return message.OK;
		}

		int tankWarningStatus() {
			if (gasInTank <= 0) {
				return warning.GAS_WARNING;
			}

			return warning.NO_WARNING;
		}
};

class Car {
	public:
		carEngine engine;
		carTyres tyres;
		carTank tank;
		CarSpec spec;
		Messages message;
		WarningCodes warning;

	public:
		int computeSpeed() {
			double speed[4];
				speed[0] = tyres.speedWheel[0] * 3.1415927 * ((double)(spec.wheelDiameter));
				speed[1] = tyres.speedWheel[1] * 3.1415927 * ((double)(spec.wheelDiameter));
				speed[2] = tyres.speedWheel[2] * 3.1415927 * ((double)(spec.wheelDiameter));
				speed[3] = tyres.speedWheel[3] * 3.1415927 * ((double)(spec.wheelDiameter));

			double min = speed[0];
			double max = speed[0];

			for (unsigned int i = 1; i < 4; ++i) {
				if (speed[i] < min) {
					min = speed[i];
				}

				if (speed[i] > max) {
					max = speed[i];
				}
			}

			double v[2];

			// Remove one min and one max.
			bool min_removed = false;
			bool max_removed = false;
			int count = 0;

			for (unsigned int i = 0; i < 4; ++i) {
				if (! min_removed && speed[i] == min) {
					min_removed = true;
					continue;
				}
	
				if (! max_removed && speed[i] == max) {
					max_removed = true;
					continue;
				}
			v[count++] = speed[i];
			}
			
			double carSpeed = (((v[0] + v[1]) / 2) / 63360) * 3600;
			return carSpeed;
		}
		

		string printSpeed() {

			if (computeSpeed() < 0) {
				return message.SENSOR_ERROR;
			}

			if ((tyres.speedWheel[0] < 0) || (tyres.speedWheel[1] < 0) || (tyres.speedWheel[2] < 0) || (tyres.speedWheel[3] < 0)) {
				return message.SENSOR_ERROR;
			}

			int toPrint = computeSpeed();
			char buffer[512];
			sprintf (buffer, "%d", toPrint);
			std::string ret(buffer);
			return ret;
		}

		int getWarningStatus() {
			if ((engine.engineWarningStatus() != 0) || (tyres.tyreWarningStatus() != 0) || (tank.tankWarningStatus() != 0)) {
				return warning.CAR_WARNING;
			}

			if ((engine.engineWarningStatus() == 0) && (tyres.tyreWarningStatus() == 0) || (tank.tankWarningStatus() == 0)) {
				return warning.NO_WARNING;
			}
		}

		string displayComputer() {
			string status;
			status = "Speed: " + printSpeed() + "\n" + "Engine rev: " + engine.printRev() + "\n" + "Engine status: " + engine.printStatus() + "\n" + "Tyres: " + tyres.printStatus() + "\n" + "Gas: " + tank.printStatus() + "\n";
			return status;
		}

		void setSpec(CarSpec& s) {
			engine.spec = s;
			tyres.spec = s;
			tank.spec = s;
			spec = s;
		}

		void setSensors(double pressure[4], double speed[4], int engineRev, int engineTemp, double gasInTank) {
			for (int i = 0; i < 4; i++) {
				tyres.pressure[i] = pressure [i];
				tyres.speedWheel[i] = speed[i];
			}

			engine.engineRev = engineRev;
			engine.engineTemp = engineTemp;
			tank.gasInTank = gasInTank;
		}
};

/**
 * Car tester class.
 *
 * Functionality: sets all sensor values to testing cases, and check
 * if the car status (onboard computer and car error system) is
 * conform with the expected result for those sensor values.
 *
 * Note: only a subclass of Car can access the method 'setSensors' of
 * Car.
 *
 */
struct CarTester : Car {
  // Initialize the car with a manufacturer specification (tyre
  // pressure range, wheel diameter, max. engine temperature.
  CarTester(CarSpec& s) {
    setSpec(s);
  }
  // Set the values of all the car sensors to user-defined values.
  void setAllSensors(double pressure[4], double speed[4], int engineRev,
		     int engineTemp, double gasInTank)
  {
    setSensors(pressure, speed, engineRev, engineTemp, gasInTank);
  }
  // Check if the error system of the car has the expected status.
  bool testWarning(int expected) {
    if (getWarningStatus() != expected)
      return false;
    return true;
  }
  // Check if the speedometer has the expected value.
  bool testSpeed(int expected) {
    if (computeSpeed() != expected)
      return false;
    return true;
  }
  // Check if the on-board computer prints what is expected.
  bool testComputer(std::string speedS, std::string revS,
		    std::string tempS, std::string tyresS, std::string gasS) {
    if (speedS != printSpeed() ||
	revS != engine.printRev() ||
	tempS != engine.printStatus() ||
	tyresS != tyres.printStatus() ||
	gasS != tank.printStatus())
      return false;
    return true;
  }
  // Test a full car.
  bool testCar(int exp_warning, int exp_speed,
	       std::string exp_speed_str,
	       std::string exp_rev,
	       std::string exp_temp_status,
	       std::string exp_tyres_status,
	       std::string exp_gas_status)
  {
    if (testWarning(exp_warning) &&
	testSpeed(exp_speed) &&
	testComputer(exp_speed_str, exp_rev, exp_temp_status, exp_tyres_status,
		     exp_gas_status))
      return true;
    return false;
  }
};

int main()
{
  // Set the spec for the car.
  CarSpec carspec;
  carspec.minTyrePressure = 2.0;
  carspec.maxTyrePressure = 35.0;
  carspec.wheelDiameter = 19;
  carspec.maxEngineTemperature = 100;
  // Instantiate a tester.
  CarTester t(carspec);

  // Testing.

  // Test 1:
  std::cout << "[TEST] Testing spec 1" << std::endl;
  double pressureTest[] = { 32, 32, 32, 32 };
  double speedWheel[] = { 20, 20, 20, 20 };
  WarningCodes w;
  t.setAllSensors(pressureTest, speedWheel, 3500, 70, 15);
  if (t.testCar(w.NO_WARNING, 67, "67", "3500", "OK", "OK", "OK"))
    std::cout << "[PASS] Car conforms spec" << std::endl;
  else {
    std::cout << "[FAIL] Car does not conform spec" << std::endl;
  }
  std::cout << "[INFO] Showing computer output:" << std::endl;
  std::cout << t.displayComputer();

  // Test 2:
  std::cout << "[TEST] Testing spec 2" << std::endl;
  t.setAllSensors(pressureTest, speedWheel, 3500, 700, 15);
  if (t.testCar(w.CAR_WARNING, 67, "67", "3500", "TOO HOT", "OK", "OK"))
    std::cout << "[PASS] Car conforms spec" << std::endl;
  else {
    std::cout << "[FAIL] Car does not conform spec" << std::endl;
  }
  std::cout << "[INFO] Showing computer output:" << std::endl;
  std::cout << t.displayComputer();

  // Test 3:
  std::cout << "[TEST] Testing spec 3" << std::endl;
  pressureTest[0] = 1.5;
  t.setAllSensors(pressureTest, speedWheel, 3500, 700, 15);
  if (t.testCar(w.CAR_WARNING, 67, "67", "3500", "TOO HOT", "PUNCTURE", "OK"))
    std::cout << "[PASS] Car conforms spec" << std::endl;
  else {
    std::cout << "[FAIL] Car does not conform spec" << std::endl;
  }
  std::cout << "[INFO] Showing computer output:" << std::endl;
  std::cout << t.displayComputer();


  return 0;
}