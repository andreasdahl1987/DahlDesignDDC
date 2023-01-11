# 10\_MatrixAndAnalog.ino

###

```
//------------------------------
//-------MATRIX VARIABLES-------
//------------------------------

uint8_t row[] = {0};
const uint8_t rowCount = sizeof(row) / sizeof(row[0]);

uint8_t col[] = {0};
const uint8_t colCount = sizeof(col) / sizeof(col[0]);

bool nonMatrixIncluded = false;

uint8_t nonMatrix[] = {0};
const uint8_t nonMatrixCount = sizeof(nonMatrix) / sizeof(nonMatrix[0]);

//---------------------------------------
//--------MATRIX DESCRIPTION-------------
//---------------------------------------

const uint8_t buttonNumber[rowCount][colCount] =
{
  {0, 0, 0, 0, 0},     //ROW 1
  {0, 0, 0, 0, 0},     //ROW 2
  {0, 0, 0, 0, 0},     //ROW 3
  {0, 0, 0, 0, 0},     //ROW 4
  {0, 0, 0, 0, 0}      //ROW 5
};

//---------------------------------------
//--------ANALOG DESCRIPTION-------------
//---------------------------------------

const uint8_t analogButtonNumber[10] =         //ANALOG BUTTONS 1
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

const uint8_t analogButtonNumberIncMode[10] =  //ANALOG BUTTONS 2
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
```

#### Pins

We start by describing the pins used in the matrix.

* `uint8_t row[] = {0};` Insert pin numbers for your rows, starting with first row.

If wired like the board at the top of [3.Wiring](https://github.com/andreasdahl1987/DahlDesignDDC/wiki/3.-Wiring), you'd write it like this:

`uint8_t row[] = {15,14,16,10};`

_If you're using non-matrix switches, use the number `99` instead of a row pin._

* `uint8_t col[] = {0};` The same as above. For the example picture this will be `uint8_t col[] = {3,4,5,6,7};`

_If you're using non-matrix switches exclusively, you don't even have any column pins. In that case, use the number `99` for column pins as well._ A setup for 4 x 4 matrix including only non-matrix switches would look like this:

`uint8_t row[] = {99,99,99,99};`

`uint8_t col[] = {99,99,99,99};`

* A hybrid system with the first two rows reserved for non-matrix switches could look like this:

`uint8_t row[] = {99,99,4,5};`

`uint8_t col[] = {15,10,14,7};`

* `bool nonMatrixIncluded = false;` Is set to `true` if you're using switches non-matrix switches.
* `uint8_t nonMatrix[] = {0};` Only relevant if using switches not wired in matrix. List the actual pin numbers that these switches are connected to. The order doesn't matter, this is just used for pulling up the pins.

#### Matrix description

The reason why I set up my matrix in a spreadsheet is this:

![image](https://user-images.githubusercontent.com/40788634/194886077-1af05ab1-d62c-446a-ab3b-11fc3579d9d0.png)

```
const uint8_t buttonNumber[rowCount][colCount] =
{
  {20, 0, 4, 5, 6},     //ROW 1
  {9, 10, 11, 12, 13},  //ROW 2
  {14, 0, 8, 22, 0},    //ROW 3
  {16, 0, 7, 18, 0},    //ROW 4
  {0, 1, 2, 3, 0}       //ROW 5
};
```

You simply copy your planned matrix to this one. By default it is a 5 x 5 matrix. Adjust it accordingly. 4 x 7 would be like this:

```
const uint8_t buttonNumber[rowCount][colCount] =
{
  {0, 0, 0, 0, 0, 0, 0},     //ROW 1
  {0, 0, 0, 0, 0, 0, 0},     //ROW 2
  {0, 0, 0, 0, 0, 0, 0},     //ROW 3
  {0, 0, 0, 0, 0, 0, 0},     //ROW 4
};
```

#### Analog description

First of all, state how many analog switches your project has. In this case 5.&#x20;

`#define analogSwitchCount 5`

The same way you set up the matrix button numbers, your planned analog switches goes in here:

<figure><img src="../.gitbook/assets/image (1).png" alt=""><figcaption></figcaption></figure>

```
const uint8_t analogButtonNumber[analogSwitchCount] =         
{ 69, 83, 0, 0, 97};

const uint8_t analogButtonNumberIncMode[analogSwitchCount] = 
{ 81, 95, 0, 0, 0};
```
