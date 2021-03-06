#include <cassert>
#include <cstdlib>
#include "ContentSerializer.hpp"
#include "GL.hpp"
#include "../include/Reindeer/Layer.hpp"

namespace Reindeer
{
	Layer::Layer(void *serialized, size_t size) : serialized(serialized), serialized_end((Content *)((char *)serialized + size))
	{
	}

	Layer::~Layer()
	{
		ContentWalker walker(serialized);
		
		Content *content;
		
		while((content = &walker.peek_object<Content>()) != serialized_end)
		{
			content->deallocate(walker);
			
			// TODO: Add a conditional for debug test
			assert(walker.read_object<size_t>() == 0xBEEF);
		}
		
		std::free(serialized);
	}

	void Layer::render()
	{
		ContentWalker walker(serialized);

		Content *content;
		
		while((content = &walker.peek_object<Content>()) != serialized_end)
		{
			content->render(walker);
			
			// TODO: Add a conditional for debug test
			assert(walker.read_object<size_t>() == 0xBEEF);
		}

		gluRaiseErrors();
	}
};
