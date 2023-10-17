#include "NumCpp.hpp"
#include <cstdlib>
#include <iostream>
#include <random>
#include <boost/any.hpp>
#include "Neuron_Functions.h"
#include "HeuralNetwork.h"

using namespace std;
using namespace nc;


const int input_neurones = 2352; //Количество нейронов на первом слое
const int hidden_neurones = 300; //Количество нейронов на скрытом слое
const int output_neurones = 3; //Количество нейронов на последнем слое
const double learning_rate = 0.3; //Скорость обучения сети
const string training_file = "training_30k.csv"; //Название файла с тренировочными данными
const string testing_file = "testing_5k.csv"; //Название файла с файлами тестирования
const string neurons_weights = "neuron_weights.csv"; //Название файла с весами для нейронной сети после обучения
const string color_list = "color_list.csv"; //Список всех возможных цветов
const NdArray <double> who_inputs = random::randFloat<double>({ hidden_neurones, input_neurones }, -1, 1); // Начальные веса между первым и скрытым слоем
const NdArray <double> whi_inputs = random::randFloat<double>({ output_neurones, hidden_neurones }, -1, 1); // Начальные веса между скрытым и выходным слоем



int main() {
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	NeuralNetwork* neuronka = new NeuralNetwork(input_neurones, hidden_neurones, output_neurones, learning_rate, who_inputs, whi_inputs);
	bool key = 1;
	int value;
	color_green();
	cout << "Добро пожаловать в нейронную сеть по определению цветов." << endl;
	color_white();
	while (key) {
		color_green();
		cout << endl  << "Выберите пункт из списка ниже, что бы произвести определенное действие." << endl;
		color_white();
		cout << "1. Начать обучение сети с созданием файла с весами."
			<< endl << "2. Начать тестирование сети без отображения ответов ";
			color_red(); 
			cout << "(Необходим файл с весами)." << endl;
		color_white();
		cout << "3. Начать тестирование сети с отображением ответов ";
		color_red();
		cout << "(Необходим файл с весами).";
		color_white();
		cout << endl << "4. Произвести найстроку сети ";
		color_red();
		cout << "(Необходим файл с весами).";
		color_white();
		cout << endl << "5. Загадать сети свой цвет ";
		color_red();
		cout << "(Необходим файл с весами). ";
			color_white();
		cout << endl << "6. Выход из сети. " << endl << "Ваш ответ: ";
		color_white();
		cin >> value;
		switch (value) {
		case 1:
			neural_training(training_file, neurons_weights, *neuronka);
			break;
		case 2:
			if (neuron_open_weights(neurons_weights)) {
				neural_testing(testing_file, *neuronka, 0);
			}
			break;
		case 3:
			if (neuron_open_weights(neurons_weights)) {
				neural_testing(testing_file, *neuronka, 1);
			}
			break;
		case 4:
			neural_weights(neurons_weights, *neuronka);
			break;
		case 5:
			system("python user_test.py");
			user_test_from_python(*neuronka);
			break;
		case 6:
			key = 0;
			break;
		default:
			color_red();
			cout << "Вы выбрали не правильный пункт. Попробуйте еще раз." << endl;
			color_green();
			continue;
		}
	}
	system("pause");

}
