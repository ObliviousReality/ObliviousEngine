#include "oepch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platforms/OpenGL/GLBuffer.h"
namespace OE
{
	VertexBuffer* VertexBuffer::Create(float* vertexes, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			OE_CORE_ASSERT(false, "RENDERER API 'none' NOT SUPPORTED");
			return nullptr;
		case RenderAPI::API::OpenGL:
			return new GLVertexBuffer(vertexes, size);
		default:
			OE_CORE_ASSERT(false, "UNKOWN RENDERER API SET");
			return nullptr;
		}
	}
	IndexBuffer* IndexBuffer::Create(uint32_t* indexes, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			OE_CORE_ASSERT(false, "RENDERER API 'none' NOT SUPPORTED");
			return nullptr;
		case RenderAPI::API::OpenGL:
			return new GLIndexBuffer(indexes, count);
		default:
			OE_CORE_ASSERT(false, "UNKOWN RENDERER API SET");
			return nullptr;
		}
	}
}