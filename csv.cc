#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include <stdlib.h>
#include "csv.hh"

#if 0
#define DEV
#endif

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
  if (!m_ifs.is_open())
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

/////////////////////////////////////////////////////////////////////////////////////////////////////
//read_csv_t::read
/////////////////////////////////////////////////////////////////////////////////////////////////////

int read_csv_t::read(const std::string &file_name)
{
  std::string str_rec;
  std::ifstream ifs;

  ifs.open(file_name.c_str());
  if (!ifs.is_open())
  {
    return -1;
  }

  std::getline(ifs, str_rec);

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  //get number of fields in header (assume no quotes)
  /////////////////////////////////////////////////////////////////////////////////////////////////////

  size_t nbr_fields = 0;
  size_t pos_last = 0;
  while (true)
  {
    size_t pos = str_rec.find(',', pos_last + 1);
    if (pos == std::string::npos)
    {
      //no more fields
      break;
    }
    pos_last = pos;
    nbr_fields++;
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  //parse rows
  /////////////////////////////////////////////////////////////////////////////////////////////////////

  size_t found = 0;
  size_t invalid = 0;
  size_t row = 1;
  while (std::getline(ifs, str_rec))
  {
    pos_cma.clear();
    row++;

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //find separators
    /////////////////////////////////////////////////////////////////////////////////////////////////////

    pos_last = 0;
    while (true)
    {
      size_t pos = str_rec.find(',', pos_last + 1);
      if (pos == std::string::npos)
      {
        //no more fields
        break;
      }

      //skip quoted fields, that can have commas inside
      if (pos < str_rec.size() - 1 && str_rec.at(pos + 1) == '"')
      {
        pos_cma.push_back(pos);

        //find the next quote
        size_t pos2 = str_rec.find('"', pos + 2);
        if (pos2 == std::string::npos)
        {
          std::cout << "Missing quote at row " << row << std::endl;
          assert(0);
        }
        //assume after '"' is ','
        pos_last = pos2 + 1;
        assert(str_rec.at(pos_last) == ',');
        pos_cma.push_back(pos_last);
        continue;
      }

      pos_cma.push_back(pos);
      pos_last = pos;
    }


    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //detect field 1 (code),
    //extract fiels 5 (date), 19 (lat), 20 (lon), 21 (zip)
    /////////////////////////////////////////////////////////////////////////////////////////////////////

    std::string str = get_field(str_rec, 1);
    if (str.compare("S0311") == 0)
    {
#ifdef DEV
      std::cout << std::endl;
      for (size_t idx = 0; idx < pos_cma.size() - 1; idx++)
      {
        str = get_field(str_rec, idx);
        std::cout << idx << " " << str << " ";
        std::cout << std::endl;
      }
#endif
      std::cout << row << " ";
      str = get_field(str_rec, 5);
      std::cout << str << " ";
      str = get_field(str_rec, 19);

      /////////////////////////////////////////////////////////////////////////////////////////////////////
      //detect invalid fields 
      /////////////////////////////////////////////////////////////////////////////////////////////////////

      for (size_t i = 1; i < str.size(); i++)
      {
        if (isspace(str.at(i)))
        {
          invalid++;
          break;
        }
      }

      std::cout << str << " ";
      str = get_field(str_rec, 20);
      std::cout << str << " ";
      str = get_field(str_rec, 21);
      std::cout << str << " ";
      std::cout << std::endl;
      found++;
    }
  }

  ifs.close();
  std::cout << "Processed " << row - 1 << " rows" << std::endl;
  std::cout << "S0311 codes: " << found << std::endl;
  std::cout << "Invalid rows: " << invalid << std::endl;
  return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//read_csv_t::get_field
/////////////////////////////////////////////////////////////////////////////////////////////////////

std::string read_csv_t::get_field(const std::string &rec, const size_t idx)
{
  size_t pos_c1 = pos_cma.at(idx);
  size_t pos_c2 = pos_cma.at(idx + 1);
  size_t len = pos_c2 - pos_c1 - 1;
  std::string str = rec.substr(pos_c1 + 1, len);
  return str;
}

