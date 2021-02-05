#include <fstream>
#include <iostream>
#include <cstring>
#include "csv_printer.h"  // NOLINT

namespace csci3081 {

    CSVPrinter::CSVPrinter(std::string outputLocation) {
        outputLocation_ = outputLocation;
        data1Header_ = "";
        data2Header_ = "";
        data3Header_ = "";
    }
    void CSVPrinter::UpdateHeader(std::string data1Header,
        std::string data2Header, std::string data3Header) {
        data1Header_ = data1Header;
        data2Header_ = data2Header;
        data3Header_ = data3Header;
    }
    void CSVPrinter::AddData(float data1, float data2, float data3) {
        data1Vals_.push_back(data1);
        data2Vals_.push_back(data2);
        data3Vals_.push_back(data3);
    }
    void CSVPrinter::WriteToCSV() {
        std::ofstream file(outputLocation_,
        std::fstream::in | std::fstream::out | std::fstream::app);
        if (!file) {
            std::cerr << "Error opening Statistics.csv in delivery_scheduler"
            << strerror(errno) << std::endl;
            return;
        } else {
            std::cout << outputLocation_ << " successfully opened" << std::endl;
        }
        // file << data1Header_;
        // file << ",";
        // file << data2Header_;
        // file << ",";
        // file << data3Header_;
        // file << "\n";
        // Write in data
        for (int i = 0; i < data1Vals_.size(); i++) {
        // Write Column Data
            file << data1Vals_[i];
            file << ",";
            file << data2Vals_[i];
            file << ",";
            file << data3Vals_[i];
            file << "\n";
        }
        file.close();
    }
    }  // namespace csci3081
