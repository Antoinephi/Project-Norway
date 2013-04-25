#include "circularbuffer.h"

CircularBuffer::CircularBuffer(int size){
    imgBuffer = new Image[size];
    noOfImages = 0;
    readCounter = 0;
    postCounter = 0;
    this->size = size;
}

void CircularBuffer::post(Image img){
    imgBuffer[postCounter].DeepCopy(&img);
    if(postCounter<size-1)postCounter++;
    else postCounter=0;
    if(noOfImages<size)noOfImages++;
}

Image CircularBuffer::read(){
    if(readCounter>=100)readCounter=0;
    return imgBuffer[readCounter++];
}

void CircularBuffer::clear(){
    delete[] imgBuffer;
    noOfImages=0;
}
