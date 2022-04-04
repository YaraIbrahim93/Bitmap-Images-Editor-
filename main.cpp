// Program: Main.cpp
// Purpose: Demonstrate use of bmplib for handling
//          bmp colored and grayscale images
//          Program load a gray image and store in another file
// Author:  Mohamed Alaa Eddin Mostafa - 20211083 B
// Author:  Islam Sayed -
// Author:  Yara -
// Date:    4/3/2022

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image1[SIZE][SIZE];
unsigned char newImage[SIZE][SIZE];
unsigned char RGBImage[SIZE][SIZE][RGB];
unsigned char newRGBImage[SIZE][SIZE][RGB];

void readGSImage() {
    char imageFileName[100];
    cout << "Enter The Source Image File Name:";
    cin >> imageFileName;
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

void saveGSImage() {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter The Target Image File Name:";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, newImage);
}
//------------------------------GREY SCALE BITMAP FILTERS------------------------------//

// BLACK AND WHITE Image #1
void GSblackAndWhite() {
    readGSImage();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] > 127)
                newImage[i][j] = 255;
            else
                newImage[i][j] = 0;
        }
    }
    saveGSImage();
}

// INVERT Image #2
void GSinvertImage() {
    readGSImage();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            newImage[i][j] = 255 - image[i][j];
        }
    }
    saveGSImage();
}

// Merge Image #3
void GSmerge() {
    readGSImage();
    char image2ndFileName[100];
    cout << "Enter The Second Source Image File Name:";
    cin >> image2ndFileName;
    strcat(image2ndFileName, ".bmp");
    readGSBMP(image2ndFileName, image1);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            newImage[i][j] = (image1[i][j] + image[i][j]) / 2;
        }
    }
    saveGSImage();
}

// FLIP Image #4
void GSflip() {
    readGSImage();
    int n;
    cout << "\n1.Horizontally\n"
            "2.Vertically\n"
            "Operation NO.";
    cin >> n;
    if (n == 1) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                newImage[i][j] = image[255 - i][j];
            }
        }
        saveGSImage();
    }
    if (n == 2) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                newImage[i][j] = image[i][255 - j];
            }
        }
        saveGSImage();
    }


}

// ROTATE Image #5
void GSrotate90() {
    readGSImage();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            newImage[i][j] = image[255 - j][i];
        }
    }
    saveGSImage();
}

void GSrotate180() {
    readGSImage();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            newImage[i][j] = image[255 - i][255 - j];
        }
    }
    saveGSImage();
}

void GSrotate270() {
    readGSImage();
    int k = 255;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            newImage[i][j] = image[j][k];
        }
        k--;
    }
    saveGSImage();
}

// Darken And Lighten Image #6
void GSdarkenAndLighten() {
    readGSImage();
    int n;
    cout << "\n1.Darken"
            "\n2.Lighten"
            "\nOperation No.";
    cin >> n;
    if (n == 2) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (image[i][j] >= SIZE / 2)
                    newImage[i][j] = image[i][j] + 64;
                else
                    newImage[i][j] = image[i][j] + 128;
            }
        }
        saveGSImage();
    }

    if (n == 1) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                newImage[i][j] = image[i][j] * 0.5;
            }
        }
        saveGSImage();
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
                newImage[i][j] = 255;
            } else
                newImage[i][j] = image1[i][j];
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
                newImage[i * 2][j * 2] = image[i][j];
                newImage[i * 2][(j * 2) + 1] = image[i][j];
                newImage[(i * 2) + 1][j * 2] = image[i][j];
                newImage[(i * 2) + 1][(j * 2) + 1] = image[i][j];
            }
        }
        saveGSImage();
    } else if (quarter == 2) {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 127; j < SIZE; j++) {
                newImage[i * 2][j * 2] = image[i][j];
                newImage[i * 2][(j * 2) + 1] = image[i][j];
                newImage[(i * 2) + 1][j * 2] = image[i][j];
                newImage[(i * 2) + 1][(j * 2) + 1] = image[i][j];
            }
        }
        saveGSImage();
    } else if (quarter == 3) {
        for (int i = SIZE / 2; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                newImage[((i - SIZE / 2) * 2)][j * 2] = image[i][j];
                newImage[((i - SIZE / 2) * 2)][(j * 2) + 1] = image[i][j];
                newImage[((i - SIZE / 2) * 2) + 1][j * 2] = image[i][j];
                newImage[((i - SIZE / 2) * 2) + 1][(j * 2) + 1] = image[i][j];
            }
        }
        saveGSImage();
    } else if (quarter == 4) {
        for (int i = SIZE / 2; i < SIZE; i++) {
            for (int j = SIZE / 2; j < SIZE; j++) {
                newImage[((i - SIZE / 2) * 2)][j * 2] = image[i][j];
                newImage[((i - SIZE / 2) * 2)][(j * 2) + 1] = image[i][j];
                newImage[((i - SIZE / 2) * 2) + 1][j * 2] = image[i][j];
                newImage[((i - SIZE / 2) * 2) + 1][(j * 2) + 1] = image[i][j];
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
                newImage[i][j] = image[row][col];
                col += 2;
            }
            row += 2;
        }
    }
    if (operation == 2) {
        for (int i = 0; i < SIZE / 3; i++) {
            int col = 0;
            for (int j = 0; j < SIZE / 3; j++) {
                newImage[i][j] = image[row][col];
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
                newImage[i][j] = image[row][col];
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
                newImage[i][j] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = SIZE / 2; j < SIZE; j++) {
                newImage[i][j] = image[i][255 - j];
            }
        }
        saveGSImage();
    }
    if (n == 2) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = SIZE / 2; j < SIZE; j++) {
                newImage[i][j] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                newImage[i][j] = image[i][255 - j];
            }
        }
        saveGSImage();
    }
    if (n == 3) {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE; j++) {
                newImage[i][j] = image[i][j];
            }
        }
        for (int i = SIZE / 2; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                newImage[i][j] = image[255 - i][j];
            }
        }
        saveGSImage();
    }
    if (n == 4) {
        for (int i = SIZE / 2; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                newImage[i][j] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE; j++) {
                newImage[i][j] = image[255 - i][j];
            }
        }
        saveGSImage();
    }
}

// SHUFFLE Image #B

// BLUR Image #C
void GSblur() {
    readGSImage();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            newImage[i][j] = (image[i - 2][j - 2] + image[i - 2][j - 1] + image[i - 2][j] + image[i - 2][j + 1] +
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
    cout << "Enter RGB Image Source File Name:";
    cin >> RGBImageFileName;
    strcat(RGBImageFileName, ".bmp");
    readRGBBMP(RGBImageFileName, RGBImage);
}

void saveRGBImage() {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter The Target Image File Name:";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeRGBBMP(imageFileName, newRGBImage);
}

void loadGSImageMenu() {
    char operation;
    cout << "\nChoose The Method You Want:"
            "\n1.Black & White Filter"
            "\n2.Invert Filter"
            "\n3.Merge Filter"
            "\n4.Flip Image"
            "\n5.Darken and Lighten Image"
            "\n6.Rotate Image"
            "\n7.Detect Image Edges"
            "\n8.Enlarge Image"
            "\n9.Shrink Image"
            "\na.Mirror 1/2 Image"
            "\nb.Shuffle Image"
            "\nc.Blur Image"
            "\n0.Exit"
            "\nOperation No.";
    cin >> operation;
    if (operation == '1') {
        GSblackAndWhite();
    }
    if (operation == '2') {
        GSinvertImage();
    }
    if (operation == '3') {
        GSmerge();
    }
    if (operation == '4') {
        GSflip();
    }
    if (operation == '5') {
        GSdarkenAndLighten();
    }
    if (operation == '6') {
        int n;
        cout << "1.Rotate 90 Clockwise\n"
                "2.Rotate 180 Clockwise\n"
                "3.Rotate 270 Clockwise\n"
                "4.Rotate 360 Clockwise\n"
                "Operation No.";
        cin >> n;
        if (n == 1)
            GSrotate90();
        else if (n == 2)
            GSrotate180();
        else if (n == 3)
            GSrotate270();
        else if (n == 4) {
            cout << "It Remains The Same Image";
        }

    }
    if (operation == '7') { // DETECT EDGES
        GSdetectEdges();
    }
    if (operation == '8') {
        GSenlarge();

    }
    if (operation == '9') { // SHRINK
        GSshrink();
    }
    if (operation == 'a') { // MIRROR 1/2
        GSmirror();
    }
    if (operation == 'b') { // SHUFFLE

    }
    if (operation == 'c') { // BLUR
        GSblur();
    }
    if (operation == '0') {
        cout << "Thanks For using Our Application";
    }
}


// Load Image
void loadRGBImageMenu() {
    char operation;
    cout << "\nChoose The Method You Want:"
            "\n1.Black & White Filter"
            "\n2.Invert Filter"
            "\n3.Merge Filter"
            "\n4.Flip Image"
            "\n5.Darken and Lighten Image"
            "\n6.Rotate Image"
            "\n7.Detect Image Edges"
            "\n8.Enlarge Image"
            "\n9.Shrink Image"
            "\na.Mirror 1/2 Image"
            "\nb.Shuffle Image"
            "\nc.Blur Image"
            "\n0.Exit"
            "\nOperation No.";
    cin >> operation;
    if (operation == '1') {

    }

    if (operation == '2') {

    }
    if (operation == '3') {

    }
    if (operation == '4') {

    }
    if (operation == '5') {

    }
    if (operation == '6') {
        int n;
        cout << "1.Rotate 90 Clockwise\n"
                "2.Rotate 180 Clockwise\n"
                "3.Rotate 270 Clockwise\n"
                "4.Rotate 360 Clockwise\n"
                "Operation No.";
        cin >> n;
        if (n == 1) {

        } else if (n == 2) {

        } else if (n == 3) {

        } else if (n == 4) {
            cout << "It Remains The Same Image";
        }

    }
    if (operation == '7') { // DETECT EDGES

    }
    if (operation == '8') {


    }
    if (operation == '9') { // SHRINK

    }
    if (operation == 'a') { // MIRROR 1/2

    }
    if (operation == 'b') { // SHUFFLE

    }
    if (operation == 'c') { // BLUR

    }
    if (operation == '0') {
        cout << "Thanks For using Our Application";
    }
}

int main() {
    int operation;
    cout << "Hello, User Welcome To Simple Bitmap Images Editor"
            "\nChoose Type of Images You Want To Filter"
            "\n1.Grey Scale Image"
            "\n2.RGB Image"
            "\n3.Exit"
            "\nOperation NO.";
    cin >> operation;
    if (operation == 1) {
        loadGSImageMenu();
    }
    else if(operation==2){
        loadRGBImageMenu();
    }
    else if(operation==3){
        cout<<"Thanks For Using Our Application";
    }else
        cout<<"Wrong Operation";
}