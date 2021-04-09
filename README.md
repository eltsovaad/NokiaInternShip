# CSV-table reader
Reads CSV file from such a table, where the first element is always empty:  
```
,A,B,Cell  
1,1,0,1  
2,2,=A1+Cell30,0  
30,0,=B1+A1,5 
 ```
And prints "evaluated" table in the console:
  ```
  ,A,B,Cell
  1,1,0,1
  2,2,6,0
  30,0,1,5
  ```
 ## Building and compilation
- cd to the NokiaInternShip-master folder (with CMakeLists.txt)
- use  
```
cmake CMakeLists.txt -G "MinGW Makefiles"
```
- than  
```
make
```
- and finally 
```
NokiaInternShip.exe text.csv
```
to run an app with an example
## Adavntages and constraints
- Column names can contain commas, but this name should be placed in quotations
```
,A,B,Cell,"A,B"
```
- Use double quotations, if you want to have a quotation mark in a column name
```
,A,B,Cell,""Ruslan and Ludmila""
```
- Column names can only contain characters, line numbers shold be integer
- Each cell can consist a number with floating point, or a formula
- A formula can contain a link to the other cell, or one arithmetic operation with numbers or links
- Numbers with floating point are displayed with 2 characters precision
- First element of the first line should be empty
- Program ignores spaces and tabs, so avoid them in the names of columns
## Furthermore
You can find some test cases [in the "tests" folder](https://github.com/eltsovaad/NokiaInternShip/blob/master/tests/README.md)
