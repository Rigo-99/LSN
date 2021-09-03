#include <iostream>
#ifndef __ProgressBar__
#define __ProgressBar__

class ProgressBar {

private:
	int max,width,actual,a_per,a_pos;

protected:

public:
	// constructors
	ProgressBar(int massimo, int larghezza);
	// destructor
	~ProgressBar();
	// methods
	void Punto();
	void Mostra();
	void Reset();
};

#endif // __ProgressBar__

