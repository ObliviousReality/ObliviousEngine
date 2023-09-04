#pragma once

#include "ObliviousEngine/Renderer/VertexArray.h"

namespace OE
{
	class GLVertexArray : public VertexArray
	{
	public:
		GLVertexArray();
		virtual ~GLVertexArray();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void addVertexBuffer(const Ref<VertexBuffer>& buf) override;
		virtual void setIndexBuffer(const Ref<IndexBuffer>& buf) override;

		virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const override { return vertexBufs; }
		virtual const Ref<IndexBuffer>& getIndexBuffer() const override { return indexBuf; }

	private:
		std::vector<Ref<VertexBuffer>> vertexBufs;
		Ref<IndexBuffer> indexBuf;
		uint32_t rendererID;
	};
}