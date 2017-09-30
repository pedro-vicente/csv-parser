#include <iostream>
#include <string>
#include <stdlib.h>
#include "csv.hh"

/////////////////////////////////////////////////////////////////////////////////////////////////////
//main
/////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
  read_csv_t csv;
  std::string file_name;

  if (csv.open("../test.csv") < 0)
  {
    std::cout << "Cannot open file ../test.csv" << std::endl;
    return 1;
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  //iterate until an empty row is returned (end of file)
  /////////////////////////////////////////////////////////////////////////////////////////////////////

  std::vector<std::string> row;
  while (true)
  {
    row = csv.read_row();
    if (row.size() == 0)
    {
      break;
    }
    for (size_t idx = 0; idx < row.size(); idx++)
    {
      std::cout << idx << "\t" << row.at(idx).c_str() << std::endl;
    }
    std::cout << std::endl;
  }

  return 0;
}

