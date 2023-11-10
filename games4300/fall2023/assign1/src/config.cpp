#include "config.h"


#include <fstream>
#include <iostream>
#include <sstream>

namespace bounce
{

   void parseCircleConfiguration(std::stringstream &ss, circle_t *circle)
   {
      ss >> circle->name
         >> circle->position.x 
         >> circle->position.y
         >> circle->speed.x     
         >> circle->speed.y 
         >> circle->color.red 
         >> circle->color.green 
         >> circle->color.blue
         >> circle->radius;
   }


   void parseFontConfiguration(std::stringstream &ss, font_t *font)
   {
      ss >> font->fileName
         >> font->size 
         >> font->color.red 
         >> font->color.green 
         >> font->color.blue;
   }

   void parseRectangleConfiguration(std::stringstream &ss, rectangle_t *rect)
   {
      ss >> rect->name
         >> rect->position.x 
         >> rect->position.y
         >> rect->speed.x     
         >> rect->speed.y 
         >> rect->color.red 
         >> rect->color.green 
         >> rect->color.blue
         >> rect->width
         >> rect->height;
   }

   void parseWindowConfiguration(std::stringstream &ss, window_t *window)
   {
      ss >> window->width
         >> window->height; 
   }


   std::ostream& printCircleConfiguration(std::ostream &os, const circle_t *circle)
   {
      os   << "\nCircle Configuration\n"
            << "name:       "   << circle->name
            << "\nposition x: " << circle->position.x 
            << "\nposition y: " << circle->position.y 
            << "\nspeed    x: " << circle->speed.x     
            << "\nspeed    y: " << circle->speed.y 
            << "\ncolor    R: " << circle->color.red 
            << "\ncolor    G: " << circle->color.green
            << "\ncolor    B: " << circle->color.blue
            << "\nradius    : " << circle->radius
            << "\n";

         return os;

   }

   std::ostream& printFontConfiguration(std::ostream &os, const font_t *font)
   {
      os       << "\nFont Configuration\n" 
               << "fileName: " << font->fileName
               << "\nsize: " << font->size
               << "\ncolor R: " << font->color.red 
               << " G: " << font->color.green 
               << " B:" << font->color.blue << "\n";

      return os;
   }


   std::ostream& printRectangleConfiguration(std::ostream &os, const rectangle_t *rect)
   {
      os   << "\nRectangle Configuration\n"
            << "name:       "       << rect->name
            << "\nposition x: " << rect->position.x 
            << "\nposition y: " << rect->position.y 
            << "\nspeed    x: " << rect->speed.x     
            << "\nspeed    y: " << rect->speed.y 
            << "\ncolor    R: " << rect->color.red 
            << "\ncolor    G: " << rect->color.green
            << "\ncolor    B: " << rect->color.blue
            << "\nwidth     : " << rect->width
            << "\nheight    : " << rect->height
            << "\n";

         return os;
   }

   std::ostream& printWindowConfiguration(std::ostream &os, const window_t *window)
   {
      os       << "\nWindow Configuration\n" 
               << "width:  " << window->width
               << "\nheight: " << window->height << "\n";
            
      return os;
   }



   bool loadConfiguration(std::string fileName,  window_t *window, font_t *font, 
                           std::vector<rectangle_t> &rects, std::vector<circle_t> &circles)
   { 
      char line[256];
      
      // open file
      std::ifstream infile(fileName, std::ifstream::in);

      if(!infile.is_open())
      {
         std::cerr << __func__ << " Error opening " << fileName << "\n";
         return false; 
      }

      // parse file one line at a time 
      while(infile.getline(line, 256, '\n'))
      { 
         std::stringstream ss;
         std::string tagName;
         bounce::ConfigTag tag;

         ss << line;                               // store line in string stream
         ss >> tagName;                            // extract tag name 
         tag = configTable.find(tagName)->second;  // convert string to integer enum
         
         switch(tag)
         {
            case ConfigTag::FONT:
               parseFontConfiguration(ss, font);
               printFontConfiguration(std::cout, font);
               break;
            
            case ConfigTag::CIRCLE:
               {
                  circle_t circle;
                  parseCircleConfiguration(ss, &circle);
                  printCircleConfiguration(std::cout, &circle);
                  circles.push_back(circle);
               }
               break;
            
            case ConfigTag::RECTANGLE:
               {
                  rectangle_t rect;
                  parseRectangleConfiguration(ss, &rect);
                  printRectangleConfiguration(std::cout, &rect);
                  rects.push_back(rect);
               }
               break;

            case ConfigTag::WINDOW:
               parseWindowConfiguration(ss, window);
               printWindowConfiguration(std::cout, window);
               break;
            
            default:
               std::cerr << "Warning, unkown tag name: " << tagName <<  " in file: " << fileName << "\n";
               std::cerr << "Discarding the following line: " << line << "\n";
               break;
         }
      }

      if(!infile.eof())
      {
         std::cerr << "Warning file read did not terminate due to eof\n";
      }

      infile.close();

      return true;
   }

} // end namespace