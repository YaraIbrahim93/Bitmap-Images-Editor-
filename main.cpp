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

void saveImage() {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter The Target Image File Name:";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, newImage);
}

// BLACK AND WHITE Image #1
void blackAndWhite() {

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] > 127)
                newImage[i][j] = 255;
            else
                newImage[i][j] = 0;
        }
    }
    saveImage();
}

// INVERT Image #2
void invertImage() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            newImage[i][j] = 255 - image[i][j];
        }
    }
    saveImage();
}

// Merge Image #3
void merge() {
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
    saveImage();
}

// FLIP Image #4
void flip() {
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
        saveImage();
    }
    if (n == 2) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                newImage[i][j] = image[i][255 - j];
            }
        }
        saveImage();
    }


}

// ROTATE Image #5
void rotate90() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            newImage[i][j] = image[255 - j][i];
        }
    }
    saveImage();
}

void rotate180() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            newImage[i][j] = image[255 - i][255 - j];
        }
    }
    saveImage();
}

void rotate270() {
    int k = 255;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            newImage[i][j] = image[j][k];
        }
        k--;
    }
    saveImage();
}

// Darken And Lighten Image #6
void darkenAndLighten() {
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
        saveImage();
    }

    if (n == 1) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                newImage[i][j] = image[i][j] * 0.5;
            }
        }
        saveImage();
    }
}

// Detect Images Edges #7
void detectEdges() {
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
    saveImage();
}
// Enlarge Image #8
void enlarge() {
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
        saveImage();
    } else if (quarter == 2) {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 127; j < SIZE; j++) {
                newImage[i * 2][j * 2] = image[i][j];
                newImage[i * 2][(j * 2) + 1] = image[i][j];
                newImage[(i * 2) + 1][j * 2] = image[i][j];
                newImage[(i * 2) + 1][(j * 2) + 1] = image[i][j];
            }
        }
        saveImage();
    } else if (quarter == 3) {
        for (int i = SIZE / 2; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                newImage[((i - SIZE / 2) * 2)][j * 2] = image[i][j];
                newImage[((i - SIZE / 2) * 2)][(j * 2) + 1] = image[i][j];
                newImage[((i - SIZE / 2) * 2) + 1][j * 2] = image[i][j];
                newImage[((i - SIZE / 2) * 2) + 1][(j * 2) + 1] = image[i][j];
            }
        }
        saveImage();
    } else if (quarter == 4) {
        for (int i = SIZE / 2; i < SIZE; i++) {
            for (int j = SIZE / 2; j < SIZE; j++) {
                newImage[((i - SIZE / 2) * 2)][j * 2] = image[i][j];
                newImage[((i - SIZE / 2) * 2)][(j * 2) + 1] = image[i][j];
                newImage[((i - SIZE / 2) * 2) + 1][j * 2] = image[i][j];
                newImage[((i - SIZE / 2) * 2) + 1][(j * 2) + 1] = image[i][j];
            }
        }
        saveImage();
    }
}

// SHRINK Image #9
void shrink() {
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
        saveImage();
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
        saveImage();
    }
}

// Mirror Image #A
void mirror() {
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
        saveImage();
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
        saveImage();
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
        saveImage();
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
        saveImage();
    }
}

// SHUFFLE Image #B

// BLUR Image #C
void blur() {
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
    saveImage();
}

// Load Image
void loadImage() {
    char operation;
    char imageFileName[100];
    cout << "Hello, User Welcome To Our Simple PhotoShop Application"
            "\nChoose The Method You Want:"
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
    cout << "Enter The Source Image File Name:";
    cin >> imageFileName;
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);

    if (operation == '1') {
        blackAndWhite();
    }
    if (operation == '2') {
        invertImage();
    }
    if (operation == '3') {
        merge();
    }
    if (operation == '4') {
        flip();
    }
    if (operation == '5') {
        darkenAndLighten();
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
            rotate90();
        else if (n == 2)
            rotate180();
        else if (n == 3)
            rotate270();
        else if (n == 4) {
            // Pass
        }

    }
    if (operation == '7') { // DETECT EDGES
        detectEdges();
    }
    if (operation == '8') {
        enlarge();

    }
    if (operation == '9') { // SHRINK
        shrink();
    }
    if (operation == 'a') { // MIRROR 1/2
        mirror();
    }
    if (operation == 'b') { // SHUFFLE

    }
    if (operation == 'c') { // BLUR
        blur();
    }
    if (operation == '0') {

    }
}

// Save Image


int main() {
    loadImage();
    cout << "\nDone!, Thanks For Using Our Application";
    return 0;
}


