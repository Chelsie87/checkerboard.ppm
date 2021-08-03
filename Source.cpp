#include <fstream>
#include <cstdio>
#include <string>
using namespace std;

int main() {
    //height and width of board
    int height = 800, width = 800;
    //variable to keep track when to swap from color 1 or color 2
    int change_color = 0;
    int square_length = 96;
    //amt of squares  (by 2s)
    int square_count = 0;
    int white_space = 16;
    //add height for looping the patterns
    int add_h = 0;

    //Red-Yellow ppm
    ofstream outfile("checkerboard.ppm", ios_base::out | ios_base::binary);
    //Black-White ppm
    ofstream second("checkerboard_2.ppm", ios_base::out | ios_base::binary);
    ifstream input("checkerboard.ppm", ios_base::in | ios_base::binary);

    //header --- p6 800x800 225 channels
    outfile << "P6" << " " << width << " " << height << " 255" << endl;
    //second header --- p6 800x800 225 channels
    second << "P6" << " " << width << " " << height << " 255" << endl;

    //use pointers to create 3 matrixcies
    //matrix for first channel (Red) 
    int** in_matrix_ch1 = new int* [height];
    for (int i = 0; i < height; ++i)
        in_matrix_ch1[i] = new int[width];

    //matrix for second channel (Green)
    int** in_matrix_ch2 = new int* [height];
    for (int i = 0; i < height; ++i)
        in_matrix_ch2[i] = new int[width];

    //matrix for thrid channel (Blue)
    int** in_matrix_ch3 = new int* [height];
    for (int i = 0; i < height; ++i)
        in_matrix_ch3[i] = new int[width];
    
    //write to file 
    //R G B
    //black 0 0 0
    //white 255 255 255
    //red 255 0 0
    //yellow 255 255 0
    //0,0 --> (char)255.....

    //set the white spaces
    //first row line of white spaces 16x800
    for (int i_h = 0; i_h < 16; i_h++) {
        for (int i_w = 0; i_w < width; i_w++) {

            in_matrix_ch1[i_h][i_w] = 255;
            in_matrix_ch2[i_h][i_w] = 255;
            in_matrix_ch3[i_h][i_w] = 255;
        }
    }

    //first col line of white spaces 800x16
    for (int i_h = 0; i_h < height; i_h++) {
        for (int i_w = 0; i_w < 16; i_w++) {
            in_matrix_ch1[i_h][i_w] = 255;
            in_matrix_ch2[i_h][i_w] = 255;
            in_matrix_ch3[i_h][i_w] = 255;
        }
    }

    //last row line of white spaces from 784-800 x 800
    for (int i_h = 784; i_h < height; i_h++) {
        for (int i_w = 0; i_w < width; i_w++) {

            in_matrix_ch1[i_h][i_w] = 255;
            in_matrix_ch2[i_h][i_w] = 255;
            in_matrix_ch3[i_h][i_w] = 255;
        }
    }

    //last col line of white spaces from 800 x 784-800
    for (int i_h = 0; i_h < height; i_h++) {
        for (int i_w = 784; i_w < width; i_w++) {

            in_matrix_ch1[i_h][i_w] = 255;
            in_matrix_ch2[i_h][i_w] = 255;
            in_matrix_ch3[i_h][i_w] = 255;
        }
    }

    /*****************
    //first checkerboard square 96x96
    for (int i_h = 16; i_h < 112; i_h++) {
        for (int i_w = 16; i_w <  112; i_w++) {
            
            in_matrix_ch1[i_h][i_w] = 255;
            in_matrix_ch2[i_h][i_w] = 0;
            in_matrix_ch3[i_h][i_w] = 0;
        }
    }

    //second checkerboard square 96x96 TEST 16x122 x 122x208
    for (int i_h = 16; i_h < 112; i_h++) {
        for (int i_w = 112; i_w < 208; i_w++) {

            in_matrix_ch1[i_h][i_w] = 255;
            in_matrix_ch2[i_h][i_w] = 255;
            in_matrix_ch3[i_h][i_w] = 0;
        }
    }
    //*********************
    */

    //2 rows x 4 times = 8 
    for (int i = 0; i < 4; i++) {

        //First row == 16x112 x 16x784 (800-16)
        //Pattern 1 [Red Yellow Red Yellow Red Yellow Red Yellow]
        for (int i_h = 16 + add_h; i_h < 112 + add_h; i_h++) {
            for (int i_w = 16; i_w < width - 16; i_w++) {

                //If still in 1st square, make Red
                if (change_color < 96) {
                    in_matrix_ch1[i_h][i_w] = 255;
                    in_matrix_ch2[i_h][i_w] = 0;
                    in_matrix_ch3[i_h][i_w] = 0;

                    
                }
                //If changed to next square (96px...) but not 2 squares past, make Yellow
                else if (change_color >= 96 && change_color < 192) {
                    in_matrix_ch1[i_h][i_w] = 255;
                    in_matrix_ch2[i_h][i_w] = 255;
                    in_matrix_ch3[i_h][i_w] = 0;

                }
                //If end of current square, make Red
                else if (change_color == 192) {
                    in_matrix_ch1[i_h][i_w] = 255;
                    in_matrix_ch2[i_h][i_w] = 0;
                    in_matrix_ch3[i_h][i_w] = 0;

                    //reset square color counter
                    change_color = 0;
                    
                    //increment because it has moved 2 squares
                    square_count += 2;
                }
                //inc every pixel within each horizontal line (16 - 784) 
                change_color++;
            }
        }

        //Pattern 2: [Yellow Red Yellow Red Yellow Red Yellow Red]
        for (int i_h = 112 + add_h; i_h < 208 + add_h; i_h++) {
            for (int i_w = 16; i_w < width - 16; i_w++) {

                if (change_color < 96) {
                    in_matrix_ch1[i_h][i_w] = 255;
                    in_matrix_ch2[i_h][i_w] = 255;
                    in_matrix_ch3[i_h][i_w] = 0;
                }
                else if (change_color >= 96 && change_color < 192) {
                    in_matrix_ch1[i_h][i_w] = 255;
                    in_matrix_ch2[i_h][i_w] = 0;
                    in_matrix_ch3[i_h][i_w] = 0;

                }
                else if (change_color == 192) {
                    in_matrix_ch1[i_h][i_w] = 255;
                    in_matrix_ch2[i_h][i_w] = 255;
                    in_matrix_ch3[i_h][i_w] = 0;

                    change_color = 0;
                    square_count += 2;
                }

                change_color++;
            }
        }
        
        //when you reach 8, you complete 1 whole row. 
        //this signals to not print the next row because it is pattern 2
        //this continues for the whole board
        if (square_count >= 8)
        {
            //add to the for loop height
            add_h += 192;
            //reset individual square counter to 0 to recount for new row
            square_count = 0;
        }
    }

    //output for base ppm
    for (int i_h = 0; i_h < height; i_h++) {
        for (int i_w = 0; i_w < width; i_w++) {

            outfile << (char)in_matrix_ch1[i_h][i_w];
            outfile << (char)in_matrix_ch2[i_h][i_w];
            outfile << (char)in_matrix_ch3[i_h][i_w];
        }
    }

    char r, g, b;

    //transforming data for second ppm --- inverted colors
    for (int i_h = 0; i_h < height; i_h++) {
        for (int i_w = 0; i_w < width; i_w++) {

            input.get(r);
            input.get(g);
            input.get(b);
            in_matrix_ch1[i_h][i_w] = 255 - (int)r;
            in_matrix_ch2[i_h][i_w] = 255 - (int)g;
            in_matrix_ch3[i_h][i_w] = 255 - (int)b;
        }
    }

    //second output
    for (int i_h = 0; i_h < height; i_h++) {
        for (int i_w = 0; i_w < width; i_w++) {

            second << (char)in_matrix_ch1[i_h][i_w];
            second << (char)in_matrix_ch2[i_h][i_w];
            second << (char)in_matrix_ch3[i_h][i_w];
        }
    }

    outfile.close();

    return EXIT_SUCCESS;
}