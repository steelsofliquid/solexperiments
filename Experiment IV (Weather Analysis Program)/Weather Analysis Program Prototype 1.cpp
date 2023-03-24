#include <iostream>
#include <fstream>

using namespace std;

int main() {
    string filename;
    cout << "Enter the name of the weather data file: ";
    cin >> filename;

    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    double sum_temp = 0, sum_humid = 0;
    int count = 0;
    double temp, humid;
    while (file >> temp >> humid) {
        sum_temp += temp;
        sum_humid += humid;
        count++;
    }

    if (count == 0) {
        cerr << "No data found in file." << endl;
        return 1;
    }

    double avg_temp = sum_temp / count;
    double avg_humid = sum_humid / count;

    cout << "Average temperature: " << avg_temp << endl;
    cout << "Average humidity: " << avg_humid << endl;

    return 0;
}
