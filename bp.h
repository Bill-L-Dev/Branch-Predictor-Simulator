#ifndef BP_H
#define BP_H

/*	This is a C++ header file to define the available functions 
	of a branch predictor class

	Branch Predictor Variants:
	- bimodal
	- gshare

	Author: William Layman

*/

//Includes
#include <string>
#include <stdint.h>
#include <vector>
#include <iostream>

//Namespaces
using namespace std;

// Structs / Helper Classes
class GBHR {

private:
	unsigned int n;
	uint32_t gbhr = 0;

public:
	void SetN(unsigned int n);
	void Update(char outcome);
	uint32_t Get();
};

class SaturatingTwoBitCounter {

private:
	unsigned int count = 2;

public:
	void Increment();
	void Decrement();
	unsigned int Get();



};

class RunMetrics {
private:

	uint64_t num_predictions = 0;
	uint64_t num_mispredictions = 0;
	double misprediction_rate = 0.0;

public:
	void UpdateMetrics(bool mispredicted);
	void PrintMetrics();

};

//Class Definition
class BP {

private:
/*	Parameters	*/

	//BP parameters
	string bp_type;
	int m;
	int n;
	vector<SaturatingTwoBitCounter> prediction_table;
	RunMetrics run_metrics;
	GBHR gbhr;

	//Validation Parameters
	bool valid;

/*	Private Functions	*/

	// Setup Functions
	void SetPredictionTable(int m);


public:
	// constructors and deconstructors
	BP();
	BP(string type, int m, int n = 0);
	BP(const BP& c);
	~BP();

	// Class Control
	

	// Simulation Functions
	void SendCommand(uint32_t PC, char outcome);

	//Output Functions
	void PrintMetrics();	// specific formatting tailored to class output requirements

	void PrintPredictionTable();





};
#endif
