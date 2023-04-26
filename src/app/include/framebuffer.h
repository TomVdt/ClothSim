#include <GL/glew.h>
#include "GLFW/glfw3.h"

class FrameBuffer {
private:
    GLuint fbo;
    GLuint texture;
    GLuint rbo;

public:
	FrameBuffer();

	~FrameBuffer();
	
    GLuint getFrameTexture();
	
    void rescaleFrameBuffer(int width, int height);
	
    void create(int width, int height);

    void bind() const;
	
    void release() const;
};