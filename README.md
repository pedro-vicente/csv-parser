# csv-parser
Contribution for Code for DC - The Rat Hack

https://github.com/eclee25/the-rat-hack

C++ program that reads CSV file and extracts rodent complaints.
It includes a built class to parse CSV files

Building with CMake in Unix
------------
<pre>
git clone https://github.com/pedro-vicente/csv-parser.git
cd csv-parser
mkdir build
cd build
cmake ..
make
</pre>

Usage
------------
<pre>
./read_dc311 -f FILE
</pre>

where FILE is a CSV DC311 file

Example output with included CSV file
------------
<pre>
./read_dc311 -f ../dc_311-2016_100.csv
</pre>

<pre>
2 2016-10-29T15:09:22Z 38.91374182 -77.00176208 20002
9 2016-10-31T15:08:27Z 38.87106718 -76.94948596 20020
10 2016-10-31T20:12:42Z 38.91523017 -77.0201263 20001
13 2016-10-29T16:57:43Z 38.87867148 -76.92896433 20019
17 2016-10-31T15:30:18Z 38.89967673 -76.98869758 20002
18 2016-10-31T17:19:47Z 38.88146063 -76.98961269 20003
Processed 98 rows
S0311 codes: 6
</pre>

A C++ class was done to read the CSV files. It reads the following 4 cases:
------------

<pre>
1,field 2,field 3,
1,field 2,"field 3 quoted, with separator",
1,field 2,"field 3
with newline",
1,field 2,"field 3
with newline and separator,",
</pre>

C++ class usage
------------

Iterate until an empty row is returned (end of file). A row is a vector where each entry is a CSV column. 

```c++
read_csv_t csv;
csv.open("../test.csv");
std::vector<std::string> row;
while (true)
{
  row = csv.read_row();
  if (row.size() == 0)
  {
    break;
  }
}
```

Example to extract a column. This examples detects if column 2 is the string "S0311" and prints column 22

```c++
if (row.at(2).compare("S0311") == 0)
{
  std::cout << row.at(22).c_str() << std::endl;
}
```

CSV reference
------------

https://tools.ietf.org/html/rfc4180

