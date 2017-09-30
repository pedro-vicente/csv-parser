#include <iostream>
#include <string>
#include <stdlib.h>
#include "csv.hh"

/////////////////////////////////////////////////////////////////////////////////////////////////////
//usage
/////////////////////////////////////////////////////////////////////////////////////////////////////

void usage()
{
  std::cout << "usage: ./read_dc311 -f FILE" << std::endl;
  std::cout << "-f FILE: CSV DC311 file" << std::endl;
  exit(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//main
/////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
  read_csv_t csv;
  std::string file_name;

  if (argc == 1)
  {
    usage();
  }

  for (int i = 1; i < argc; i++)
  {
    if (argv[i][0] == '-')
    {
      switch (argv[i][1])
      {
      case 'f':
        file_name = argv[i + 1];
        i++;
        break;
      default:
        usage();
      }
    }
    else
    {
      usage();
    }
  }

  if (csv.open(file_name) < 0)
  {
    std::cout << "Cannot open file " << file_name.c_str() << std::endl;
    return 1;
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  //iterate until an empty row is returned (end of file)
  /////////////////////////////////////////////////////////////////////////////////////////////////////

  size_t found = 0;
  size_t rows = 0;
  std::vector<std::string> row;
  while (true)
  {
    row = csv.read_row();
    rows++;
    if (row.size() == 0)
    {
      break;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //detect field 2 (code),
    //extract fiels 6 (date), 20 (lat), 21 (lon), 22 (zip)
    /////////////////////////////////////////////////////////////////////////////////////////////////////

    if (row.at(2).compare("S0311") == 0)
    {
      found++;
      std::cout << row.at(6).c_str() << " ";
      std::cout << row.at(20).c_str() << " ";;
      std::cout << row.at(21).c_str() << " ";;
      std::cout << row.at(22).c_str() << std::endl;
    }
  }

  std::cout << "Processed " << rows << " rows" << std::endl;
  std::cout << "S0311 codes: " << found << std::endl;
  return 0;
}

