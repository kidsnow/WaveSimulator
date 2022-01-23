#include "grid.h"


GridBuffer::GridBuffer(int gridSize, float gridLength) :
	renderBufferPointer_(nullptr)
{
	/*
	 * gridSize * gridSize 크기로 보여지는 grid를 생성할텐데
	 * wave가 새어나가지 않게 하기 위해서 한쪽 끝은 고정해야 해서
	 * 양쪽 끝에 한 줄씩 grid를 추가로 생성해주어야 한다.
	 * 양쪽 끝의 grid는 계산에만 참여하고 rendering되지는 않는다.
	 * 
	 * xy평면을 기준으로 z값만 시뮬레이션에 참여한다.
	 * 시뮬레이션 계산 시에는 y값만 유의미함.
	 * x, y값은 오직 rendering만을 위해 존재.
	 * 
	 * Element 순서는 x축 major한 order로 메모리에 배치.
	 *
	 * y
	 * ^
	 * |(n+2)*n
	 * |...
	 * |2n   2n+1 2n+2 ...
	 * |n    n+1  n+2  ...
	 * |0    1    2    ...  n-1
	 * +---------------------> x
	 */

	// 일단 모든 element를 (0.0f, 0.0f, 0.0f, 1.0f)로 init.
	elements_.resize(gridSize * (gridSize + 2));

	// 시뮬레이션 계산 시 양쪽 끝에 있는 두 줄은 고정되어 있어야 한다.
	// 계산 시 고정되어야 하는 element들은 w값에 0을 넣어 마킹해둔다.
	for (int i = 0; i < gridSize; i++)
	{
		elements_[i].w = 0.0f;
		elements_[gridSize * (gridSize + 1) + i].w = 0.0f;
	}

	float elementLength = gridLength / (gridSize - 1);
	// Rendering에 참여하는 element들은 x와 y값이 있어야 한다.
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			int index = gridSize * (i + 1) + j;
			elements_[index].x = j * elementLength;
			elements_[index].y = i * elementLength;
		}
	}

	// Rendering을 위한 buffer pointer는 simulation 계산을 위한 buffer pointer와 위치가 다름.
	renderBufferPointer_ = elements_.data();
	renderBufferPointer_ += gridSize;
}

GridBuffer::~GridBuffer()
{
}

void* GridBuffer::GetBufferPointer()
{
	return elements_.data();
}

void* GridBuffer::GetRenderBufferPointer()
{
	return renderBufferPointer_;
}

Grid::Grid(int gridSize, float gridLength) :
	gridSize_(gridSize),
	gridLength_(gridLength),
	frontBufferIndex_(0)
{
	for (int i = 0; i < bufferCount_; i ++)
		buffers_.push_back(new GridBuffer(gridSize_, gridLength_));
}

Grid::~Grid()
{
	for (auto buffer : buffers_)
		delete buffer;

	buffers_.clear();
}

int Grid::GetGridSize()
{
	return gridSize_;
}

float Grid::GetGridLength()
{
	return gridLength_;
}

int Grid::GetBufferCount()
{
	return bufferCount_;
}

GridBuffer* Grid::GetBufferAt(int index)
{
	return buffers_[index];
}

int Grid::GetFrontBufferIndex()
{
	return frontBufferIndex_;
}