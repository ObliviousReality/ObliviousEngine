#pragma once
#include "ObliviousEngine/Renderer/Buffer.h"

namespace OE
{
	class GLVertexBuffer : public VertexBuffer
	{
	public:
		GLVertexBuffer(float* vertexes, uint32_t size);
		virtual ~GLVertexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual const BufferLayout& getLayout() const override { return m_Layout; }
		virtual void setLayout(const BufferLayout& layout) override { m_Layout = layout; }
	private:
		uint32_t rendererID;
		BufferLayout m_Layout;
	};

	class GLIndexBuffer : public IndexBuffer
	{
	public:
		GLIndexBuffer(uint32_t* indexes, uint32_t count);
		virtual ~GLIndexBuffer();

		virtual void bind() const;
		virtual void unbind() const;
		virtual uint32_t getCount() const { return count; }
	private:
		uint32_t rendererID;
		uint32_t count;

	};
}