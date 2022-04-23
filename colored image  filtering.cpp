/* Title: colored image filters
 * Purpose of the code: how to work on the image after load it into 3D array
 * and how to loop on the row, columns and colors
 * Author 1: Farahhmagedd03
 * Author 2: Shaimaa 1111
 * Author 3: Roaa-Fathi03*/

#include <iostream>
#include <cstring>
#include "bmplib.cpp"
#include "bmplib.h"
#include <string>

using namespace std;

unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char image3[SIZE][SIZE];
unsigned char quarter1[SIZE][SIZE];
unsigned char quarter2[SIZE][SIZE];
unsigned char quarter3[SIZE][SIZE];
unsigned char quarter4[SIZE][SIZE];
unsigned char shuffledImage[SIZE][SIZE];

int choice5, choice8, quarterOrder,oldRows, oldCols, newRows, newCols, x, y;

string choice;
string choice4;
string choice_a;

//functions used in the program
void loadGrayImage();
void saveGrayImage();
void BlackWhiteFilter();
void invertImage();
void mergeImages();
void FlipImage();
void rotateImage();
void lightenAndDarkenImage();
void DetectImageEdges();
void enlargeImage();
void shrinkImage();
void MirrorHalfImage();
void shuffleImage();
void blurImage();

int main(){
    cout << "hello our dear user " << endl;
    loadGrayImage(); // take the name of the image from the user and load it to apply the filters in
    cout << "please select a filter to apply or 0 to exit:  " << endl;
    cout << "1- Black and white Filter." << endl;
    cout << "2- Invert Filter." << endl;
    cout << "3- Merge Filter." << endl;
    cout << "4- Flip Image ." << endl;
    cout << "5- Rotate Image." << endl;
    cout << "6- Darken and Lighten Filter ." << endl;
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
        saveGrayImage();
    }
    else if (choice == "2"){
        invertImage();
        saveGrayImage();
    }
    else if (choice == "3"){
        mergeImages();
    }
    else if (choice == "4") {
        FlipImage();
        saveGrayImage();
    }
    else if (choice == "5"){
        rotateImage();
        saveGrayImage();
    }
    else if (choice == "6"){
        lightenAndDarkenImage();
        saveGrayImage();
    }
    else if (choice == "7") {
        DetectImageEdges();
        saveGrayImage();
    }
    else if (choice == "8"){
        enlargeImage();
    }
    else if (choice == "9"){
        shrinkImage();
    }
    else if (choice == "a") {
        MirrorHalfImage();
        saveGrayImage();
    }
    else if (choice == "b"){
        shuffleImage();
    }
    else if (choice == "c"){
        blurImage();
        saveGrayImage();
    }
    else if (choice == "0") {
        cout << " thank you for using out filter"; // exit
    }
    else
        cout << "Invalid character" ;
    //saveGrayImage(); // this function to save the changes on the image after apply the filter on it (gray version)
}
//-----------------------------------------------
void loadGrayImage(){
 char image_file_name[100];

    // Get gray scale image file name
    cout << "Please enter the source file name: ";
    cin >> image_file_name;

    // Add to it .bmp extension and load image
    strcat(image_file_name, ".bmp");
    readGSBMP(image_file_name, image);
}
//-----------------------------------------------
void saveGrayImage() {
    char image_file_name[100];

    // Get gray scale image target file name
    cout << "Please enter the target image file name: ";
    cin >> image_file_name;

    // Add to it .bmp extension and load image
    strcat(image_file_name, ".bmp");
    writeGSBMP(image_file_name, image);
}
//-----------------------------------------------
// Filter 1: Black and White Filter
void BlackWhiteFilter() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // we compare the average of gray in each pixel
            // with 127 so if it is greater will be white otherwise will be black
            if (image[i][j] > 127) {
                image[i][j] = 255;
            }
            else {
                image[i][j] = 0;
            }
        }
    }
}
//-----------------------------------------------
// Filter 2: Invert Filter
void invertImage() {
    // Looping through each single pixel in the original image, and replacing each white pixel to a black one, each black pixel to a white one, and each pixel with the one with the opposite level of brightness.
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] == 0) {
                image[i][j] = 255;
            }
            else if (image [i][j] == 255) {
                image[i][j] = 0;
            }
            else {
                image[i][j] = 255 - image[i][j];
            }
        }
    }
}
//-----------------------------------------------
//Filter 3: Merge Images
void mergeImages(){
    char imageFileName[100];

    //taking the second image from the user "image2"
    cout << "Enter the second source image file name: ";
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image2);

    //taking the average of every 2 pixels from both images  into a new loaded "image3"
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image3[i][j] = (image[i][j] + image2[i][j]) / 2;
        }
    }
    char newImageFileName[100];

    //letting the user choose a name to the new image "image3"
    cout << "enter the target image file name: ";
    cin >> newImageFileName;

    //attaching .bmp to the name chosen by user and saving "image3"
    strcat(newImageFileName, ".bmp");
    writeGSBMP(newImageFileName, image3);
}
//-----------------------------------------------
// Filter 4: Flip Filter
void FlipImage() {
    cout << " please select a number to determine how to flip " << endl;
    cout << "1- Flip Horizontally. " << endl;
    cout << "2- Flip Vertically. " << endl;
    cin >> choice4; // take the input from the user to flip the image horizontally or vertically
    if (choice4 == "1") {
        for (int i = 0; i < (SIZE / 2); i++) {
            for (int j = 0; j < SIZE; j++) {
                // here we loop on the half of the rows
                // because we want to swap the elements on each row to flip it 180 deg
                swap(image[i][j], image[SIZE - 1 - i][j]);
            }
        }
    }
    else if (choice4 == "2") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < (SIZE / 2); j++) {
                // here we loop on the half of the columns
                // because we want to swap the elements on each column to do as reflection
                swap(image[i][j], image[i][SIZE - 1 - j]);
            }
        }
    }
}
//-----------------------------------------------
// Filter 5: Rotate Filter
void rotateImage() {
    cout << "Please, enter a number to select the clockwise degrees of rotation: " << endl; // Asking the user about the number of clockwise degrees.
    cout << "1 - 90 degrees." << endl;
    cout << "2 - 180 degrees." << endl;
    cout << "3 - 270 degrees." << endl;
    cin >> choice5;

    if (choice5 == 1) { // If the choice was clockwise 90 degrees.
        for (int i = 0; i < SIZE / 2; i++) { // Looping through each single pixel in half the original image, and swapping each vertical pixel to be a horizontal one, and vice versa.
            for (int j = i; j < SIZE - i - 1; j++) {
                int temp = image[i][j];
                image[i][j] = image[j][SIZE - 1 - i];
                image[j][SIZE - 1 - i] = image[SIZE - 1 - i][SIZE - 1 - j];
                image[SIZE - 1 - i][SIZE - 1 - j] = image[SIZE - 1 - j][i];
                image[SIZE - 1 - j][i] = temp;
            }
        }
    }

    else if (choice5 == 2) { // If the choice was clockwise 180 degrees.
        for (int i = 0; i < SIZE; i++) // We rotate the original image by 90 clockwise degrees twice, so we repeat the same process twice.
            for (int j = 0, k = SIZE - 1; j < k; j++, k--) // Looping through each single pixel in half the original image, and swapping each vertical pixel to be a horizontal one, and vice versa.
                swap(image[j][i], image[k][i]);

        for (int i = 0; i < SIZE; i++)
            for (int j = i; j < SIZE; j++)
                swap(image[i][j], image[j][i]);

        for (int i = 0; i < SIZE; i++)
            for (int j = 0, k = SIZE - 1; j < k; j++, k--)
                swap(image[j][i], image[k][i]);

        for (int i = 0; i < SIZE; i++)
            for (int j = i; j < SIZE; j++)
                swap(image[i][j], image[j][i]);
    }
    else { // If the choice was clockwise 270 degrees.
        for (int i = 0; i < SIZE / 2; i++) { // We rotate the original image by 90 clockwise degrees thrice, so we repeat the same process thrice.
            for (int j = i; j < SIZE - i - 1; j++) { // Looping through each single pixel in half the original image, and swapping each vertical pixel to be a horizontal one, and vice versa.
                int temp = image[i][j];
                image[i][j] = image[j][SIZE - 1 - i];
                image[j][SIZE - 1 - i] = image[SIZE - 1 - i][SIZE - 1 - j];
                image[SIZE - 1 - i][SIZE - 1 - j] = image[SIZE - 1 - j][i];
                image[SIZE - 1 - j][i] = temp;
            }
        }
        for (int i = 0; i < SIZE; i++)
            for (int j = 0, k = SIZE - 1; j < k; j++, k--)
                swap(image[j][i], image[k][i]);

        for (int i = 0; i < SIZE; i++)
            for (int j = i; j < SIZE; j++)
                swap(image[i][j], image[j][i]);

        for (int i = 0; i < SIZE; i++)
            for (int j = 0, k = SIZE - 1; j < k; j++, k--)
                swap(image[j][i], image[k][i]);

        for (int i = 0; i < SIZE; i++)
            for (int j = i; j < SIZE; j++)
                swap(image[i][j], image[j][i]);
    }
}
//-----------------------------------------------
//Filter 6 : lighten and darken image
void lightenAndDarkenImage(){
    char lORd;
    //letting the user choose between darkening or lightening the image
    cout << "Do you want to (d)arken or (l)ighten?";
    cin >> lORd;

    //lightening the color of the image by adding 255 to each pixel then dividing it by 2
    if(lORd == 'l'){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = (image[i][j] + 255) / 2;
            }
        }
    }
    //darkening the color of the image by halving the pixel color
    else if(lORd == 'd'){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] *= 0.5;
            }
        }
    }
}
//..................................................
// Filter 7: Detect Image Edges Filter
void DetectImageEdges() {
    BlackWhiteFilter(); // we call the black and white function
    // because we compare each index and the next to it with 0 and 255
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // we check each two adjacent pixels
            // if they are the same put each equals to 255 (white) otherwise equals 0 (black)
            if (image[i][j] == image[i][j + 1]) {
                image[i][j] = 255;
            }
            else if (image[i][j] != image[i][j + 1]) {
                image[i][j] = 0;
            }
        }
    }
}
//-----------------------------------------------
// Filter 8: Enlarge Filter
void enlargeImage() {
    // Asking the user to determine which quarter to enlarge.
    cout << "Please, enter a number to determine which quarter to enlarge: " << endl;
    cout << "1 - Right upper quarter." << endl;
    cout << "2 - Left upper quarter." << endl;
    cout << "3 - Right lower quarter." << endl;
    cout << "4 - Left lower quarter." << endl;
    cin >> choice8;

    if (choice8 == 1) { // If the chosen quarter is the first one.
        for (int i = 0, x = 0; i < SIZE; i += 2, x++) { // Looping through each single pixel in the original image, and adding it to the first four pixels in the new one.
            for (int j = 0, y = 0; j < SIZE; j += 2, y++) {
                quarter1[i][j] = image[x][y];
                quarter1[i][j + 1] = image[x][y];
                quarter1[i + 1][j] = image[x][y];
                quarter1[i + 1][j + 1] = image[x][y];
            }
        }
        char newImage[100];
        cout << "Please, enter the target image file name: " << endl; // Asking about the new image name.
        cin >> newImage;
        strcat(newImage, ".bmp"); // Adding .bmp extension to load and, write it.
        writeGSBMP(newImage, quarter1); // Writing and creating the new image.
    }

    else if (choice8 == 2) { // If the chosen quarter is the second one.
        for (int i = 0, x = 0; i < SIZE; i += 2, x++) { // Looping through each single pixel in the original image, and adding it to the first four pixels in the new one.
            for (int j = 0, y = 128; j < SIZE; j += 2, y++) {
                quarter2[i][j] = image[x][y];
                quarter2[i][j + 1] = image[x][y];
                quarter2[i + 1][j] = image[x][y];
                quarter2[i + 1][j + 1] = image[x][y];
            }
        }
        char newImage[100];
        cout << "Please, enter the target image file name: " << endl; // Asking about the new image name.
        cin >> newImage;
        strcat(newImage, ".bmp"); // Adding .bmp extension to load and, write it.
        writeGSBMP(newImage, quarter2); // Writing and creating the new image.

    }

    else if (choice8 == 3) { // If the chosen quarter is the third one.
        for (int i = 0, x = 128; i < SIZE; i += 2, x++) { // Looping through each single pixel in the original image, and adding it to the first four pixels in the new one.
            for (int j = 0, y = 0; j < SIZE; j += 2, y++) {
                quarter3[i][j] = image[x][y];
                quarter3[i][j + 1] = image[x][y];
                quarter3[i + 1][j] = image[x][y];
                quarter3[i + 1][j + 1] = image[x][y];
            }
        }
        char newImage[100];
        cout << "Please, enter the target image file name: " << endl; // Asking about the new image name.
        cin >> newImage;
        strcat(newImage, ".bmp"); // Adding .bmp extension to load and, write it.
        writeGSBMP(newImage, quarter3); // Writing and creating the new image.

    }

    else { // If the chosen quarter is the fourth one.
        for (int i = 0, x = 128; i < SIZE; i += 2, x++) { // Looping through each single pixel in the original image, and adding it to the first four pixels in the new one.
            for (int j = 0, y = 128; j < SIZE; j += 2, y++) {
                quarter4[i][j] = image[x][y];
                quarter4[i][j + 1] = image[x][y];
                quarter4[i + 1][j] = image[x][y];
                quarter4[i + 1][j + 1] = image[x][y];
            }
        }
        char newImage[100];
        cout << "Please, enter the target image file name: " << endl; // Asking about the new image name.
        cin >> newImage;
        strcat(newImage, ".bmp"); // Adding .bmp extension to load and, write it.
        writeGSBMP(newImage, quarter4); // Writing and creating the new image.
    }
}
//-----------------------------------------------
//Filter 9 : shrink Filter
void shrinkImage(){
    int shrinkSize;

    cout << " please choose the shrinkage size:\n";
    cout << " choose 2 for 1/(2)\n";
    cout << " choose 3 for 1/(3)\n";
    cout << " choose 4 for 1/(4)\n" << endl;
    cout << " >> "<< endl;
    cin >> shrinkSize;

    //skipping a shrink size number and loading it into a new loaded image "image2"
    for (int i = 0, x = 0; i < SIZE; i += shrinkSize, ++x) {
        for (int j = 0, y = 0; j < SIZE; j += shrinkSize, ++y) {
            image2[x][y] = image[i][j];
        }
    }
    //turning the rest of the pixels into white color
    for (int i = (256 / shrinkSize), x = 0, w = (256 / shrinkSize); i < SIZE; ++i, x++, ++w) {
        for (int j = (256 / shrinkSize), y = (256 / shrinkSize), z = 0; j < SIZE; ++j, y++, ++z) {
            image2[i][j] = 255;
            image2[x][y] = 255;
            image2[w][z] = 255;
        }
    }
    char  imageFileName[100];

    cout << "enter the target image file name: ";
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, image2);
}
//..................................................
// Filter a: Mirror Half Images Filter
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
                // we loop on the half of the columns to reflect the right or the left of the image
                image[i][j] = image[i][SIZE - 1 - j];
                // we take the value of the right pixels and put it on the left in the same row
            }
        }
    }
    else if (choice_a == "2") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < (SIZE / 2); j++) {
                // we loop on the half of the columns to reflect the right or the left of the image
                image[i][SIZE - 1 - j] = image[i][j];
                // we take the value of the left pixels and put it on the right in the same row

            }
        }
    }
    else if (choice_a == "3") {
        for (int i = 0; i < (SIZE / 2); i++) {
            for (int j = 0; j < SIZE; j++) {
                // we loop on the half of the rows to reflect
                // the upper half or the lower half of the image
                image[SIZE - 1 - i][j] = image[i][j];
                // we take the value of the upper pixels and put it on the lower in the same column

            }
        }
    }
    else if (choice_a == "4") {
        for (int i = 0; i < (SIZE / 2); i++) {
            for (int j = 0; j < SIZE; j++) {
                // we loop on the half of the rows to reflect
                // the upper half or the lower half of the image
                image[i][j] = image[SIZE - 1 - i][j];
                // we take the value of the lower pixels and put it on the upper in the same column
            }
        }
    }
}
//-----------------------------------------------
// Filter b: Shuffle Filter
void shuffleImage() {
    for (int k = 1; k < 5; k++) {
        cout << "Please, enter the quarter number: " << k <<  endl; // Asking about the new quarters order for four times.
        cin >> quarterOrder;

        if (quarterOrder == 1 || quarterOrder == 2) { // If the chosen quarter is 1 or 2, then we set the old rows (original image) reference to 0.
            oldRows = 0;
        }
        else { // Otherwise, it is set to 128.
            oldRows = 128;
        }

        if (quarterOrder == 1 || quarterOrder == 3) { // If the chosen quarter is 1 or 3, then we set the old columns (original image) reference to 0.
            oldCols = 0;
        }
        else { // Otherwise, it is set to 128.
            oldCols = 128;
        }

        if (k == 1 || k == 2) { // If the chosen quarter is 1 or 2, then we set the new rows (shuffled image) reference to 0.
            newRows = 0;
        }
        else { // Otherwise, it is set to 128.
            newRows = 128;
        }

        if (k == 1 || k == 3) { // If the chosen quarter is 1 or 2, then we set the new columns (shuffled image) reference to 0.
            newCols = 0;
        }
        else { // Otherwise, it is set to 128.
            newCols = 128;
        }

        if (quarterOrder == 1) { // If the chosen quarter is 1.
            x = newRows; // We set the counter x to the value of the new rows refernce, and adding each single pixel in the original image to the shuffled one.
            for (int i = 0; i < 128; i++, x++) {
                y = newCols; // Counter y is set the value of the new columns refernce.
                for (int j = 0; j < 128; j++, y++) {
                    shuffledImage[x][y] = image[i][j];
                }
            }

        }
        else if (quarterOrder == 2) { // If the chosen quarter is 2.
            x = newRows; // We set the counter x to the value of the new rows refernce, and adding each single pixel in the original image to the shuffled one.
            for (int i = 0; i < 128; i++, x++) {
                y = newCols; // Counter y is set the value of the new columns refernce.
                for (int j = 128; j < 256; j++, y++) {
                    shuffledImage[x][y] = image[i][j];
                }
            }

        }
        else if (quarterOrder == 3) { // If the chosen quarter is 3.
            x = newRows; // We set the counter x to the value of the new rows refernce, and adding each single pixel in the original image to the shuffled one.
            for (int i = 128; i < 256; i++, x++) {
                y = newCols; // Counter y is set the value of the new columns refernce.
                for (int j = 0; j < 128; j++, y++) {
                    shuffledImage[x][y] = image[i][j];
                }
            }

        }
        else { // If the chosen quarter is 4.
            x = newRows; // We set the counter x to the value of the new rows refernce, and adding each single pixel in the original image to the shuffled one.
            for (int i = 128; i < 256; i++, x++) {
                y = newCols; // Counter y is set the value of the new columns refernce.
                for (int j = 128; j < 256; j++, y++) {
                    shuffledImage[x][y] = image[i][j];
                }
            }
        }
    }
    char newImage[100];
    cout << "Please, enter the target image file name: " << endl; // Asking about the new image name.
    cin >> newImage;
    strcat(newImage, ".bmp"); // Adding .bmp extension to load, and write it.
    writeGSBMP(newImage, shuffledImage); // Writing and creating the new image.
}
//----------------------------------------------
//Filter c : blue image
void blurImage(){
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            //taking the average of the surrounding pixels of each pixel
            image[i][j] = (image[i][j]+image[i-1][j-1]+image[i-1][j]+image[i+1][j]+image[i][j-1]+image[i][j+1]+image[i-1][j+1]+image[i][j+1]+image[i+1][j+1]+image[i-2][j-2]+image[i-2][j]+image[i+2][j]+image[i][j-2]+image[i][j+2]+image[i-2][j+2]+image[i][j+2]+image[i+2][j+2]) /17 ;
        }
    }
}

