#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <cmath>
#include <windows.h>

using namespace std::chrono;
using namespace std;



/*
requires #include <windows.h>

1: Blue
2: Green
3: Cyan
4: Red
5: Purple
6: Yellow (Dark)
7: Default white
8: Gray/Grey
9: Bright blue
10: Brigth green
11: Bright cyan
12: Bright red
13: Pink/Magenta
14: Yellow
15: Bright white

The Function requires an integer value and then sets the color of foreground with respect to the above colors.

*/
void ChangeColor(int value)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  value);
    return;
}





// This function is used to create a random array of size given by the user and range given by the user
void InitializeArray(int MyArr[] , int SizeOfArray, int LowestValue, int MaxValue)
{

    srand(time(0)) ;
    for(int i = 0 ; i < SizeOfArray ; i ++)
    {
        int RanNumber = (rand()%(MaxValue-LowestValue+1)+LowestValue) ;// random number between lowest value and largest value
        MyArr[i] = RanNumber ;
    }

    return;
}


//This function is used to print the array
void PrintArray (int Array[], int SizeOfArray)
{
    cout << endl;
    for (int i = 0; i<SizeOfArray; i++)
    {
        cout << Array[i] << "  ";
    }
    cout << endl;

    return;
}


//If input is not an integer this function is used to clear the input value and ask the user to enter an integer value
void InputFail(int &value)
{
    while(cin.fail())
        {
            cin.clear();
            string dummy;
            getline(cin,dummy);
            ChangeColor(4);
            cout << "Please enter an integer value " << endl;
            ChangeColor(7);
            cin >> value;
        }

    return;
}



int BubbleSort(int arr[], int a) //a is the size of the array
{
    int counter = 0;
    for (int i = 0; i < a-1; i++)
    {
        for (int j = 0; j < a-i-1; j++)
        {
            counter++;
            if (arr[j] > arr[j+1]) //value at index i is compared to the value right next to it
            {
                int temp;
                temp=arr[j+1]; //temp variable has value of the value at index j+1
                arr[j+1]=arr[j];
                arr[j]=temp; //basically values are swapped if value at index j is greater than the one next to it
            }
        }
    }
    return counter;
}



int SelectionSort(int arr[],int a) // a is the size of the array
{
    int counter=0;
    for (int i=0;i<a;i++)
    {
        int smallest=arr[i]; //value at index one is assigned considered as smallest value
        int smallindex=i; //index 0 is the index for the smallest value in array
        for(int j=i;j<a;j++)
        {                        //the whole array is compared to the value at index i
            if (arr[j]<smallest) //array is checked sequentially
            {
                smallest=arr[j]; //smallest value of array is now value at index j
                smallindex=j; //smallest index is now j
            }
            counter++;

        }
            int temp; //used to swap values at index i with the value that is less than the value at index i
            temp=arr[smallindex];
            arr[smallindex]=arr[i];
            arr[i]=temp;
    }

    return counter;
}



int InsertionSort(int MyArr[],int MaxVal)
{
    int counter = 0;

    for(int i = 0 ; i < MaxVal ; i++) // why this condition ???
    {
        int temp = MyArr[i]; // temp is assigned value of element under consideration for its correct position in sorted array
        int j = i;
        counter++;
        int x = 0;
        //loop while temp has a value lower than every element to its left
        while(  j > 0  && temp < MyArr[j-1])  // j > 0 because then the least value for j will be 1 and MyArr[j-1] = MyArr[0] can be compared with temp.
        {
           // swapping values to the right to make space for input of temp value ( element under consideration)
            MyArr[j] = MyArr[j-1];
            j--; // J is decreasing so that element of array with a lower index is checked with temp
            if (x>0)
            {
                counter ++;
            }
            x++;
        }
         // moving current element to its  correct position.
        MyArr[j] = temp;
    }

    return counter;
}



/* Quick Sort starts here
Quick Sort takes the first value of in the array and then sorts the array according to that value
Values smaller than that value are kept to the left side of the array
Values greater than that value are sorted to the right side of the array
The first value is then moved to its correct place in the array
This is repeated by dividing the array into smaller arrays and repeating the same loop until the array is entirely sorted
*/

int DividingArray(int Array[], int LowestIndex, int HighestIndex, int &Counter)
{
    int Temp;
    int Pivot = Array[LowestIndex]; // This value is compared with entire array
    int j = HighestIndex+1;
    for (int i=HighestIndex; i>LowestIndex; i--)
    {
        if (Array[i]>Pivot)        //if value at index i is greater than the value of the pivot it is swapped with the value at index j.
                                   //if value at index i is smaller than the value of the pivot it isn't changed
        {
            j--;
            Temp = Array[i];
            Array[i] = Array[j];
            Array[j] = Temp;
        }
        Counter++;

    }

    //The value that was compared with the entire array is now put in its correct place in the array

    Temp=Array[j-1];
    Array[j-1]=Array[LowestIndex];
    Array[LowestIndex]=Temp;

    return(j-1);   //The position in the array in which the pivoting value is put is returned

}


int CounterOfQuickSort = 0;
int QuickSort (int Array[], int LowestIndex, int HighestIndex)
{
    if (LowestIndex < HighestIndex)

    {
        int DividingIndex = DividingArray(Array, LowestIndex, HighestIndex, CounterOfQuickSort);

        QuickSort (Array, LowestIndex, DividingIndex-1); // the array is sorted recursively for values lower than the dividing index
        QuickSort (Array, DividingIndex+1, HighestIndex); // the array is sorted recursively for values greater than the dividing index
    }

    return CounterOfQuickSort;
}
// QuickSort function was taken from https://www.geeksforgeeks.org/quick-sort/
// Quick Sort ends here



/*Merge Sort starts here
Merge Sort divides the array into smaller sub arrays using recursion until the array reaches a size of 1
The recursion then runs backwards passing each array into the sort function and sorting each sub array
All the sub arrays are then sorted with each other until the entire array is sorted
*/

void Sort(int Array[], int LeftHandIndex, int MiddleIndex, int RightHandIndex, int & counter)
{
    int i = LeftHandIndex;
    int j = MiddleIndex+1;
    int k = 0;
    int n = RightHandIndex + 1;
    int TempArray[n]; //Temporary Array is created to store values

    while (i<=MiddleIndex && j<n) //Loop runs until i doesnt reach the middle value or j doesnt reach the value of n
    {
        counter++;
        if (Array[i]<Array[j])
        {
            TempArray[k]=Array[i];
            k++;
            i++;
        }
        else
        {
            TempArray[k]=Array[j];
            k++;
            j++;
        }
    }

// in the above loop there will always be a value that wont be sorted as either the condition of i or j will be met and so the remaining value will be taken by the array here
    while (i<=MiddleIndex)
    {
        counter++;
        TempArray[k]=Array[i];
        k++;
        i++;
    }

    while (j<n)
    {
        counter++;
        TempArray[k]=Array[j];
        k++;
        j++;
    }

//This function is used to transfer the sorted values in the temporary array back in the main array
    for (int a = LeftHandIndex; a<n; a++)
    {
        Array[a]=TempArray[a-LeftHandIndex];
    }

    return;
}

int CounterOfMergeSort = 0;

int MergeSort (int Array[], int LeftHandIndex, int RightHandIndex)
{
    int MiddleIndex;
    if (LeftHandIndex<RightHandIndex) // if lower limit is less than upper limit. If condition is not met, the next step is implemented and recursion is stopped
    {
        MiddleIndex = (LeftHandIndex+RightHandIndex)/2; // then find the mid point which will be the upper limit for next call

        MergeSort (Array, LeftHandIndex, MiddleIndex); //RECURSION STARTS !!!!! until left hand value equals right hand value
        MergeSort (Array, MiddleIndex+1, RightHandIndex); // Recursion again until condition is again not met

        Sort(Array, LeftHandIndex, MiddleIndex, RightHandIndex, CounterOfMergeSort); // Sorting after each step and then merging

    }

    return CounterOfMergeSort;

}
// Some of the MergeSort function and Sort function were taken from https://www.geeksforgeeks.org/merge-sort/
// Merge Sort ends here



// if the lower value of the range input by the user is greater than the higher value of the range then this function is used
//Until the user enters a lower value and a larger value correctly
void RangeFail (int& LowerValue, int& LargerValue)
{
    while (LowerValue>LargerValue)
    {
        ChangeColor(4);
        cout << endl << "The values you entered are wrong " << endl << endl;
        cout << "Please enter the LOWER value of the range of numbers you want in the array " << endl;
        ChangeColor(7);
        cin >> LowerValue;
        InputFail(LowerValue);

        ChangeColor(4);
        cout << "Please enter the HIGHER value of the range of numbers you want in the array " << endl;
        ChangeColor(7);
        cin >> LargerValue;
        InputFail(LargerValue);
    }

    return;
}


//Used to input the range of the array the user wants
void RangeOfArray(int& LowerValue, int& LargerValue)
{
    ChangeColor(2);
    cout << "Enter the lower value of the range of numbers you want in the array" << endl;
    ChangeColor(7);
    cin >> LowerValue;
    InputFail(LowerValue); //if a is not an integer

    ChangeColor(2);
    cout << "Enter the higher value of the range of numbers you want in the array" << endl;
    ChangeColor(7);
    cin >> LargerValue;
    InputFail(LargerValue); // if b is not an integer

    RangeFail(LowerValue,LargerValue); //if values of range are entered incorrectly

    return;
}



//This function lets the user choose the type of sorting they want and then outputs the time it takes for the sorting to happen
void SortingMethods (int Array[], int SizeOfArray)
{
    int Selection;

    cout << endl << endl;
    ChangeColor(2);
    cout << "Choose the sorting method you want to apply on this array " << endl;
    cout << "1. Bubble Sort " << endl;
    cout << "2. Selection Sort " << endl;
    cout << "3. Insertion Sort " << endl;
    cout << "4. Merge Sort " << endl;
    cout << "5. Quick Sort " << endl;
    cout << "6. All" << endl << endl;
    ChangeColor(7);

    cin >> Selection;
    InputFail(Selection);

    while (Selection>6 || Selection<1)
    {
        ChangeColor(4);
        cout << endl << "Please enter a value between 1 and 6 " << endl;
        ChangeColor(7);
        cin >> Selection;
        InputFail(Selection);
    }

    switch (Selection)
    {
        case 1:
            {
                auto t1 = high_resolution_clock::now(); //Time starts here
                int x = BubbleSort (Array, SizeOfArray);
                auto t2 = high_resolution_clock::now(); // Time ends here
                auto difference1 = duration_cast<nanoseconds>(t2-t1); //Difference in time is calculated and converted into nanoseconds

                cout << "\n \nThe sorted array is \n \n";
                PrintArray(Array,SizeOfArray);

                ChangeColor(4);
                cout << endl << "The sorting was done " << x << " times " << endl;
                cout << "The time taken for bubble sort is " << difference1.count() << " nanoseconds" << endl << endl;
                ChangeColor(7);
                break;
            }
        case 2:
            {
                auto t3 = high_resolution_clock::now();
                int x = SelectionSort (Array, SizeOfArray);
                auto t4 = high_resolution_clock::now();
                auto difference2 = duration_cast<nanoseconds>(t4-t3);

                cout << "The sorted array is " << endl;
                PrintArray(Array,SizeOfArray);

                ChangeColor(4);
                cout << endl << "The sorting was done " << x << " times " << endl;
                cout << "The time taken for selection sort is " << difference2.count() << "nanoseconds" << endl << endl;
                ChangeColor(7);
                break;
            }
        case 3:
            {
                auto t5 = high_resolution_clock::now();
                int x = InsertionSort (Array, SizeOfArray);
                auto t6 = high_resolution_clock::now();
                auto difference3 = duration_cast<nanoseconds>(t6-t5);

                cout << "The sorted array is " << endl;
                PrintArray(Array,SizeOfArray);

                ChangeColor(4);
                cout << endl << "The sorting was done " << x << " times " << endl;
                cout << "The time taken for insertion sort is " << difference3.count() << " nanoseconds "<< endl << endl;
                ChangeColor(7);
                break;
            }
        case 4:
            {
                auto t7 = high_resolution_clock::now();
                int x = MergeSort (Array, 0, SizeOfArray-1);
                auto t8 = high_resolution_clock::now();
                auto difference4 = duration_cast<nanoseconds>(t8-t7);

                cout << "The sorted array is " << endl;
                PrintArray(Array,SizeOfArray);

                ChangeColor(4);
                cout << endl << "The sorting was done " << x << " times " << endl;
                cout << "The time taken for merge sort is " << difference4.count() << " nanoseconds " << endl << endl;
                ChangeColor(7);
                break;
            }
        case 5:
            {
                auto t9 = high_resolution_clock::now();
                int x = QuickSort (Array, 0, SizeOfArray-1);
                auto t10 = high_resolution_clock::now();
                auto difference5 = duration_cast<nanoseconds>(t10-t9);

                cout << "The sorted array is " << endl;
                PrintArray(Array,SizeOfArray);

                ChangeColor(4);
                cout << endl << "The sorting was done " << x << " times " << endl;
                cout << "The time taken for quick sort is " << difference5.count() << " nanoseconds" << endl << endl;
                ChangeColor(7);
                break;
            }
        case 6:
            {
                int Array1[SizeOfArray], Array2[SizeOfArray], Array3[SizeOfArray], Array4[SizeOfArray], Array5[SizeOfArray];

                for (int i = 0; i<SizeOfArray; i++)
                {
                    Array1[i]=Array[i];
                    Array2[i]=Array[i];
                    Array3[i]=Array[i];
                    Array4[i]=Array[i];
                    Array5[i]=Array[i];
                }
                auto t1 = high_resolution_clock::now();
                int x1 = BubbleSort (Array1, SizeOfArray);
                auto t2 = high_resolution_clock::now();
                auto difference1 = duration_cast<nanoseconds>(t2-t1);

                auto t3 = high_resolution_clock::now();
                int x2 = SelectionSort (Array2, SizeOfArray);
                auto t4 = high_resolution_clock::now();
                auto difference2 = duration_cast<nanoseconds>(t4-t3);

                auto t5 = high_resolution_clock::now();
                int x3 = InsertionSort (Array3, SizeOfArray);
                auto t6 = high_resolution_clock::now();
                auto difference3 = duration_cast<nanoseconds>(t6-t5);

                auto t7 = high_resolution_clock::now();
                int x4 = MergeSort (Array4, 0, SizeOfArray-1);
                auto t8 = high_resolution_clock::now();
                auto difference4 = duration_cast<nanoseconds>(t8-t7);

                auto t9 = high_resolution_clock::now();
                int x5 = QuickSort (Array5, 0, SizeOfArray-1);
                auto t10 = high_resolution_clock::now();
                auto difference5 = duration_cast<nanoseconds>(t10-t9);

                cout << "The sorted array is " << endl;
                PrintArray(Array5, SizeOfArray);


                cout << "The time taken for bubble sort is " << difference1.count() << " nanoseconds" << endl;
                cout << "The sorting was done " << x1 << " times " << endl << endl;

                cout << "The time taken for selection sort is " << difference2.count() << " nanoseconds" << endl;
                cout << "The sorting was done " << x2 << " times " << endl << endl;

                cout << "The time taken for insertion sort is " << difference3.count() << " nanoseconds" << endl;
                cout << "The sorting was done " << x3 << " times " << endl << endl;

                cout << "The time taken for merge sort is " << difference4.count() << " nanoseconds" << endl;
                cout << "The sorting was done " << x4 << " times " << endl << endl;

                cout << "The time taken for quick sort is " << difference5.count() << " nanoseconds" << endl;
                cout << "The sorting was done " << x5 << " times " << endl << endl;

                //TIme is compared to see which is the fastest
                ChangeColor(4);
                if (difference1.count()<difference2.count() && difference1.count()<difference3.count() && difference1.count()<difference4.count() && difference1.count()<difference5.count())
                    cout << "Bubble Sort is the fastest sorting method for this data set" << endl;

                else if (difference2.count()<difference3.count() && difference2.count()<difference4.count() && difference2.count()<difference5.count())
                    cout << "Selection Sort is the fastest sorting method for this data set " << endl;

                else if (difference3.count()<difference4.count() && difference3.count()<difference5.count())
                    cout << "Insertion Sort is the fastest sorting method for this data set " << endl;

                else if (difference4.count()<difference5.count())
                    cout << "Merge Sort is the fastest sorting method for this data set" << endl;

                else
                    cout << "Quick Sort is the fastest sorting method for this data set " << endl;

                //Number of times the data is compared to sort is checked to see which sorting method runs the least number of times
                if (x1<x2 && x1<x3 && x1<x4 && x1<x5)
                    cout << "Bubble sort ran the least number of times " << endl;
                else if (x2<x3 && x2<x4 && x2<x5)
                    cout << "Selection sort ran the least number of times" << endl;
                else if (x3<x4 && x3<x5)
                    cout << "Insertion sort ran the least number of times" << endl;
                else if (x4<x5)
                    cout << "Merge sort ran the least number of times" << endl;
                else
                    cout << "Quick sort ran the least number of times " << endl;
                ChangeColor(7);
                break;
            }
    }

    return;
}



int main ()
{
    ChangeColor(4);
    cout<<endl<<endl;
    cout << "\t \t \t \t \t \t \t \t \t SORTING ARRAYS \n \n \n \n";
    ChangeColor(7);

    string option;
    ChangeColor(2);
    cout << "Do you want to sort an array " << endl;
    ChangeColor(7);
    cin >> option;

    while (option == "yes" || option == "Yes" || option == "y" || option == "Y")
    {
        int SizeOfArray;
        ChangeColor(2);
        cout << endl << "Enter the size of the array you want to sort" << endl;
        ChangeColor(7);
        cin >> SizeOfArray;
        InputFail(SizeOfArray);

        while (SizeOfArray<=0)
        {
            cin.clear();
            ChangeColor(4);
            cout << "Please enter a value for size greater than 0" << endl;
            ChangeColor(7);
            cin >> SizeOfArray;

            InputFail(SizeOfArray);
        }

        int Array[SizeOfArray];

        int DataSort;
        ChangeColor(2);
        cout << endl << "What type of data do you want to sort" << endl;
        cout << "1. Random Data " << endl;
        cout << "2. Almost Sorted Data " << endl; //Data is completely sorted except for last few values of data
        cout << "3. Data in Descending Order " << endl; //Data is in descending order
        ChangeColor(7);

        cin >> DataSort;
        InputFail(DataSort);
        cout << endl;

        while (DataSort<1 || DataSort>3)
        {
            ChangeColor(4);
            cout << endl << "Please enter an integer value between 1 and 3 " << endl;
            ChangeColor(7);
            cin >> DataSort;
            InputFail(DataSort);
        }

        if (DataSort == 1)
        {
            int LowerValue, LargerValue;
            RangeOfArray(LowerValue, LargerValue);

            InitializeArray(Array, SizeOfArray, LowerValue, LargerValue); //initializing a random array

            cout << endl << "The array is " << endl;
            PrintArray(Array, SizeOfArray);

            SortingMethods(Array, SizeOfArray);

        }

        else if (DataSort==2)
        {
            int LowerValue, LargerValue;
            RangeOfArray(LowerValue, LargerValue);

            InitializeArray(Array, SizeOfArray, LowerValue, LargerValue);
            QuickSort(Array, 0, SizeOfArray-1);

//The array is first sorted and the last few values of the array are changed to make it an almost sorted array

            srand(time(0));
            for (int i = SizeOfArray-(SizeOfArray/100); i<SizeOfArray; i++)
            {
                Array[i]=(rand()%(LargerValue-LowerValue+1)+LowerValue);
            }

            cout << "The almost sorted array is " << endl;
            PrintArray(Array,SizeOfArray);

            SortingMethods (Array,SizeOfArray);
        }

        else if (DataSort==3)
        {
            int LowerValue,LargerValue;
            RangeOfArray(LowerValue,LargerValue);

            InitializeArray(Array, SizeOfArray, LowerValue, LargerValue);
            QuickSort(Array,0,SizeOfArray-1);

//The array is sorted then reversed to make the array in descending order

            for (int i = 0; i<SizeOfArray/2; i++)
            {
                int Temp = Array[i];
                Array[i] = Array[SizeOfArray-1-i];
                Array[SizeOfArray-1-i] = Temp;
            }


            cout << "The almost sorted array is  " << endl;
            PrintArray(Array,SizeOfArray);

            SortingMethods (Array,SizeOfArray);
        }

        cout << "\n \n \n \n";
        ChangeColor(2);
        cout << "Do you want to sort another array " << endl;
        ChangeColor(7);
        cin >> option;

    }

    return 0;
}

