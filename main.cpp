// Program: Main.cpp
// Purpose: Demonstrate use of bmplib for handling
//          bmp colored and grayscale images
//          Program load a gray image and store in another file
// Author:  Mohamed Alaa Eddin Mostafa - 20211083 B
// Author:  Eslam Sayed - 20211012
// Author:  Yara Ibrahim - 20210447
// Date:    4/3/2022

#include <iostream>
#include <cstring>
#include "bmplib.cpp"
#include <iomanip>
#include <algorithm>
using namespace std;
// GS templates
unsigned char image[SIZE][SIZE];
unsigned char image1[SIZE][SIZE];
unsigned char newGSImage[SIZE][SIZE];
// RGB templates
unsigned char RGBImage[SIZE][SIZE][RGB];
unsigned char newRGBImage[SIZE][SIZE][RGB];
unsigned char newRGBImage1[SIZE][SIZE][RGB];

void readGSImage() {
    char imageFileName[100];
    cout << "Enter The Source Image File Name\n";
    cin >> imageFileName;
    strcat(imageFileName, ".bmp");
    while(readGSBMP(imageFileName, image)){
        cout << "Enter The Source Image File Name\n";
        cin >> imageFileName;
        strcat(imageFileName, ".bmp");
    }
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
        for (int j  = 0; j < SIZE; j++) {
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
    while (readGSBMP(imageFileName, image)){
        cout << "Enter The first Source Image File Name\n";
        cin >> imageFileName;
        strcat(imageFileName, ".bmp");
    }
    cout << "Enter The Second Source Image File Nam\n";
    cin >> image2ndFileName;
    strcat(image2ndFileName, ".bmp");
    while (readGSBMP(image2ndFileName, image1)){
        cout << "Enter The Second Source Image File Nam\n";
        cin >> image2ndFileName;
        strcat(image2ndFileName, ".bmp");
    }
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
    if (rotate_degree == 1 or rotate_degree == 2 or rotate_degree == 3) {
        readGSImage() ;
        for (int i = 0; i < rotate_degree; i++) {
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
        saveGSImage();
    }else {
        cout << "Wrong rotation enter\n";
    }
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
// Detect Images Edges #7
void GSdetectEdges() {
    readGSImage();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] > 127)
                image1[i][j] = 255;
            else
                image1[i][j] = 0;
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image1[i][j] == 0 && image1[i - 1][j] == 0 && image1[i + 1][j] == 0 && image1[i][j - 1] == 0 &&
                image1[i][j + 1] == 0) {
                newGSImage[i][j] = 255;
            } else
                newGSImage[i][j] = image1[i][j];
        }
    }
    saveGSImage();
}
// Enlarge Image #8
void GSenlarge() {
    readGSImage();
    int quarter;
    cout << "Enter Quarter:";
    cin >> quarter;
    if (quarter == 1) {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                newGSImage[i * 2][j * 2] = image[i][j];
                newGSImage[i * 2][(j * 2) + 1] = image[i][j];
                newGSImage[(i * 2) + 1][j * 2] = image[i][j];
                newGSImage[(i * 2) + 1][(j * 2) + 1] = image[i][j];
            }
        }
        saveGSImage();
    } else if (quarter == 2) {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 127; j < SIZE; j++) {
                newGSImage[i * 2][j * 2] = image[i][j];
                newGSImage[i * 2][(j * 2) + 1] = image[i][j];
                newGSImage[(i * 2) + 1][j * 2] = image[i][j];
                newGSImage[(i * 2) + 1][(j * 2) + 1] = image[i][j];
            }
        }
        saveGSImage();
    } else if (quarter == 3) {
        for (int i = SIZE / 2; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                newGSImage[((i - SIZE / 2) * 2)][j * 2] = image[i][j];
                newGSImage[((i - SIZE / 2) * 2)][(j * 2) + 1] = image[i][j];
                newGSImage[((i - SIZE / 2) * 2) + 1][j * 2] = image[i][j];
                newGSImage[((i - SIZE / 2) * 2) + 1][(j * 2) + 1] = image[i][j];
            }
        }
        saveGSImage();
    } else if (quarter == 4) {
        for (int i = SIZE / 2; i < SIZE; i++) {
            for (int j = SIZE / 2; j < SIZE; j++) {
                newGSImage[((i - SIZE / 2) * 2)][j * 2] = image[i][j];
                newGSImage[((i - SIZE / 2) * 2)][(j * 2) + 1] = image[i][j];
                newGSImage[((i - SIZE / 2) * 2) + 1][j * 2] = image[i][j];
                newGSImage[((i - SIZE / 2) * 2) + 1][(j * 2) + 1] = image[i][j];
            }
        }
        saveGSImage();
    }
}
// SHRINK Image #9
void GSshrink() {
    readGSImage();
    int row = 0;
    int operation;
    cout << "\n1.Shrink to 1/2"
            "\n2.Shrink to 1/3"
            "\n3.Shrink to 1/4"
            "\nOperation No.";
    cin >> operation;
    if (operation == 1) {
        for (int i = 0; i < SIZE / 2; i++) {
            int col = 0;
            for (int j = 0; j < SIZE / 2; j++) {
                newGSImage[i][j] = image[row][col];
                col += 2;
            }
            row += 2;
        }
    }
    if (operation == 2) {
        for (int i = 0; i < SIZE / 3; i++) {
            int col = 0;
            for (int j = 0; j < SIZE / 3; j++) {
                newGSImage[i][j] = image[row][col];
                col += 3;
            }
            row += 3;
        }
        saveGSImage();
    }
    if (operation == 3) {
        for (int i = 0; i < SIZE / 4; i++) {
            int col = 0;
            for (int j = 0; j < SIZE / 4; j++) {
                newGSImage[i][j] = image[row][col];
                col += 4;
            }
            row += 4;
        }
        saveGSImage();
    }
}
// Mirror Image #A
void GSmirror() {
    readGSImage();
    int n;
    cout << "\n1.Left 1/2"
            "\n2.Right 1/2"
            "\n3.Up 1/2"
            "\n4.Down 1/2"
            "\nOperation No.";
    cin >> n;
    if (n == 1) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                newGSImage[i][j] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = SIZE / 2; j < SIZE; j++) {
                newGSImage[i][j] = image[i][255 - j];
            }
        }
        saveGSImage();
    }
    if (n == 2) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = SIZE / 2; j < SIZE; j++) {
                newGSImage[i][j] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                newGSImage[i][j] = image[i][255 - j];
            }
        }
        saveGSImage();
    }
    if (n == 3) {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE; j++) {
                newGSImage[i][j] = image[i][j];
            }
        }
        for (int i = SIZE / 2; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                newGSImage[i][j] = image[255 - i][j];
            }
        }
        saveGSImage();
    }
    if (n == 4) {
        for (int i = SIZE / 2; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                newGSImage[i][j] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE; j++) {
                newGSImage[i][j] = image[255 - i][j];
            }
        }
        saveGSImage();
    }
}
// SHUFFLE Image #B
void GSsuffle(){
    int selection[4] ;
    readGSImage() ;
    cout << "\n" << "Enter the sequence of the numbers\n" ;
    for (int i = 0 ; i < 4 ; i++){
        cout << "Enter the " << i+1 << " quareter\n" ;
        cin >> selection[i] ;
        if (selection[i] != 4 and selection[i] != 2 and selection[i] != 3 and selection[i] != 1){
            cout << "Out range\n" ;
            i-- ;
        }
    }
    for (int i = 0 ; i < 4 ; i++){
        for (int j = 0 ; j < SIZE / 2 ; j++){
            for (int k = 0 ; k < SIZE / 2 ; k++){
                int q = j, w = k  , t = j, y = k;
                if (selection[i] == 2)
                    y += SIZE / 2 ;
                if (selection[i] == 3)
                    t += SIZE / 2 ;
                if (selection[i] == 4){
                    t += SIZE / 2;
                    y += SIZE / 2;
                }
                if (i == 1)
                    w += SIZE / 2 ;
                if (i == 2)
                    q += SIZE / 2 ;
                if (i == 3){
                    q += SIZE / 2;
                    w += SIZE / 2;
                }
                newGSImage[q][w] = image[t][y] ;
            }
        }
    }
    saveGSImage() ;
}
// BLUR Image #C
void GSblur() {
    readGSImage();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            newGSImage[i][j] = (image[i - 2][j - 2] + image[i - 2][j - 1] + image[i - 2][j] + image[i - 2][j + 1] +
                                image[i - 2][j + 2] +
                                image[i - 1][j - 2] + image[i - 1][j - 1] + image[i - 1][j] + image[i - 1][j + 1] +
                                image[i - 1][j + 2] +
                                image[i][j - 2] + image[i][j - 1] + image[i][j] + image[i][j + 1] + image[i][j + 2] +
                                image[i + 1][j - 2] + image[i + 1][j - 1] + image[i + 1][j] + image[i + 1][j + 1] +
                                image[i + 1][j + 1] +
                                image[i + 2][j - 2] + image[i + 2][j - 1] + image[i + 2][j] + image[i + 2][j + 1] +
                                image[i + 2][j + 2]) / 25;
        }
    }
    saveGSImage();
}
//------------------------------RGB BITMAP FILTERS------------------------------//
void readRGBImage() {
    char RGBImageFileName[100];
    cout << "Enter RGB Image Source File Name\n";
    cin >> RGBImageFileName;
    strcat(RGBImageFileName, ".bmp");
    while(readRGBBMP(RGBImageFileName, RGBImage)){
        cout << "Enter RGB Image Source File Name\n";
        cin >> RGBImageFileName;
        strcat(RGBImageFileName, ".bmp");
    }
}
void saveRGBImage() {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter The Target Image File Name\n";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeRGBBMP(imageFileName, newRGBImage);
}
//RGB Black And White #1
void RGBblackAndWhite() {

    readRGBImage();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int sum = 0;
            for (int k = 0; k < RGB; k++) {
                sum += RGBImage[i][j][k];
            }
            newGSImage[i][j] = sum / 3;
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (newGSImage[i][j] > 127)
                newGSImage[i][j] = 255;
            else
                newGSImage[i][j] = 0;
        }
    }
    saveGSImage();
}
//RGB Invert #2
void RGBInvert() {
    readRGBImage();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                newRGBImage[i][j][k] = 255 - RGBImage[i][j][k];
            }
        }
    }
    saveRGBImage();
}
//RGB Merge #3
void RGBMerge() {
    char imageFileName[100];
    char image2ndFileName[100];
    cout << "Enter The first Source Image File Name\n";
    cin >> imageFileName;
    strcat(imageFileName, ".bmp");
    while (readRGBBMP(imageFileName, RGBImage)){
        cout << "Enter The first Source Image File Name\n";
        cin >> imageFileName;
        strcat(imageFileName, ".bmp");
    }
    cout << "Enter The Second Source Image File Nam\n";
    cin >> image2ndFileName;
    strcat(image2ndFileName, ".bmp");
    while (readRGBBMP(image2ndFileName, newRGBImage1)){
        cout << "Enter The Second Source Image File Nam\n";
        cin >> image2ndFileName;
        strcat(image2ndFileName, ".bmp");
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0 ; k < RGB ;k ++) {
                // Save the Average of each pixel in each photo
                newRGBImage[i][j][k] = (newRGBImage1[i][j][k] + RGBImage[i][j][k]) / 2;
            }
        }
    }
    saveRGBImage();
}
//RGB Flip #4
void RGBFlip() {
    int n;
    cout << "\n1.Horizontally\n"
            "2.Vertically\n"
            "Operation NO.";
    cin >> n;
    readRGBImage();
    if (n == 2) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++) {
                    newRGBImage[i][j][k] = RGBImage[255 - i][j][k];
                }
            }
        }
        saveRGBImage();
    } else if (n == 1) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++) {
                    newRGBImage[i][j][k] = RGBImage[i][255 - j][k];
                }
            }
        }
        saveRGBImage();
    }

}
//RGB Rotate #5
void RGBrotate() {
    int rotate_degree ;
    cout << "\n1.90\n"
            "2.180\n"
            "3.270\n"
            "Operation NO --> ";
    cin >> rotate_degree ;
    if (rotate_degree == 1 or rotate_degree == 2 or rotate_degree == 3) {
        readRGBImage() ;
        for (int i = 0; i < rotate_degree; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < SIZE; k++) {
                    for (int r = 0 ; r < RGB ; r++) {
                        // Transpose the 3d array
                        newRGBImage1[j][k][r] = RGBImage[k][j][r];
                    }
                }
            }
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < SIZE; k++) {
                    for (int r = 0 ; r < RGB ; r++) {
                        //flip vertically
                        newRGBImage[j][k][r] = newRGBImage1[j][255 - k][r];
                        // Store the new image to the main image to use it again
                        RGBImage[j][k][r] = newRGBImage[j][k][r];
                    }
                }
            }
        }
        saveRGBImage();
    }else {
        cout << "Wrong rotation enter\n";
    }
}
//RGB Darken And Lighten #6
void RGBDarkenAndLighten() {
    readRGBImage();
    int operation;
    cout << "\n1.Darken"
            "\n2.Lighten"
            "\nOperation No.";
    cin >> operation;
    if (operation == 1){
        for (int i = 0 ; i < SIZE ; i++){
            for (int j = 0 ; j < SIZE ; j++) {
                for (int k = 0 ; k < RGB ; k++) {
                    newRGBImage[i][j][k] = RGBImage[i][j][k] / 2;
                }
            }
        }
        cout << "\n" ;
        saveGSImage();
    }
    else if (operation == 2){
        for (int i = 0 ; i < SIZE ; i++){
            for (int j = 0 ; j < SIZE ; j++) {
                for (int k = 0 ; k < SIZE ; k++) {
                    newRGBImage[i][j][k] = RGBImage[i][j][k] / 2 + 127;
                }
            }
        }
        cout << "\n" ;
        saveRGBImage();
    }
    else {
        cout << "Wrong operation\n" ;
    }
}
//RGB Detect Image Edges #7
void RGBdetectImageEdges() {
    readRGBImage();

    // Change RGB Image to Greyscale Image
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int sum = 0;
            for (int k = 0; k < RGB; k++) {
                sum += RGBImage[i][j][k];
            }
            image[i][j] = sum / 3;
        }
    }

    // Change Greyscale Image Into Black And White Image.
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] > 127)
                image1[i][j] = 255;
            else
                image1[i][j] = 0;
        }
    }

    // Detect Black&White Image Edges
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image1[i][j] == 0 && image1[i - 1][j] == 0 && image1[i + 1][j] == 0 && image1[i][j - 1] == 0 &&
                image1[i][j + 1] == 0) {
                newGSImage[i][j] = 255;
            } else
                newGSImage[i][j] = image1[i][j];
        }
    }
    saveGSImage();

}
//RGB Enlarge Image #8
void RGBenlarge() {
    readRGBImage();
    int x , y  , row_set = 0 , column_set = 0 , quarter ,r , c;
    cout << "Enter the Quarter you want to enlarge\n" ;
    cin >> quarter ;
    if (quarter == 1){
        row_set = 0 ;
        column_set = 0 ;
    }
    else if (quarter == 2){
        column_set += SIZE / 2 ;
    }
    else if (quarter == 3){
        row_set += SIZE / 2 ;
    }
    else if (quarter == 4){
        row_set += SIZE / 2 ;
        column_set += SIZE / 2 ;
    }
    if (quarter == 1 or quarter == 2 or quarter == 3 or quarter == 4) {
        for (int i = 0; i < SIZE / 2; i++) {
            r = i + row_set;
            if (r >= SIZE / 2) {
                x = (r - SIZE / 2) * 2;
            } else {
                x = r * 2;
            }
            for (int j = 0; j < SIZE / 2; j++) {
                c = j + column_set;
                if (c >= SIZE / 2) {
                    y = (c - SIZE / 2) * 2;
                } else {
                    y = c * 2;
                }
                for (int k = 0; k < RGB; k++) {
                    newRGBImage[x][y][k] = RGBImage[r][c][k];
                    newRGBImage[x][y + 1][k] = RGBImage[r][c][k];
                    newRGBImage[x + 1][y][k] = RGBImage[r][c][k];
                    newRGBImage[x + 1][y + 1][k] = RGBImage[r][c][k];
                }
            }
        }
        saveRGBImage();
    }else {
        cout << "Wrong Quarter chosen\n" ;
    }
}
//RGB Shrink Image #9
void RGBshrink() {
    readRGBImage();
    int x , y , scale;
    cout << "1.Shrink to 1/2"
            "\n2.Shrink to 1/3"
            "\n3.Shrink to 1/4"
            "\nOperation No.";
    cin >> scale ;
    // Make the background white
    for (int i = 0 ; i < SIZE ; i++){
        for (int j = 0 ; j < SIZE ; j++){
            for (int r = 0 ; r < RGB ; r++) {
                newRGBImage[i][j][r] = 255;
            }
        }
    }
    if (scale < 4) {
        scale += 1 ;
        for (int i = 0; i < SIZE / scale; i++) {
            x = i * scale;
            for (int j = 0; j < SIZE / scale; j++) {
                y = j * scale;
                for (int r = 0; r < RGB; r++) {
                    newRGBImage[i][j][r] = RGBImage[x][y][r];
                }
            }
        }
        saveRGBImage();
    }else {
        cout << "Out of the scale's range\n";
    }
}
//RGB Mirror #A
void RGBmirror() {
    readRGBImage();
    int mirror_side , row_set = 0, column_set = 0 , start;
    cout << "Choose the side of the mirror"
            "\n1.Up"
            "\n2.Down"
            "\n3.Left"
            "\n4.Right"
            "\nOperation No.";
    cin >> mirror_side ;
    if (mirror_side == 1 or mirror_side == 2) {
        if (mirror_side == 1){
            row_set = SIZE / 2 ;
            column_set = SIZE ;
            start = 0 ;
        }
        if (mirror_side == 2){
            row_set = SIZE ;
            column_set = SIZE  ;
            start = SIZE / 2 ;
        }
        for (int i = start; i < row_set; i++) {
            for (int j = 0; j < column_set; j++) {
                for (int r = 0; r < RGB; r++) {
                    newRGBImage[i][j][r] = RGBImage[i][j][r];
                    newRGBImage[255 - i][j][r] = RGBImage[i][j][r];
                }
            }
        }
        saveRGBImage();
    }
    else if (mirror_side == 3 or mirror_side == 4){
        if (mirror_side == 3){
            row_set = SIZE  ;
            column_set = SIZE / 2 ;
            start = 0 ;
        }
        if (mirror_side == 4){
            row_set = SIZE ;
            column_set = SIZE  ;
            start = SIZE / 2 ;
        }
        for (int i = 0; i < row_set; i++) {
            for (int j = start; j < column_set; j++) {
                for (int r = 0; r < RGB; r++) {
                    newRGBImage[i][j][r] = RGBImage[i][j][r];
                    newRGBImage[i][255 - j][r] = RGBImage[i][j][r];
                }
            }
        }
        saveRGBImage();
    }
    else {
        cout << "Wrong side chosen\n" ;
    }
}
//RGB Shuffle #B
void RGBshuffle() {
    int selection[4] ;
    readRGBImage();
    cout << "Enter the sequence of the numbers\n" ;
    for (int i = 0 ; i < 4 ; i++){
        cout << "Enter the " << i+1 << " quareter\n" ;
        cin >> selection[i] ;
        if (selection[i] != 4 and selection[i] != 2 and selection[i] != 3 and selection[i] != 1){
            cout << "Out range\n" ;
            i-- ;
        }
    }
    for (int i = 0 ; i < 4 ; i++){
        for (int j = 0 ; j < SIZE / 2 ; j++){
            for (int k = 0 ; k < SIZE / 2 ; k++){
                int q = j, w = k  , t = j, y = k;
                if (selection[i] == 2)
                    y += SIZE / 2 ;
                if (selection[i] == 3)
                    t += SIZE / 2 ;
                if (selection[i] == 4){
                    t += SIZE / 2;
                    y += SIZE / 2;
                }
                if (i == 1)
                    w += SIZE / 2 ;
                if (i == 2)
                    q += SIZE / 2 ;
                if (i == 3){
                    q += SIZE / 2;
                    w += SIZE / 2;
                }
                for (int r = 0 ; r < RGB ; r++) {
                    newRGBImage[q][w][r] = RGBImage[t][y][r];
                }
            }
        }
    }
    saveRGBImage();
}
//RGB Blur #C
void RGBblur() {
    readRGBImage();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                newRGBImage[i][j][k] = (RGBImage[i - 2][j - 2][k] + RGBImage[i - 2][j - 1][k] + RGBImage[i - 2][j][k] +
                                        RGBImage[i - 2][j + 1][k] +
                                        RGBImage[i - 2][j + 2][k] +
                                        RGBImage[i - 1][j - 2][k] + RGBImage[i - 1][j - 1][k] + RGBImage[i - 1][j][k] +
                                        RGBImage[i - 1][j + 1][k] +
                                        RGBImage[i - 1][j + 2][k] +
                                        RGBImage[i][j - 2][k] + RGBImage[i][j - 1][k] + RGBImage[i][j][k] +
                                        RGBImage[i][j + 1][k] +
                                        RGBImage[i][j + 2][k] +
                                        RGBImage[i + 1][j - 2][k] + RGBImage[i + 1][j - 1][k] + RGBImage[i + 1][j][k] +
                                        RGBImage[i + 1][j + 1][k] +
                                        RGBImage[i + 1][j + 1][k] +
                                        RGBImage[i + 2][j - 2][k] + RGBImage[i + 2][j - 1][k] + RGBImage[i + 2][j][k] +
                                        RGBImage[i + 2][j + 1][k] +
                                        RGBImage[i + 2][j + 2][k]) / 25;
            }
        }
    }
    saveRGBImage();
}
int Choose_Filter(){
    string operation , picture_Type;
    cout << "1.GS\n"
            "2.RGB\n"
            "0.Exit\n"
            "Operation No." ;
    cin >> picture_Type ;
    if (picture_Type == "1" or picture_Type == "2" or picture_Type == "0") {
        if (picture_Type == "0"){
            return 0;
        }
        cout << "\n";
        cout << setw(38) << setfill('-') << "  " << setw(38) << setfill('-') << "  " << setw(37) << setfill('-')
             << "\n";
        cout
                << "|        Operation          |  No. |  |         Operation         |  No. |  |         Operation         |  No. |\n";
        cout << setw(38) << setfill('-') << "  " << setw(38) << setfill('-') << "  " << setw(37) << setfill('-')
             << "\n";
        cout
                << "|  Black and White Filter   |  1   |  |    Invert image Filter    |  2   |  |    Merge image Filter     |  3   |\n";
        cout
                << "|     Flib image Filter     |  4   |  |    Rotate image Filter    |  5   |  | Darken and Lighten filter |  6   |\n";
        cout
                << "|    Detect edges Filter    |  7   |  |    Enlarge image Filter   |  8   |  |    Shrink image Filter    |  9   |\n";
        cout
                << "|    Mirror image Filter    |  A   |  |    Shuffle image Filter   |  B   |  |     Blur image Filter     |  C   |\n";
        cout << setw(38) << setfill('-') << "  " << setw(38) << setfill('-') << "  " << setw(37) << setfill('-')
             << "\n";
        cout
                << "|            Exit           |  0   |  |            Exit           |  0   |  |            Exit           |  0   |\n";
        cout << setw(38) << setfill('-') << "  " << setw(38) << setfill('-') << "  " << setw(37) << setfill('-')
             << "\n";
        cout << "Enter the operation you want to apply\nyou can enter lowercase or uppercase letters\n";
        cin >> operation;
        operation.erase(remove(operation.begin(), operation.end(), ' '), operation.end());
        if (operation == "1") {
            if (picture_Type == "1") {
                GSblackAndWhite();
            }
            if (picture_Type == "2"){
                RGBblackAndWhite() ;
            }

        } else if (operation == "2") {
            if (picture_Type == "1") {
                GSinvertImage();
            }
            if (picture_Type == "2") {
                RGBInvert();
            }
        } else if (operation == "3") {
            if (picture_Type == "1") {
                GSmerge();
            }
            if (picture_Type == "2"){
                RGBMerge();
            }
        } else if (operation == "4") {
            if (picture_Type == "1") {
                GSflip();
            }
            if (picture_Type == "2"){
                RGBFlip();
            }
        } else if (operation == "5") {
            if (picture_Type == "1") {
                GSrotate();
            }
            if (picture_Type == "2"){
                RGBrotate();
            }
        } else if (operation == "6") {
            if (picture_Type == "1") {
                GSdarkenAndLighten();
            }
            if (picture_Type == "2"){
                RGBDarkenAndLighten() ;
            }
        } else if (operation == "7") {
            if (picture_Type == "1") {
                GSdetectEdges();
            }
            if (picture_Type == "2"){
                RGBdetectImageEdges();
            }
        } else if (operation == "8") {
            if (picture_Type == "1") {
                GSenlarge();
            }
            if (picture_Type == "2"){
                RGBenlarge();
            }
        } else if (operation == "9") {
            if (picture_Type == "1") {
                GSshrink();
            }
            if (picture_Type == "2"){
                RGBshrink();
            }
        } else if (operation == "A" or operation == "a") {
            if (picture_Type == "1") {
                GSmirror();
            }
            if (picture_Type == "2"){
                RGBmirror();
            }
        } else if (operation == "B" or operation == "b") {
            if (picture_Type == "1") {
                GSsuffle();
            }
            if (picture_Type == "2"){
                RGBshuffle();
            }
        } else if (operation == "C" or operation == "c") {
            if (picture_Type == "1") {
                GSblur();
            }
            if (picture_Type == "2"){
                RGBblur();
            }
        }else if (operation == "0" or picture_Type == "0") {
            cout << "Thank you for using";
            return 0;
        } else {
            cout << "Wrong operation\n";
        }
    }else {
        cout << "Wrong Type enterd\n" ;
    }
    Choose_Filter();
}
int main() {
    Choose_Filter() ;
}
