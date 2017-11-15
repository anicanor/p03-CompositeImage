//Author: Aaron Nicanor

#include <iostream>
#include <vector>
#include <string>
#include "bitmap.h"

using namespace std;

//Decomposition
/* While the user does not input "DONE"
   Save the first bitmap  image's size and add to a counter each time we add an image that's the same size as the first image. Put each new image in a vector of Bitmaps
   If the counter is about to go past 10, deny any additional bitmap images
   When the user tries to composite an image, it checks if the counter is at least 2
   If not, the program will deny the user of making a composite image
   If it is, it will take the first and the second bitmap, take an average of each rgb pixel, save it into the first bitmap, and once it's all done, it will inform the user the progress that has been done.
   It will do this for every image selected by the user and once it's done, the image will be saved as a bitmap image called "composite-anicanor.bmp"
 */


//Prototypes
//Takes the average of two pixels
Pixel average(Pixel, Pixel);
//Takes two bitmap images and creates a composite image. Will also inform the user the progress of the overall composite function
Bitmap composite(Bitmap, Bitmap, int, int);
//Adds a bitmap into the collection of bitmaps and checks if any subsequent bitmaps are the same size
void addBitmap(vector<Bitmap>&, int&, string);

int main(){

        int total = 0;
        vector <Bitmap> collection;
        bool finish;
        string input;
        Bitmap bmp;

        do{

                cout<<"(C)omposite"<<endl<<"(D)one"<<endl<<"Or, if you want to add an image, type the file name:"<<endl;
                cin>>input;
                if (input == "D" || input == "d"){

                        finish = true;

                }else if(input == "C" || input == "c"){

                        if(total < 2){

                                cout<<"Not enough images to composite"<<endl;

                        }else{

                                bmp = collection[0];
                                for(int i = 1; i < total; i++){

                                        bmp = composite(bmp,collection[i],total,i);

                                }
                                cout<<total<<" of "<<total<<" images are done"<<endl;
                                bmp.save("composite-anicanor.bmp");
                        }

                }else{

                        if (total != 10){

                                if (total >= 1){

                                addBitmap(collection, total, input);


                                }else{

                                        bmp.open(input);
                                        
                                        if(bmp.isImage() == true){

                                            collection.push_back(bmp);
                                            total += 1;
                                        }

                                }
                        }else{

                                cout<<"Maximum number of images reached. Either quit out or composite image"<<endl;
                        }
                }
        } while(finish != true);

        return 0;
}

Pixel average(Pixel img1, Pixel img2){

        img1.red += img2.red;
        img1.green += img2.green;
        img1.blue += img2.blue;
        img1.red /= 2;
        img1.green /= 2;
        img1.blue /= 2;

        return img1;
}

Bitmap composite(Bitmap bmp1, Bitmap bmp2, int total, int done){

        vector < vector <Pixel> > px1, px2;
        px1 = bmp1.toPixelMatrix();
        px2 = bmp2.toPixelMatrix();
        for(int i = 0; i < px1.size(); i++){

                for(int o = 0; o < px1[0].size(); o++){

                        px1[i][o] = average(px1[i][o], px2[i][o]);
                }
        }
        bmp1.fromPixelMatrix(px1);
        cout<<done<<" of "<<total<<" images are done"<<endl;

        return bmp1;
}

void addBitmap(vector <Bitmap> &collection, int &total, string input){

        Bitmap bmp;
        vector < vector <Pixel> > check1, check2;
        check1 = collection[0].toPixelMatrix();
        bmp.open(input);
        check2 = bmp.toPixelMatrix();
        if(check1.size() == check2.size() && check1[0].size() == check2[0].size()){

                collection.push_back(bmp);
                total += 1;
        }else{

                cout<<"size of inputed image does not match previous image sizes"<<endl;
        }
}
