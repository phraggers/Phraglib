
//========================
// Phraglib test
//========================

#include <PL/PL.h>

struct State
{
    u32 shaderProgram;
    r32 vertices[12];
    u32 indices[6];
    u32 VBO, VAO, EBO;
    u8 wireframeMode;
};

// Fatal errors that prevent Phraglib from starting will produce an OS MessageBox (if possible).
void PL_ErrorCallback()
{
    PL_PrintErr("%s\n", PL_GetErrorString());
}

// This gets called once before main loop.
void PL_Startup()
{
    PL_SetWindowTitle("Phraglib Test");
    
    cstr vertsrc = "#version 330 core\n"
        "layout (location=0) in vec3 aPos;\n"
        "void main() {\n"
        "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    
    cstr fragsrc = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
        "}\0";
    
    State *state = (State*)PL_GetUserMemory();
    state->shaderProgram = PL_GLCreateProgram(vertsrc, fragsrc);
    {r32 *vertex = state->vertices;
        *vertex++ = 0.5f; *vertex++ = 0.5f; *vertex++ = 0.0f;
        *vertex++ = 0.5f; *vertex++ = -0.5f; *vertex++ = 0.0f;
        *vertex++ = -0.5f; *vertex++ = -0.5f; *vertex++ = 0.0f;
        *vertex++ = -0.5f; *vertex++ = 0.5f; *vertex++ = 0.0f;}
    state->indices[0]=0; state->indices[1]=1; state->indices[2]=3;
    state->indices[3]=1; state->indices[4]=2; state->indices[5]=3;
    
    glGenVertexArrays(1, &state->VAO);
    glGenBuffers(1, &state->VBO);
    glGenBuffers(1, &state->EBO);
    glBindVertexArray(state->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, state->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(state->vertices), state->vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, state->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(state->indices), state->indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(r32), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// This gets called every frame, after input and event handling, before window update.
void PL_Frame()
{
    State *state = (State*)PL_GetUserMemory();
    
    // F11: toggle fullscreen
    if(PL_GetKeyState(K_F11)->downTick)
    {
        PL_ToggleWindowFullscreen();
    }
    
    // ALT+F4: quit
    if(PL_GetKeyState(K_F4)->downTick)
    {
        if(PL_GetKeyState(K_LALT)->isDown)
            PL_Quit();
    }
    
    // F1: toggle wireframe mode
    if(PL_GetKeyState(K_F1)->downTick)
    {
        switch(state->wireframeMode)
        {
            case 0: //fill
            { // fill > line
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                state->wireframeMode = 1;
            } break;
            case 1: // line
            { // line > point
                glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
                state->wireframeMode = 2;
            } break;
            case 2: // point
            { // point > fill
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                state->wireframeMode = 0;
            } break;
        }
    }
    
    glUseProgram(state->shaderProgram);
    glBindVertexArray(state->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //glBindVertexArray(0);
}