
#include "ImageData.h"

#include <cassert>
#include <iostream>

namespace canvas
{
   
   ImageData::ImageData(void * data, int width, int height, Canvas::Format format)
      : m_bitmap(new SkBitmap()),
        m_format(format)
   {
      assert(data);

      m_bitmap->setConfig(SkBitmap::kARGB_8888_Config, width, height);
      m_bitmap->allocPixels();
      
      m_bitmap->lockPixels();

      if (format == Canvas::kRGBA)
      {
         unsigned char * targetData = static_cast<unsigned char*>(m_bitmap->getPixels());
         unsigned char * sourceData = static_cast<unsigned char*>(data);
         
         for (size_t i = 0; i < m_bitmap->getSize(); i += 4)
         {
            targetData[i + 0] = sourceData[i + 3];
            targetData[i + 1] = sourceData[i + 0];
            targetData[i + 2] = sourceData[i + 1];
            targetData[i + 3] = sourceData[i + 2];
         }
      }
      else
      {
         memcpy(m_bitmap->getPixels(), data, m_bitmap->getSize());
      }

      m_bitmap->unlockPixels();
   }
   
   ImageData::ImageData(ImageData const& other)
      : m_bitmap(other.m_bitmap),
        m_format(other.m_format)
   {
   }
   
   ImageData::~ImageData()
   {
      delete m_bitmap;
   }
   
   int ImageData::width() const
   {
      assert(m_bitmap);
      return m_bitmap->width();
   }
   
   int ImageData::height() const
   {
      assert(m_bitmap);
      return m_bitmap->height();
   }

   void ImageData::setWidth(int)
   {
      assert(0 && "Invalid operation, not allowed to set width!");
   }
   
   void ImageData::setHeight(int)
   {
      assert(0 && "Invalid operation, not allowed to set height!");
   }
   
}