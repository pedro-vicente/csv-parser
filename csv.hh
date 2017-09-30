#ifndef READ_CSV_HH
#define READ_CSV_HH 1

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/////////////////////////////////////////////////////////////////////////////////////////////////////
//read_csv_t
/////////////////////////////////////////////////////////////////////////////////////////////////////

class read_csv_t
{
public:
  read_csv_t();
  int read(const std::string &file_name);
  int open(const std::string &file_name);
  std::vector<std::string> read_row();
private:
  std::string get_field(const std::string &rec, const size_t idx);
  std::vector<size_t> pos_cma;
  std::ifstream m_ifs;
};

#endif
