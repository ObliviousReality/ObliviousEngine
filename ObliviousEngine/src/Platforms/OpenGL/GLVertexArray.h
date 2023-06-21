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

		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& buf) override;
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& buf) override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const override { return vertexBufs; }
		virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const override { return indexBuf; }

	private:
		std::vector<std::shared_ptr<VertexBuffer>> vertexBufs;
		std::shared_ptr<IndexBuffer> indexBuf;
		uint32_t rendererID;
	};
}