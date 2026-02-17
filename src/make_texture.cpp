#include "config.h"
#include "make_texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



Material::Material(const char* filename) : texture(1) {
    // Balik gambar (Penting untuk OpenGL)
   

    GLint width, height, nrChannels;
    GLubyte* data = stbi_load(filename, &width, &height, &nrChannels, STBI_rgb_alpha);

    glGenTextures(1, texture.data()); 
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    stbi_set_flip_vertically_on_load(true);

    if (data) // <--- CEK APAKAH GAMBAR KETEMU?
    {
        std::cout << "SUKSES: Texture berhasil dimuat: " << filename << std::endl;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        // JIKA MUNCUL TULISAN INI DI CONSOLE, BERARTI PATH SALAH
        std::cout << "ERROR: Gagal memuat texture! Cek path: " << filename << std::endl;
    }
// ...
// Ganti bagian ini:
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Ubah jadi GL_LINEAR
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// ...
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
}

Material::~Material(){
    glDeleteTextures(static_cast<GLsizei>(texture.size()), texture.data());
}

void Material::use() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
}
