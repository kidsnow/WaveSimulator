#include "wave_simulator.h"

#include "grid.h"


WaveSimulator::WaveSimulator(Grid* grid) :
	grid_(grid)
{

}

WaveSimulator::~WaveSimulator()
{

}

void WaveSimulator::Step()
{
	int bufferCount = grid_->GetBufferCount();
	int cur = (grid_->GetFrontBufferIndex() + 1) % bufferCount;
	grid_->SetFrontBufferIndex(cur);
}