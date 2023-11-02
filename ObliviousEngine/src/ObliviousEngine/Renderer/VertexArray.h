#pragma once

#include <memory>
#include "Buffer.h"

namespace OE
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void addVertexBuffer(const Ref<VertexBuffer>& buf) = 0;
		virtual void setIndexBuffer(const Ref<IndexBuffer>& buf) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& getIndexBuffer() const = 0;


		static Ref<VertexArray> Create();
	};
}