#ifndef CIRCULARBUFFER_H_INCLUDED
#define CIRCULARBUFFER_H_INCLUDED

#include "flycapture/FlyCapture2.h"


using namespace FlyCapture2;

/*! \class CircularBuffer
   * \brief A circular buffer of Images
   *
   */

class CircularBuffer
{
    public:

        int noOfImages;  /*!< The number of image added in the buffer. */

         /*!
         *  \brief Constructor
         *
         *  Constructs the circular buffer
         *
         *  \param size : the number of images that the buffer can savel
         */
        CircularBuffer(int size);
          /*!
         *  \brief Post a new image
         *
         *  Post a new image in the buffer
         *
         *  \param img : the image to save
         *  \return void
         */
        void post(Image img);
        /*!
         *  \brief Clear the buffer
         *
         *  It clear the buffer totally
         *
         *  \return void
         */
        void clear();
        /*!
         *  \brief Read the next image
         *
         *  Return the next image and increment the read counter
         *
         *  \return Image : the next Image.
         */
        Image read();

    private:

        Image* imgBuffer;
        int readCounter;
        int postCounter;
        int size;

};


#endif // CIRCULARBUFFER_H_INCLUDED
