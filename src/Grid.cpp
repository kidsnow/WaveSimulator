#include "grid.h"


GridBuffer::GridBuffer(int gridSize, float gridLength) :
	renderBufferPointer_(nullptr)
{
	/*
	 * gridSize * gridSize ũ��� �������� grid�� �������ٵ�
	 * wave�� ������� �ʰ� �ϱ� ���ؼ� ���� ���� �����ؾ� �ؼ�
	 * ���� ���� �� �پ� grid�� �߰��� �������־�� �Ѵ�.
	 * ���� ���� grid�� ��꿡�� �����ϰ� rendering������ �ʴ´�.
	 * 
	 * xy����� �������� z���� �ùķ��̼ǿ� �����Ѵ�.
	 * �ùķ��̼� ��� �ÿ��� y���� ���ǹ���.
	 * x, y���� ���� rendering���� ���� ����.
	 * 
	 * Element ������ x�� major�� order�� �޸𸮿� ��ġ.
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

	// �ϴ� ��� element�� (0.0f, 0.0f, 0.0f, 1.0f)�� init.
	elements_.resize(gridSize * (gridSize + 2));

	// �ùķ��̼� ��� �� ���� ���� �ִ� �� ���� �����Ǿ� �־�� �Ѵ�.
	// ��� �� �����Ǿ�� �ϴ� element���� w���� 0�� �־� ��ŷ�صд�.
	for (int i = 0; i < gridSize; i++)
	{
		elements_[i].w = 0.0f;
		elements_[gridSize * (gridSize + 1) + i].w = 0.0f;
	}

	float elementLength = gridLength / (gridSize - 1);
	// Rendering�� �����ϴ� element���� x�� y���� �־�� �Ѵ�.
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			int index = gridSize * (i + 1) + j;
			elements_[index].x = j * elementLength;
			elements_[index].y = i * elementLength;
		}
	}

	// Rendering�� ���� buffer pointer�� simulation ����� ���� buffer pointer�� ��ġ�� �ٸ�.
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