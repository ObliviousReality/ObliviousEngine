#include "oepch.h"
#include "ObliviousEngine/Renderer/Buffer.h"

#include "ObliviousEngine/Renderer/Renderer.h"
#include "Platforms/OpenGL/GLBuffer.h"
namespace OE
{
	Ref<VertexBuffer> VertexBuffer::Create(float* vertexes, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			OE_CORE_ASSERT(false, "RENDERER API 'none' NOT SUPPORTED");
			return nullptr;
		case RenderAPI::API::OpenGL:
			return CreateRef<GLVertexBuffer>(vertexes, size);
		default:
			OE_CORE_ASSERT(false, "UNKOWN RENDERER API SET");
			return nullptr;
		}
	}
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indexes, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			OE_CORE_ASSERT(false, "RENDERER API 'none' NOT SUPPORTED");
			return nullptr;
		case RenderAPI::API::OpenGL:
			return CreateRef<GLIndexBuffer>(indexes, count);
		default:
			OE_CORE_ASSERT(false, "UNKOWN RENDERER API SET");
			return nullptr;
		}
	}
}