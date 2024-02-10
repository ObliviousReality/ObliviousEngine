#pragma once

#include "ObliviousEngine/Renderer/OrthoCamera.h"
#include "ObliviousEngine/Renderer/RenderCommand.h"
#include "ObliviousEngine/Renderer/Shader.h"

namespace OE
{

    class Renderer
    {
    public:
        static void Init();
        static void Finish();

        static void WindowResize(uint32_t w, uint32_t h);

        static void BeginScene(OrthographicCamera & camera); // TODO: Scene Params
        static void EndScene();

        static void Draw(const Ref<Shader> & shader,
                         const Ref<VertexArray> & vArray,
                         const glm::mat4 & transform = glm::mat4(1.0f));

        inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }

    private:
        struct SceneParams
        {
            glm::mat4 ViewProjMatrix;
        };

        static Scope<SceneParams> params;
    };
} // namespace OE
