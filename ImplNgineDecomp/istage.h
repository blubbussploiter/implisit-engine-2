#pragma once

namespace RBX
{
	class Kernel;

	class IStage
	{
	private:

		IStage* upstream, *downstream;

	public:

		Kernel* getKernel()
		{
			return downstream->getKernel();
		}

		void stepWorld(int worldStepId, int uiStepId, bool throttling)
		{
			downstream->stepWorld(worldStepId, uiStepId, throttling);
		}

	};
}