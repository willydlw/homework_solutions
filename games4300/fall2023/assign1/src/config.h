#ifndef CONFIG_FILE_H
#define CONFIG_FILE_H

#include <map>
#include <string>
#include <vector>
#include <cstdint>


namespace bounce
{
   /*****************
    * Enumeration - Configuration Tags
   */
   enum class ConfigTag {CIRCLE, FONT, RECTANGLE, WINDOW};


   /*****************
    * Map string tag to enumeration 
   */
   static std::map<std::string, ConfigTag> const configTable = 

      {{"Circle", ConfigTag::CIRCLE}, 
      {"Font", ConfigTag::FONT}, 
      {"Rectangle", ConfigTag::RECTANGLE},
      {"Window", ConfigTag::WINDOW}
      };


   /*****************
    * Configuration Data Structures
   */

   struct space2d_t{
      float x;
      float y;
   };

   struct color_t{
      int red;
      int green;
      int blue;
   };


   /*****************
   * Window Configuration Format
   *
   * Window W H
   *
   * Width    W  int 
   * Height   H  int  
   * 
   */

   struct window_t{
      unsigned int width;
      unsigned int height;
   };


   /*****************
    * Circle Configuration Format
    * 
    * Circle N X Y SX SY R G B R
    * 
    * Defines a CircleShape with:
    *    Shape Name        N        std::string
    *    Initial position  (X,Y)    float, float
    *    Initial speed     (SX, SY) float, float
    *    RGB color         R,G,B    int, int, int
    *    Radius            R        float
    *
    */
   struct circle_t{
      std::string name;
      space2d_t   position;
      space2d_t   speed;
      color_t     color;
      float       radius;
   };


   /*****************
    * Rectangle Configuration Format
    * 
    * Rectangle N X Y SX SY R G B W H
    * 
    * Defines a RectangleShape with:
    *    Shape Name        N        std::string
    *    Initial position  (X,Y)    float, float
    *    Initial speed     (SX, SY) float, float
    *    RGB color         R,G,B    int, int, int
    *    Size              (W,H)    float, float
    *
    */
   struct rectangle_t{
      std::string name;
      space2d_t   position;
      space2d_t   speed;
      color_t     color;
      float       width;
      float       height;
   };


   /*****************
    * Font Configuration Format
    *
    * Font F S R G B
    * 
    * This line defines the font which is to be used to draw text 
    * for this program. The format of the line is as follows:
    * 
    *    Font File F     std::string (it will have no spaces)
    *    Font Size S     int
    *    RGB Color       R,G,B    int, int, int 
   */

   struct font_t{
      std::string  fileName;
      int          size;
      color_t      color;
   };


   /**************************
    * Function Prototypes
   */

   bool loadConfiguration(std::string fileName, window_t *window, font_t *font, std::vector<rectangle_t> &rects, 
                        std::vector<circle_t> &circles); 


   void parseCircleConfiguration(std::stringstream &ss, circle_t *circle);
   void parseFontConfiguration(std::stringstream &ss, font_t *font);

   void parseRectangleConfiguration(std::stringstream &ss, rectangle_t *rect);
   void parseWindowConfiguration(std::stringstream &ss, window_t *window);

   std::ostream& printCircleConfiguration(std::ostream &os, const circle_t *circle);
   std::ostream& printFontConfiguration(std::ostream &os, const font_t *font);
   std::ostream& printRectangleConfiguration(std::ostream &os, const rectangle_t *rect);
   std::ostream& printWindowConfiguration(std::ostream &os, const window_t *window);

} // end namespace


#endif 