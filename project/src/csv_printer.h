#ifndef CSV_PRINTER_H
#define CSV_PRINTER_H

#include <string>
#include <vector>

namespace csci3081 {
/// The csv printer in the drone delivery subsystem
/**
 * The CSVPrinter class is responsible for formatting data.
 * We will be using this to output data such as the distance a drone has traveled,
 * the amount of packages a drone has delivered, and how long it took for a package
 * to be delivered.
*/
class CSVPrinter {
 public:
 	/** Constructs a CSVPrinter class.
     * @param outputLocation, a string representing where we want this data to go.
     */
    explicit CSVPrinter(std::string outputLocation);
	/** Updates the header of the file.
	* @param data1Header, the title of the first data column.
	* @param data2Header, the title of the second data column.
	* @param data3Header, the title of the third data column.
     */
    void UpdateHeader(std::string data1Header, std::string data2Header, std::string data3Header);
	/** Adds data to the file.
	* @param data1, adds data to the first column in the form of a float.
	* @param data2, adds data to the second column in the form of a float.
	* @param data3, adds data to the third column in the form of a float.
     */
    void AddData(float data1, float data2, float data3);
	/** Does the actual writing of the file.
     */
    void WriteToCSV();

 private:
    std::string outputLocation_;
    // Column Headers
    std::string data1Header_;
    std::string data2Header_;
    std::string data3Header_;
    // Column Data
    std::vector<float> data1Vals_;
    std::vector<float> data2Vals_;
    std::vector<float> data3Vals_;
};
}  // namespace csci3081
#endif
