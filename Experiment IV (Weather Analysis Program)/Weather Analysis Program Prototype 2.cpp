#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

// Define a struct to hold weather data
struct WeatherData {
    int hour;
    double temperature;
    double humidity;
};

// Function to parse a line of CSV data into a WeatherData struct
WeatherData parseData(string line) {
    WeatherData data;
    stringstream ss(line);
    string field;

    getline(ss, field, ',');
    data.hour = stoi(field);

    getline(ss, field, ',');
    data.temperature = stod(field);

    getline(ss, field, ',');
    data.humidity = stod(field);

    return data;
}

int main() {
    // Open the input file
    ifstream input("weather.csv");

    // Read in the data and store it in a vector
    vector<WeatherData> data;
    string line;
    while (getline(input, line)) {
        data.push_back(parseData(line));
    }

    // Calculate the mean temperature and humidity
    double tempSum = 0.0;
    double humidSum = 0.0;
    for (auto& datum : data) {
        tempSum += datum.temperature;
        humidSum += datum.humidity;
    }
    double meanTemp = tempSum / data.size();
    double meanHumid = humidSum / data.size();

    // Calculate the standard deviation of the temperature and humidity
    double tempVar = 0.0;
    double humidVar = 0.0;
    for (auto& datum : data) {
        tempVar += pow(datum.temperature - meanTemp, 2);
        humidVar += pow(datum.humidity - meanHumid, 2);
    }
    double tempSD = sqrt(tempVar / data.size());
    double humidSD = sqrt(humidVar / data.size());

    // Print out the results
    cout << "Mean temperature: " << meanTemp << endl;
    cout << "Mean humidity: " << meanHumid << endl;
    cout << "Temperature standard deviation: " << tempSD << endl;
    cout << "Humidity standard deviation: " << humidSD << endl;

    // Close the input file
    input.close();

    return 0;
}

