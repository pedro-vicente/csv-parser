#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include <stdlib.h>
#include "csv.hh"

/////////////////////////////////////////////////////////////////////////////////////////////////////
//read_csv_t::read_csv_t
/////////////////////////////////////////////////////////////////////////////////////////////////////

read_csv_t::read_csv_t()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//read_csv_t::open
/////////////////////////////////////////////////////////////////////////////////////////////////////

int read_csv_t::open(const std::string &file_name)
{
  m_ifs.open(file_name.c_str());
  if (!m_ifs)
  {
    return -1;
  }
  return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//read_csv_t::read_row
/////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<std::string> read_csv_t::read_row()
{
  bool quote_mode = false;
  std::vector<std::string> row;
  std::string column;
  char c;
  while (m_ifs.get(c))
  {
    switch (c)
    {
      /////////////////////////////////////////////////////////////////////////////////////////////////////
      //separator ',' detected. 
      //in quote mode add character to column
      //push column if not in quote mode
      /////////////////////////////////////////////////////////////////////////////////////////////////////

    case ',':
      if (quote_mode == true)
      {
        column += c;
      }
      else
      {
        row.push_back(column);
        column.clear();
      }
      break;

      /////////////////////////////////////////////////////////////////////////////////////////////////////
      //quote '"' detected. 
      //toggle quote mode
      /////////////////////////////////////////////////////////////////////////////////////////////////////

    case '"':
      quote_mode = !quote_mode;
      break;

      /////////////////////////////////////////////////////////////////////////////////////////////////////
      //line end detected
      //in quote mode add character to column
      //return row if not in quote mode
      /////////////////////////////////////////////////////////////////////////////////////////////////////

    case '\n':
    case '\r':
      if (quote_mode == true)
      {
        column += c;
      }
      else
      {
        return row;
      }
      break;

      /////////////////////////////////////////////////////////////////////////////////////////////////////
      //default, add character to column
      /////////////////////////////////////////////////////////////////////////////////////////////////////

    default:
      column += c;
      break;
    }
  }

  //return empty vector if end of file detected 
  m_ifs.close();
  std::vector<std::string> v;
  return v;
}

