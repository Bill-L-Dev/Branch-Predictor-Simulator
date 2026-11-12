
/*	This is a C++ program to define the functions of a
	gshare branch predictor class

	The definition of the gshare function class is
	located within bp.h

	Author: William Layman

*/

//Header Files
#include "bp.h"
#include <cmath>
#include <iomanip>

//Namespaces
using namespace std;

//Definitions

//Globals

//Functions

/*	Branch Predictor Functions */

	// constructors and deconstructors
	BP::BP() {
		valid = false;

	}

	BP::BP(string type, int m, int n) {
		SetPredictionTable(m);
		gbhr.SetN(n);
		bp_type = type;
		this->m = m;
		this->n = n;	
		valid = true;

		
	}

	BP::BP(const BP& c) {};

	BP::~BP(){};

	// Setup Functions
	void BP::SetPredictionTable(int m) {
		prediction_table.clear();
		prediction_table.resize(pow(2, m));

	}

	// Simulation Functions
	void BP::SendCommand(uint32_t PC, char outcome) {
		if (valid) {


			if(bp_type == "gshare") {
			// gshare implementation //

				// determine the index of prediction table entry to update
				uint32_t mask = (1u << (m+2)) - 1;
				uint32_t index = ((PC & mask) >> 2) ^ ((gbhr.Get()) << (m-n));

				// update run metrics / make prediction
				run_metrics.UpdateMetrics((prediction_table[index].Get() >= 2 && outcome == 'n') || (prediction_table[index].Get() < 2 && outcome == 't'));

				// update prediction table entry
				if (outcome == 't') {
					prediction_table[index].Increment();
				}
				else if (outcome == 'n') {
					prediction_table[index].Decrement();
				}
				else {
					cout << "Error: Branch outcome not recognized." << endl;
				}

				// update global branch history register
				gbhr.Update(outcome);

				//
			}

			else if(bp_type == "bimodal") {
			// bimodal implementation //
				uint32_t mask = (1u << (m+2)) - 1;
				uint32_t index = (PC & mask) >> 2;


				// update run metrics
				run_metrics.UpdateMetrics((prediction_table[index].Get() >= 2 && outcome == 'n') || (prediction_table[index].Get() < 2 && outcome == 't'));

				if (outcome == 't') {
					prediction_table[index].Increment();
				}
				else if (outcome == 'n') {
					prediction_table[index].Decrement();
				}
				else {
					cout << "Error: Branch outcome not recognized." << endl;
				}

			}

			else {
				cout << "Error: Branch Predictor type not recognized." << endl;
			}
			

		}
		else {
			cout << "Error: Branch Predictor not initialized." << endl;
		}

		return;

	}

	// Data View Functions

	void BP::PrintMetrics() {
		run_metrics.PrintMetrics();
		PrintPredictionTable();
		return;
	}

	void BP::PrintPredictionTable() {
		cout << "FINAL " ;
			if (bp_type == "gshare") {
				cout << "GSHARE CONTENTS" << endl;
			}
			else if (bp_type == "bimodal") {
				cout << "BIMODAL CONTENTS" << endl;
			}
			else {
				cout << "BRANCH PREDICTOR CONTENTS" << endl;
			}

		for (long unsigned int i = 0; i < prediction_table.size(); i++) {
			cout << i << " " << prediction_table[i].Get() << endl;
		}
		return;
	}

/*	SaturatingTwoBitCounter Functions	*/

	// manipulation
	void SaturatingTwoBitCounter::Increment() {
		if (count < 3) count++;
		return;
	}

	void SaturatingTwoBitCounter::Decrement() {
		if (count > 0) count--;
		return;
	}

	unsigned int SaturatingTwoBitCounter::Get() {
		return count;
	}

/*	RunMetrics Functions	*/

	// manipulation
	void RunMetrics::UpdateMetrics(bool mispredicted) {
		num_predictions++;
		if (mispredicted) num_mispredictions++;
		misprediction_rate = (double)num_mispredictions / (double)num_predictions;
		return;
	}

	void RunMetrics::PrintMetrics() {
		cout << "OUTPUT" << endl;
		cout << "number of predictions: " << num_predictions << endl;
		cout << "number of mispredictions: " << num_mispredictions << endl;
		cout << "misprediction rate: " << fixed << setprecision(2) << misprediction_rate * 100 << "%" << endl;
		return;
	}

/*	GBHR Functions	*/

	// setup 
		void GBHR::SetN(unsigned int n) {
			this->n = n;
			gbhr = 0;
		}



	// manipulation

	void GBHR::Update(char outcome) {
		gbhr = gbhr >> 1;

		if (outcome == 't'){
			gbhr = gbhr | (1u << (n-1));
		}
		else if (outcome == 'n') {
			gbhr = gbhr & ~(1u << (n-1));
		}
		else {
			cout << "Error: Branch outcome not recognized." << endl;
		}

		return;
	}

	// accessors

	uint32_t GBHR::Get() {
		return gbhr;
	}