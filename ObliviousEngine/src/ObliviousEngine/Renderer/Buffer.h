#pragma once

namespace OE
{

	enum class ShaderType
	{
		None = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4,
		Bool
	};

	static uint32_t ShaderTypeSize(ShaderType type)
	{
		switch (type)
		{
		case OE::ShaderType::None:
			return 0;
		case OE::ShaderType::Float:
			return 4;
		case OE::ShaderType::Float2:
			return 8;
		case OE::ShaderType::Float3:
			return 12;
		case OE::ShaderType::Float4:
			return 16;
		case OE::ShaderType::Mat3:
			return 3 * 3 * 4;
		case OE::ShaderType::Mat4:
			return 4 * 4 * 4;
		case OE::ShaderType::Int:
			return 4;
		case OE::ShaderType::Int2:
			return 4 * 2;
		case OE::ShaderType::Int3:
			return 4 * 3;
		case OE::ShaderType::Int4:
			return 4 * 4;
		case OE::ShaderType::Bool:
			return 1;
		default:
			OE_CORE_ASSERT(false, "UNKNOWN SHADER TYPE");
			return 0;
		}
	}

	struct BufferElement
	{
		std::string name;
		ShaderType type;
		uint32_t size;
		size_t offset;
		bool normalised;

		BufferElement() = default;

		BufferElement(ShaderType type_in, const std::string& name_in, bool normalised_in = false)
			: name(name_in), type(type_in), size(ShaderTypeSize(type)), offset(0), normalised(false)
		{
		}

		uint32_t getComponentCount() const
		{
			switch (type)
			{
			case OE::ShaderType::None:
				return 0;
			case OE::ShaderType::Float:
				return 1;
			case OE::ShaderType::Float2:
				return 2;
			case OE::ShaderType::Float3:
				return 3;
			case OE::ShaderType::Float4:
				return 4;
			case OE::ShaderType::Mat3:
				return 3 * 3;
			case OE::ShaderType::Mat4:
				return 4 * 4;
			case OE::ShaderType::Int:
				return 1;
			case OE::ShaderType::Int2:
				return 2;
			case OE::ShaderType::Int3:
				return 3;
			case OE::ShaderType::Int4:
				return 4;
			case OE::ShaderType::Bool:
				return 1;
			default:
				OE_CORE_ASSERT(false, "UNKNOWN SHADER TYPE");
				return 0;
			}
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& element)
			:elements(element)
		{
			calculateVars();
		}

		inline uint32_t getStride() const { return stride; }
		inline const std::vector<BufferElement>& getElements() const { return elements; }

		std::vector<BufferElement>::iterator begin() { return elements.begin(); }
		std::vector<BufferElement>::iterator end() { return elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return elements.end(); }
	private:
		void calculateVars()
		{
			size_t off = 0;
			stride = 0;
			for (auto& e : elements)
			{
				e.offset = off;
				off += e.size;
				stride += e.size;
			}
		}
	private:
		std::vector<BufferElement> elements;
		uint32_t stride = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual const BufferLayout& getLayout() const = 0;
		virtual void setLayout(const BufferLayout& layout) = 0;

		static Ref<VertexBuffer> Create(float* vertexes, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		virtual uint32_t getCount() const = 0;
		static Ref<IndexBuffer> Create(uint32_t* indexes, uint32_t count);
	};
}