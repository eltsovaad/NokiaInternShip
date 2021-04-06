## TC-1
**Description:** simple test with integers to evaluate  
**Input:** [file simpleInt.csv](https://github.com/eltsovaad/NokiaInternShip/blob/master/tests/simpleInt.csv)  
**Expected output:**
```
,A,B,C,Cell
1,25,2,25,4
3,4,-21,2,3
10,6,21,1,2
50,1,3,4,0
```
**Real output** [file simpleInt.csv](https://github.com/eltsovaad/NokiaInternShip/blob/master/tests/results/simpleInt.csv)  
**Comment:** Passed  
## TC-2
**Description:** simple test with doubles to evaluate  
**Input:** [file simpleDouble.csv](https://github.com/eltsovaad/NokiaInternShip/blob/master/tests/simpleDouble.csv)  
**Expected output:**
```
,A,B,C,Cell
1,25.2,2,25.2,4.7
3,25.39,0.19,2,3.3
10,5,20.50,1,2.9
50,1,3,3,0
```
**Real output** [file simpleInt.csv](https://github.com/eltsovaad/NokiaInternShip/blob/master/tests/results/simpleDouble.csv)  
**Comment:** Passed  
## TC-3
**Description:** complicated test with formulas and quotations in column names  
**Input:** [file hardColumnNames.csv](https://github.com/eltsovaad/NokiaInternShip/blob/master/tests/hardColumnNames.csv)  
**Expected output:**
```
,Birds,Cats,"Birds,Cats","my_favourite_book""Birds,Cats"""
1,25,2,27,17982
2,4,21,25,16650
3,6,21,27,17982
4,1,3,4,2664
```
**Real output** [file hardColumnNames.csv](https://github.com/eltsovaad/NokiaInternShip/blob/master/tests/results/hardColumnNames.csv)  
**Comment:** Passed  
## TC-4
**Description:** running a program without filename as a parameter  
**Input:**   
**Expected output:** Error and closing a program  
**Real output** 
```
You should specify filename!
```
**Comment:** Passed  
## TC-5
**Description:** running a program with a wrong filename  
**Input:**   ajyhsbdjld.fff  
**Expected output:** Error and closing a program  
**Real output**   
```
File not found!
```
**Comment:** Passed  
## TC-6
**Description:** running a program with an empty file    
**Input:**   [empty file](https://github.com/eltsovaad/NokiaInternShip/blob/master/tests/emptyFile.csv)  
**Expected output:** Error and closing a program  
**Real output**   
```
File is empty!
```
**Comment:** Passed  
## TC-7
**Description:** running a program without an empty firstline in the file   
**Input:**   [file with an empty first line](https://github.com/eltsovaad/NokiaInternShip/blob/master/tests/emptyFirstLine.csv)  
**Expected output:** Error and closing a program  
**Real output**   
```
First line is empty!
```
**Comment:** Passed  
## TC-8
**Description:** running a program with a first element not empty  
**Input:**   [file with a first element not empty](https://github.com/eltsovaad/NokiaInternShip/blob/master/tests/notEmptyFirstSimbol.csv)  
**Expected output:** Error and closing a program  
**Real output**   
```
First symbol of the fisrt line should be empty!
```
**Comment:** Passed  
## TC-9
**Description:** file contains duplicate column names  
**Input:**   [file with duplicate column names](https://github.com/eltsovaad/NokiaInternShip/blob/master/tests/doubleColumnNames.csv)  
**Expected output:** Error and closing a program  
**Real output**  
```
Duplicate columns found!
```
**Comment:** Passed  
## TC-10
**Description:** file contains commas at the end of the line  
**Input:**   [file with commas at the end of the line](https://github.com/eltsovaad/NokiaInternShip/blob/master/tests/commasAtTheEnd.csv)  
**Expected output:** Error and closing a program  
**Real output**   
```
Found a comma at the end of the line!
```
**Comment:** Passed  
## TC-12
**Description:** file contains empty cell  
**Input:**   [file with empty cell](https://github.com/eltsovaad/NokiaInternShip/blob/master/tests/emptyArgument.csv)  
**Expected output:** Error and closing a program  
**Real output**  
```
Empty cell found!
```
**Comment:** Passed  
## TC-12
**Description:** file contains a column without a name  
**Input:**   [file with a column without a name](https://github.com/eltsovaad/NokiaInternShip/blob/master/tests/columnWithNoName.csv)  
**Expected output:** Error and closing a program  
**Real output**  
```
Empty cell found!
```
**Comment:** Passed, but error could be more eloquent  
## TC-13
**Description:** file contains less than 2 lines  
**Input:**   [file with less than 2 lines](https://github.com/eltsovaad/NokiaInternShip/blob/master/tests/oneLine.csv)  
**Expected output:** Error and closing a program  
**Real output**  
```
You should have at least 2 lines at the table!
```
**Comment:** Passed  
## TC-14
**Description:** file contains lines with different length  
**Input:**   [file with lines with different length](https://github.com/eltsovaad/NokiaInternShip/blob/master/tests/differentLineSizes.csv)  
**Expected output:** Error and closing a program  
**Real output**  
```
Found lines with different length!
```
**Comment:** Passed  
## TC-15
**Description:** invalid formula in a cell  
**Input:**   [file with A1 instead of =A1](https://github.com/eltsovaad/NokiaInternShip/blob/master/tests/notANumberInCell.csv)  
**Expected output:** Error and closing a program  
**Real output**  
```
A3: Invalid expression found!
```
**Comment:** Passed  
## TC-16
**Description:** invalid formant of line name  
**Input:**   [file with not integer linemane](https://github.com/eltsovaad/NokiaInternShip/blob/master/tests/letterInLineName.csv)  
**Expected output:** Error and closing a program  
**Real output**  
```
AA: Found not integer line name!
```
**Comment:** Passed  
## TC-17
**Description:** There is a loop in formula links  
**Input:**   [file with a loop](https://github.com/eltsovaad/NokiaInternShip/blob/master/tests/loopInFormulas.csv)  
**Expected output:** Error and closing a program  
**Real output**  
```
A1: A loop in links found!
```
**Comment:** Passed  
## TC-18
**Description:** A link to the non-existent cell  
**Input:**   [file with a link to the non-existent cell](https://github.com/eltsovaad/NokiaInternShip/blob/master/tests/wrongLineNameInCell.csv)  
**Expected output:** Error and closing a program  
**Real output**  
```
A3: Couldn't find cell!
```
**Comment:** Passed  
## TC-19
**Description:** Dividion by zero  
**Input:**   [file with a dividion by zero](https://github.com/eltsovaad/NokiaInternShip/blob/master/tests/divideBy0.csv)   
**Expected output:** Error and closing a program  
**Real output** 
```
B3: Division by zero!
```
**Comment:** Passed  
## TC-20
**Description:** More than 1 operation in a cell  
**Input:**   [file with more than 1 operation in cell](https://github.com/eltsovaad/NokiaInternShip/blob/master/tests/moreThanOneOperationInACell.csv)  
**Expected output:** Error and closing a program  
**Real output** 
```
B3: Found more than one operation in a cell
```
**Comment:** Passed  
## TC-22
**Description:** not closed quotations  
**Input:**   [file notClosedQuotes.csv](https://github.com/eltsovaad/NokiaInternShip/blob/master/tests/notClosedQuotes.csv)  
**Expected output:** Error and closing a program  
**Real output** 
```
You haven't closed quotes!
```
**Comment:** Passed  
## TC-23
**Description:** extra column name in the title  
**Input:**   [file notClosedQuotes.csv](https://github.com/eltsovaad/NokiaInternShip/blob/master/tests/oneMoreColumnName.csv)  
**Expected output:** Error and closing a program  
**Real output** 
```
Found lines with different length!
```
**Comment:** Passed  
