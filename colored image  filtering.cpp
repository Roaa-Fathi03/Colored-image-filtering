#include <iostream>
#include "bmplib.cpp"
#include "bmplib.h"
#include <string>
#include <cstring>

using namespace std;

unsigned char image[SIZE][SIZE][RGB];
unsigned char image2[SIZE][SIZE][RGB];
unsigned char image3[SIZE][SIZE][RGB];
unsigned char quarter1[SIZE][SIZE][RGB];
unsigned char quarter2[SIZE][SIZE][RGB];
unsigned char quarter3[SIZE][SIZE][RGB];
unsigned char quarter4[SIZE][SIZE][RGB];
unsigned char shuffledImage[SIZE][SIZE][RGB];

int choice5, choice8, quarterOrder, oldRows, oldCols, newRows, newCols, x, y;
string choice;
string choice4;
string choice_a;

//functions used in the program
void loadColoredImage();
void saveColoredImage();
void BlackWhiteFilter();
void invertImage();
void FlipImage();
void rotateImage();
void DetectImageEdges();
void enlargeImage();
void MirrorHalfImage();
void shuffleImage();
void mergeColoredImages();
void lightenAndDarkenColoredImage();
void shrinkColoredImage();
void blurColoredImage();

int main() {
    cout << "Hello our dear user." << endl;
    loadColoredImage(); // take the name of the image from the user and load it to apply the filters in
    cout << "Please, select a filter to apply or 0 to exit:  " << endl;
    cout << "1 - Black and white filter." << endl;
    cout << "2 - Invert image." << endl;
    cout << "3 - Merge images." << endl;
    cout << "4 - Flip image." << endl;
    cout << "5 - Darken and lighten image." << endl;
    cout << "6 - Rotate image." << endl;
    cout << "7 - Detect image Edges." << endl;
    cout << "8 - Enlarge image ." << endl;
    cout << "9 - Shrink image ." << endl;
    cout << "a - Mirror 1/2 Image ." << endl;
    cout << "b - Shuffle image ." << endl;
    cout << "c - Blur image ." << endl;
    cout << "s - Save the image to a file." << endl;
    cout << "0 - Exit." << endl;
    cin >> choice; // take the no. of the filter that user want to apply

    if (choice == "1") {
        BlackWhiteFilter();
        saveColoredImage();
    }
    else if (choice == "2"){
        invertImage();
        saveColoredImage();
    }
    else if (choice == "3"){
        mergeColoredImages();
    }
    else if (choice == "4") {
        FlipImage();
        saveColoredImage();
    }
    else if (choice == "5"){
        rotateImage();
        saveColoredImage();
    }
    else if (choice == "6"){
        lightenAndDarkenColoredImage();
        saveColoredImage();
    }
    else if (choice == "7") {
        DetectImageEdges();
        saveColoredImage();
    }
    else if (choice == "8"){
        enlargeImage();
    }
    else if (choice == "9"){
        shrinkColoredImage();
    }
    else if (choice == "a") {
        MirrorHalfImage();
        saveColoredImage();
    }
    else if (choice == "b"){
        shuffleImage();
    }
    else if (choice == "c"){
        blurColoredImage();
        saveColoredImage();
    }
    else if (choice == "0") {
        cout << " thank you for using out filter"; // exit
    }
    else
        cout << "Invalid character" ;
    //saveColoredImage(); // this function to save the changes on the image after apply the filter on it (colored version)
    return 0;
}
//------------------------------
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
//------------------------------
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

//------------------------------
//Filter 1 :Balck and White Image
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
//------------------------------
//Filter 2 : invert Image
void invertImage() {
    for (int i = 0; i < SIZE; i++) {
        // Looping through each single pixel in the original image,
        // and replacing each pixel with the one with the opposite level of brightness.
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                image[i][j][k] = 255 - image[i][j][k];
            }
        }
    }
}
//------------------------------
//Filter 3 :merge Image
void mergeColoredImages(){
    char imageFileName[100];

    //taking the second image from the user "image2"
    cout << "Enter the second source image file name: ";
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    readRGBBMP(imageFileName, image2);

    //taking the average of every 2 pixels from both images  into a new loaded "image3"
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image3[i][j][k] = (image[i][j][k] + image2[i][j][k]) / 2;
            }
        }
    }
    char  newImageFileName[100];

    //letting the user choose a name to the new image "image3"
    cout << "enter the target image file name: ";
    cin >> newImageFileName;

    //attaching .bmp to the name chosen by user and saving "image3"
    strcat(newImageFileName, ".bmp");
    writeRGBBMP(newImageFileName, image3);
}

//------------------------------
//Filter 4 : Flip Image
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
//------------------------------
//Filter 5 : Rotate image
void rotateImage() {
    cout << "Please, enter a number to select the clockwise degrees of rotation: " << endl; // Asking the user about the number of clockwise degrees.
    cout << "1 - 90 degrees." << endl;
    cout << "2 - 180 degrees." << endl;
    cout << "3 - 270 degrees." << endl;
    cin >> choice5;

    if (choice5 == 1) { // If the choice was clockwise 90 degrees.
        for (int i = 0; i < SIZE / 2; i++) {
            // Looping through each single pixel in half the original image,
            // and swapping each vertical pixel to be a horizontal one, and vice versa.
            for (int j = i; j < SIZE - i - 1; j++) {
                for (int k = 0; k < RGB; k++) {
                    int temp = image[i][j][k];
                    image[i][j][k] = image[j][SIZE - 1 - i][k];
                    image[j][SIZE - 1 - i][k] = image[SIZE - 1 - i][SIZE - 1 - j][k];
                    image[SIZE - 1 - i][SIZE - 1 - j][k] = image[SIZE - 1 - j][i][k];
                    image[SIZE - 1 - j][i][k] = temp;
                }
            }
        }

    }
    else if (choice5 == 2) { // If the choice was clockwise 180 degrees.
        for (int i = 0; i < SIZE / 2; i++) {
            // We rotate the original image by 90 clockwise degrees twice,
            // so we repeat the same process twice.
            for (int j = i; j < SIZE - i - 1; j++) {

                // Looping through each single pixel in half the original image,
                // and swapping each vertical pixel to be a horizontal one, and vice versa.
                for (int k = 0; k < RGB; k++) {
                    int temp = image[i][j][k];
                    image[i][j][k] = image[j][SIZE - 1 - i][k];
                    image[j][SIZE - 1 - i][k] = image[SIZE - 1 - i][SIZE - 1 - j][k];
                    image[SIZE - 1 - i][SIZE - 1 - j][k] = image[SIZE - 1 - j][i][k];
                    image[SIZE - 1 - j][i][k] = temp;
                }
            }
        }

        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = i; j < SIZE - i - 1; j++) {
                for (int k = 0; k < RGB; k++) {
                    int temp = image[i][j][k];
                    image[i][j][k] = image[j][SIZE - 1 - i][k];
                    image[j][SIZE - 1 - i][k] = image[SIZE - 1 - i][SIZE - 1 - j][k];
                    image[SIZE - 1 - i][SIZE - 1 - j][k] = image[SIZE - 1 - j][i][k];
                    image[SIZE - 1 - j][i][k] = temp;
                }
            }
        }

    }
    else { // If the choice was clockwise 270 degrees.
        for (int i = 0; i < SIZE / 2; i++) {
            // We rotate the original image by 90 clockwise degrees thrice, so we repeat the same process thrice.
            for (int j = i; j < SIZE - i - 1; j++) {
                // Looping through each single pixel in half the original image,
                // and swapping each vertical pixel to be a horizontal one, and vice versa.
                for (int k = 0; k < RGB; k++) {
                    int temp = image[i][j][k];
                    image[i][j][k] = image[j][SIZE - 1 - i][k];
                    image[j][SIZE - 1 - i][k] = image[SIZE - 1 - i][SIZE - 1 - j][k];
                    image[SIZE - 1 - i][SIZE - 1 - j][k] = image[SIZE - 1 - j][i][k];
                    image[SIZE - 1 - j][i][k] = temp;
                }
            }
        }

        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = i; j < SIZE - i - 1; j++) {
                for (int k = 0; k < RGB; k++) {
                    int temp = image[i][j][k];
                    image[i][j][k] = image[j][SIZE - 1 - i][k];
                    image[j][SIZE - 1 - i][k] = image[SIZE - 1 - i][SIZE - 1 - j][k];
                    image[SIZE - 1 - i][SIZE - 1 - j][k] = image[SIZE - 1 - j][i][k];
                    image[SIZE - 1 - j][i][k] = temp;
                }
            }
        }

        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = i; j < SIZE - i - 1; j++) {
                for (int k = 0; k < RGB; k++) {
                    int temp = image[i][j][k];
                    image[i][j][k] = image[j][SIZE - 1 - i][k];
                    image[j][SIZE - 1 - i][k] = image[SIZE - 1 - i][SIZE - 1 - j][k];
                    image[SIZE - 1 - i][SIZE - 1 - j][k] = image[SIZE - 1 - j][i][k];
                    image[SIZE - 1 - j][i][k] = temp;
                }
            }
        }
    }
}
//------------------------------
//Filter 6 : Lightening and Darkening an image
void lightenAndDarkenColoredImage(){
    char userInput;
    //letting the user choose between darkening or lightening the image
    cout << "Do you want to (d)arken or (l)ighten?";
    cin >> userInput;

    //lightening the color of the image by adding 255 to each pixel then dividing it by 2
    if (userInput == 'd'){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = image[i][j][k] *= 0.5;
                }
            }
        }
    }
        //darkening the color of the image by halving the pixel color
    else if (userInput == 'l'){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = (image[i][j][k] + 255) /2;
                }
            }
        }
    }
}

//------------------------------
//Filter 7 : Detect image Edges
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

//------------------------------
//Filter 8 : Enlarge Image
void enlargeImage() {
    cout << "Please, enter a number to determine which quarter to enlarge: " << endl; // Asking the user to determine which quarter to enlarge.
    cout << "1 - Right upper quarter." << endl;
    cout << "2 - Left upper quarter." << endl;
    cout << "3 - Right lower quarter." << endl;
    cout << "4 - Left lower quarter." << endl;
    cin >> choice8;

    if (choice8 == 1) { // If the chosen quarter is the first one.
        for (int i = 0, x = 0; i < SIZE; i += 2, x++) {
            // Looping through each single pixel in the original image,
            // and adding it to the first four pixels in the new one.
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

    }
    else if (choice8 == 2) { // If the chosen quarter is the second one.
        for (int i = 0, x = 0; i < SIZE; i += 2, x++) { // Looping through each single pixel in the original image,
            // and adding it to the four first pixels in the new one.
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

    }
    else if (choice8 == 3) { // If the chosen quarter is the third one.
        for (int i = 0, x = 128; i < SIZE; i += 2, x++) {
            // Looping through each single pixel in the original image,
            // and adding it to the first four pixels in the new one.
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

    }
    else { // If the chosen quarter is the fourth one.
        for (int i = 0, x = 128; i < SIZE; i += 2, x++) {
            // Looping through each pixel in the original image,
            // and adding it to the first four pixels in the new one.
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
//------------------------------
//Filter 9 : Shrink Image
void shrinkColoredImage(){
    int shrinkSize;

    //choosing the shrinkage size
    cout << "please choose the shrinkage size:\n" << "1/(2)\n" << "1/(3)\n" << "1/(4)\n" << ">> ";
    cin >> shrinkSize;

    //skipping the shrink size number entered by the user and loading it into a new loaded image "image2"
    for (int i = 0, x = 0; i < SIZE; i += shrinkSize, ++x) {
        for (int j = 0, y = 0; j < SIZE; j += shrinkSize, ++y) {
            for (int k = 0; k < RGB; k ++) {
                image2[x][y][k] = image[i][j][k];
            }
        }
    }
    //turning the rest of the pixels into white color
    for (int i = (256 / shrinkSize), x = 0, w = (256 / shrinkSize); i < SIZE; ++i, x++, ++w) {
        for (int j = (256 / shrinkSize), y = (256 / shrinkSize), z = 0; j < SIZE; ++j, y++, ++z) {
            for (int k = 0; k < RGB; ++k) {
                image2[i][j][k] = 255;
                image2[x][y][k] = 255;
                image2[w][z][k] = 255;
            }
        }
    }

    char  imageFileName[100];

    cout << "enter the target image file name: ";
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image2);
}
//------------------------------
//Filter a : Mirror Half Image
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
                    //mirror the right half
                }
            }
        }
    }
    else if (choice_a == "2") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < (SIZE / 2); j++) {
                for (int k = 0; k < RGB; k++) {
                    // we loop on the half of the columns to reflect the right or the left of the image
                    image[i][SIZE - 1 - j][k] = image[i][j][k];
                    // we take the value of the left pixels and put it on the right in the same row
                    //mirror the left half
                }
            }
        }
    }
    else if (choice_a == "3") {
        for (int i = 0; i < (SIZE / 2); i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++) {
                    // we loop on the half of the rows to reflect
                    // the upper half or the lower half of the image
                    image[SIZE - 1 - i][j][k] = image[i][j][k];
                    // we take the value of the upper pixels and put it on the lower in the same column
                    //mirror the upper half
                }
            }
        }
    }
    else if (choice_a == "4") {
        for (int i = 0; i < (SIZE / 2); i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++) {
                    // we loop on the half of the rows to reflect
                    // the upper half or the lower half of the image
                    image[i][j][k] = image[SIZE - 1 - i][j][k];
                    // we take the value of the lower pixels and put it on the upper in the same column
                    //mirror the lower half
                }
            }
        }
    }
}
//------------------------------
//Filter b :Suffle Image
void shuffleImage() {
    for (int l = 1; l < 5; l++) {
        cout << "Please, enter the " << l << " quarter order: " << endl; // Asking about the new quarters order for four times.
        cin >> quarterOrder;

        if (quarterOrder == 1 || quarterOrder == 2) {
            // If the chosen quarter is 1 or 2,
            // then we set the old rows (original image) reference to 0.
            oldRows = 0;
        }
        else { // Otherwise, it is set to 128.
            oldRows = 128;
        }

        if (quarterOrder == 1 || quarterOrder == 3) {
            // If the chosen quarter is 1 or 3,
            // then we set the old columns (original image) reference to 0.
            oldCols = 0;
        }
        else { // Otherwise, it is set to 128.
            oldCols = 128;
        }

        if (l == 1 || l == 2) {
            // If the chosen quarter is 1 or 2,
            // then we set the new rows (shuffled image) reference to 0.
            newRows = 0;
        }
        else { // Otherwise, it is set to 128.
            newRows = 128;
        }

        if (l == 1 || l == 3) { // If the chosen quarter is 1 or 2,
            // then we set the new columns (shuffled image) reference to 0.
            newCols = 0;
        }
        else { // Otherwise, it is set to 128.
            newCols = 128;
        }

        if (quarterOrder == 1) { // If the chosen quarter is 1.
            x = newRows; // We set the counter x to the value of the new rows refernce,
            // and adding each single pixel in the original image to the shuffled one.
            for (int i = 0; i < 128; i++, x++) {
                y = newCols; // Counter y is set the value of the new columns refernce.
                for (int j = 0; j < 128; j++, y++) {
                    for (int k = 0, z = 0; k < RGB; k++, z++)
                        shuffledImage[x][y][z] = image[i][j][k];
                }
            }

        }
        else if (quarterOrder == 2) { // If the chosen quarter is 2.
            x = newRows; // We set the counter x to the value of the new rows refernce,
            // and adding each single pixel in the original image to the shuffled one.
            for (int i = 0; i < 128; i++, x++) {
                y = newCols; // Counter y is set the value of the new columns refernce.
                for (int j = 128; j < 256; j++, y++) {
                    for (int k = 0, z = 0; k < RGB; k++, z++)
                        shuffledImage[x][y][z] = image[i][j][k];
                }
            }

        }
        else if (quarterOrder == 3) { // If the chosen quarter is 3.
            x = newRows; // We set the counter x to the value of the new rows refernce,
            // and adding each single pixel in the original image to the shuffled one.
            for (int i = 128; i < 256; i++, x++) {
                y = newCols; // Counter y is set the value of the new columns refernce.
                for (int j = 0; j < 128; j++, y++) {
                    for (int k = 0, z = 0; k < RGB; k++, z++) {
                        shuffledImage[x][y][z] = image[i][j][k];
                    }
                }
            }

        }
        else { // If the chosen quarter is 4.
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
    char newImage[100];
    cout << "Please, enter the target image file name: " << endl; // Asking about the new image name.
    cin >> newImage;
    strcat(newImage, ".bmp"); // Adding .bmp extension to load, and write it.
    writeRGBBMP(newImage, shuffledImage); // Writing and creating the new image.
}
//------------------------------
//Filter c : Blur image
void blurColoredImage(){
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                //taking the average of the surrounding pixels of each pixel
                image[i][j][k] = (image[i][j][k]+image[i-1][j-1][k]+image[i-1][j][k]+image[i+1][j][k]+image[i][j-1][k]+image[i][j+1][k]+image[i-1][j+1][k]+image[i][j+1][k]+image[i+1][j+1][k]+image[i-2][j-2][k]+image[i-2][j][k]+image[i+2][j][k]+image[i][j-2][k]+image[i][j+2][k]+image[i-2][j+2][k]+image[i][j+2][k]+image[i+2][j+2][k]) /17 ;

            }
        }
    }
}
