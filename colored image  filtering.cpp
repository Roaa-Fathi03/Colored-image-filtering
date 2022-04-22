#include <iostream>
#include <cstring>
#include "bmplib.cpp"
#include "bmplib.h"
#include <string>

using namespace std;

unsigned char image[SIZE][SIZE][RGB];
unsigned char quarter1[SIZE][SIZE][RGB];
unsigned char quarter2[SIZE][SIZE][RGB];
unsigned char quarter3[SIZE][SIZE][RGB];
unsigned char quarter4[SIZE][SIZE][RGB];
unsigned char shuffledImage[SIZE][SIZE][RGB];

int choice8, quarterOrder, oldRows, oldCols, newRows, newCols, x, y;

string choice;
string choice4;
string choice_a;

void loadColoredImage();
void saveColoredImage();
void BlackWhiteFilter();
void FlipImage();
void MirrorHalfImage();
void DetectImageEdges();
void enlargeImage();

int main(){
    cout << "hello our dear user " << endl;
    loadColoredImage(); // take the name of the image from the user and load it to apply the filters in
    cout << "please select a filter to apply or 0 to exit:  " << endl;
    cout << "1- Black and white Filter." << endl;
    cout << "2- Invert Filter." << endl;
    cout << "3- Merge Filter." << endl;
    cout << "4- Flip Image ." << endl;
    cout << "5- Darken and Lighten Filter." << endl;
    cout << "6- Rotate Image." << endl;
    cout << "7- Detect Image Edges." << endl;
    cout << "8- Enlarge Image ." << endl;
    cout << "9- Shrink Image ." << endl;
    cout << "a- Mirror 1/2 Image ." << endl;
    cout << "b- Shuffle Image ." << endl;
    cout << "c- Blur Image ." << endl;
    cout << "s- Save the Image to a file." << endl;
    cout << "0- Exit ." << endl;
    cin >> choice; // take the no. of the filter that user want to apply
    if (choice == "1") {
        BlackWhiteFilter();
    }
    else if (choice == "2"){
        //invertImage();
    }
    else if (choice == "3"){
        cout << "hello";
    }
    else if (choice == "4") {
        FlipImage();
    }
    else if (choice == "5"){
        //rotateImage();
    }
    else if (choice == "6"){
        cout << "hello";
    }
    else if (choice == "7") {
        DetectImageEdges();
    }
    else if (choice == "8"){
        enlargeImage();
    }
    else if (choice == "9"){
        cout << "hello";
    }
    else if (choice == "a") {
        MirrorHalfImage();
    }
    else if (choice == "b"){
        //shuffleImage();
    }
    else if (choice == "c"){
        cout << "hello";
    }
    else if (choice == "0") {
        cout << " thank you for using out filter"; // exit
    }
    saveColoredImage(); // this function to save the changes on the image after apply the filter on it (colored version)
    return 0;
}
//_______________
void loadColoredImage(){
    // take the name of the image from the user and load it to apply the filters in
    char image_file_name[100];

    // Get colored image file name
    cout << " Enter the source image file name: ";
    cin >> image_file_name;

    // Add to it .bmp extension and load image
    strcat(image_file_name, ".bmp");
    readRGBBMP(image_file_name, image);
}
//_______________
void saveColoredImage() {
    // this function to save the changes on the image after apply the filter on it (colored version)
    char image_file_name[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> image_file_name;

    // Add to it .bmp extension and load image
    strcat(image_file_name, ".bmp");
    writeRGBBMP(image_file_name, image);
}

//_______________
void BlackWhiteFilter() {
    double gray_avg;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                gray_avg = 0;
                // we calculate the average of the three colors to get the gray version
                // then invert it into black and white
                gray_avg += (image[i][j][0] * 0.299) + (image[i][j][1] * 0.587) + (image[i][j][2] * 0.114);
                image[i][j][k] = gray_avg;
                // we compare the average of gray in each pixel
                // with 127 so if it is greater will be white otherwise will be black
                if (image[i][j][k] > 127) {
                    image[i][j][k] = 255;
                }
                else {
                    image[i][j][k] = 0;

                }
            }
        }
    }
}


//_______________
void FlipImage() {
    cout << " please select a number to determine how to flip " << endl;
    cout << "1-  Horizontal Flip. " << endl;
    cout << "2-  Vertical Flip. " << endl;
    cin >> choice4;// take the input from the user to flip the image horizontally or vertically
    if (choice4 == "1") {
        for (int i = 0; i < (SIZE / 2); i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++) {
                    // here we loop on the half of the rows
                    // because we want to swap the elements on each row to flip it 180 deg
                    swap(image[i][j][k], image[SIZE - 1 - i][j][k]);
                    // then we swap the two indexes together
                }
            }
        }
    }
    else if (choice4 == "2") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < (SIZE / 2); j++) {
                for (int k = 0; k < RGB; k++) {
                    // here we loop on the half of the columns
                    // because we want to swap the elements on each column to do as reflection
                    swap(image[i][j][k], image[i][SIZE - 1 - j][k]);
                    // then we swap the two indexes together

                }
            }
        }
    }
}
//-----------------------------------------------
void DetectImageEdges() {
    BlackWhiteFilter();// we call the black and white function
    // because we compare each index and the next to it with 0 and 255
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                // we check each two adjacent pixels
                // if they are the same put each equals to 255 (white) otherwise equals 0 (black)
                if (image[i][j][k] == image[i][j + 1][k]) {
                    image[i][j][k] = 255;
                }
                else if (image[i][j][k] != image[i][j + 1][k] ) {
                    image[i][j][k] = 0;
                }
            }
        }
    }
}

//-----------------------------------------------
void enlargeImage() {
    cout << "Please, enter a number to determine which quarter to enlarge: " << endl; // Asking the user to determine which quarter to enlarge.
    cout << "1 - Right upper quarter." << endl;
    cout << "2 - Left upper quarter." << endl;
    cout << "3 - Right lower quarter." << endl;
    cout << "4 - Left lower quarter." << endl;
    cin >> choice8;

    if (choice8 == 1) { // If the chosen quarter is the first one.
        for (int i = 0, x = 0; i < SIZE; i += 2, x++) { // Looping through each single pixel in the original image, and adding it to the first four pixels in the new one.
            for (int j = 0, y = 0; j < SIZE; j += 2, y++) {
                for (int k = 0, z = 0; k < RGB; k++, z++) {
                    quarter1[i][j][k] = image[x][y][z];
                    quarter1[i][j + 1][k] = image[x][y][z];
                    quarter1[i + 1][j][k] = image[x][y][z];
                    quarter1[i + 1][j + 1][k] = image[x][y][z];
                }
            }
        }
        char newImage[100];
        cout << "Please, enter the target image file name: " << endl; // Asking about the new image name.
        cin >> newImage;
        strcat(newImage, ".bmp"); // Adding .bmp extension to load and, write it.
        writeRGBBMP(newImage, quarter1); // Writing and creating the new image.

    } else if (choice8 == 2) { // If the chosen quarter is the second one.
        for (int i = 0, x = 0; i < SIZE; i += 2, x++) { // Looping through each single pixel in the original image, and adding it to the four first pixels in the new one.
            for (int j = 0, y = 128; j < SIZE; j += 2, y++) {
                for (int k = 0, z = 0; k < RGB; k++, z++) {
                    quarter2[i][j][k] = image[x][y][z];
                    quarter2[i][j + 1][k] = image[x][y][z];
                    quarter2[i + 1][j][k] = image[x][y][z];
                    quarter2[i + 1][j + 1][k] = image[x][y][z];
                }
            }
        }
        char newImage[100];
        cout << "Please, enter the target image file name: " << endl; // Asking about the new image name.
        cin >> newImage;
        strcat(newImage, ".bmp"); // Adding .bmp extension to load and, write it.
        writeRGBBMP(newImage, quarter2); // Writing and creating the new image.

    } else if (choice8 == 3) { // If the chosen quarter is the third one.
        for (int i = 0, x = 128; i < SIZE; i += 2, x++) { // Looping through each single pixel in the original image, and adding it to the first four pixels in the new one.
            for (int j = 0, y = 0; j < SIZE; j += 2, y++) {
                for (int k = 0, z = 0; k < RGB; k++, z++) {
                    quarter3[i][j][k] = image[x][y][z];
                    quarter3[i][j + 1][k] = image[x][y][z];
                    quarter3[i + 1][j][k] = image[x][y][z];
                    quarter3[i + 1][j + 1][k] = image[x][y][z];
                }
            }
        }
        char newImage[100];
        cout << "Please, enter the target image file name: " << endl; // Asking about the new image name.
        cin >> newImage;
        strcat(newImage, ".bmp"); // Adding .bmp extension to load, write it.
        writeRGBBMP(newImage, quarter3); // Writing and creating the new image.

    } else { // If the chosen quarter is the fourth one.
        for (int i = 0, x = 128; i < SIZE; i += 2, x++) { // Looping through each pixel in the original image, and adding it to the first four pixels in the new one.
            for (int j = 0, y = 128; j < SIZE; j += 2, y++) {
                for (int k = 0, z = 0; k < RGB; k++, z++) {
                    quarter4[i][j][k] = image[x][y][z];
                    quarter4[i][j + 1][k] = image[x][y][z];
                    quarter4[i + 1][j][k] = image[x][y][z];
                    quarter4[i + 1][j + 1][k] = image[x][y][z];
                }
            }
        }
        char newImage[100];
        cout << "Please, enter the target image file name: " << endl; // Asking about the new image name.
        cin >> newImage;
        strcat(newImage, ".bmp"); // Adding .bmp extension to load, and write it.
        writeRGBBMP(newImage, quarter4); // Writing and creating the new image.
    }
}
//-----------------------------------------------
void MirrorHalfImage() {
    cout << "please select which half you want: " << endl;
    cout << "1- Right half" << endl;
    cout << "2- left half" << endl;
    cout << "3- Upper half" << endl;
    cout << "4- lower half" << endl;
    cin >> choice_a; // take the input from the user to miror which half
    if (choice_a == "1") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < (SIZE / 2); j++) {
                for (int k = 0; k < RGB ; k++) {
                    // we loop on the half of the columns to reflect the right or the left of the image
                    image[i][j][k] = image[i][SIZE - 1 - j][k];
                    // we take the value of the right pixels and put it on the left in the same row

                }
            }
        }
    }
    if (choice_a == "2") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < (SIZE / 2); j++) {
                for (int k = 0; k < RGB; k++) {
                    // we loop on the half of the columns to reflect the right or the left of the image
                    image[i][SIZE - 1 - j][k] = image[i][j][k];
                    // we take the value of the left pixels and put it on the right in the same row
                }
            }
        }
    }
    if (choice_a == "3") {
        for (int i = 0; i < (SIZE / 2); i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++) {
                    // we loop on the half of the rows to reflect
                    // the upper half or the lower half of the image
                    image[SIZE - 1 - i][j][k] = image[i][j][k];
                    // we take the value of the upper pixels and put it on the lower in the same column
                }
            }
        }
    }
    if (choice_a == "4") {
        for (int i = 0; i < (SIZE / 2); i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++) {
                    // we loop on the half of the rows to reflect
                    // the upper half or the lower half of the image
                    image[i][j][k] = image[SIZE - 1 - i][j][k];
                    // we take the value of the lower pixels and put it on the upper in the same column
                }
            }
        }
    }
}
//-----------------------------------------------
void shuffleImage() {
    for (int l = 1; l < 5; l++) {
        cout << "Please, enter the " << l << " quarter order: " << endl; // Asking about the new quarters order for four times.
        cin >> quarterOrder;

        if (quarterOrder == 1 || quarterOrder == 2) { // If the chosen quarter is 1 or 2, then we set the old rows (original image) reference to 0.
            oldRows = 0;
        } else { // Otherwise, it is set to 128.
            oldRows = 128;
        }

        if (quarterOrder == 1 || quarterOrder == 3) { // If the chosen quarter is 1 or 3, then we set the old columns (original image) reference to 0.
            oldCols = 0;
        } else { // Otherwise, it is set to 128.
            oldCols = 128;
        }

        if (l == 1 || l == 2) { // If the chosen quarter is 1 or 2, then we set the new rows (shuffled image) reference to 0.
            newRows = 0;
        } else { // Otherwise, it is set to 128.
            newRows = 128;
        }

        if (l == 1 || l == 3) { // If the chosen quarter is 1 or 2, then we set the new columns (shuffled image) reference to 0.
            newCols = 0;
        } else { // Otherwise, it is set to 128.
            newCols = 128;
        }

        if (quarterOrder == 1) { // If the chosen quarter is 1.
            x = newRows; // We set the counter x to the value of the new rows refernce, and adding each single pixel in the original image to the shuffled one.
            for (int i = 0; i < 128; i++, x++) {
                y = newCols; // Counter y is set the value of the new columns refernce.
                for (int j = 0; j < 128; j++, y++) {
                    for (int k = 0, z = 0; k < RGB; k++, z++)
                        shuffledImage[x][y][z] = image[i][j][k];
                }
            }
        } else if (quarterOrder == 2) { // If the chosen quarter is 2.
            x = newRows; // We set the counter x to the value of the new rows refernce, and adding each single pixel in the original image to the shuffled one.
            for (int i = 0; i < 128; i++, x++) {
                y = newCols; // Counter y is set the value of the new columns refernce.
                for (int j = 128; j < 256; j++, y++) {
                    for (int k = 0, z = 0; k < RGB; k++, z++)
                        shuffledImage[x][y][z] = image[i][j][k];
                }
            }

        } else if (quarterOrder == 3) { // If the chosen quarter is 3.
            x = newRows; // We set the counter x to the value of the new rows refernce, and adding each single pixel in the original image to the shuffled one.
            for (int i = 128; i < 256; i++, x++) {
                y = newCols; // Counter y is set the value of the new columns refernce.
                for (int j = 0; j < 128; j++, y++) {
                    for (int k = 0, z = 0; k < RGB; k++, z++) {
                        shuffledImage[x][y][z] = image[i][j][k];
                    }
                }
            }

        } else { // If the chosen quarter is 4.
            x = newRows; // We set the counter x to the value of the new rows refernce, and adding each single pixel in the original image to the shuffled one.
            for (int i = 128; i < 256; i++, x++) {
                y = newCols; // Counter y is set the value of the new columns refernce.
                for (int j = 128; j < 256; j++, y++) {
                    for (int k = 0, z = 0; k < 128; k++, z++) {
                        shuffledImage[x][y][z] = image[i][j][k];
                    }
                }
            }
        }
    }
}
char newImage[100];
    cout << "Please, enter the target image file name: " << endl; // Asking about the new image name.
    cin >> newImage;
    
    strcat(newImage, ".bmp"); // Adding .bmp extension to load, and write it.
    writeRGBBMP(newImage, shuffledImage); // Writing and creating the new image.
//-----------------------------------------------
