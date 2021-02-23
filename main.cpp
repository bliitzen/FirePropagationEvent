/*
  Christian France - Homework 1 - Fire Propogation Event - 2/19/21

  This program simulates a VERY simple fire spreading. If an element is burning, it's
  neighbor elements will be burning in the next iteration to simulate fire spread.

  This program generates data files for each element on the grid. The grid is a 7x7 matrix
  simulating the fire. "+" meaning there fire is burning at that element and "-" meaning the
  fire is not burning at that element!
*/

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <time.h>

using namespace std;
const int SIZE = 7; // Array size / loop amount

struct Firelet { // INIT Struct
  double fuel_content = 0.0; // Fire ingredients
  double terrain_slope = 0.0;
  int wind_direction = 0;
  string fireStatus = "Okay";

  // Converts the data to string to print to a txt file
  string _to_string() const {
        ostringstream stream_out;
        stream_out << "Fuel Content: " << fuel_content 
        << " \nTerrain Slope: " << terrain_slope 
        << " \nWind Direction: " << wind_direction
        << " \nFire Status: " << fireStatus;
        return stream_out.str();
    }

};

// Overload << operator to output the structure data to a file
ostream& operator<<(ostream& stream_out, const Firelet& map) {
    stream_out << map.fuel_content << " " << map.terrain_slope << " " << map.wind_direction << " " << map.fireStatus;
    return stream_out;
}

// Print function to display the fire status grid.
void printGrid(Firelet map[SIZE][SIZE]) {
  for(int i = 0; i < SIZE; i++) {
    for(int k = 0; k < SIZE; k++) {
      if(map[i][k].fireStatus == "Okay") {
        cout << "- ";
      }
      else {
        cout << "+ ";
      }
    }
    cout << endl;
  }
}

/*
  checkGrid function determines where the fire will spread. I used a very basic
  algo that spreads the fire if the neighbor element is not burning.
*/
void checkGrid(Firelet map[SIZE][SIZE]) {
  string temp[SIZE][SIZE];

  for(int i = 0; i < SIZE - 1; i++) {
    for(int k = 0; k < SIZE - 1; k++) {
      if(map[i][k].fireStatus == "Burning" && map[i][k+1].fireStatus == "Okay"){
        temp[i][k+1] = "Burning";
      }
      if(map[i][k].fireStatus == "Burning" && map[i+1][k].fireStatus == "Okay"){
        temp[i+1][k] = "Burning";
      }
      if(map[i][k].fireStatus == "Burning" && map[i+1][k+1].fireStatus == "Okay"){
        temp[i+1][k+1] = "Burning";
      }
    }
  }

  // seperate temp array, so the fire won't spread every loop.
  // this nested loop reassigns values after determing which elements will burn next
  for(int i = 0; i < SIZE; i++) {
    for(int k = 0; k < SIZE; k++) {
      if(temp[i][k] == "Burning"){
        map[i][k].fireStatus = "Burning";
      }
    }
  }
}

// Generates the file for the current data
void generateFile(Firelet map[SIZE][SIZE], int iter1, int iter2) {
  ofstream dataFile;
  string fileName = "FPEData_" + to_string(iter1) + "_" + to_string(iter2) +".txt"; // File name based on element location
  dataFile.open(fileName, ios_base::out); // rewrite every time simulation is run
  if(!dataFile) {
    cout << "Error opening file..." << endl;
  } else {
    dataFile << map[iter1][iter2]._to_string();
  }
}

int main() {
  Firelet map[SIZE][SIZE];
  srand(time(NULL));
  bool loop = true;
  int time = 1;

  for(int i = 0; i < SIZE; i++) { // Fill struct array with random weights
    for(int k = 0; k < SIZE; k++){
      map[i][k].fuel_content = rand() % 10; // Fuel content range: 0-10
      map[i][k].terrain_slope = rand() % 10; // Terrain slope range: 0-10
      map[i][k].wind_direction = rand() % 7; // Wind direction range: 0-7 (Octal)

      generateFile(map, i, k); // generateFile for every struct iteration
    }
  }

  map[0][0].fireStatus = "Burning"; // Initialize the fire at [0][0] for ease of simulation

  for(int i = 0; i < 60; i++){
    cout << "-";
  }

  cout << "\nFIRE PROPOGATION EVENT:" << endl;
  cout << "Each '+' means the fire is burning." << endl;
  cout << "Each '-' means the fire is not burning"  << endl;

  for(int i = 0; i < 60; i++){
    cout << "-";
  }

  cout << "\nFire at time: 0 hrs" << endl;
  
  printGrid(map); // Prints initial grid with fire at [0][0]

  while(loop) { // Simulation Loop
    if(time == 8){ // Runs for "8 hours"
      loop = false;
    }

    checkGrid(map); // Check grid each loop to determine fire spread

    // Prints the fire at given loop iteration
    cout << "\nFire at time: " << time << " hrs" << endl;
    printGrid(map);
    time += 1; // iter time each loop
  }    
}
