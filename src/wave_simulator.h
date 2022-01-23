#pragma once

class Grid;

class WaveSimulator
{
public:
	WaveSimulator(Grid* grid);
	~WaveSimulator();

public:
	void Step();

private:
	Grid* grid_;
};