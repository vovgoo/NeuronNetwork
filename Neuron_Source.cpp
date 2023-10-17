#include "Neuron_Functions.h"

void color_red() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, FOREGROUND_RED);
}
void color_green() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
}
void color_white() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

bool neoron_test(NdArray <double> neuron_answer, NdArray <double> target_list) {
	NdArray <double> neuron_ans = { neuron_answer[0],neuron_answer[1],neuron_answer[2] };
	NdArray <double> res = (neuron_ans - target_list);
	if (abs(res[0]*100) < 10 && abs(res[1] * 100) < 10 && abs(res[2] * 100) < 10)
		return 1;
	return 0;
}

bool neuron_open_weights(string neurons_weights) {
	fstream file;
	file.open(neurons_weights);
	if (file.is_open()) {
		return 1;
	}
	color_red();
	cout << "Не удалось создать или открыть файл, для записи весов нейронной сети." << endl;
	color_white();
	return 0;
}

void neural_training(string training_file, string neurons_weights, NeuralNetwork &neuronka) {
	fstream training;
	training.open(training_file, ios::in);
	if (training.is_open() == 0) {
		color_red();
		cout << "Не удалось открыть файл с тренировочными данными. Возможно файл отсутствует или поврежден." << endl;
		color_white();
	}
	else {
		color_green();
		cout << "Файл с тренировочными данными был успешно открыт. Приступаем к обучению сети." << endl;
		color_white();
		NdArray <double> inputs_list(1, 2352);
		NdArray <double> target_list(1, 3);
		int count = 0; int count_training = 0;
		for (int j = 0; j < 30000; j++) {
			count = 0;
			unsigned int start_time = clock();
			for (int i = 0; i < 2355; i++) {
				if (count == 0 || count == 1 || count == 2) {
					training >> target_list[count];
					target_list[count] /= 100;
					count++;
				}
				else {
					training >> inputs_list[i - 3];
					inputs_list[i - 3] = (inputs_list[i - 3] / 255.0 * 0.99) + 0.01;
				}
			}
			unsigned int end_time = clock();
			neuronka.training(inputs_list, target_list);
			count_training++;
			cout << "Тренировочные данные под номером " << count_training << " успешно прошли тестирование. Время совершения теста: " << end_time - start_time << " мс." << endl;
		}
		training.close();
		color_green();
		cout << "Записываем веса обученной нейронной сети в файл." << endl;
		fstream file;
		file.open(neurons_weights);
		if (neuron_open_weights(neurons_weights)) {
			int count = 0;
			for (int i = 0; i < 706500; i++) {
				if (i < 705600) {
					file << neuronka.whi[i];
				}
				else {
					file << neuronka.who[count];
					count++;
				}
			}
			file.close();
			cout << "Файл с весами успешно был создан и записан. Дальше загружать нейронную сеть можете из него." << endl;
		}

		cout << "Обучение сети успешно завершено. Приятного пользования." << endl;
		color_white();
	}
}

void neural_testing(string testing_file, NeuralNetwork& neuronka, bool key) {
	fstream testing;
	testing.open(testing_file, ios::in);
	if (testing.is_open() == 0) {
		color_red();
		cout << "Не удалось открыть файл с тестовыми данными. Возможно файл отсутствует или поврежден." << endl;
		color_white();
	}
	else {
		color_green();
		cout << "Файл с тестировочными файлами был успешно открыт. Приступаем к тестированию сети." << endl;
		color_white();
		NdArray <double> inputs_list(1, 2352);
		NdArray <double> target_list(1, 3);
		int count = 0, count_testing = 0, test_count = 0;
		for (int j = 0; j < 5000; j++) {
			count = 0;
			unsigned int start_time = clock();
			for (int i = 0; i < 2355; i++) {
				if (count == 0 || count == 1 || count == 2) {
					testing >> target_list[count];
					target_list[count] /= 100;
					count++;
				}
				else {
					testing >> inputs_list[i - 3];
					inputs_list[i - 3] = (inputs_list[i - 3] / 255.0 * 0.99) + 0.01;
				}
			}
			unsigned int end_time = clock();
			NdArray <double> Neuron_Answer = neuronka.query(inputs_list);
			if (key != 0) {
				cout << endl << "Ответ нейронной сети: " << endl << "RED: " << (int)(Neuron_Answer[0] * 100) << "%" << endl << "GREEN:" << (int)(Neuron_Answer[1] * 100) << "%" << endl << "BLUE: " << (int)(Neuron_Answer[2] * 100) << "%" << endl;
				cout << endl << "Ожидаемый ответ: " << endl << "RED: " << target_list[0] * 100 << "%" << endl << "GREEN: " << target_list[1] * 100 << "%" << endl << "BLUE: " << target_list[2] * 100 << "%" << endl << endl;
			}
			if (neoron_test(Neuron_Answer, target_list)) {
				test_count++;
			}

			count_testing++;
			cout << "Тестовые данные под номером " << count_testing << " успешно прошли тестирование. Время совершения теста: " << end_time - start_time << " мс." << endl;
		}
		testing.close();
		color_green();
		cout << "Тестирование сети успешно завершено. Сеть успешно угадала " << test_count << "/5000. Процент успешно угаданных ответов сетью: " << (double)test_count / 5000 * 100  << "%."  << endl;
		color_white();
	}
}

void neural_weights(string neurons_weights, NeuralNetwork& neuronka) {
	fstream weights;
	weights.open(neurons_weights, ios::in);
	if (weights.is_open() == 0) {
		color_red();
		cout << "Не удалось открыть файл с весами нейронной сети. Возможно файл отсутствует или поврежден." << endl;
		color_white();
	}
	else {
		color_green();
		cout << "Файл с весами нейронной сети был успешно открыт. Приступаем к настройки сети." << endl;
		color_white();
		NdArray <double> whi_output(300, 2352);
		NdArray <double> who_output(3, 300);
		int count = 0;
		unsigned int start_time = clock();
		for (int i = 0; i < 706500; i++) {
			if (i < 705600) {
				weights >> whi_output[i];
			}
			else {
				weights >> who_output[count];
				count++;
			}
		}
		unsigned int end_time = clock();
		weights.close();
		neuronka.whi = whi_output;
		neuronka.who = who_output;
		color_green();
		cout << "Настройка сети была произведена успешно. Время настройки сети: " << start_time - end_time << " мс. Приятного пользования." << endl;
		color_white();
	}
}

void user_test_from_python(NeuralNetwork& neuronka) {
	fstream testing;
	testing.open("user_primers.csv", ios::in);
	if (testing.is_open() == 0) {
		color_red();
		cout << "Не удалось открыть файл с пользовательскими данными для теста. Возможно файл отсутствует или поврежден." << endl;
		color_white();
	}
	else {
		color_green();
		cout << "Файл с данными для пользовательского теста успешно открыт. Приступаем к тестированию сети." << endl;
		color_white();
		NdArray <double> inputs_list(1, 2352);
		NdArray <double> target_list(1, 3);
		int count = 0;
		unsigned int start_time = clock();
		for (int i = 0; i < 2355; i++) {
			if (count == 0 || count == 1 || count == 2) {
				testing >> target_list[count];
				target_list[count] /= 100;
				count++;
			}
			else {
				testing >> inputs_list[i - 3];
				inputs_list[i - 3] = (inputs_list[i - 3] / 255.0 * 0.99) + 0.01;
			}
		}
		unsigned int end_time = clock();
		NdArray <double> Neuron_Answer = neuronka.query(inputs_list);
		cout << "Результаты тестирования: " << endl;
		cout << endl << "Ответ нейронной сети: " << endl << "RED: " << (int)(Neuron_Answer[0] * 100) << "%" << endl << "GREEN:" << (int)(Neuron_Answer[1] * 100) << "%" << endl << "BLUE: " << (int)(Neuron_Answer[2] * 100) << "%" << endl;
		cout << endl << "Ожидаемый ответ: " << endl << "RED: " << target_list[0] * 100 << "%" << endl << "GREEN: " << target_list[1] * 100 << "%" << endl << "BLUE: " << target_list[2] * 100 << "%" << endl << endl;
		testing.close();
		color_green();
		cout << "Тестирование сети успешно завершено. " << endl;
		color_white();
	}
}