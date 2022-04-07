// Program: Main.cpp
// Purpose: Demonstrate use of bmplib for handling
//          bmp colored and grayscale images
//          Program load a gray image and store in another file
// Author:  Mohamed Alaa Eddin Mostafa - 20211083 B
// Author:  Islam Sayed - 20211012
// Author:  Yara - 20210447
// Date:    4/3/2022

#include <iostream>
#include <cstring>
#include "bmplib.cpp"
#include <iomanip>
#include <algorithm>
using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image1[SIZE][SIZE];
unsigned char newGSImage[SIZE][SIZE];

void readGSImage() {
    char imageFileName[100];
    cout << "Enter The Source Image File Name\n";
    cin >> imageFileName;
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

void saveGSImage() {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter The Target Image File Name\n";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, newGSImage);
}
//------------------------------GREY SCALE BITMAP FILTERS------------------------------//

// BLACK AND WHITE Image #1
void GSblackAndWhite(){
    readGSImage();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // Convert the greater than the average to a white pixel
            if (image[i][j] > 127)
                newGSImage[i][j] = 255;
                // Convert the lower than the average to a black pixel
            else
                newGSImage[i][j] = 0;
        }
    }
    cout << "\n" ;
    saveGSImage();
}

// INVERT Image #2
void GSinvertImage() {
    readGSImage();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // Convert each degree of gray to the opposite degree
            // For example 255 >> black will convert to 0 >> white
            newGSImage[i][j] = 255 - image[i][j];
        }
    }
    cout << "\n" ;
    saveGSImage();
}

// Merge Image #3
void GSmerge() {
    char imageFileName[100];
    char image2ndFileName[100];
    cout << "Enter The first Source Image File Name\n";
    cin >> imageFileName;
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
    cout << "Enter The Second Source Image File Nam\n";
    cin >> image2ndFileName;
    strcat(image2ndFileName, ".bmp");
    readGSBMP(image2ndFileName, image1);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // Save the Average of each pixel in each photo
            newGSImage[i][j] = (image1[i][j] + image[i][j]) / 2;
        }
    }
    cout << "\n" ;
    saveGSImage();
}

// FLIP Image #4
void GSflip() {
    readGSImage();
    string operation;
    cout << "\n1.Horizontally\n"
            "2.Vertically\n"
            "Operation NO --> ";
    cin >> operation;
    operation.erase(remove(operation.begin() , operation.end() , ' ') , operation.end()) ;
    if (operation == "1") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                newGSImage[i][j] = image[255 - i][j];
            }
        }
        cout << "\n" ;
        saveGSImage();
    }
    else if (operation == "2") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                newGSImage[i][j] = image[i][255 - j];
            }
        }
        cout << "\n" ;
        saveGSImage();
    }else {
        cout << "Wrong operation\n" ;
    }
}

// ROTATE Image #5
void GSrotate() {
    int rotate_degree ;
    cout << "\n1.90\n"
            "2.180\n"
            "3.270\n"
            "Operation NO --> ";
    cin >> rotate_degree ;
    if (rotate_degree > 3 or rotate_degree < 0){
        while (rotate_degree > 3 or rotate_degree < 0){
            cout << "Wrong Operation\n";
            cout << "\n Enter the angle of rotate\n1 --> 90 \n2 --> 180 \n3 --> 270\n";
            cin >> rotate_degree ;
        }
    }
    readGSImage() ;
    for (int i = 0 ; i < rotate_degree ; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                // Transpose the 2d array
                image1[j][k] = image[k][j];
            }
        }
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                //flip vertically
                newGSImage[j][k] = image1[j][255 - k];
                // Store the new image to the main image to use it again
                image[j][k] = newGSImage[j][k];
            }
        }
    }
    cout << "\n" ;
    saveGSImage();
}


// Darken And Lighten Image #6
void GSdarkenAndLighten() {
    readGSImage();
    string operation;
    cout << "\n1.Darken"
            "\n2.Lighten"
            "\nOperation No.";
    cin >> operation;
    operation.erase(remove(operation.begin() , operation.end() , ' ') , operation.end()) ;
    if (operation == "1"){
        for (int i = 0 ; i < SIZE ; i++){
            for (int j = 0 ; j < SIZE ; j++) {
                newGSImage[i][j] = image[i][j] / 2 ;
            }
        }
        cout << "\n" ;
        saveGSImage();
    }
    else if (operation == "2"){
        for (int i = 0 ; i < SIZE ; i++){
            for (int j = 0 ; j < SIZE ; j++) {
                newGSImage[i][j] = image[i][j] / 2 + 127;
            }
        }
        cout << "\n" ;
        saveGSImage();
    }
    else {
        cout << "Wrong operation\n" ;
    }
}
int Choose_Filter (){
    string operation ;
    cout << "\n" ;
    cout << setw (40) << setfill('-')  << "  " << setw (40) << setfill('-') << "\n" ;
    cout << "|        Operation         | number  |  |         Operation         | number  |\n";
    cout << setw (40) << setfill('-')  << "  " << setw (40) << setfill('-') << "\n" ;
    cout << "|  Black and White Filter  |   1     |  |      Flip Image Filter    |   4     |\n";
    cout << "|   Invert Image Filter    |   2     |  |        Rotate Image       |   5     |\n";
    cout << "|   Merge Images Filter    |   3     |  | Darken and Lighten Filter |   6     |\n";
    cout << setw (40) << setfill('-')  << "  " << "|            EXIT           |   0     |\n" ;
    cout << setw (40) << setfill(' ') <<" " << setw (40) << setfill('-') << "\n" ;
    cout << "Enter the operation you want to apply\n" ;
    cin >> operation ;
    operation.erase(remove(operation.begin() , operation.end() , ' ') , operation.end()) ;
    if (operation == "1"){
        GSblackAndWhite() ;
    }
    if (operation == "2"){
        GSinvertImage() ;
    }
    if (operation == "3"){
        GSmerge() ;
    }
    if (operation == "4"){
        GSflip() ;
    }
    if (operation == "5"){
        GSrotate();
    }
    if (operation == "6"){
        GSdarkenAndLighten();
    }
    if (operation == "0"){
        cout << "Thank you for using" ;
        return 0 ;
    }

    Choose_Filter();
}
int main() {
    Choose_Filter() ;
}
