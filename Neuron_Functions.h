#pragma once
#include "NumCpp.hpp"
#include <iostream>
#include <windows.h>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <boost/any.hpp>
#include "HeuralNetwork.h"
using namespace std;
using namespace nc;

void color_green();
void color_red();
void color_white();
bool neuron_open_weights(string neurons_weights);
bool neoron_test(NdArray <double> neuron_answer, NdArray <double> target_list);
void neural_training(string training_file, string neurons_weights, NeuralNetwork& nueronka);
void neural_testing(string testing_file, NeuralNetwork& neuronka, bool key);
void neural_weights(string neurons_weights, NeuralNetwork& neuronka);
void user_test_from_python(NeuralNetwork& neuronka);
