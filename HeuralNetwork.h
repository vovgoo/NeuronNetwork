#pragma once
#ifndef _NEURALNETWORK_H_
#define _NEURALNETWORK_H_

#include "NumCpp.hpp"
#include <iostream>
#include <random>
#include <cmath>
#include <fstream>
#include <boost/any.hpp>

using namespace std;
using namespace nc;

class NeuralNetwork { // Создание класса Нейронной сети
	public:
		int inodes;
		int hnodes;
		int onodes;
		double lr;
		NdArray<double> whi;
		NdArray<double> who;

		NeuralNetwork(int input_neurones, int hidden_neurones, int output_neurones, double learning_rate, NdArray <double> whi_inputs, NdArray <double> who_inputs) { // Конструктор класса Нейронной сети
			inodes = input_neurones;
			hnodes = hidden_neurones;
			onodes = output_neurones;
			lr = learning_rate;
			whi = whi_inputs;
			who = who_inputs;
		}

		void training(NdArray<double> inputs_list, NdArray<double> targets_list) { // Процедура тренировки сети
			inputs_list = inputs_list.transpose();
			targets_list = targets_list.transpose();
			NdArray <double> hidden_inputs = dot<double>(whi, inputs_list);
			NdArray <double> hidden_outputs = all_activate(hidden_inputs);
			NdArray <double> final_inputs = dot<double>(who, hidden_outputs);
			NdArray <double> final_outputs = all_activate(final_inputs);
			NdArray <double> outputs_errors = targets_list - final_outputs;
			NdArray <double> hidden_errors = dot<double>(who.transpose(), outputs_errors);
			who += lr * dot<double>((outputs_errors * final_outputs * (1.0 - final_outputs)), hidden_outputs.transpose());
			whi += lr * dot<double>((hidden_errors * hidden_outputs * (1.0 - hidden_outputs)), inputs_list.transpose());
		}

		NdArray <double> query(NdArray<double> inputs) { // Процедура для получения ответа у сети
			inputs = inputs.transpose();
			NdArray <double> hidden_inputs = dot<double>(whi, inputs);
			NdArray <double> hidden_outputs = all_activate(hidden_inputs);
			NdArray <double> final_inputs = dot<double>(who, hidden_outputs);
			NdArray <double> final_outputs = all_activate(final_inputs);
			return final_outputs;

		}

	private:
		NdArray <double> all_activate(NdArray <double> inputs) { 
			NdArray<double>output = zeros<double>(inputs.size(), 1);
			for (int i = 0; i < inputs.size(); i++) {
				output[i] = activate_function(inputs[i]);
			}
			return output;

		}
		double activate_function(double input) { //Sigmoid functions
			double sigmoid = 1 / (1 + exp(-input));
			return sigmoid;
		}
};

#endif