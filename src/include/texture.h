#pragma once

typedef GLuint TexPixel;

GLuint load_file_texture(const char* aFilename,int clamp=1);
//GLuint load_file_texture(const char * aFilename, int clamp = 1);

GLuint load_blank_texture(const char* aFilename,int Clamp,int width,int height);
//GLuint create_blank_texture(const char* aFilename,int Clamp,int width,int height);


//static void load_blank_texture(const char* aFilename,int Clamp,int w,int h,unsigned long* src);


void reload_textures();
GLuint DeleteTextBitmap(const char* aFilename);
GLuint EmptyTextureStore();
