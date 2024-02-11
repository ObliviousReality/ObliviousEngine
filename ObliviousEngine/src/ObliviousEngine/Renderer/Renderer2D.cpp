#include "oepch.h"

#include "RenderCommand.h"
#include "Renderer2D.h"
#include "Shader.h"
#include "VertexArray.h"

#include <glm/ext/matrix_transform.hpp>

namespace OE
{
    struct R2DStorage
    {
        Ref<VertexArray> vArray;
        // Ref<Shader> flatShader;
        Ref<Shader> textureShader;
        Ref<Texture2D> standardTexture;
    };

    static R2DStorage * storage;

    void Renderer2D::Init()
    {
        PROFILE_FUNCTION();
        storage = new R2DStorage();
        storage->vArray = VertexArray::Create();

        float square[5 * 4] = { -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,
                                0.5f,  0.5f,  0.0f, 1.0f, 1.0f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f };

        Ref<VertexBuffer> vertexBuf = VertexBuffer::Create(square, sizeof(square));

        BufferLayout layout = { { ShaderType::Float3, "position" }, { ShaderType::Float2, "a_TexCoord" } };

        vertexBuf->setLayout(layout);
        storage->vArray->addVertexBuffer(vertexBuf);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

        Ref<IndexBuffer> indexBuf = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

        storage->vArray->setIndexBuffer(indexBuf);

        storage->standardTexture = Texture2D::Create(1, 1);
        uint32_t standardTextureData = 0xffffffff;
        storage->standardTexture->setData(&standardTextureData, sizeof(uint32_t));

        storage->textureShader = Shader::Create("assets/shaders/Texture.glsl");
        storage->textureShader->bind();
        storage->textureShader->setInt("u_Texture", 0);
    }
    void Renderer2D::Finish()
    {
        PROFILE_FUNCTION();
        delete storage;
    }

    void Renderer2D::BeginScene(const OrthographicCamera & camera)
    {
        PROFILE_FUNCTION();
        storage->textureShader->bind();
        storage->textureShader->setMat4("u_ViewProj", camera.getViewProjMatrix());
    }

    void Renderer2D::EndScene() { PROFILE_FUNCTION(); }

    void Renderer2D::DrawRect(const glm::vec2 & pos, const glm::vec2 & size, const glm::vec4 & colour, float a)
    {
        DrawRect({ pos.x, pos.y, 0.0f }, size, colour, a);
    }

    void Renderer2D::DrawRect(const glm::vec3 & pos, const glm::vec2 & size, const glm::vec4 & colour, float a)
    {
        PROFILE_FUNCTION();
        storage->textureShader->setFloat4("u_Colour", colour);
        storage->standardTexture->bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)
                              * glm::rotate(glm::mat4(1.0f), glm::radians(a), glm::vec3(0, 0, 1))
                              * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        storage->textureShader->setMat4("transform", transform);

        storage->vArray->bind();
        RenderCommand::DrawIndexed(storage->vArray);
    }

    void Renderer2D::DrawRect(const glm::vec2 & pos,
                              const glm::vec2 & size,
                              const Ref<Texture2D> & texture,
                              float a,
                              const glm::vec4 & colour)
    {
        DrawRect({ pos.x, pos.y, 0.0f }, size, texture, a, colour);
    }

    void Renderer2D::DrawRect(const glm::vec3 & pos,
                              const glm::vec2 & size,
                              const Ref<Texture2D> & texture,
                              float a,
                              const glm::vec4 & colour)
    {
        PROFILE_FUNCTION();
        storage->textureShader->setFloat4("u_Colour", colour);
        texture->bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)
                              * glm::rotate(glm::mat4(1.0f), glm::radians(a), glm::vec3(0, 0, 1))
                              * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        storage->textureShader->setMat4("transform", transform);

        storage->vArray->bind();
        RenderCommand::DrawIndexed(storage->vArray);
    }
} // namespace OE
