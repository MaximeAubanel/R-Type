#pragma once

#include <iostream>
#include "Input.h"


class TestInput
{
public:
	TestInput()
	{

	}

	~TestInput()
	{

	}

	void update(TacosEngine::Input &input)
	{
		for (int i = 0; i < 42; i++)
		{
			if (input.getKey(static_cast<TacosEngine::Key>(i)))
				std::cout << "Key " << i << " pressed" << std::endl;
		}
	}
};