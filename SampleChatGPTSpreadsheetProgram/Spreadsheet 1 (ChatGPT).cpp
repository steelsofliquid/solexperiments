#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Spreadsheet {
private:
    int rows, cols;
    vector<vector<string> > data;
public:
    Spreadsheet(int r, int c) : rows(r), cols(c) {
        data.resize(rows);
        for (int i = 0; i < rows; ++i) {
            data[i].resize(cols);
        }
    }

    void setCell(int r, int c, string value) {
        data[r][c] = value;
    }

    string getCell(int r, int c) const {
        return data[r][c];
    }

    void print() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << data[i][j] << "\t";
            }
            cout << endl;
        }
    }
};

int main() {
    Spreadsheet s(5, 3);

    s.setCell(0, 0, "Name");
    s.setCell(0, 1, "Age");
    s.setCell(0, 2, "Country");

    s.setCell(1, 0, "John");
    s.setCell(1, 1, "25");
    s.setCell(1, 2, "USA");

    s.setCell(2, 0, "Maria");
    s.setCell(2, 1, "30");
    s.setCell(2, 2, "Brazil");

    s.print();

    return 0;
}

