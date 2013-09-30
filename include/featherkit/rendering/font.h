#pragma once
#include <string>
#include <stdexcept>
#include <freetype-gl.h>

namespace fea
{
    class InvalidFontException : public std::runtime_error 
    {
        public:
            InvalidFontException(const std::string& message);
    };

    class TextSurface;
    
    class Font
    {
        public:
            Font(TextSurface& surface);
            Font(TextSurface& surface, const std::string& path, const float fontSize = 12.0f);
            ~Font();
            void createFont(const std::string& path, const float fontSize = 12.0f);
            void resize(const float fontSize);
            texture_font_t* getInternalFont() const;
        private:
            std::string fontPath;
            texture_font_t* textureFont;
            TextSurface* owner;
    };
}
