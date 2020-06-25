#pragma once
#ifndef SWAP_H
#define SWAP_H

class Swap
{
public:
	Swap() {};
	~Swap() {};

	void swap(int *xp, int *yp) {
		int temp = *xp;
		*xp = *yp;
		*yp = temp;
	};
};

#endif