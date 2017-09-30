#include <iostream>
#include <string>
#include <stdlib.h>
#include "csv.hh"

/////////////////////////////////////////////////////////////////////////////////////////////////////
//usage
/////////////////////////////////////////////////////////////////////////////////////////////////////

void usage()
{
  std::cout << "usage: ./rodents -f FILE" << std::endl;
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

  if (csv.read(file_name) < 0)
  {
  }
  return 0;
}

