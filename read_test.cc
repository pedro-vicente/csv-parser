#include <iostream>
#include <string>
#include <stdlib.h>
#include "csv.hh"

/////////////////////////////////////////////////////////////////////////////////////////////////////
//usage
/////////////////////////////////////////////////////////////////////////////////////////////////////

void usage()
{
  std::cout << "usage: ./read_test -f FILE" << std::endl;
  std::cout << "-f FILE: CSV file" << std::endl;
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

