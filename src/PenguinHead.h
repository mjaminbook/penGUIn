//
//  PenguinHead.h
//  Basic_Graphics
//
//  Created by Ruthie Berman on 4/22/17.
//
//

#ifndef PenguinHead_h
#define PenguinHead_h

#include "GLSLProgram.h"
#include "config.h"
#include "Texture.h"
#include "Mesh.h"
#define GLM_FORCE_RADIANS
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/constants.hpp>

namespace basicgraphics {
    class PenguinHead {
    public:
        PenguinHead();
        ~PenguinHead(){};
        
        // Calculate and set up buffers to render to screen
        void createHead(float radius);
        
        // Draw Penguin head to screen
        void draw(GLSLProgram &shader);
        
    protected:
        std::vector< std::shared_ptr<Texture> > textures;
        std::unique_ptr<Mesh> _mesh;
    };
}

#endif /* PenguinHead_h */
